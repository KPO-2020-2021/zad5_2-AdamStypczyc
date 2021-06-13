## Podsumowanie mojej pracy
Celem tego zadania było wymodelowanie powierzchni Tytana. Problemów z tym zadaniem nie miałem aż tyle co z 1. fazą drona. Początkowo przeszedłem do wymodelowania przeszkód, tworzę je poprzez przerabianie w konstruktorze tych klas prostopadłościanu. Jednym z większych problemów było zrozumienie shared pointerów, ale poszło to w miarę sprawnie, bo już wcześniej je sobie przyswajałem, ponieważ jedna z wersji zadania 5.1 opierała się na nich, ale nic z jej nie wyszło. Następnie problem miałem z łączem do gnuplota ale przerzucenie nowego łącz pomogło. Potem przez jakiś czas zabezpieczałem program i myślałem jak to zrobić aby przeszkody nie były zagnieżdżone w podstawie. Testów nie ma, bo nie są wymagane. Program kompiluje się komenda make i uruchamia komendą ./main.
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


