// #include "../tests/doctest/doctest.h"
// #include "lacze_do_gnuplota.hh"
// #include "Scena.hh"
// /****************************************************************
//  * --------------------------------------------------------------
//  * 
//  * Klasy wektor i macierz nie były testowane, bobyły testowane w 
//  * poprzednich zadaniach
//  * Tak samo niektóre metodyz klasy dron, tj.
//  * obort, obrot_rotorow, zapisz i pokaz_srodek nie były testowane, 
//  * ponieważ bazują one na metodach z klasy graniastoslup
//  * metoda akcja została przetestowana ręcznie
//  * metoda dzialanie w klasie Scena jest takim "menu" klejącym 
//  * wszystko w całość, też zostało przetestowane ręcznie 
//  * ______________________________________________________________
//  ****************************************************************/
// TEST_CASE("ddd")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp;
//     Prostopadloscian Pr = Prostopadloscian(tmp);
//     Lacze.DodajNazwePliku("../datasets/test_prosto.dat");
//     Lacze.ZmienTrybRys(PzG::TR_3D);
//     Lacze.UstawZakresX(-100, 100);
//     Lacze.UstawZakresY(-100, 100);
//     Lacze.UstawZakresZ(-100, 100);
//     Pr.zapis();
//     Lacze.Rysuj();
//     std::cout << "Wciśnij ENTER";
//     std::cin.ignore(1024, '\n');
//     Lacze.UsunNazwePliku("../datasets/test_prosto.dat");
// }
// TEST_CASE("Test graniastoslup - test pokaz środek i ustaw środek")
// {
//     Graniastoslup Gr;
//     Wektor3D wek = {100, 200, 300};
//     Gr.ustaw_srodek(wek);
//     CHECK(Gr.pokaz_srodek() == wek);
// }
// TEST_CASE("Test graniastoslup - test pokaz nazwa i ustaw nazwa")
// {
//     Graniastoslup Gr;
//     std::string nazwa = "nazwa";
//     Gr.ustaw_nazwa(nazwa);
//     CHECK(Gr.pokaz_nazwa() == nazwa);
// }
// TEST_CASE("Test graniastoslup - test translacja")
// {
//     //uzywamy do testu prostopadloscianu, bo ma więcej punktów do sprawdzenia
//     Wektor3D pocz = {0, 0, 0};
//     Wektor3D koniec = {5, 5, 5};
//     Prostopadloscian Pr = Prostopadloscian(pocz, 10, 10, 10);
//     Pr.translacja(koniec);

//     Wektor3D tmp = {0, 10, 10};
//     CHECK(Pr[0] == tmp);

//     tmp = {0, 10, 0};
//     CHECK(Pr[1] == tmp);

//     tmp = {10, 10, 10};
//     CHECK(Pr[2] == tmp);

//     tmp = {10, 10, 0};
//     CHECK(Pr[3] == tmp);

//     tmp = {10, 0, 10};
//     CHECK(Pr[4] == tmp);

//     tmp = {10, 0, 0};
//     CHECK(Pr[5] == tmp);

//     tmp = {0, 0, 10};
//     CHECK(Pr[6] == tmp);

//     tmp = {0, 0, 0};
//     CHECK(Pr[7] == tmp);

//     tmp = {5, 5, 5};
//     CHECK(Pr.pokaz_srodek() == tmp);
// }
// TEST_CASE("Test graniastoslup - test rotacja")
// {
//     //uzywamy do testu prostopadloscianu, bo ma więcej punktów do sprawdzenia
//     Wektor3D pocz = {0, 0, 0};
//     Prostopadloscian Pr = Prostopadloscian(pocz, 10, 10, 10);
//     Wektor3D tab_1[8];
//     Wektor3D tab_2[8];
//     for (int i = 0; i < 8; ++i)
//     {
//         tab_1[i] = Pr[i];
//     }
//     double radian = 90 * M_PI / 180;
//     Macierz3x3 tmp;
//     Oblicz_Macierz_ObrotuZ(radian, tmp);
//     Pr.rotacja(tmp);
//     for (int i = 0; i < 8; ++i)
//     {
//         tab_2[i] = Pr[i];
//     }
//     CHECK(tab_1[0] == tab_2[2]);
//     CHECK(tab_1[1] == tab_2[3]);
//     CHECK(tab_1[2] == tab_2[4]);
//     CHECK(tab_1[3] == tab_2[5]);
//     CHECK(tab_1[4] == tab_2[6]);
//     CHECK(tab_1[5] == tab_2[7]);
//     CHECK(tab_1[6] == tab_2[0]);
//     CHECK(tab_1[7] == tab_2[1]);
// }
// TEST_CASE("Test graniastoslup - test zapis")
// {
//     //uzywamy do testu prostopadloscianu, bo ma więcej punktów do sprawdzenia
//     Wektor3D pocz = {0, 0, 0};
//     Wektor3D pocz_dolny = {0, 0, -5};
//     Wektor3D pocz_gorny = {0, 0, 5};
//     Prostopadloscian Pr = Prostopadloscian(pocz, 10, 10, 10, "../datasets/zapis_test.dat");
//     Pr.zapis();
//     std::ifstream StrmIn;
//     Wektor3D tab[16];
//     StrmIn.open("../datasets/zapis_test.dat");
//     for (int i = 0; i < 16; ++i)
//     {
//         StrmIn >> tab[i];
//     }
//     StrmIn.close();
//     CHECK(tab[0] == pocz_gorny);

