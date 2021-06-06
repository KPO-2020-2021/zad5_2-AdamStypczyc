// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "Wektor3D.hh"
#include "Macierz.hh"
#include "Prostopadloscian.hh"
#include "../include/lacze_do_gnuplota.hh"
#include "Scena.hh"

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

int main()
{
       if (1)
       {
              Scena Scena1;
              std::cout << "--------------------------------------------------------" << std::endl;
              std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
              std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
              std::cout << "--------------------------------------------------------" << std::endl;

              while (Scena1.dzialanie())
              {
                     Scena1.pokaz_lacze().Rysuj();
              }
       }
       std::cout << "--------------------------------------------------------" << std::endl;
       std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
       std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
       std::cout << "--------------------------------------------------------" << std::endl;
}
