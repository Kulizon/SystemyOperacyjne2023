==================== Polecenie ====================

Zmodyfikować program z ćwiczenia 1b, tak aby komunikaty procesów potomnych były
wypisywane przez program uruchamiany przez funkcję execlp. Nazwę programu do uruchomienia przekazywać przez argumenty programu procesu macierzystego.
Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork-exec jak wyżej i dlaczego?

==================== Wstęp ====================

Programy zostały napisane w języku C i pokazuje przykładowe użycia funkcji związanych z procesami.

Polecenia make:
make all
make run-cw2
make clean

Program włączać komendą:
make run-cw2

==================== Realizacja ====================

Program wypisuje odpowiednie identyfikatory procesów tworzonych przy pomocy funkcji fork() oraz funkcji execlp(). 
Funkcja execlp() wywoływana jest w procesie potomnym od razu po jego utworzeniu, i wowołuje program printOutInfo.c, który wypisuje identyfikatory.

==================== Odpowiedzi ====================

Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork-exec jak wyżej i dlaczego?

Powstanie n procesów potomnych.
Po każdym sklononowaniu procesu, nowy (sklowonay) proces wywołuje funkcję execpl, która "nadpisuje" aktualny proces, procesem który jedynie wypisuje identyfikatory.
W ten sposób przez pętle iteruje jedynie proces macierzysty.













