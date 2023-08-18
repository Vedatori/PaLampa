#include "WiFiCaptain.h"

#include <WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include "Preferences.h"
#include "WebSocketsServer.h"   //https://github.com/Links2004/arduinoWebSockets
#include "SPIFFS.h"

WebSocketsServer webSocket = WebSocketsServer(1337);

Preferences wifiPreferences;

WebServer webserver(80);

credentials apCredentials;
credentials stationCredentials;

// DNS server
uint8_t DNS_PORT = 53;
DNSServer dnsServer;

bool softApEnabled = 0;
bool lastConnectionType = 1; // 1 - softAP, 0 - external wifi

char commandBuffer[128];
char sendCommandBuffer[128];
const uint8_t extWiFiConnectTimeout = 50;   //*100 ms

bool clientConnectedCaptain[3] = {false, false, false};
uint8_t clientNumCaptain = 0;

void handleRoot() {
    File f = SPIFFS.open("/webApp.html", "r");
    webserver.streamFile(f, "text/html");
    f.close();

    lastConnectionType = (webserver.client().localIP() == WiFi.softAPIP());
}
void handleStatus() {
    File f = SPIFFS.open("/status.html", "r");
    webserver.streamFile(f, "text/html");
    f.close();

    lastConnectionType = (webserver.client().localIP() == WiFi.softAPIP());
}
void handleStyle() {
    File f = SPIFFS.open("/style.css", "r");
    webserver.streamFile(f, "text/css");
    f.close();
}

void handleRedirectRoot() {
    redirect("/");
}
void redirect(String path) {
    webserver.sendHeader("Location", path);
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
}
void handleSoftApEnable() {
    softApEnable();
    redirect("wifi");
}

void handleWifi() {
    lastConnectionType = webserver.client().localIP() == WiFi.softAPIP();
    webserver.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    webserver.sendHeader("Pragma", "no-cache");
    webserver.sendHeader("Expires", "-1");

    String Page;
    Page += F(
        "<!DOCTYPE html><html lang='en'><head>"
        "<meta name='theme-color' content='#404040' />"
        "<meta name='viewport' content='width=device-width'>"
        "<title>Time-O-Mat</title>"
        "<link rel='stylesheet' type='text/css' href='style.css'>"
        "<style>.textDiv {margin : 3vw;}</style>"
        "</head><body><div class='textDiv'>"
        "<h1>WiFi setup</h1>");
    if(lastConnectionType) {
        Page += String(F("<p>Current connection: soft AP ")) + apCredentials.ssid + F("</p>");
    } else {
        Page += String(F("<p>Current connection: external WiFi ")) + stationCredentials.ssid + F("</p>");
    }
    Page +=
        String(F(
        "<p><a href='/'><input type = 'button' value = 'Remote Control page'/></a></p>"
        "<table><tr><th align='left'>SoftAP configuration</th></tr>"
        "<tr><td>SSID: ")) +
        String(apCredentials.ssid) +
        F("</td></tr>"
        "<tr><td>IP address: ") +
        WiFi.softAPIP().toString() +
        F("</td></tr><tr><td>State: ") +
        String(softApEnabled ? "enabled" : "disabled") +
        F("</td></tr></table>") +
        String(softApEnabled ? "" : "<a href='/softApEnable'><input type = 'button' value = 'Enable SoftAP'/></a><br>") +
        F("\r\n<br /><table><tr><th align='left'>External WiFi configuration</th></tr>"
        "<tr><td>SSID: ") +
        String(stationCredentials.ssid) +
        F("</td></tr>"
        "<tr><td>IP address: ") +
        WiFi.localIP().toString() +
        F("</td></tr><tr><td>State: ") +
        String((WiFi.status() == WL_CONNECTED) ? "connected" : "unconnected") +
        F("</td></tr></table>"
        "<br>"
        "<form method='POST' action='wifisave'><b>Connect to external WiFi:</b><br>"
        "<input type='text' placeholder='network' name='n'/>"
        "<br /><input type='password' placeholder='password' name='p'/>"
        "<br /><input type='submit' value='Connect'/></form><br>"
        "<table><tr><th align='left'>Available WiFi networks (signal power [dBm])</th></tr>");
    int n = WiFi.scanNetworks();
    if (n > 0) {
        for (int i = 0; i < n; i++) {
        Page += String(F("\r\n<tr><td>SSID: ")) + WiFi.SSID(i) + ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? F(" ") : F(" *")) + F(" (") + WiFi.RSSI(i) + F(")</td></tr>");
        }
    } else {
        Page += F("<tr><td>No WiFi found</td></tr>");
    }
    Page += F(
        "</table>"
        "</div></body></html>");
    webserver.send(200, "text/html", Page);
    webserver.client().stop(); // Stop is needed because we sent no content length
}

