V tomto dokumentu je uveden návod na osazení desky plošných spojů elektronickými součástkami. Některé součástky byly osazeny strojově při výrobě desek. Zbytek osazení je předmětem tohoto návodu.
Pro tento návod si zavedeme následující pojmy:
* DPS (Deska Plošných Spojů) - Laminátová deska pokrytá elektricky vodivými měděnými cestami, na kterou budeme nyní pájet součástky.
* PCB (Printed Circuit Board) - To stejné, co DPS.
* SMD (Surface Mount Device) - Tzv. bezvývodové elektronické součástky, které mají krátké nožičky. Tyto součástky jsou připájeny k DPS pouze z jedné strany. Tyto součástky byly osazevy strojově při výrobě DPS.
* THT (Through-hole Technology) - Tzv. vývodové elekotronické součástky, které mají dlouhé nožičky. Tyto nožičky jsou před zapájením součástky prostrčeny skrz otvory v DPS.

THT součástky budeme pájet následujícím způsobem:
1. Součástku vkládáme ze strany, kde je její obrys naznačen bílou čárou, tzv. silkscreenem.
1. Vývody (nožičky) součástek prostrčíme přisušnými otvory v DPS. Musí to jít lehce.
1. Součástku přitlačíme až k desce nebo co nejblíže.
1. Součástku pájíme ze strany, na kterou trčí její vývody. Tzn. z opačné strany, než je její bílý obrys na silkscreenu.
1. Vývody po zapájení zastřihneme.

