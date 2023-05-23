# AlgoritmiGrafuri
Acest program aplica algoritmul lui Prim si algoritmul Dijkstra pe grafuri orientate/neorientate si conexe/neconexe


Structuri:

Structura AdjListNode
Reprezintă un nod în lista de adiacență și conține informații despre destinația nodului într-o muchie, distanța asociată muchiei și scorul asociat muchiei.

Structura AdjList
Reprezintă o listă de adiacență și conține un pointer la primul nod din listă și adâncimea listei.

Structura Graph
Reprezintă un graf cu liste de adiacență și conține informații despre componente conexe, numărul de noduri din graf, numărul de componente conexe, numele nodurilor, greutatea comorii și vectorul de liste de adiacență.

Structura MinHeapNode
Reprezintă un nod într-un heap minim și conține informații despre un nod din graf și distanța asociată acestuia.

Cerinta 1:

Pentru rezolvarea acestei cerinte, am inceput prin a asocia grafului numarul de componente conexe maximale. Daca graful este este conex, atunci se aplica algoritmul lui Prim pe intreg graful, altfel, se scrie in fisierul de output numarul de componente conexe si se apeleaza o functie care returneaza un vector de subgrafuri, reprezentand componentele conexe maximale, iar apoi se aplica algoritmul lui Prim pe fiecare in parte.
In final, se sorteaza vectorul de costuri ale componentelor conexe.

Cerinta 2:

Pentru rezolvarea acestei cerinte, incep prin a verifica daca exista drum de la corabie la insula si invers. In caz afirmativ, se aplica algoritmul Dijkstra modificat, folosind un minHeap, care stabileste drumul favorabil in functie de scorul arcului si care returneaza distanta de la insula la corabie. De asemenea, functiei i se transmite ca parametru si un vector (path) care sa retina nodurile ce formeaza drumul favorabil. La iesirea din functie, se parcurge acel vector si se stabileste adancimea minima dintre acele noduri. In final, se calculeaza numarul de drumuri necesare transportarii comorii (greutate comoara / adancime minima), se incrementeaza numarul de drumuri pentru a suplimenta restul (daca e cazul) si se scriu valorile cerute in fisierul de output.