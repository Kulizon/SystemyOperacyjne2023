Program napisany jest w języku C i implementuje problem producenta-konsumenta z buforem cyklicznym.
Wykorzystane zostały: pamięć dzielona i semafory standardu POSIX.

Aby włączyć program na jeden z trzech sposobów należy użyć jednej z komend:
    make run-cw7S       // (biblioteka statyczna)
    make run-cw7D1      // (biblioteka dynamiczna sposób 1)
    make run-cw7D2      // (biblioteka dynamiczna sposób 2)

Na końcu wywołania programy porównywane są pliki wynikowe i zrodlowe.

Argumenty wywołania programu "main" są postaci:
    "./PROGRAM_PRODUCENT" "./PROGRAM_KONSUMENT" "./NAZWA_PLIKU_ZRODLOWEGO"  "./NAZWA_PLIKU_WYNIKOWEGO"
Wszystkie pliki muszą znajdować się w tym samym katalogu.