___
# Obsah
* [Nízké součástky](#nizke)
* [Ovládací součástky](#ovladaci)
* [Měřicí součásstky](#meridla)
* [Vložení displeje](#displej)
* [LED deska](#LEDdeska)
* [Výroba kabelu](#tukabel)
* [Připevnění krytky](#krytka)
___

<!-- _________________________________________________________________ -->
# <a name = nizke>Nízké součástky</a>

## Potřebujeme:
* Hlavní PCB (černý)
* 2pin JST konektor
* piezoměnič
* 2x kondenzátor
* štípací kleště
* páječka

![alt](SupportFiles/IMG_4641.jpeg)

## Postup:
Vložte piezoměnič na jeho místo v desce, Dávejte pozor na polaritu, symbol plus na součástce musí být u symbolu plus na desce.
![alt](SupportFiles/IMG_4645.jpeg)
![alt](SupportFiles/IMG_4647.jpeg)

Zapájejete piezoměnič. Pomocí štípacích kleští zakraťte vývody.
![alt](SupportFiles/IMG_4649.jpeg)

Vložte do desky konektor JST.Pozor na orientaci, je důležité ho otočit přesně tak, jako je na obrázku.
![alt](SupportFiles/IMG_5635-min.jpg)
![alt](SupportFiles/IMG_5636-min.jpg)

Zapájejte. Zakraťte vývody.
![alt](SupportFiles/IMG_4660.jpeg)
![alt](SupportFiles/IMG_4664.jpeg)

VLožte do desky kondenzátor na místo označené C11. Pozor na polaritu, kratší vývod musí být zastrčený do poloviny kruhu, která je bíle vybarvená. Druhý kondenzátor vložte stejným způsobem na místo C19. Zapájejte, zakraťe vývody.
![alt](SupportFiles/IMG_4666.jpeg)
![alt](SupportFiles/IMG_4677.jpeg)

Takto má deska vypadat po zapájení prvních součástí.
![alt](SupportFiles/IMG_4685.jpeg)

Kleštěmi oddělte 4 piny z dutinkové lišty. Lištu rozstřihněte na místě, kde je pátý pin od kraje, ten se tím zničí.
![alt](SupportFiles/IMG_4688.jpeg)

Opatrně zařízněte boky lišty.
![alt](SupportFiles/IMG_4691.jpeg)

Lištu vložte do prostoru konektoru na displej, jak vidíte na obrázku. Zapájejte ji.
![alt](SupportFiles/IMG_4694.jpeg)

Výsledný pohled
![alt](SupportFiles/IMG_4700.jpeg)

<!-- _________________________________________________________________ -->
# <a name = ovladaci>Ovládací součástky</a>

## Potřebujeme:
* Hlavní PCB
* 3D tištěný tool pro tlačítka (3 díry)
* 3x tlačítko
* Potenciometr
* Konektor
* štípací kleště
* páječka

![alt](SupportFiles/IMG_4703.jpeg)

## Postup:
Nasaďte konektor na hlavní PCB. POZOR! Mezi součástkami jsou dva podobné konektory, tady musíte použít ten, který má krátké nezahnuté nožičky. Konektor musí mít správnou polaritu, výřez musí být směřován na stejnou stranu, jako je na obrázku. Konektor zapájejte.
![alt](SupportFiles/IMG_4704.jpeg)
![alt](SupportFiles/IMG_4706.jpeg)

Usaďte do desky potenciometr.
![alt](SupportFiles/IMG_4713.jpeg)

 Zapájejte všechny vývody včetně velkých plochých. Zakraťte vývody.
![alt](SupportFiles/IMG_4718.jpeg)

VLožte tlačítka do hlavního PCB. 
![alt](SupportFiles/IMG_4721.jpeg)

Na tlačítka nasuňte nástroj s děrami. Musí padnout na všechna zároveň.
![alt](SupportFiles/IMG_4724.jpeg)
![alt](SupportFiles/IMG_4726.jpeg)

Zapájejte tlačítka na hlavní PCB. Zakraťte vývody.
![alt](SupportFiles/IMG_3330.jpeg)

<!-- _________________________________________________________________ -->
# <a name = meridla>Měřicí součástky</a>

## Potřebujeme:
* Hlavní PCB
* 2x fotorezistor
* teplotní senzor
* Distanční díl na fotorezistor
* štípací kleště
* páječka

![alt](SupportFiles/IMG_4751.jpeg)

Do otvoru označeného R13 nasuňte fotorezistor. Odměřte ho podle dříve použitého toolu tak, jak ukazuje obrázek. Zapájejte.
![alt](SupportFiles/IMG_4736.jpeg)
![alt](SupportFiles/IMG_4740.jpeg)
![alt](SupportFiles/IMG_4742.jpeg)

Druhý fotorezistor nasuňte do 3D tištěného distančního dílu. Zapájejte na místo R14. Zakraťte vývody obou fotorezitstorů.
![alt](SupportFiles/IMG_4747.jpeg)
![alt](SupportFiles/IMG_4753.jpeg)
![alt](SupportFiles/IMG_4758.jpeg)

Výsledný pohled na spodní fotorezistor.
![alt](SupportFiles/IMG_4761.jpeg)

Teplotní senzor zasuňte do desky pouze na několik milimetrů. 
![alt](SupportFiles/IMG_5632-min.jpg)

Podložte si desku, aby se senzor při pájení neohnul.
![alt](SupportFiles/IMG_5633-min.jpg)

Zapájejte. Po zapájení jednoho vývodu ověřte, že je senzor postavený rovně. Pokud ne, tak si senzor ohněte do směru kolmého k desce.
![alt](SupportFiles/IMG_5634-min.jpg)

<!-- _________________________________________________________________ -->
# <a name = displej>Vložení displeje</a>

## Potřebujeme:
* hlavní PCB
* Displej s připájenou kolíkovou lištou
* Plastový držák displeje

![alt](SupportFiles/IMG_4768.jpeg)

# Postup:
Zastřihněte vývody kolíkové lišty vedoucí do displeje.
![alt](SupportFiles/IMG_5637-min.jpg)

Opatrně vložte displej do držáku. Můžete ho mírně rozevřít, ale dávejte pozor, ať bok nevylomíte.
![alt](SupportFiles/IMG_4771.jpeg)
![alt](SupportFiles/IMG_4773.jpeg)

Zasuňte displej s držákem do hlavní desky pomocí kolíkové lišty.
![alt](SupportFiles/IMG_4774.jpeg)
![alt](SupportFiles/IMG_4775.jpeg)

<!-- _________________________________________________________________ -->
# <a name = LEDdeska>LED deska</a>

## Potřebujeme:
* LED desku
* Teplotní senzor
* Úhlový konektor černý 8 pin
* Úhlový konektor bílý JST 3 pin
* Nástroj pro usazení teplotního senzoru
* Epoxidové lepidlo s kovovým plnivem (namíchá vedoucí)
* Dávkovací špejli
* páječku

![alt](SupportFiles/IMG_4777.jpeg)

## Postup:
Vložte teplotní senzor do 3D tištěného nástroje tak, aby nápis směřoval směrem dovnitř. Ohněte podle nástroje nožičky.
![alt](SupportFiles/IMG_4787.jpeg)

Otočte senzor teploty tak, aby byl čitelný nápis na něm.
![alt](SupportFiles/IMG_4790.jpeg)

Naneste malé množství připraveného epoxidu na plochu senzoru.
![alt](SupportFiles/IMG_4799.jpeg)

Vložte senzor do desky tak, aby směřoval směrem doprostřed desky. Tento krok provádějte pod dohledem vedoucího.
![alt](SupportFiles/IMG_4806.jpeg)

Desku se senzorem pořád umístěným v nástroji přitlačte z druhé strany směrem ke stolu.
![alt](SupportFiles/IMG_4811.jpeg)

Senzor připájejte, zakraťte vývody.
![alt](SupportFiles/IMG_4813.jpeg)

Do desky vložte 3pin bílý konektor. Připájejte a zaktaťte vývody.
![alt](SupportFiles/IMG_4819.jpeg)

Černý konektor vložte do desky stejným směrem, jako vidíte na obrázku.
![alt](SupportFiles/IMG_4821.jpeg)

Desku z druhé strany podepřete nástrojem použitým v minulém kroku.
![alt](SupportFiles/IMG_4825.jpeg)

Konektor připájejte. Výsledný pohled
![alt](SupportFiles/IMG_4826.jpeg)

<!-- _________________________________________________________________ -->
# <a name = tukabel>Výroba kabelu</a>

## Potřebujeme:
* kabel o délce 46 cm
* Kleště nebo malý svěrák na krimpování kabelu
* 2x konektor
* 1x krytka konektoru

![alt](SupportFiles/IMG_4830.jpeg)

POZOR! Kabel se vyrábí pouze na speciálním stanovišti pod dohledem vedoucího. Pokud se konektory nakrimpují špatně, musí se odstřihnout a tím se celý kabel zničí.

## Postup:
Odměřte a ustřihněte si kabel o délce 46 cm.
![alt](SupportFiles/IMG_4829.jpeg)

Nasuňte konektor na kabel tak, aby výstupek směřoval ke kraji kabelu. Šipka na konektoru musí směřovat k červené žíle kabelu.
![alt](SupportFiles/IMG_4834.jpeg)

Zarovnejte konec kabelu s konektorem. Stlačením kabel nakrimpujte. Pozor, je to nevratná operace, nechte si tento krok předem potvrdit vedoucím.
![alt](SupportFiles/IMG_4839.jpeg)

Ohněte kabel přes konektor a upněte ho do krytky. Ta se do konektoru nacvakne.
![alt](SupportFiles/IMG_4843.jpeg)
![alt](SupportFiles/IMG_4844.jpeg)

Na druhý konec kabelu nasuňte konektor tak, aby výstupek směřoval ke kraji kabelu. Šipka na konektoru musí směřovat k červené žíle kabelu.
![alt](SupportFiles/IMG_4848.jpeg)

Zarovnejte konec kabelu s konektorem. Stlačením kabel nakrimpujte. Pozor, je to nevratná operace, nechte si tento krok předem potvrdit vedoucím.
![alt](SupportFiles/IMG_4849.jpeg)

Zapojte kabel. Konec kabelu, kde je na konektoru krytka, se zapojuje do bílé desky s LED, druhý konec do černé hlavní desky. Společně s vedoucím nahrajte firmware a proveďte funkční test sestavy.
![alt](SupportFiles/IMG_4855.jpeg)

<!-- _________________________________________________________________ -->
# <a name = krytka>Připevnění krytky</a>

## Potřebujeme:
* Epoxid bez kovového plniče (namíchá vedoucí)
* Dávkovací špejli
* LED desku
* 3D tištěnou krytku na vývody konektoru

![alt](SupportFiles/IMG_4856.jpeg)

## Postup:
Naneste malé množství epoxidu na plochy na krajích krytky.
![alt](SupportFiles/IMG_4863.jpeg)

Přilepte krytku přes vývody konektoru. Krytka musí být zarovnaná s krajem desky.
![alt](SupportFiles/IMG_4867.jpeg)

<!-- _________________________________________________________________ -->
# <a name = pasek>LED pásek</a>

## Potřebujeme:
* Kabel se 3 vývody
* LED pásek
* pájku

![alt](SupportFiles/IMG_4942.jpeg)

## Postup:
Naneste trochu cínu na LED pásek. Dávejte pozor, z jaké strany pásek pájíte, musí se připojovat na stranu, kde je na střední plošce napsáno Din. Strana, kde je u prostřední plošky napsáno Do musí zůstat volná.
![alt](SupportFiles/IMG_4944.jpeg)

Připájejte kabely v následujícím pořadí:
Černá - 5V
Žlutá - Din
Červená GND
![alt](SupportFiles/IMG_4946.jpeg)

Výsledné zapojení
![alt](SupportFiles/IMG_4948.jpeg)

<!-- _________________________________________________________________ -->
# <a name = touch>Kabel na touch senzor</a>

## Potřebujeme:
* Kabel se 2 vývody
* Měděná páska
* Záslepku pro dotykové tlačítko

## Postup:
Ustřihněte si kusy měděné pásky o délce 11 mm a 20 mm. 
![alt](SupportFiles/IMG_5641-min.jpg)

11mm kusu zastřihněte kleštěmi rožky.
![alt](SupportFiles/IMG_5646.jpeg)

Na střed obou kusů naneste cín.
![alt](SupportFiles/IMG_5652-min.jpg)

K 11mm kusu připájejte červený drátek z kabelu. Cu pásku pájejte kolmo ke kabelu.
![alt](SupportFiles/IMG_5656-min.jpg)
![alt](SupportFiles/IMG_5661-min.jpg)

Stejným způsobem připájejte i černý akbel k 20mm kusu pásky.
