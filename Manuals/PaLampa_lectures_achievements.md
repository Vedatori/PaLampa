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
Napište program, který bude blikat jako železniční přejezd. Blikat budou LED 0. a 15, oba červenou barvou.


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


# Lekce 4 (potenciometer)


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

## Úkol 8 - zesilování LED (zesílení nebo zeslabení LED za pomocí otáčení potenciometru)
Napište program, který rozezní piezoakustický měnič, pokud Time-O-Mat vneseme do temnoty.

## Úkol 11 - měnění HSVs (otáčení potenciometru mění barvy RGB LED )
Napište program, který při každém stisku jednoho z tlačítek na dotykové liště rozsvítí další LED v rámci jednoho segmentu a původní LED zhasne - "posune" světlo na LED na další pozici(začne se LED s indexem 0 a vždy se zvyšuje o 1). Po dosažení poslední LED se znovu rozsvítí nultá LED a proces se opakuje. Pokud není tlačítlo stisknuto, pořád svítí stejná LED.


# Lekce 5 (světelný sensor)
Ukážeme si podmínku "if" na příkladu s LED.

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

## Úkol 10 - Světelná signaliazce tmy (pokud tma tak zvyš jas ps.světelný sensor za lampou)
Napište program, který rozezní piezoakustický měnič, pokud Time-O-Mat vneseme do temnoty.

## Úkol 11 - Noční světlo (sensor pod lampou hlídá jas aby nebyl moc silný)
Napište program, který při každém stisku jednoho z tlačítek na dotykové liště rozsvítí další LED v rámci jednoho segmentu a původní LED zhasne - "posune" světlo na LED na další pozici(začne se LED s indexem 0 a vždy se zvyšuje o 1). Po dosažení poslední LED se znovu rozsvítí nultá LED a proces se opakuje. Pokud není tlačítlo stisknuto, pořád svítí stejná LED.


# Lekce 6 (touch sensor)
Time-O-Mat začne komunikovat s počítačem pomocí sériové linky. Vyčteme okolní teplotu.

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

## Úkol 12 - Dotyk (když se dotkneš lampa blikne čímkoliv)
Přepracujte úkol 9 tak, aby Time-O-Mat přes sériovou linku přenášel číslo LED, která právě svítí.


# Lekce 7 (teploměr)
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

## Úkol 13 - Přehřívání (teploměr v horním segmentu hlídá teplotu proti přehřívání a vypne led)
Napište program, který bude blikat třetí barevnou LED červenou barvou. Doba svitu i doba zhasnutí je 300 ms.

## Úkol 14 - Teplota okolí (teploměr pod lampou hlídá teplotu okolí a v závislosti na tom mění barvy led červená přes zelenou až po modrou (zelena je ok, červená je vedro, žlutá je mid, modrá je zima(modrá je pod 25°C, zelená je 25°C až 28°C, žlutá 28°C až 30°C, červená je 30°C plus)))
Napište program, který každou vteřinu krátce rozsvítí zadní LED pásek. Doba svitu je 100 ms v každé vteřině.


# Lekce 8 (piezo)


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


# Lekce 9 (displey)
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

## Úkol 17 - TEXT (zobraz text)
Napište program, který bude blikat třetí barevnou LED červenou barvou. Doba svitu i doba zhasnutí je 300 ms.

## Úkol 18 - Tvar (zobraz čtverec)
Napište program, který každou vteřinu krátce rozsvítí zadní LED pásek. Doba svitu je 100 ms v každé vteřině.

## Úkol 19 - Obrázek (zobraz obrázek)
Napište program, který bude blikat jako železniční přejezd. Blikat budou LED 0. a 15, oba červenou barvou.