void handleWifiSave() {
    credentials aCredentials;
    Serial.println("wifi save");
    webserver.arg("n").toCharArray(aCredentials.ssid, sizeof(aCredentials.ssid) - 1);
    webserver.arg("p").toCharArray(aCredentials.password, sizeof(aCredentials.password) - 1);
    stationCredentials = aCredentials;
    webserver.sendHeader("Location", "wifi", true);
    webserver.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    webserver.sendHeader("Pragma", "no-cache");
    webserver.sendHeader("Expires", "-1");
    webserver.send(302, "text/plain", "");    // Empty content inhibits Content-length header so we have to close the socket ourselves.
    webserver.client().stop(); // Stop is needed because we sent no content length
    saveCredentials(aCredentials);
    connectWifiAsClient(aCredentials);
}

void handleOtaUpload() {
    if (SPIFFS.exists("/otaUpdate.html")) {
        File f = SPIFFS.open("/otaUpdate.html", "r");
        webserver.streamFile(f, "text/html");
        f.close();
    } else {
        // Create raw string with html
        String webPage = R"(
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport"
            content="width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0">
        <meta name="theme-color" content="#404040" />
        <title>OTA Updater</title>
        <link rel="stylesheet" type="text/css" href="style.css">
    </head>
    <body>
        <div class="wrapper">
            <p>
                OTA (Over the air) update allows you to update the ESP32 firmware and file system without having to connect it to your computer via USB.
                If you have trouble with uploading code from your PC, you might have to fix it trough the OTA update.
                <br/>
                To update the ESP32, you need to upload a <b>firmware.bin</b> file. You can download the latest firmware from the <a href="https://github.com/Vedatori/PaLampa/" target="_blank"></a> Releases page.
                <br/>
                Than continue with updating <b>spiffs.bin</b> file (file system). You can download the latest file system also from the GitHub repository.
            </p>

            <form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
                <input type='file' name='update'>
                <input type='submit' value='Update'>
            </form>
            <div id='prg'>progress: 0%</div>

            <p><a href='/'><input type = 'button' value = 'Back to home page'/></a></p>
        </div>
        <script>
        document.querySelector('form').addEventListener('submit', function(e) {
        e.preventDefault();

        var form = document.getElementById('upload_form');
        var data = new FormData(form);

        var xhr = new XMLHttpRequest();

        xhr.open('POST', '/update', true);
        xhr.onload = function() {
            if (xhr.status >= 200 && xhr.status < 400) {
                console.log('success!');
                document.getElementById('prg').textContent = 'progress: done! (ESP32 has been successfully updated and will be rebooted)';
            } else {
                // Handle error
                console.error('Error: ' + xhr.status);
                document.getElementById('prg').textContent = 'progress: error!: ' + xhr.status;
            }
        };

        xhr.upload.addEventListener('progress', function(evt) {
            if (evt.lengthComputable) {
                var per = evt.loaded / evt.total;
                document.getElementById('prg').textContent = 'progress: ' + Math.round(per * 100) + '%';
            }
        });

        xhr.send(data);
    });
</script>
    </body>
</html>
)";
        webserver.sendHeader("Connection", "close");
        webserver.send(200, "text/html", webPage);
    }
}

void handleOtaUploadProgress() {
    webserver.sendHeader("Connection", "close");
    webserver.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    printf("OTA Update: %s\n", Update.hasError() ? "FAIL" : "OK");
    delay(1000);
    ESP.restart();
}


