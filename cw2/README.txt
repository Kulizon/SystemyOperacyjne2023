(e) Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork-exec jak wyżej i dlaczego?

Powstanie n procesów potomnych.
Po każdym sklononowaniu procesu, nowy (sklowonay) proces wywołuje funkcję execpl, która "nadpisuje" aktualny proces, procesem który jedynie wypisuje identyfikatory.
W ten sposób przez pętle iteruje jedynie proces macierzysty.




