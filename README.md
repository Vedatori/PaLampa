# PaLampa [cz]
PaLampa je chytrá stolní lampička navržená jako výrobek na Letní robotický tábor 2023 organizovaný spolkem [Vědátoři](www.vedatori.cz). 
Jedná se o výrobek speciálně vyvinutý tak, aby si na něm člověk mohl zlepšit dovednosti při mechanické stavbě, pájení a programování. 
Účastníci dostali tento výrobek jako stavebnici, kdy pájeli nestandardní součástky na DPS s předem osazenými SMD součástkami a z předem připravených dílů sestavili mechanickou část. 
Po finalizaci je možné výrobek programovat a díky množství vstupních a výstupních periferií si naprogramované funkcionality přehledně demonstrovat. 
Nakonec je výrobek možné použít jako chytrou a praktickou stolní lampičku. 

Mechanickou část lze rozdělit na dvě hlavní části - spodní krabici a horní lampu. Vnější části krabice jsou vyřezány z překližky na laserové řezačce a obsahují zámkové západky. 
Ty se při stavbě lepí disperzním lepidlem a po vyschnutí tvoří pevný základ pro uložení ostatních dílů. 
Základní díl horní lampy je vytisknutý na 3D tiskárně a světelný difuzor je vyřezán z plexiskla, které bylo následně zmatněno. 
Spojení osmiček a krabice zajišťuje 3D tištěný nosník umístěný uvnitř krabice, který také fixuje desky plošných spojů (DPS). 
Spojení krabice a lampy zajišťuje překližkový nosník napojený skrze ohebné kouby, kdy spodní kloub disponuje aretací v několika polohách. 

Hlavní DPS obsahuje zejména mikrokontroler ESP32, který je na ni připájen. Programování a napájení je zajištěno přes USB-C. 
Hlavní DPS obsahuje také tlačítka, dotyková tlačítka, potenciometr, fotorezistory, teplotní senzor, OLED grafickou obrazovku a bzučák. 
V lampě je vsazena DPS osazená LED světly svítícími teplou a studenou bílou, stejně jako řadou adresovatelných RGB LED. Další takové LED jsou umístěny zezadu na nosníku, kde zajišťují ambientní podsvětlení prostoru za výrobkem. 
Výrobek je rozebiratelný, jednotlivé DPS jsou spojeny konektory, vzdálenější periferie pomocí kabelů.

Všechny periferie byly zvoleny tak, aby vytvořily výrobek s mnoha volitelnými postranními funkcionalitami. 
Díky nim je možné u účastníků tábora rozvíjet jejich schopnost algoritmizovat úlohu a programovat. 
Pro hodiny byla vytvořena softwarová knihovna, která výrazně zjednodušuje interakci s periferiemi. 
Pomocí této knihovny byl vytvořen vzorový software, pomocí kterého je možné výrobek používat v základním nastavení. 
Výrobek je možné ovládat pomocí vstupních periferií nebo přes WiFi skrz počítač nebo smartphone, které přistupojí k interně hostované webové stránce. 
Všechny tyto vlastnosti lze upravovat a přidávat nové funkcionality podle přání uživatele. Zařízení se programuje ve Visual studio Code v jazyce C++ pomocí frameworku esp32-arduino.

Myšlenkou tohoto projektu je, aby výrobek tvořil každodenní užitečný doplněk pokoje, ale aby mohl být jeho software jednoduše modifikován a rozvíjen tak, jak si každý jeho vlastník představuje.

## Návod
Při stavbě hodin Time-O-Mat postupujte podle připravených návodů v následujícím pořadí:
1. [Návod pro elektroniku](https://github.com/Vedatori/PaLampa/blob/main/Manuals/PaLampa_electronics_cz.md)
1. [Návod pro mechaniku](https://github.com/Vedatori/PaLampa/blob/main/Manuals/PaLampa_mechanics_cz.md)
1. [Návod pro programování](https://github.com/Vedatori/PaLampa/blob/main/Manuals/PaLampa_programming_cz.md)
1. [Lekce na programování](https://github.com/Vedatori/PaLampa/blob/main/Manuals/PaLampa_lectures_achievements.md)

# PaLampa [en]
PaLampa is a smart desk lamp designed as a product for the Summer Robotics Camp 2023 organized by the association Vědátoři. It is a product specially developed to help individuals improve their skills in mechanical construction, soldering, and programming. Participants received this product as a kit, where they soldered non-standard components onto a PCB with pre-mounted SMD components and assembled the mechanical part from pre-prepared pieces. After completion, the product can be programmed, and the programmed functionalities can be easily demonstrated thanks to the variety of input and output peripherals. In the end, the product can be used as a smart and practical desk lamp.

The mechanical part can be divided into two main components - the bottom box and the upper lamp. The outer parts of the box are laser-cut from plywood and include locking mechanisms. These are glued together with dispersion adhesive during construction, forming a sturdy foundation for the placement of other components.
The core component of the upper lamp is 3D-printed, and the light diffuser is cut from frosted plexiglass. The connection between the box and the lamp is ensured by a 3D-printed beam located inside the box, which also secures the printed circuit boards (PCBs).
The connection between the box and the lamp is facilitated by a plywood beam connected through flexible joints, with the lower joint having several locking positions.

The main PCB (Printed Circuit Board) primarily features the ESP32 microcontroller, which is soldered onto it. Programming and power supply are provided through USB-C. The main PCB also includes buttons, touch buttons, a potentiometer, photoresistors, a temperature sensor, an OLED graphic display, and a buzzer.
In the lamp, there is a PCB embedded with warm and cool white LEDs, as well as a series of addressable RGB LEDs. Additional LEDs of this kind are positioned at the rear on the beam, providing ambient lighting for the area behind the product. The product is modular, and the individual PCBs are connected via connectors, while remote peripherals are linked using cables.

All peripherals were selected to create a product with many optional side functionalities. Thanks to these features, participants in the camp can develop their ability to algorithmize tasks and program. A software library was developed for the lessons, significantly simplifying the interaction with peripherals. Using this library, a sample software was created that allows the product to be used in its basic configuration.
The product can be controlled through input peripherals or via Wi-Fi using a computer or smartphone connecting to an internally hosted web page. All of these features can be customized, and new functionalities can be added as per the user's desires. The device is programmed in Visual Studio Code using the C++ language and the esp32-arduino framework.

The idea behind this project is for the product to serve as an everyday useful addition to a room, but with software that can be easily modified and expanded as envisioned by each owner.

## Licence
* Obsah tohoto repozitáře mimo složku *Software* je sdílen pod licencí [Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/).
* Obsah složky *Software* je sdílen pod licencí [GNU Lesser General Public License v3.0](https://www.gnu.org/licenses/lgpl-3.0.en.html).


## License
* The contents of this repository excluding folder *Software* is shared under license [Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/).
* The contents of the folder *Software* is shared under license [GNU Lesser General Public License v3.0](https://www.gnu.org/licenses/lgpl-3.0.en.html).

![](Manuals/SupportFiles/IMG_4021.jpeg)
![](Manuals/SupportFiles/IMG_4026.jpeg)
![](Manuals/SupportFiles/IMG_4066.jpeg)
![](Manuals/SupportFiles/IMG_4028.jpeg)