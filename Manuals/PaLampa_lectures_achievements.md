V tomto dokumentu se nachází rozpis programovacích lekcí a zadání programovacích úkolů. 

**Programovací lekce** nejsou povinné, ale jsou velmi vhodné pro začátečníky. Zájem o lekci budete vyjadřovat tak, že na svůj řádek v tabulce připíšete na konec číslo lekce, o kterou máte zájem. Jakmile jste lekci absolvovali, číslo zakroužkujete tak, aby bylo jasné, které lekce už jste absolvovali. Účast na lekci je ohodnocena 1 Chotěcoinem.

**Programovací úkoly** jsou úkoly, které budete řešit samostatně. Ke každému úkolu potřebujete soubor znalostí, který je obsažen v některých z lekcí. Úkoly je však možné řešit i jen pomocí programovacího manuálu (pro pokročilé). Splnění úkolu bude kontrolovat vedoucí a odmění ho 2 - 4 Chotěcoiny. Po splnění úkolu si v tabulce na vašem řádku zaznačte křížkem jeho splnění. 

# Lekce 0
Zprovozníme programovací prostředí VS Code + PlatformIO tak, abyste mohli nahrát kód do PaLampy z vašeho PC.


# Lekce 1 (led)
Rozsviť teplou a studenou ledku na 10%.

## Výsledný kód

```
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
    // id panelu, (0 = warm, 1 = cool)
    // brightness, (0-1)
    paLampa.lights.setWhite(0, 0.1);
    paLampa.lights.setWhite(0, 0.1);
}

void loop() {
}

```

## Úkol 1 - Rozsviť teplé bílé LED
Napište program, který každou vteřinu krátce rozsvítí teplé bíle ledky. Doba zobrazení je 250 ms v každé vteřině.

## Úkol 2 - Rozsviť studené bílé LED
Napište program, který bude blikat jako železniční přejezd. Blikat budou střídavě studené ledky, a teplé ledky v 500 ms intervalu.

# Lekce 2
Rozblikáme 8. barevnou LED na horním segmentu.

## Výsledný kód

```
#include "PaLampa/PaLampa.h"

void setup() {
    paLampa.begin();
}

void loop() {
    paLampa.lights.setColor(0,8,red); // rozsvítí 8. LED červenou barvou
    delay(300); //delay 300ms
    paLampa.lights.setColor(0,8,black); // zhasne 8. LED
    delay(300);
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
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    if(ToMat.buttonRead(0)) {
        ToMat.piezo.tone(100);
    }
    else {
        ToMat.piezo.stop();
    }
    delay(20);
}
```

## Úkol 6 - Manuální blikání LED 
Napište program, který bliká libovolnou LED pouze při stisknutém pravého tlačítka. Doba svícení je 200 ms. Doba zhasnutí je 200 ms.

## Úkol 7 - Stabilní stav LED
Napište program, který bude stiskem tlačítka přepínat svícení dvou různých LED. Vždy bude svítit pouze jedena LED, stiskem tlačítka se jedna LED vypne a zapne se ta druhá. Dalším stiskem tlačítka se znovu zapne pouze ta původní LED a proces lze opakovat.

# Lekce 4 (piezo)


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

## Úkol 8 - dlouhé pííííííp (piezo dělá neustálí zvuk)
Napište program, který bude blikat libovolným segmentem a rychlost tohoto blikání se zvětší, když se sníží intenzita osvětlení na předním fotorezistoru (např. bude zakrytý prstem).

## Úkol 9 - základní melodie (jednoduchá krátká melodie z pieza bonus přidání tlačítka)
Napište program, který počítá, kolikrát bylo stisknuto tlačítko SW1. Při resetování programu se počítadlo vynuluje. Pokud chceme zjistit, kolikrát bylo tlačítko SW1 stisknuto, musíme stisknout tlačítko SW2 a program musí pípnout daným počtem pípnutí.

# Lekce 5 (potenciometer)


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

## Úkol 10 - zesilování LED (zesílení nebo zeslabení LED za pomocí otáčení potenciometru)
Napište program, který rozezní piezoakustický měnič, pokud Time-O-Mat vneseme do temnoty.

## Úkol 11 - měnění RGB (otáčení potenciometru mění barvy RGB LED )
Napište program, který při každém stisku jednoho z tlačítek na dotykové liště rozsvítí další LED v rámci jednoho segmentu a původní LED zhasne - "posune" světlo na LED na další pozici(začne se LED s indexem 0 a vždy se zvyšuje o 1). Po dosažení poslední LED se znovu rozsvítí nultá LED a proces se opakuje. Pokud není tlačítlo stisknuto, pořád svítí stejná LED.


# Lekce 6 (světelný sensor)
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

## Úkol 12 - Světelná signaliazce tmy (pokud tma tak zviš jas ps.světelný sensor za lampou)
Napište program, který rozezní piezoakustický měnič, pokud Time-O-Mat vneseme do temnoty.

## Úkol 13 - Noční světlo (sensor pod lampou hlídá jas aby nebyl moc silný)
Napište program, který při každém stisku jednoho z tlačítek na dotykové liště rozsvítí další LED v rámci jednoho segmentu a původní LED zhasne - "posune" světlo na LED na další pozici(začne se LED s indexem 0 a vždy se zvyšuje o 1). Po dosažení poslední LED se znovu rozsvítí nultá LED a proces se opakuje. Pokud není tlačítlo stisknuto, pořád svítí stejná LED.


# Lekce 7 (touch sensor)
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

## Úkol 14 - Dotyk (když se dotkneš lampa blikne čímkoliv)
Přepracujte úkol 9 tak, aby Time-O-Mat přes sériovou linku přenášel číslo LED, která právě svítí.



