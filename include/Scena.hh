#pragma once
#include <list>
#include <iomanip>
#include "dron.hh"
#include "Plaskowyz.hh"
#include "Ostroslup.hh"
#include "Skarpa.hh"
/*!
 * \brief Definicje globalne
 * \param ZAKRES zakres gnuplota
 * \param POCZATEK początek siatki
 * \param POLOZENIE_1 położenie startowe drona 0
 * \param POLOZENIE_2 położenie startowe drona 1 
 * \param POLOZENIE_3 położenie startowe plaskowyzu
 * \param POLOZENIE_4 położenie startowe ostroslupa 1.
 * \param POLOZENIE_5 położenie startowe ostroslupa 2.
 * \param POLOZENIE_6 położenie startowe skarpy
 * \param ROZMIAR ilość kratek w siatce
 */
#define ZAKRES 700
#define POCZATEK \
    {            \
        0, 0, 0  \
    }
#define ROZMIAR 15
#define POLOZENIE_1  \
    {                \
        170, 170, 15 \
    }
#define POLOZENIE_2  \
    {                \
        400, 400, 15 \
    }

#define POLOZENIE_3 \
    {               \
        400, 200, 0 \
    }
#define POLOZENIE_4 \
    {               \
        125, 450, 0 \
    }
#define POLOZENIE_5 \
    {               \
        330, 580, 0 \
    }
#define POLOZENIE_6 \
    {               \
        550, 550, 0 \
    }

/*!
 * \brief Deklaracja klasy Scena
 * Łączy wszystko w całość
 * \param Lacze łącze do gnuplota
 * \param tab_dronów tablica wskaźników na obiekty klasy dron
 * \param siatka podłoże na którym ląduje dron
 * \param index_elementu_plasko index plaskowyzu
 * \param index_elementu_ostr index ostroslupa
 * \param index_elementu_skr index skarpy
 * \param index_drona index drona
 */
class Scena
{
    PzG::LaczeDoGNUPlota Lacze;
    std::list<std::shared_ptr<Graniastoslup>> Elementy_powierzchni;
    std::list<std::shared_ptr<dron>> Lst_dronow;
    Wektor3D siatka[ROZMIAR][ROZMIAR];
    int index_elementu_plasko;
    int index_elementu_ostr;
    int index_elementu_skr;
    int index_drona;

public:
    Scena();
    bool dzialanie();
    void stworz_siatka(std::string nazwa);
    PzG::LaczeDoGNUPlota pokaz_lacze();
};
/*!
 * \brief Metoda zwracająca łącze do gnuplota
 * \return Zwraca łącze.
 */
PzG::LaczeDoGNUPlota Scena::pokaz_lacze()
{
    return this->Lacze;
}

/*!
 * \brief Metoda tworząca podłoże na którym może wylądować dron
 * \param nazwa nazwa pliku do którego ma zostać wpisana siatka
 * \param StrmPlikowy strumień umożliwiający zapis do pliku
 * \param odstep odległość pomiędzy kratkami w siatce
 */
void Scena::stworz_siatka(std::string nazwa)
{
    std::fstream StrmPlikowy;
    double odstep = (ZAKRES + 50) / ROZMIAR;
    siatka[0][0] = POCZATEK;
    for (int i = 0; i < ROZMIAR; ++i)
    {
        if (i > 0)
        {
            siatka[i][0] = siatka[i - 1][0];
            siatka[i][0][1] += odstep;
        }
        for (int j = 1; j < ROZMIAR; ++j)
        {
            siatka[i][j] = siatka[i][j - 1];
            siatka[i][j][0] += odstep;
        }
    }

    StrmPlikowy.open(nazwa, std::ios::out);
    for (int i = 0; i < ROZMIAR; ++i)
    {
        for (int j = 0; j < ROZMIAR; ++j)
        {
            StrmPlikowy << siatka[i][j] << std::endl;
        }
        StrmPlikowy << std::endl;
    }
    StrmPlikowy << std::endl;
    for (int i = 0; i < ROZMIAR; ++i)
    {
        for (int j = 0; j < ROZMIAR; ++j)
        {
            StrmPlikowy << siatka[j][i] << std::endl;
        }
        StrmPlikowy << std::endl;
    }
    StrmPlikowy << std::endl;
    StrmPlikowy.close();
}
/*!
 * \brief Konstruktor bezparametryczny klasy scena
 * Konstruktor tworzący siatkę i dwa drony, inicjalizujący Lacze i ustawiający jego zakres.
 */