void handleOtaUpdate() {
    HTTPUpload& upload = webserver.upload();

    if (upload.status == UPLOAD_FILE_START) {
        printf("Update: %s\n", upload.filename.c_str());

        // Check if the uploaded file is for SPIFFS or firmware based on the file name or path.
        if (upload.filename == "spiffs.bin") {
            if (!SPIFFS.begin(true)) {
                Serial.println("An Error has occurred while mounting SPIFFS");
                return;
            }

            if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_SPIFFS)) {
                Update.printError(Serial);
            }
        } else {
            if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH)) { //start with max available size
                Update.printError(Serial);
            }
        }

    } else if (upload.status == UPLOAD_FILE_WRITE) {
        /* flashing firmware to ESP or SPIFFS */
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
            Update.printError(Serial);
        }
    } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
            if (upload.filename == "spiffs.bin") {
                printf("SPIFFS Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
                printf("OTA Update Success: %u\nRebooting...\n", upload.totalSize);
            }
        } else {
            Update.printError(Serial);
        }
    }
}





void handleNotFound() {
    File f = SPIFFS.open("/notFound.html", "r");
    webserver.streamFile(f, "text/html");
    f.close();

    lastConnectionType = (webserver.client().localIP() == WiFi.softAPIP());
}

void softApEnable() {
    if(strlen(apCredentials.password) < 8) {
        WiFi.softAP(apCredentials.ssid, NULL);  // Set no password
    }
    else {
        WiFi.softAP(apCredentials.ssid, apCredentials.password);    // Set password
    }
    WiFi.softAPsetHostname(apCredentials.ssid);

    // Setup the DNS server redirecting all the domains to the apIP
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
    softApEnabled = 1;
    printf("enabled softAP\n");
}

void softApDisable() {
    if(softApEnabled) {
        WiFi.softAPdisconnect(1);
        softApEnabled = 0;
        printf("disabled softAP\n");
    }
}

void connectWifiAsClient(const credentials aCredentials) {
    WiFi.disconnect();
    WiFi.begin(aCredentials.ssid, aCredentials.password);
    for(uint8_t i = 0; i < extWiFiConnectTimeout; ++i) {
        delay(100);
        if(WiFi.status() == WL_CONNECTED) {
            break;
        }
        if(i == (extWiFiConnectTimeout - 1)) {
            WiFi.disconnect();
            Serial.print("Failed connecting to ");
            Serial.println(stationCredentials.ssid);
            return;
        }
    }
    WiFi.setHostname(apCredentials.ssid);

    Serial.print("Connected to remote WiFi: ");
    Serial.print(stationCredentials.ssid);
    Serial.print(" with IP address: ");
    Serial.println(WiFi.localIP());   // You can get IP address assigned to ESP
}

void loadCredentials() {
    wifiPreferences.begin("wifiCapt", false);
    wifiPreferences.getBytes("credentials", &stationCredentials, sizeof(stationCredentials));
    wifiPreferences.end();
    Serial.println("Recovered credentials:");
    Serial.println(stationCredentials.ssid);
    Serial.println(strlen(stationCredentials.password) > 0 ? "********" : "<no password>");
}

void saveCredentials(const credentials aCredentials) {
    wifiPreferences.begin("wifiCapt", false);
    wifiPreferences.putBytes("credentials", &aCredentials, sizeof(aCredentials));
    wifiPreferences.end();
}

void handleClients(void * param) {
    for(;;) {
        webserver.handleClient();
        dnsServer.processNextRequest();
        webSocket.loop();
        if((WiFi.status() != WL_CONNECTED) && !softApEnabled) {
            softApEnable();
        }
        vTaskDelay(20);
    }
}


