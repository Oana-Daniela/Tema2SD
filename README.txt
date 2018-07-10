Puisor Oana-Daniela
311 CD			

			Tema 2

Functiile createTree si createTreeNode:

	 In prima functie am alocat memorie pentru un tree empty si am creat
 nodul nil (santinela) avand height-ul 0 si elem, info setate si ele pe 0. 
Apoi am setat nodul root al tree-ului ca fiind santinela. Cealalta functie
 a fost la fel de simpla, am alocat memorie pentru un nod, am setat info si
 elem folosind functiile primite si setate in structura tree si am setat
 height-ul pe 1, conform cerintei.

Functia isEmpty :

	Am verificat daca nodul root este egal sau nu cu santinela. 
Daca era egal atunci tree-ul era gol si se returna 1, daca nu atunci se 
returna 0.

Functia search :

	Am ales o implementare recursiva pentru ca aceasta este
cea mai simpla.  Daca nodul primit ca si argument este diferit de nil, 
atunci comparam valoare sa cu elem si daca sunt egale atunci inseamna 
ca am gasit nodul, daca nu atunci trebuie sa cautam in subarborele stang
 sau in subarborele drept.Daca valoarea cautata este mai mica decat 
valoarea nodului curent, atunci cautam in subarborele stang, altfel
 in cel drept. Recursivitatea se opreste atunci cand ajungeam la nil.

Functiile minimum si maximum :

	 Acestea intorc nodul cu valoarea minima si cel cu
 valoarea maxima din tree. Arborii AVL sunt arbori binari si prin
 constructia lor, nodul cel mai din stanga va fi cel cu valoarea cea mai
 mica, iar cel din dreapta de tot cel cu valoarea cea mai mare. Folosind 
aceasta observatie, am extras nodul minim si maxim, selectand nodul de 
la extrema respectiva.

Functiile succesor si predecesor 
	
 	Si aceste functii au fost asemanatoare
 intre ele. Prima trebuia sa intoarca primul nod cu valoarea mai mare decat
 al unuia curent, iar cea dea doua trebuia sa intoarca primul nod cu valoarea
 mai mica decat cea primita ca si argument. Algoritmul a fost asemanator pentru
 cele doua functii. Succesorul unui nod este cel mai mic nod ca si valoare din
 subarborele sau drept (proprietate obtinuta din constructia arborelui binar) 
daca acest subarbore exista. Daca nu, daca nodul curent are parinte si este 
copilul din stanga parintelui, atunci sigur parintele este succesorul. Daca
 nici aceasta conditie nu e indeplinita si nodul are parinte, dar este copilul
 din dreapta al acestuia si nodul are si bunic, bunicul avand parintele in 
partea stanga, atunci clar succesorul nodului e bunicul. Functia predecesor
 este simetrica, pasii algoritmului fiind asemanatori.

Functiile avlGetBalance si avlFixup :

	Aici m-am folosit de factorul balance. Functia de fixup
asigura proprietate de arbore AVL in momentul in care se fac insertii 
si stergeri.Am tratat cele 4 cazuri de rotatii, rotatii care sunt exemplificate si 
in cod. Algoritmul functie fixup presupune iterarea de jos in 
sus si actualizarea balance-ului, dupa care se verifica
 daca se indeplineste unul din cele 4 cazuri. Daca se indeplineste, atunci se 
roteste corespunzator.

Functia insert :
	
	 Daca tree-ul era gol, prin insertia unui nod el va ajunge sa 
aiba un element si acesta sa fie chiar root-ul. Cu siguranta in acest moment nu 
vom avea o debalansare, avand un singur element in tree. Daca cumva se mai 
insereaza un element si avem deja un nod root, atunci trebuie sa vedem unde il
 inseram. Pentru aceasta vom compara valoarea de inserat cu cea a nodului root,
 daca e mai mica atunci ne ducem in stanga, daca nu in dreapta. Si continuam acest
 proces pana ajungem la frunze. In acest moment vom sti care este nodul parinte, 
la care vom deveni copil si timp si pozitia (daca va trebui sa inseram la dreapta
 sau la stanga lui). In acest moment, putem face insertia, adica realiza legaturile
 necesare intre parinte si copil. Nu am uitat sa actualizez size-ul si sa apelez 
fixup-ul pentru ca insertia acestui nod poate destabiliza tree-ul.

Functia delete 	
	 La delete am facut doar
 cel mai simplu caz si anume cel al unui nod frunza, adica a unui nod
 care nu are niciun copil. Acest caz era simplu, pentru ca stergerea implica 
doar pierderea legaturilor cu parintele. Avem nevoie si de fixup pentru ca 
stergerea, la fel ca si insertia destabilizeaza arborele.
