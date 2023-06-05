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





