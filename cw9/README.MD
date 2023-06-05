Problem wzajemnego wykluczania wątków standardu POSIX z użyciem muteksów.

Program na początku tworzy i inicjalizuję muteks, a następnie tworzy wątki w ilości podanej w argumentach wywołaniach programu.
Wątki posiadają sekcje krytyczne w ilości podanej w arguementach wywołania.
Wypisują odpowiednio swoje sekcje krytyczne i prywatne wraz z numerami porządkowymi.
Każda aktualizacja licznika jest wypisywana.

Na koniec programu sprawdzana jest poprawność synchronizacji wątków.
Oczekiwany wynik to ilość_sekcji * ilość_wątków.


Argumenty wywołania programu: liczba_wątków_programu liczba_sekcji_krytycznych