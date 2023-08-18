#include "Oled_module.h"

void Oled_module::widgetMapClear() {
    for(int i = 0; i < sizeof(widgetMap)/sizeof(widgetMap[0]); i++){
        for(int o = 0; o < sizeof(widgetMap[0])/sizeof(widgetMap[0][0]); o++){
            widgetMap[i][o] = false;
        }
    }
}
//Fakt hnusnej kód ahead
bool Oled_module::widgetMapFindSpot(int& column, int& row, bool reserve){
    //printf("widgetMapFindSpot: c%d r%d %s\n", column, row, (reserve)? "reserve": "");
    if(column < 1 || column > 2) column = 2;
    if(row < 1 || row > 8) row = 4;
    if(column == 1) {
        int newRow1 = 1;
        int newRow2 = 1;
        int rowCounter1 = 0;
        int rowCounter2 = 0;
        for(int o = 0; o < sizeof(widgetMap[0])/sizeof(widgetMap[0][0]); o++){
                if(!widgetMap[0][o]) {
                    if(rowCounter1==0) newRow1 = o+1;
                    rowCounter1++;
                    if(rowCounter1==row){
                        if(reserve){
                            //reserve
                            for(int o = newRow1-1; o < newRow1-1+row; o++){
                                widgetMap[0][o] = true;
                            }
                        }    
                    
                        //return data
                        column = 0+1;
                        row = newRow1;
                        return true;
                    }
                }else{
                    rowCounter1 = 0;
                }

                if(!widgetMap[1][o]) {
                    if(rowCounter2==0) newRow2 = o+1;
                    rowCounter2++;
                    if(rowCounter2==row){
                        if(reserve){
                            //reserve
                            for(int o = newRow2-1; o < newRow2-1+row; o++){
                                widgetMap[1][o] = true;
                            }
                        }    
                    
                        //return data
                        column = 1+1;
                        row = newRow2;
                        return true;
                    }
                }else{
                    rowCounter2 = 0;
                }
            




        }
        return false;
    }
    //else: column == 2
    int newRow = 1;
    int rowCounter = 0;
    for(int o = 0; o < sizeof(widgetMap[0])/sizeof(widgetMap[0][0]); o++){
        if(!widgetMap[0][o] && !widgetMap[1][o]) {
            //printf("row %d OK\n", o);
            if(rowCounter == 0) newRow = o+1;
            rowCounter++;
            if(rowCounter == row){
                if(reserve) {
                    for(int o = newRow-1; o < newRow-1+row; o++){
                        widgetMap[0][o] = true;
                        widgetMap[1][o] = true;
                    }
                }

                //return data
                column = 1;
                row = newRow;
                return true;
            }
        }else{
            rowCounter = 0;
        }
    }
    return false;
}

void Oled_module::widgetMapPrint() {
    Serial.println("=====");
    for(int i = 0; i < sizeof(widgetMap[0])/sizeof(widgetMap[0][0]); i++) {
        for(int o = 0; o < sizeof(widgetMap)/sizeof(widgetMap[0]); o++){
            Serial.print((widgetMap[o][i])? '#' : ' ');
        }
        Serial.print("\n");
    }
    Serial.println("=====");
}

void Oled_module::widgetMapReserve(int c0, int c1, int r0, int r1) {
    for(int i = c0; i <= c1; i++){
        for(int o = r0; o <= r1; o++){
            widgetMap[i][o] = true;
        }
    }
}

Oled_module::Oled_module(int SCREEN_WIDTH, int SCREEN_HEIGHT, int ADDRESS) {
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    SCREEN_ADDRESS = ADDRESS;
}

void Oled_module::begin() {
    display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        printf("Oled SSD1306 begin failed");
        abort();
        return;
    }
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.display();
    widgetMapClear();
}

void Oled_module::sendClear(bool autoSendTask) {
    if(autoSendTask && (!autoSend || !dataChanged)) return;
    dataChanged = false;
    display.display();
    display.clearDisplay();
    widgetMapClear();
}

void Oled_module::drawLogo() {
    display.clearDisplay();
    display.drawBitmap(0, 0, oled_module::vedatoriBitmap128x64, 128, 64, WHITE);    
}

void Oled_module::widgetText(String text ,int16_t size, int column, int row) {
    if(size < 1 || size > 3) size = 1;

    int rowSize = size;
    int columnSize = 0;

    columnSize = (size > 2)? 2 : 1;

    if(column == -1 || row == -1){
        column = columnSize;
        row = rowSize;
        if(!widgetMapFindSpot(column, row)){
            printf("widgetText c%d r%d s%d NO SPACE\n", column, row, size);
        }
    }

    widgetMapReserve(column-1, column-2+columnSize, row-1, row-2+rowSize);
    int maxTextW = columnSize*64/(6*size);
    if(text.length() > maxTextW) text = text.substring(0, maxTextW);
    int textW = size*(text.length())*5;
    int spacing = (columnSize*64 - textW)/2;
    display.setCursor((column-1)*64 + spacing, (row-1)*8);
    display.setTextColor(WHITE);
    display.setTextSize(size);
    display.print(text);
    dataChanged = true;

}