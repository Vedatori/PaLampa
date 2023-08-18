V tomto dokumentu se nachází rozpis programovacích lekcí a zadání programovacích úkolů. 

**Programovací lekce** nejsou povinné, ale jsou velmi vhodné pro začátečníky.

**Programovací úkoly** jsou úkoly, které budete řešit samostatně. Ke každému úkolu potřebujete soubor znalostí, který je obsažen v některých z lekcí.

# Lekce 0
Zprovozníme programovací prostředí VS Code + PlatformIO tak, abyste mohli nahrát kód do PaLampy z vašeho PC.

## Úkol 0 - Demo program
Nahrát do výrobku připravený demo program z PaLampa repozitáře.

# Lekce 1
Blikneme LED světlem ve funkci `setup` a budeme jím blikat ve funci `loop`.

## Výsledný kód

```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    // id panelu, (0 = warm, 1 = cool)
    // brightness, (0-1)
    paLampa.lights.setWhite(0, 0.5);
    
    // delay(ms), 2000 ms = 5 s
    delay(2000);
    paLampa.lights.setWhite(0, 0.0);
}

void loop() {
    paLampa.lights.setWhite(1, 0.5);
    delay(500);
    paLampa.lights.setWhite(1, 0.0);
    delay(500);
}
```

## Úkol 1 - Rozsviť teplé ledky
Napište program, který každou vteřinu krátce rozsvítí teplé bíle ledky. Doba zobrazení je 250 ms v každé vteřině.

## Úkol 2 - Rozsviť studené a teplé ledky střídavě
Napište program, který bude blikat jako železniční přejezd. Blikat budou střídavě studené ledky, a teplé ledky v 500 ms intervalu.


# Lekce 2
Rozsviť barevné LED na horním a zadním segmentu.

## Výsledný kód
```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    // panel, (0 = top, 1 = back)
    // id, (0-15 top, 0-6 back)
    // color, (red, blue ...)
    paLampa.lights.setColor(0, 0, red);
    paLampa.lights.setColor(1, 0, blue);
}

void loop() {
    paLampa.lights.setColorPanel(0, red);
    delay(500);
    paLampa.lights.setColorPanel(0, black);
    delay(500);
}
```

## Úkol 3 - Blikání LED
Napište program, který bude blikat třetí barevnou LED ze zadního segmentu červenou barvou. Doba svitu i doba zhasnutí je 300 ms.

## Úkol 4 - Železniční přejezd na horním segmentu
Napište program, který bude blikat jako železniční přejezd. Blikat budou LED 0 a 15 na horním panelu, oba červenou barvou.

## Úkol 5 - Noční jezdec
Napište program, který bude postupně rozvěcovat LED na zadním segmentu červenou barvou tak, že vždy svítí jen jedna LED a každá svítí 333 ms.

# Lekce 3
Přečteme stav tlačítka, ukážeme si binární proměnnou a v závislosti na ní rozesvítíme LED.

## Výsledný kód

```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    // čísla tlačítek jsou zleva 0, 1, 2
    if(paLampa.buttonRead(0)) {
        paLampa.lights.setWhite(0, 0.1);
    }
    else {
        paLampa.lights.setWhite(0, 0);
    }
}
```

## Úkol 6 - Manuální blikání LED 
Napište program, který bliká libovolnou LED pouze při stisknutém pravém tlačítku. Doba svícení je 200 ms. Doba zhasnutí je 200 ms.

## Úkol 7 - Stabilní stav LED
Napište program, který bude stiskem tlačítka přepínat svícení dvou různých LED. Vždy bude svítit pouze jedena LED, stiskem tlačítka se jedna LED vypne a zapne se ta druhá. Dalším stiskem tlačítka se znovu zapne pouze ta původní LED a proces lze opakovat.

# Lekce 4
Přečteme stav potenciometru a zapíšeme ho do červeného kanálu na horním rgb panelu.

Vlastní rgb barvy si můžeme vytvořít pomocí ColorRGB{R, G, B}. Hodnoty R, G a B zaměňte za hodnoty 0-1 které chcete nastavit.

```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    float potVal = paLampa.potentiometerRead();
    ColorRGB color = {potVal, 0, 0};
    paLampa.lights.setColorPanel(0, color);
    delay(100);
}
```