void wifiCaptInit() {
    if(strlen(apCredentials.ssid) == 0) {
        sprintf(apCredentials.ssid, "PaLampa");
    }
    softApEnable();

    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS Mount failed");
    }

    //webserver.serveStatic("/", SPIFFS, "/webApp.html");     // quicker than specific handleRoot() function initiating SPIFFS internally
    //webserver.serveStatic("/generate_204", SPIFFS, "/webApp.html");  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
    //webserver.serveStatic("/fwlink", SPIFFS, "/webApp.html");  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
    webserver.on("/", handleRoot);
    webserver.on("/style.css", handleStyle);
    webserver.on("/generate_204", handleRedirectRoot);    //Android captive portal.
    webserver.on("/fwlink", handleRedirectRoot);    //Microsoft captive portal.
    webserver.on("/wifi", handleWifi);
    webserver.on("/wifisave", handleWifiSave);
    webserver.on("/ota", handleOtaUpload); // ota update form

    webserver.on("/update", HTTP_POST, handleOtaUploadProgress, handleOtaUpdate);
    webserver.on("/softApEnable", handleSoftApEnable);
    webserver.on("/status", handleStatus);
    webserver.onNotFound(handleNotFound);

    webserver.begin();

    //xTaskCreate(handleClients, "handleClients", 1024 * 4 , (void*) 0, 1, NULL);
    xTaskCreatePinnedToCore(handleClients, "handleClients", 10000 , (void*) 0, 1, NULL, 1);

    loadCredentials();

    if(strlen(stationCredentials.ssid) > 0) {
        connectWifiAsClient(stationCredentials);
    }

    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
}

bool getLastConnectionType() {
    return lastConnectionType;
}

void setApCredentials(String ssid, String password) {
    sprintf(apCredentials.ssid, ssid.c_str());
    sprintf(apCredentials.password, password.c_str());
}

String ipToDisp() {
    if(WiFi.status() == WL_CONNECTED) {
        return String("EX" + WiFi.localIP().toString());
    }
    else {
        return String("AP" + WiFi.softAPIP().toString());
    }

}

// Callback: receiving any WebSocket message
void onWebSocketEvent(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length) {
    clientNumCaptain = client_num;
    // Figure out the type of WebSocket event
    switch(type) {

        // Client has disconnected
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", client_num);
            if(client_num < 3) {
                clientConnectedCaptain[client_num] = false;
            }
            break;

        // New client has connected
        case WStype_CONNECTED:
        {
            IPAddress ip = webSocket.remoteIP(client_num);
            Serial.printf("[%u] Connection from ", client_num);
            Serial.println(ip.toString());

            if(!getLastConnectionType()) {
                softApDisable();
            }
            if(client_num < 3) {
                clientConnectedCaptain[client_num] = true;
            }
        }
        break;

        // Handle text messages from client
        case WStype_TEXT:{
            const char delimiter[2] = "|";
            char *token;
            token = strtok((char *)payload, delimiter);
            char statusMsg[] = "statusRequest";
            char commandMsg[] = "command";
            if(strcmp(token, statusMsg) == 0) {
                ;//TrackJet.sendStatus();
            }
            else if(strcmp(token, commandMsg) == 0) {
                token = strtok(NULL, delimiter);
                if(token != NULL) {
                    sprintf(commandBuffer, token);
                    printf("Received command: %s\n", token);
                }
            }
        }
            break;

        // For everything else: do nothing
        /*case WStype_BIN:
        case WStype_ERROR:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:*/
        default:
            break;
    }
}

char * commandGetCaptain() {
    return commandBuffer;
}

void commandClearCaptain() {
    sprintf(commandBuffer, " ");
}

void commandSendCaptain(String msgType, String payload) {
    if(clientConnectedCaptain[clientNumCaptain] == false) {
        printf("Error sending command, client disconnected\n");
        return;
    }
    if((msgType.length() + payload.length()) >= (sizeof(sendCommandBuffer)/sizeof(*sendCommandBuffer) + 1)) {
        printf("Error sending command, command too long\n");
        return;
    }
    sprintf(sendCommandBuffer, "%s,%s", msgType.c_str(), payload.c_str());
    //printf("Sendig command: %s\n", sendCommandBuffer);
    webSocket.sendTXT(clientNumCaptain, sendCommandBuffer, strlen(sendCommandBuffer));
}
