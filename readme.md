# Programátorská Dokumentace
Jedná se o konzolovou verzi hry Snake, lze hrát Singleplayer i Multiplayer.\
Aplikace je napsaná v jazyce C++.

## Základní princip fungování
V aplikaci se nachází tyto třídy:

Třída *Game* reprezentuje hru a její průběh.\
Při spuštění se zavolá metoda *void initialize()*, která vytvoří mapu a umístí do ní hady.  
Metoda *void update()* přesune kurzor konzole na pozici (0,0), provede tah všemi hady, vypíše mapu + tabulku bodů a uspí vlákno na 0.1 sekundy.\
pozn. Nepoužívám volání *console cls*, protože vykreslování by bylo o hodně pomalejší, a mapa by pak při každém překreslení nepříjemně problikávala.

Třída *Map* slouží k reprezentaci herní mapy. 
Mezi nejdůležitější metody patří:
- *print()* - vypíše obsah mapy
- *tryGetValue(MapPosition position, int& value)* - zjistí, jestli dané políčko obsahuje body, pokud ano, tak je zapíše do proměnné *value* a vrátí true, jinak vrátí false
- *void generateObstacles(float obstacleProportion)* - vygeneruje do mapy překážky (náhodně) - parametr *obstacleProportion* určuje procentuální zastoupení překážek v mapě (tzn. je v rozsahu 0 - 1, 0 = žádné překážky, 1 = samé překážky). V aplikaci jsem použil hodnotu 0.05, tzn. překážky by měly tvořit přibližně 5 % mapy.\
pozn. Okolo mapy se vygenerují zdi, aby se hadi nemohli dostat mimo herní plán.
- *MapPosition getValidStartPosition(Direction snakeHeadDirection)* - vrátí validní startovní pozici pro hada, který je orientovaný v daném směru. Metoda zkontroluje, jestli jsou 3 políčka od hlavy dopředu prázdné. Tuto metodu používám při inicializaci hry k umístění hadů do mapy. 

Třída *BaseSnake* definuje několik společných metod pro všechny typy hadů.
- metoda *void executeMove()* slouží k pohybu hada. Pohne hada o 1 políčko v daném směru (aktuální směr je uložený v atributu *direction*), a podle toho upraví obsah mapy. Také upraví body hada, pokud se dostal na políčko, které obsahuje body; nebo jej vyřadí ze hry, pokud narazil do zdi.
- metoda *void die()* vyřadí hada ze hry (tzn. jeho hlavu a tělo změní na body s hodnotou 9).

Tato třída také definuje virtuální metodu *void move()*. V programu to mám navržené tak, že metoda *move()* získá a nastaví přip. ponechá stávající směr pohybu, a poté zavolá metodu *executeMove()*, která vykoná pohyb.\
Z *BaseSnake* dědí třídy *UserSnake* a *AISnake*, které reprezentují dané typy hadů. 

Třída *UserSnake* obsahuje metodu, *tryToChangeDirection()*, která reaguje na stisk kláves W,A,S,D a podle toho změní směr hada.

Třída *AISnake* reprezentuje hada ovládaného počítačem.\
Logika AI je navržená takto: V každém tahu projde bot všechny políčka a nastaví jim prioritu podle předem určených pravidel (metoda *getPriorities()*). Pravidla pro přidělování priorit jsou definovány v const atributech - každý typ políčka má danou prioritu. Platí, že čím vyšší priorita, tím výhodnější tah. Poté bot vybere z okolních políček to s nejvyšší prioritou, a provede tah v daném směru.

Třída *Cell* a její potomci reprezentují všechny možné typy políček (prázdné políčko, zeď, políčko s body, tělo hada, hlava hada).

Dále se v aplikaci nachází enum *Direction*, ten reprezentuje daný směr (+ ještě definuje několik pomocných metod)  a struktura *MapPosition* sloužící k uchování informace o pozici v mapě - obsahuje 2 složky (řádek, sloupec).