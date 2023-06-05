==================== Polecenie ====================

(a) Napisać program wypisujący identyfikatory UID, GID, PID, PPID i PGID dla danego procesu.
(b) Wywołać funkcję fork trzy razy (najlepiej w pętli for) i wypisać powyższe identyfikatory dla procesu macierzystego oraz wszystkich procesów potomnych. 
Przy pomocy funkcji wait sprawić, aby proces macierzysty zaczekał na zakończenie wszystkich procesów potomnych.
(c) Jak w (b), tylko przy użyciu funkcji sleep (! nie używać funkcji wait) sprawiać by procesy potomne były adoptowane przez proces init lub systemd; poleceniem
pstree -p z poziomu pow loki wyświetlić drzewo procesów w danym systemie i zidentyfikować proces adoptujący osierocone procesy.
(d) Jak w (b), tylko wstawić funkcję sleep w takich miejscach programu, aby procesy pojawiały się, na ekranie grupowane pokoleniami od najstarszego do
najmłodszego, a proces macierzysty kończył się dopiero po procesach potomnych. Na podstawie wyników programu sporządzić (w
pliku tekstowym) "drzewo genealogiczne” tworzonych procesów z zaznaczonymi identyfikatorami PID, PPID i PGID.
(e) Jak w (b), tylko przy użyciu fukcji setpgid sprawić by każdy proces potomny stawał się liderem swojej własnej grupy procesów. 
Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?

==================== Wstęp ====================

Programy zostały napisane w języku C i pokazuje przykładowe użycia funkcji związanych z procesami.

Polecenia make:
make all
make run-cw1{x}, gdzie x - {a, b, c, d, e}
make clean

Odpowiednie podpunkty włączać komendą:
make run-cw1{x}, gdzie x - {a, b, c, d, e}

==================== Realizacja ====================

Program napisany został w języku C.

(a) Program korzystając z odpowiednich funkcji wypisuej identyfikatory: UID, GID, PID, PPID i PGID.
(b) Na początku program wypisuje swoje identyfikatoy (przy użyciu funckji printOutInfo()), a następnie w pętli tworzy procesy potomne, które następnie również wypisują swoje identyfikatoyr.
(c) Funkcja wait() zostaje zastąpiana funkcją sleep(), która jest wywoływana po stworzeniu procesu potomengo. Następnie proces macierzysty kończy swoje działania,
co powoduje zaadoptowanie procesu przez proces init.
(d) Funkcja sleep() wywoływana jest w procesie potomnym, przed wywołaniem funkcji printOutInfo().
(e) W procesie potomnym wywoływana jest funkcja setgpid(), która wraz z drugim argumentem 0, tworzy nową grupe procesów, której liderem jest ten proces.

==================== Odpowiedzi ====================

(e) Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?

Licząc proces macierzysty - 2 do potęgi n 
Nie licząc procesu macierzystego - (2 do potęgi n) - 1

Każdy kolejny proces "dzieli się" dwa procesy przy każdym wywołaniu, zatem:
dla i = 0:   proces

dla i = 1:   proces 
            /      \
         proces   proces <---- zliczamy tylko aktualne procesy

dla i = 2:    proces 
            /        \
       proces        proces
      /      \      /       \
   proces  proces proces  proces <---- zliczamy tylko aktualne procesy

Zauważamy, że liczba procesów róśnie wykładniczo oraz wynosi dokładnie 2 do potęgi n.


==================== Przykładowe Drzewo Genealogiczne ====================

Format: (PID, PPID, GPID)

(85541, 85540, 85540)__________________________
   |                   |                      |
   |                   |                      |
   |                   |                      |
(85548, 85541, 85540)  (85546, 85541, 85540)  (85542, 85541, 85540)
                       |                      |                  |                                
                       |                      |                  | 
                       |                      |                  | 
               (85547, 85546, 85540)    (85545, 85542, 85540)   (85543, 85542, 85540)
                                                                 | 
                                                                 | 
                                                                 |                                                                 
                                                               (85544, 85543, 85540)