//     pocz = {-5, 5, 5};
//     CHECK(tab[1] == pocz);

//     pocz = {-5, 5, -5};
//     CHECK(tab[2] == pocz);

//     CHECK(tab[3] == pocz_dolny);

//     CHECK(tab[4] == pocz_gorny);

//     pocz = {5, 5, 5};
//     CHECK(tab[5] == pocz);

//     pocz = {5, 5, -5};
//     CHECK(tab[6] == pocz);

//     CHECK(tab[7] == pocz_dolny);

//     CHECK(tab[8] == pocz_gorny);

//     pocz = {5, -5, 5};
//     CHECK(tab[9] == pocz);

//     pocz = {5, -5, -5};
//     CHECK(tab[10] == pocz);

//     CHECK(tab[11] == pocz_dolny);

//     CHECK(tab[12] == pocz_gorny);

//     pocz = {-5, -5, 5};
//     CHECK(tab[13] == pocz);

//     pocz = {-5, -5, -5};
//     CHECK(tab[14] == pocz);

//     CHECK(tab[15] == pocz_dolny);
// }
// TEST_CASE("Test prostopadłościan - konstruktor")
// {
//     Prostopadloscian Pr;
//     Wektor3D pocz;
//     Pr = Prostopadloscian(pocz, 10, 10, 10);
//     pocz = {-5, 5, 5};
//     CHECK(Pr[0] == pocz);

//     pocz = {-5, 5, -5};
//     CHECK(Pr[1] == pocz);

//     pocz = {5, 5, 5};
//     CHECK(Pr[2] == pocz);
//     pocz = {5, 5, -5};
//     CHECK(Pr[3] == pocz);

//     pocz = {5, -5, 5};
//     CHECK(Pr[4] == pocz);

//     pocz = {5, -5, -5};
//     CHECK(Pr[5] == pocz);

//     pocz = {-5, -5, 5};
//     CHECK(Pr[6] == pocz);

//     pocz = {-5, -5, -5};
//     CHECK(Pr[7] == pocz);

//     pocz = {0, 0, 0};
//     CHECK(Pr.pokaz_srodek() == pocz);
// }
// TEST_CASE("Test gransiatoslup6 - konstruktor")
// {
//     Graniastoslup6 Gr;
//     Wektor3D pocz;
//     Gr = Graniastoslup6(pocz);

//     pocz = {20, 0, 7.5};
//     CHECK(Gr[0] == pocz);

//     pocz = {20, 0, -7.5};
//     CHECK(Gr[1] == pocz);

//     pocz = {10, 17.3205080757, 7.5};
//     CHECK(Gr[2] == pocz);

//     pocz = {10, 17.3205080757, -7.5};
//     CHECK(Gr[3] == pocz);

//     pocz = {-10, 17.3205080757, 7.5};
//     CHECK(Gr[4] == pocz);

//     pocz = {-10, 17.3205080757, -7.5};
//     CHECK(Gr[5] == pocz);

//     pocz = {-20, 0, 7.5};
//     CHECK(Gr[6] == pocz);

//     pocz = {-20, 0, -7.5};
//     CHECK(Gr[7] == pocz);

//     pocz = {-10, -17.3205080757, 7.5};
//     CHECK(Gr[8] == pocz);

//     pocz = {-10, -17.3205080757, -7.5};
//     CHECK(Gr[9] == pocz);

//     pocz = {10, -17.3205080757, 7.5};
//     CHECK(Gr[10] == pocz);

//     pocz = {10, -17.3205080757, -7.5};
//     CHECK(Gr[11] == pocz);