## Úkol 8 - Zesilování LED
Napište program, který bude regulovat jas teplé LED pomocí potenciometru.

## Úkol 9 - Barevný formát HSV
Napište program, který bude při otočení potenciometru postupně měnit barvy barevné LED.


# Lekce 5
Ukážeme si fotorezistor a hodnotu jeho výstupu si zobrazíme na LED.

```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    float illumination = paLampa.photoresistor.get(1);
    paLampa.light.setWhite(0, illumination / 2);
}
```

## Úkol 10 - Světelná signaliazce tmy
Napište program, který zvýší jas pokud vstoupíme s PaLampou do tmy. Doporučuji dělit hodnotu z fotorezistoru číslem 3.

## Úkol 11 - Průměrné světlo
Napište program, který upravuje svítivost LED podle okolního osvětlení. Čím temější prostředí tím víc bude lampa svítit, a čím světlejší tím bude lampa méně svítit. Doporučuji použít zadní fotorezistor.


# Lekce 6
Ukážeme si ja zjistit hodnotu teploměru a jak se pracuje se sériovou linkou

## Výsledný kód

```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    float topTemp = paLampa.thermometer.get(1 /*0 = bottom, 1 = top*/);
    float bottomTemp = paLampa.thermometer.get(0);
    Serial.print("top = ");
    Serial.print(topTemp);
    Serial.print("°C, bottom = ");
    Serial.print(bottomTemp);
    Serial.println("°C");
    delay(500);
}

```

## Úkol 13 - Přehřívání 
Napište program, který bude hlídat teplotu horního segmentu za pomoci teploměru a když teplota přesáhne 30°C tak vypne LED světla.

## Úkol 14 - Teplota okolí 
Napište program, který bude hlídat teplotu zadního teploměru a podle ní bude měnit barvu RGB podle zadání. Modrá je pod 25°C, zelená je 25°C až 28°C, žlutá 28°C až 30°C, červená je 30°C plus.

# Lekce 7
PaLampa ještě nemá hotovou funkci na kapacitní tlačítka = tato lekce nelze udělat.

Ukážeme si jak funguje dotykové tlačítko a funkce random();

```cpp
#include "PaLampa/PaLampa.h"

void setup()
{
    paLampa.begin();
}

void loop()
{
    if(paLampa.touch.getButton(/*id, (0 = upper, 1 = secret)*/)){
        //nastavíme celý led pásek na černou
        paLampa.lights.setColorPanel(1, black);
        //nastavíme náhodný pixel na červenou
        paLampa.lights.setColor(1, random(7), red);
        delay(500);
    }
}
```

## Úkol 12 - Dotyk
Napiš program, který zapne a vypne jakoukoliv sadu LED pomocí horního dotykového tlačítka a pomocí vašeho tajného tlačítka změní barvu na náhodnou barvu pomocí funkce random.

# Lekce 8 
Ukážeme si jak rozeznít piezo.

## Výsledný kód

```cpp
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    paLampa.piezo.begin(3, 13);
}

void loop() {
    if(paLampa.buttonRead(0)) {
        paLampa.piezo.tone(100);
    }
    else {
        paLampa.piezo.stop();
    }
    delay(20);
}
```

## Úkol 15 - Dlouhé pííp
Napište program, který po stisknutí horního kapacitního tlačítka rozezní piezo tónem komorní a (a', A4). Zvuk je vypnut až po stisknutí tajného kapacitního tlačítka.

## Úkol 16 - Základní melodie
Napište program, který na piezu přehraje krátkou melodii po stisknutí libovolného tlačítka.

# Lekce 9 
Ukážeme si jak ovládat obrazovku.

PaLampa ještě nemá hotové funkce na displej = tato lekce nelze udělat.


## Výsledný kód

```cpp
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    ToMat.display.setLED(0, 5, blue);
    delay(500);

    ToMat.display.setLED(0, 5, black);
    delay(500);    
}
```

## Úkol 17 - TEXT 
Zobrazte na displeji libovolný krátký text.

## Úkol 18 - Tvar 
Zobrazte na displeji čtverec.

## Úkol 19 - Obrázek 
Zobrazte na displeji obrázek libovolného výběru.