Scena::Scena()
{
    index_drona = 0;
    index_elementu_ostr = 0;
    index_elementu_plasko = 0;
    index_elementu_skr = 0;
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

    Lacze.UstawZakresX(0, ZAKRES);
    Lacze.UstawZakresY(0, ZAKRES);
    Lacze.UstawZakresZ(-200, ZAKRES);

    Lacze.UstawRotacjeXZ(60, 30);
    Lacze.UstawSkaleXZ(1, 1);

    stworz_siatka("../datasets/siatka.dat");
    Lacze.DodajNazwePliku("../datasets/siatka.dat");

    Wektor3D tmp = Wektor3D(POLOZENIE_4);
    Elementy_powierzchni.push_front(std::make_shared<Ostroslup>(tmp, 100, 50, 200, "../datasets/Elementy_powierzchni_ostr" + std::to_string(index_elementu_ostr) + ".dat"));
    index_elementu_ostr++;
    tmp = Wektor3D(POLOZENIE_5);
    Elementy_powierzchni.push_front(std::make_shared<Ostroslup>(tmp, 120, 60, 140, "../datasets/Elementy_powierzchni_ostr" + std::to_string(index_elementu_ostr) + ".dat"));
    index_elementu_ostr++;
    tmp = Wektor3D(POLOZENIE_6);
    Elementy_powierzchni.push_front(std::make_shared<Skarpa>(tmp, 65, 65, 180, "../datasets/Elementy_powierzchni_skr" + std::to_string(index_elementu_skr) + ".dat"));
    index_elementu_skr++;
    tmp = Wektor3D(POLOZENIE_3);
    Elementy_powierzchni.push_front(std::make_shared<Plaskowyz>(tmp, 70, 70, 60, "../datasets/Elementy_powierzchni_plasko" + std::to_string(index_elementu_plasko) + ".dat"));
    index_elementu_plasko++;

    for (std::list<std::shared_ptr<Graniastoslup>>::const_iterator i = Elementy_powierzchni.begin(); i != Elementy_powierzchni.end(); ++i)
    {
        (*i)->zapis();
        Lacze.DodajNazwePliku((*i)->pokaz_nazwa().c_str());
    }

    tmp = Wektor3D(POLOZENIE_1);
    Lst_dronow.push_front(std::make_shared<dron>(index_drona, Lacze, tmp));
    (*Lst_dronow.begin())->zapisz();
    index_drona++;

    tmp = Wektor3D(POLOZENIE_2);
    Lst_dronow.push_front(std::make_shared<dron>(index_drona, Lacze, tmp));
    (*Lst_dronow.begin())->zapisz();
    index_drona++;

    Lacze.Rysuj();
}
/*!
 * \brief Metoda dająca użytkowikowi dostęp.
 * Metoda sklejająca cały program umożliwiajaca sterowanie dronami i podejmowania akcji.
 * \param wybor wybór użytkownika
 */
