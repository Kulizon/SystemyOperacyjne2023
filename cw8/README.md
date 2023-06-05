Program jest napisany w języku C i implementuje problem klient-serwer z wykorzystaniem kolejki komunikatów standardu POSIX

Aby włączyć przykładowe wywołanie programu należy użyć komendy: make run-cw8.
Po wykonaniu polecenia włączają się dwa terminale klienta i jeden terminal serwera.

W terminalach klienta należy wpisywać polecenia w formacie:
ZNAK1 OPERACJA ZNAK2, gdzie OPERACJA należy do {+, -, /, *}

Następnie polecenie zostanie wysłane na serwer, gdzie zostanie obliczone, a następnie zostanie zwrócony wynik, który zostaje sprawdzony po stronie klienta.

