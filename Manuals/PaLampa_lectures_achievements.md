V tomto dokumentu se nachází rozpis programovacích lekcí a zadání programovacích úkolů. 

**Programovací lekce** nejsou povinné, ale jsou velmi vhodné pro začátečníky. Zájem o lekci budete vyjadřovat tak, že na svůj řádek v tabulce připíšete na konec číslo lekce, o kterou máte zájem. Jakmile jste lekci absolvovali, číslo zakroužkujete tak, aby bylo jasné, které lekce už jste absolvovali. Účast na lekci je ohodnocena 1 Chotěcoinem.

**Programovací úkoly** jsou úkoly, které budete řešit samostatně. Ke každému úkolu potřebujete soubor znalostí, který je obsažen v některých z lekcí. Úkoly je však možné řešit i jen pomocí programovacího manuálu (pro pokročilé). Splnění úkolu bude kontrolovat vedoucí a odmění ho 2 - 4 Chotěcoiny. Po splnění úkolu si v tabulce na vašem řádku zaznačte křížkem jeho splnění. 

# Lekce 0
Zprovozníme programovací prostředí VS Code + PlatformIO tak, abyste mohli nahrát kód do PaLampy z vašeho PC.


# Lekce 1
Rozsviť teplé ledky na 10%, po 5 sekudndách rozsviť i studenné ledky

## Výsledný kód

```
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    // id panelu, (0 = warm, 1 = cool)
    // brightness, (0-1)
    paLampa.lights.setWhite(0, 0.1);
    
    // delay(ms), 5000 ms = 5 s
    delay(5000);
    paLampa.lights.setWhite(1, 0.1);
}

void loop() {
}
```

## Úkol 1 - Rozsviť teplé ledky
Napište program, který každou vteřinu krátce rozsvítí teplé bíle ledky. Doba zobrazení je 250 ms v každé vteřině.

## Úkol 2 - Rozsviť studené a teplé ledky střídavě
Napište program, který bude blikat jako železniční přejezd. Blikat budou střídavě studené ledky, a teplé ledky v 500 ms intervalu.


# Lekce 2
Rozsviť barevné LED na horním segmentu nebo LED pásku.

## Výsledný kód
```
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    // panel, (0 = top, 1 = strip)
    // id, (0-15 top, 0-6 strip)
    // color, (red, blue ...)
    paLampa.lights.setColor(0,1,red);
    paLampa.lights.setColor(1,0,blue);
}

void loop() {
}
```

## Úkol 3 - Blikání LED
Napište program, který bude blikat třetí barevnou LED červenou barvou. Doba svitu i doba zhasnutí je 300 ms.

## Úkol 4 - Záblesky LED pásku
Napište program, který každou vteřinu krátce rozsvítí zadní LED pásek. Doba svitu je 100 ms v každé vteřině.

## Úkol 5 - Železniční přejezd na horním segment
Napište program, který bude blikat jako železniční přejezd. Blikat budou LED 0 a 15 na horním panelu, oba červenou barvou.


# Lekce 3
Přečteme stav tlačítka, ukážeme si binární proměnnou a v závislosti na ní rozesvítíme LED.

## Výsledný kód

```
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    // id, (0, 1, 2)
    if(paLampa.buttonRead(0)){
        paLampa.lights.setWhite(0, 0.1);
    }
    else{
        paLampa.lights.setWhite(0, 0);
    }
}
```

## Úkol 6 - Manuální blikání LED 
Napište program, který bliká libovolnou LED pouze při stisknutém pravého tlačítka. Doba svícení je 200 ms. Doba zhasnutí je 200 ms.

## Úkol 7 - Stabilní stav LED
Napište program, který bude stiskem tlačítka přepínat svícení dvou různých LED. Vždy bude svítit pouze jedena LED, stiskem tlačítka se jedna LED vypne a zapne se ta druhá. Dalším stiskem tlačítka se znovu zapne pouze ta původní LED a proces lze opakovat.


# Lekce 4
Přečteme stav potenciometru a zapíšeme ho do červeného kanálu na horním rgb panelu.

Vlastní rgb barvy si můžeme vytvořít pomocí ColorRGB{R, G, B} (hodnoty R, B a B zaměňte za hodnoty 0-1 které chcete nastavit)

```
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    paLampa.lights.setColorPanel(0, ColorRGB{paLampa.potentiometerRead(), 0, 0});
    delay(100);
}
```

## Úkol 8 - zesilování LED
Napište program, který bude zesilovat/zeslabovat studené nebo teplé LED pomocí potenciometru

## Úkol 9 - měnění HSVs
Napište program, který bude při otočení potenciometru postupně mění barvy rgb LED


# Lekce 5
Ukážeme si fotorezistor a porovnání na příkladu s LED.

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    ToMat.display.setFront(black);
    if(ToMat.touchBar.getPressed(2)) {
        ToMat.display.setLED(1, 0, green);
    }
    else if(ToMat.touchBar.getPressed(3)) {
        ToMat.display.setLED(1, 2, green);
    }
    else {
        ToMat.display.setLED(1, 1, red);
    }
    delay(20);
}
```

## Úkol 10 - Světelná signaliazce tmy
Napište program, který zvíší jas pokoud vstoupíme s PaLampou do tmy. (Doporučuji dělit hodnotu z fotorezistoru číslem 3)

## Úkol 11 - Noční světlo
Napište program, který upravuje svítivost LED podle okolního osvětlení. Čím temější prostředí tím víc bude lampa svítit.

# Lekce 6 
Ukážeme si jak funguje dotykové tlačítko a funkce random();

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

int teplota;

void loop() {
    teplota = ToMat.getTemperature();
    printf("%d\n", teplota);
    delay(200);
}
```

## Úkol 12 - Dotyk
Napiš program, který zapne a vypne jakoukoliv sadu LED pomocí horního touch sensoru a pomocí vašeho "secret" tlačítka změní barvu na nějakou náhodnou barvu pomocí funkce random.


# Lekce 7 
Ukážeme si ja zjistit hodnotu teploměru.

## Výsledný kód

```
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

## Úkol 13 - Přehřívání 
Napište program, který bude hlídat teplotu horního segmentu za pomoci teploměru a když teplota přesáhne 50°C tak vypne LED světla.

## Úkol 14 - Teplota okolí 
Napište program, který bude hlídat teplotu zadního teploměru a podle ní bude měnit barvu RGB podle zadání. Modrá je pod 25°C, zelená je 25°C až 28°C, žlutá 28°C až 30°C, červená je 30°C plus.


# Lekce 8 
Ukážeme si jak rozeznít piezo.

## Výsledný kód

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

int x;

void loop() {
    ToMat.display.setFront(black);
    x = (ToMat.illumination.getRaw(0)/205);
    ToMat.display.setLED(0, x, blue);
    printf("%d \n ", x);
    delay(20);
}
```

## Úkol 15 - dlouhé pííp
Napište program, který po stisknutí prostředního tlačítka zapne piezo

## Úkol 16 - základní melodie
Napište program, který na piezu přehraje krátkou melodii po stisknutí tlačítka.


# Lekce 9 
Rozblikáme barevné LED na horním segmentu nebo LED pásku.

## Výsledný kód

```
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
Zobrazte na displeji libovolný krátký text text.

## Úkol 18 - Tvar 
Zobrazte na displeji čtverec.

## Úkol 19 - Obrázek 
Zobrazte na displeji obrázek libovolného výběru.