bool Scena::dzialanie()
{
    int index = 0;
    char wybor;
    std::cout << "Aktualny dron to dron nr: " << index << std::endl;
    while (1)
    {
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Opcje: " << std::endl;
        std::cout << "o - obrot drona o zadany kat" << std::endl;
        std::cout << "t - translacja" << std::endl;
        std::cout << "w - wybor drona" << std::endl;
        std::cout << "x - usuń drona" << std::endl;
        std::cout << "m - wyswietl menu" << std::endl;
        std::cout << "r - wykonaj lot zwiadowczny" << std::endl;
        std::cout << "d - dodaj element powierzchni Tytana" << std::endl;
        std::cout << "u - usuń element powierzchni Tytana" << std::endl;
        std::cout << "k - koniec dzialania programu" << std::endl;
        std::cout << "Twoj wybor? (m - menu) > ";
        std::cin >> wybor;
        std::cout << "------------------------------------" << std::endl;
        if (wybor == 'w')
        {
            if ((int)Lst_dronow.size() == 0)
            {
                std::cout << "Brak dronów!!!" << std::endl;
            }
            else
            {
                std::cout << "Aktualny dron to dron nr: " << index << std::endl;
                std::list<std::shared_ptr<dron>>::const_iterator wsk_0;
                wsk_0 = Lst_dronow.begin();
                for (int i = 0; i < index; ++i)
                {
                    wsk_0++;
                }
                std::cout << "Jego współrzędne to: " << (*wsk_0)->pokaz_srodek() << std::endl;
                std::cout << "------------------------------------" << std::endl;
                while (1)
                {
                    int i = 0;
                    std::cout << "Wpisz nr drona aby go wybrać" << std::endl;
                    for (std::list<std::shared_ptr<dron>>::const_iterator j = Lst_dronow.begin(); j != Lst_dronow.end(); ++j)
                    {
                        std::cout << i << " - "
                                  << " współrzędne: " << (*j)->pokaz_srodek() << std::endl;
                        i++;
                    }
                    std::cin >> index;
                    if (std::cin.good())
                    {
                        if (index >= 0 && index < (int)Lst_dronow.size())
                        {
                            std::cout << "Udało się wybrać drona :)" << std::endl;
                            std::cout << "Aktualny dron to dron nr: " << index << std::endl;
                            break;
                        }
                        else
                        {
                            std::cout << "Nie udało się wybrać drona :(" << std::endl;
                            std::cout << "Wybierz jeszcze raz :(" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(1024, '\n');
                        }
                    }
                    else
                    {
                        std::cout << "Nie udało się wybrać drona :(" << std::endl;
                        std::cout << "Wybierz jeszcze raz :(" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1024, '\n');
                    }
                }
            }
        }
        else if (wybor == 'd')
        {
            int numer;
            std::cout << "Wybierz jaki element powierzchni chcesz dodać: " << std::endl;
            std::cout << "1 - Plaskowyż" << std::endl;
            std::cout << "2 - Ostrosłup (GóraZOstrymSzczytem)" << std::endl;
            std::cout << "3 - Skarpa" << std::endl;
            std::cout << "4 - Dron" << std::endl;
            while (1)
            {
                std::cout << "Wpisz 1, 2, 3 lub 4" << std::endl;
                std::cin >> numer;
                if (std::cin.good())
                {
                    if (numer == 1 || numer == 2 || numer == 3 || numer == 4)
                    {
                        double tab[3];
                        if (numer == 1)
                        {
                            std::cout << "Podaj wymiary Plaskowyżu" << std::endl;
                            std::cout << "Podaj skale wzdłóż osi x,y,z\nPodana skala będzie pomnożona razy 2" << std::endl;
                            while (1)
                            {
                                std::cin >> tab[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[2];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            std::cout << "Wybierz położenie środka Płaskowyżu\nx,y" << std::endl;
                            Wektor3D start;
                            double tab1[3];
                            while (1)
                            {
                                std::cin >> tab1[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab1[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            tab1[2] = 0;
                            start = Wektor3D({tab1[0], tab1[1], tab1[2]});

                            Elementy_powierzchni.push_front(std::make_shared<Plaskowyz>(start, tab[0], tab[1], tab[2], "../datasets/Elementy_powierzchni_plasko" + std::to_string(index_elementu_plasko) + ".dat"));
                            std::list<std::shared_ptr<Graniastoslup>>::const_iterator j = Elementy_powierzchni.begin();
                            (*j)->zapis();
                            Lacze.DodajNazwePliku((*j)->pokaz_nazwa().c_str());
                            index_elementu_plasko++;
                        }
                        else if (numer == 2)
                        {
                            std::cout << "Podaj wymiary Ostrosłupa" << std::endl;
                            std::cout << "Podaj skale wzdłóż osi x,y,z\nPodana skala będzie pomnożona razy 2" << std::endl;
                            while (1)
                            {
                                std::cin >> tab[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[2];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            std::cout << "Wybierz położenie środka Ostrosłupa\nx,y" << std::endl;
                            Wektor3D start;
                            double tab1[3];
                            while (1)
                            {
                                std::cin >> tab1[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab1[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            tab1[2] = 0;
                            start = Wektor3D({tab1[0], tab1[1], tab1[2]});

                            Elementy_powierzchni.push_front(std::make_shared<Ostroslup>(start, tab[0], tab[1], tab[2], "../datasets/Elementy_powierzchni_ostr" + std::to_string(index_elementu_ostr) + ".dat"));
                            std::list<std::shared_ptr<Graniastoslup>>::const_iterator j = Elementy_powierzchni.begin();
                            (*j)->zapis();
                            Lacze.DodajNazwePliku((*j)->pokaz_nazwa().c_str());
                            index_elementu_ostr++;
                        }
                        else if (numer == 3)
                        {
                            std::cout << "Podaj wymiary Skarpy" << std::endl;
                            std::cout << "Podaj skale wzdłóż osi x,y,z\nPodana skala będzie pomnożona razy 2" << std::endl;
                            while (1)
                            {
                                std::cin >> tab[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[2];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            std::cout << "Wybierz położenie środka Skarpy\nx,y" << std::endl;
                            Wektor3D start;
                            double tab1[3];
                            while (1)
                            {
                                std::cin >> tab1[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab1[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            tab1[2] = 0;
                            start = Wektor3D({tab1[0], tab1[1], tab1[2]});

                            Elementy_powierzchni.push_front(std::make_shared<Skarpa>(start, tab[0], tab[1], tab[2], "../datasets/Elementy_powierzchni_skr" + std::to_string(index_elementu_skr) + ".dat"));
                            std::list<std::shared_ptr<Graniastoslup>>::const_iterator j = Elementy_powierzchni.begin();
                            (*j)->zapis();
                            Lacze.DodajNazwePliku((*j)->pokaz_nazwa().c_str());
                            index_elementu_skr++;
                        }
                        else if (numer == 4)
                        {
                            double tab[3];
                            std::cout << "Wybierz miejsce startowe drona\nx,y" << std::endl;
                            while (1)
                            {
                                std::cin >> tab[0];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            while (1)
                            {
                                std::cin >> tab[1];
                                if (std::cin.good())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(1024, '\n');
                                }
                            }
                            tab[2] = 15;
                            Wektor3D start = Wektor3D({tab[0], tab[1], tab[2]});
                            Lst_dronow.push_front(std::make_shared<dron>(index_drona, Lacze, start));
                            (*Lst_dronow.begin())->zapisz();
                            index_drona++;
                        }
                        break;
                    }
                    else
                    {
                        std::cout << "Nie udało się wybrać elementu :(" << std::endl;
                        std::cout << "Wybierz jeszcze raz :(" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1024, '\n');
                    }
                }
                else
                {
                    std::cout << "Nie udało się wybrać elementu :(" << std::endl;
                    std::cout << "Wybierz jeszcze raz :(" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                }
            }
            Lacze.Rysuj();
        }
        else if (wybor == 'u')
        {
            if ((int)Elementy_powierzchni.size() == 0)
            {
                std::cout << "Nie można skasować, bo nie ma żadnych elementów powierzchni" << std::endl;
            }
            else
            {
                int i = 0;
                int nr;
                for (std::list<std::shared_ptr<Graniastoslup>>::const_iterator j = Elementy_powierzchni.begin(); j != Elementy_powierzchni.end(); ++j)
                {
                    std::cout << i << " - " << (*j)->pokaz_nazwa() << " współrzędne: " << (*j)->pokaz_srodek() << std::endl;
                    i++;
                }
                std::cout << "Podaj numer elementu, który chcesz usunąć" << std::endl;
                while (1)
                {
                    std::cin >> nr;
                    if (std::cin.good())
                    {
                        if (nr >= 0 && nr < (int)Elementy_powierzchni.size())
                        {
                            break;
                        }
                        else
                        {
                            std::cout << "Nie ma takiego numeru\nPodaj nr jeszcze raz" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1024, '\n');
                    }
                }
                std::list<std::shared_ptr<Graniastoslup>>::const_iterator j = Elementy_powierzchni.begin();
                for (int k = 0; k < nr; ++k)
                {
                    j++;
                }
                Lacze.UsunNazwePliku((*j)->pokaz_nazwa());
                if (remove((*j)->pokaz_nazwa().c_str()) == 0)
                {
                    std::cout << "Usunięto plik: " << (*j)->pokaz_nazwa() << std::endl;
                }
                else
                {
                    std::cout << "Nie skasowano pliku: " << (*j)->pokaz_nazwa() << std::endl;
                }
                Elementy_powierzchni.erase(j);
                Lacze.Rysuj();
            }
        }
        else if (wybor == 'x')
        {
            if ((int)Lst_dronow.size() == 0)
            {
                std::cout << "Nie można usunąć, bo nie ma żadnych dronów" << std::endl;
            }
            else
            {
                int i = 0;
                int nr;
                for (std::list<std::shared_ptr<dron>>::const_iterator j = Lst_dronow.begin(); j != Lst_dronow.end(); ++j)
                {
                    std::cout << i << " - "
                              << " współrzędne: " << (*j)->pokaz_srodek() << std::endl;
                    i++;
                }
                std::cout << "Podaj numer drona, którego chcesz usunąć" << std::endl;
                while (1)
                {
                    std::cin >> nr;
                    if (std::cin.good())
                    {
                        if (nr >= 0 && nr < (int)Lst_dronow.size())
                        {
                            break;
                        }
                        else
                        {
                            std::cout << "Nie ma takiego numeru\nPodaj nr jeszcze raz" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1024, '\n');
                    }
                }
                std::list<std::shared_ptr<dron>>::const_iterator j = Lst_dronow.begin();
                for (int k = 0; k < nr; ++k)
                {
                    j++;
                }
                (*j)->usun_drona();
                Lst_dronow.erase(j);
                Lacze.Rysuj();
            }
        }
        else if (wybor == 'k')
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
            std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;

            std::cout << "Do zobaczenia!!!" << std::endl;
            break;
        }
        else if (wybor == 'o' || wybor == 't' || wybor == 'r')
        {
            if ((int)Lst_dronow.size() == 0)
            {
                std::cout << "Brak dronów!!!" << std::endl;
            }
            else
            {
                std::list<std::shared_ptr<dron>>::const_iterator wsk_1;
                wsk_1 = Lst_dronow.begin();
                for (int i = 0; i < index; ++i)
                {
                    wsk_1++;
                }
                (*wsk_1)->akcja(wybor);
            }
        }
    }
    return false;
}