//     pocz = {0, 0, 0};
//     CHECK(Gr.pokaz_srodek() == pocz);
// }
// TEST_CASE("Test drona - ruch pionowy")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp, tmp1;
//     dron Dr = dron(0, Lacze, tmp);
//     tmp = Dr.pokaz_srodek();
//     Dr.ruch_pionowy(100);
//     tmp1 = Dr.pokaz_srodek();
//     tmp[2] += 100;
//     CHECK(tmp == tmp1);
// }
// TEST_CASE("Test drona - przesuniecie")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp, tmp1;
//     dron Dr = dron(0, Lacze, tmp);
//     tmp = Dr.pokaz_srodek();
//     Dr.przesuniecie(5);
//     tmp1 = Dr.pokaz_srodek();
//     tmp[0] += 5;
//     CHECK(tmp == tmp1);
// }
// TEST_CASE("Test drona - przypisz sciezke")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp;
//     dron Dr = dron(0, Lacze, tmp);
//     Dr.przypisz_sciezke(20);
//     Wektor3D tab[4];
//     std::ifstream StrmIn;
//     StrmIn.open("../datasets/sciezka.dat");
//     for (int i = 0; i < 4 ; ++i)
//     {
//         StrmIn >> tab[i];
//     }
//     StrmIn.close();
//     tmp = {0,0,0};
//     CHECK(tab[0]==tmp);
//     tmp = {0,0,400};
//     CHECK(tab[1]==tmp);
//     tmp = {20,0,400};
//     CHECK(tab[2]==tmp);
//     tmp = {20,0,0};
//     CHECK(tab[3]==tmp);
// }
// TEST_CASE("Test rysowania prostopadłościanu")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp;
//     Prostopadloscian Pr = Prostopadloscian(tmp);
//     Lacze.DodajNazwePliku("../datasets/test_prosto.dat", PzG::RR_Ciagly, 2);
//     Lacze.ZmienTrybRys(PzG::TR_3D);
//     Lacze.UstawZakresX(-100, 100);
//     Lacze.UstawZakresY(-100, 100);
//     Lacze.UstawZakresZ(-100, 100);
//     Pr.zapis();
//     Lacze.Rysuj();
//     std::cout << "Wciśnij ENTER";
//     std::cin.ignore(1024, '\n');
//     Lacze.UsunOstatniaNazwe();
// }
// TEST_CASE("Test rysowania rotora")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp;
//     Graniastoslup6 Ro = Graniastoslup6(tmp);
//     Lacze.DodajNazwePliku("../datasets/test_gr.dat", PzG::RR_Ciagly, 2);
//     Lacze.ZmienTrybRys(PzG::TR_3D);
//     Lacze.UstawZakresX(-100, 100);
//     Lacze.UstawZakresY(-100, 100);
//     Lacze.UstawZakresZ(-100, 100);
//     Ro.zapis();
//     Lacze.Rysuj();
//     std::cout << "Wciśnij ENTER";
//     std::cin.ignore(1024, '\n');
//     Lacze.UsunOstatniaNazwe();
// }
// TEST_CASE("Test rysowania drona")
// {
//     PzG::LaczeDoGNUPlota Lacze;
//     Wektor3D tmp;
//     dron Dr = dron(0, Lacze, tmp);
//     Lacze.ZmienTrybRys(PzG::TR_3D);
//     Lacze.UstawZakresX(-100, 100);
//     Lacze.UstawZakresY(-100, 100);
//     Lacze.UstawZakresZ(-100, 100);
//     Dr.zapisz();
//     Lacze.Rysuj();
//     std::cout << "Wciśnij ENTER";
//     std::cin.ignore(1024, '\n');
//     Lacze.UsunOstatniaNazwe();
// }
// TEST_CASE("Test scena - konstruktor bezparametryczny - testuje również tworzenie siatki")
// {
//     Scena Scena1;
//     std::cout << "Aby zakończyć testy == Zamknąć gnuplota\nWciśnij ENTER" << std::endl;
//     std::cin.ignore(1024,'\n');
// }
// TEST_CASE("test zliczanie wektorów początek")
// {
//     /*!
//      * Pokazuje ile wektorów było przed powstaniem wektora liczenie
//      */
//     std::cout << "--------------------------------------------------------" << std::endl;
//     std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
//     std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
//     std::cout << "--------------------------------------------------------" << std::endl;
//     Wektor3D liczenie;
//     /*!
//      * Pokazuje ile wektorów jest po powstaniu wektora liczenie
//      * ilosc_stworzonych i ilosc_tymczasowych zwiększyły się o 1
//      */
//     std::cout << "--------------------------------------------------------" << std::endl;
//     std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
//     std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
//     std::cout << "--------------------------------------------------------" << std::endl;
// }

// TEST_CASE("test zliczanie wektorów koniec")
// {
//     /*!
//      * Pokazuje ile wektorów jest gdy wektor liczenie już nie istnieje
//      * ilosc_stworzonych została niezmieniona, lecz ilosc_tymczasowych zmniejszyła się o 1
//      * Zatem wszystko działa jak należy
//      */
//     std::cout << "--------------------------------------------------------" << std::endl;
//     std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
//     std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
//     std::cout << "--------------------------------------------------------" << std::endl;
// }