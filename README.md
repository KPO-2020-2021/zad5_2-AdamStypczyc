## Podsumowanie mojej pracy
Celem tego zadania było wymodelowanie dwóch dronów i umożliwienie poruszania się tym dronem. Problemów z tym zadaniem miałem wiele. Na samym początku problemem było poprawne zrozumienie diagramu załączonego w opisie zadania. Potem okazało się, że w rzeczywistości diagram jest bardziej poglądowy i trzeba było zrozumieć jak ten program miał wogóle wyglądać i chyba to było jednym z większych problemów. Po napisaniu co najmniej trzech wersji tego programu (nie wrzucałem ich na gita, bo nie wiedziałem czy idę w dobrą stronę) bardzo powili zaczęło się coś klarować. Rozmowy z kolegami na discordzie też pomogły. Krótką zagadką było jak tworzyć graniastosłup sześciokątny formeny, ale to było przyjemne odświeżenie wiadomości z gimnazjum. Większą zagadką było jak zapisywać graniastosłup sześciokątny formeny i prostopadłościan do pliku tak aby gnuplot rysował to jak należy. Następnie samo zbudowanie drona zajęło dużo czasu. Również różne translacje i rotacje były problemem, bo nie wiedziałem jak ma to wyglądać, gdy już myślałem, że jest dobrze dron zamiast ładnie się poruszać teleportował się i na dodatek nie na to miejsce gdzie miał wylądować. Problemów było wiele, nie pamiętam wszystkich, szło jak po gruzie, ale ważne, że jakoś się udało. Testy odpala się za pomoca ./unit_tests, a program za pomocą ./main. Przy testach dałem wymóg aby kliknąć ENTER, aby było możliwe zobaczenie rysunków w gnuplocie. 
## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Requirements: 

Example:

``` bash
> mkdir build && cd build
> cmake .. # options: -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release], Debug is default
> make
> ./main
> make test      # Makes and runs the tests.
> make coverage  # Generate a coverage report.
> make doc       # Generate html documentation.
```


