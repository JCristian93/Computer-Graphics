
Elemente de grafica pe calculator - Tema1

	* Simplified Geometry Dash
	* Jalba Cristian 333 CA
	
1. Cerinta
	Cerinta temei a fost implementarea unui joc de tip platformer ce sa fie 
similar cu jocul Geometry Dash
2. Utilizare
	In timpul jocului puteti folosi doar tasta SPACE pentru a evita obstacole
Butonul R este pentru a reseta nivelul , iar BACKSPACE este pentru pauza.

2.3 Input Tastatura
	SPACE : pentru ca jucatorul sa sara
	R : pentru a se reseta nivelul
	BACKSPACE : pentru a pune pauza jocului
	ESC : pentru a iesi complet din joc

3. Implementare
	Ca framework am folosit laboratorul 2 la care am facut mici modificari, tema 
a fost realizata in Microsoft Visual Studio 2013 .
	Tot codul se afla in main.c , am folosit vectori si variabile globale cu care 
am incercat pe cat de putintza sa minimizez cantitatea de cod duplicat . 
Sunt unele bucati de cod ce ar fi putut fi puse intr-o functie sau mai multe dar 
am preferat sa fie cat mai vizibil ce face fiecare sectiune de cod. 
	Pentru inceput am initializat in init() vectorii de triunghiuri , cercuri , platforme
si orice figura am considerat ca merita implementata . Vectorii acestia sunt iterati 
in onIdle() la fiecare pas si se fac verificari prin care vad daca playerul e aproape de 
o figura si ii spun cum sa reactioneze (sa faca translatii , rotatii , etc).
	De multe ori folosesc niste bool-uri pentru a avea un control mai bun la aparitia unui
eveniment , gen o apasare de tasta sau faptul ca se colecteaza 5 puncte si trebuie afisat 
mesajul de victorie. 
	Deoarece verific la fiecare apel al lui onIdle() toate obiectele din scena , performanta
programului lasa de dorit . Din fericire tema a cerut doar 5 cadre ceea ce nu e prea mult .
	In aproape toate conditiile folosesc functia epsilon ce primeste 2 argumente de tip float
si verifica daca diferenta lor in modul este mai mica ca 12. Am ales 12 pentru a evita cat de 
mult posibil situatii in care playerul trece prin platforme sau nu reactioneaza la triunghiuri.
	Am adaugat comentarii inainte de initializarea vectorilor ca sa specific ce se creeaza.
	
4. Testare
	Testata cu Visual Studio 2013 pe un laptop cu procesor 
i7 4712 MQ si placa video nVidia GT 840M . Pe baterie se misca
mai lent decat pe cablu . 
	
5. Probleme aparute
	Cateodata playerul sare sau intra prin platforme , dar acest lucru se rezolva daca nu se
incearca o saritura la limita pe aceasta . De asemenea la prima platforma daca 
playerul se aproprie prea mult de capatul acesteia risca sa moara instant .(Codul
considera ca a cazut in tzeapa de langa aceasta) . Sunt destul de permisiv cu 
marja functiei epsilon , din aceasta cauza apar mici buguri . 
	Am avut probleme atunci cand am facut punctele (adica steguletzele galbene), deoarece
nu reuseam sa le fac sa dispara . Mi-am dat seama ca daca nu mai translatam steguletzele
impreuna cu restul scenei si le tratam separat , reuseam sa le fac sa dispara . 
	Momentan exista un mic "bug" , care face sa dispara toate steguletzele din urma 
atunci cand iei unul nou . Gen daca sari unul si il iei pe al doilea , primul va dispare 
si el odata cu al doilea . Se poate considera acceptabil deoarece cred ca playerul trebuie 
pedepsit daca a ratat ceva . 
	
6. Continutul Arhivei
	Proiectul asa cum a fost creat in visual studio 
+ main.c(unde se afla tot codul) + Readme . 

7. Functionalitati
	Playerul sta pe loc si se misca doar pe Oy . Toata scena e translatata spre stanga
creand astfel senzatia ca playerul se misca spre dreapta . Combinata cu translatia pe Oy
apare iluzia saltului . 
	In scena exista un oponent care se misca mai rapid ca celelalte elemente si care te 
omoara daca te lovesti de el . Deoarece jocul era greu de terminat am scazut viteza oponentului
de la 20 la 10 (unde 5 e pasul tuturor elementelor).
	Triunghiurile sunt niste polygon2D definite prin 3 puncte care te omoara daca te aproprii 
de acele puncte la o distanta de 12 (marja de eroare din functia epsilon , cu care fac comparatiile).
	Platformele sunt niste polygon2D pe care playerul poate sari si de pe care poate face in 
continuare jumpuri . Poate sari de pe o platforma mai inalta pe una mai joasa si viceversa . 
Daca playerul loveste lateral platforma , atunci moare . Mai exact prima latura si coltul stanga sus
al platformei sunt deadly . 
	Cercurile sunt niste obiecte ce fac boost playerului , mai exact fac un jump automat . Pentru a
activa cercul , playerul trebuie sa sara deasupra cercului (nu la mijloc sau in partea inferioara).
	La coliziune cu un steag , acesta va disparea si playerul va castiga un punct . Daca acumuleaza
5 puncte , se pune pauza si ii apare un mesaj de victorie . El poate continua jocul sau sa apese r
daca vrea restart . In caz ca moare de 3 ori ii apare mesajul de death si jocul devine complet blocat,
singura actiune ramasa fiind de a da restart la level . 
	Groapa e un spatiu in care playerul poate sari . In cazul starii actuale a jocului , aceasta e umpluta 
cu tzepe . Playerul cade automat in groapa daca nu sare(acelasi tip de cadere ca si la platforme). 
	Checkpointurile sunt alt tip de steag care iti salveaza punctul de respawn in caz ca mori . 
Daca sari peste checkpoint , nu se va retine punctul . Am decis sa fac checkpointul diferit de punctele
efective pentru a mari diversitatea elementelor din joc . E de retinut ca in situatia in care playerul moare
de 3 ori si e fortzat sa faca reset , se reseteaza si checkpointul . Cand playerul moare , va fi imediat 
intors la ultimul checkpoint prin care a trecut corect . 
	
8. Altele
	As mai fi vrut sa pun si sunete in joc , folosind functia PlaySound() dar nu am gasit la timp niste sunete
scurte si apropriate jocului . 
	Am vrut deasemenea sa adaug si efecte de particule , vroiam sa pun niste patrate verzi ce sa apara sub player 
atunci cand acesta nu e in aer . Patratele ar fi trebuit sa se translateze la stanga si sa se scaleze din ce in ce
mai mici pana dispareau . Se pot observa niste patratzele mici la inceputul jocului , dar nu am implementat ideea
din considerente de timp . 
	

