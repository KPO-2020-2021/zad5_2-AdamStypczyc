#pragma once
#include <unistd.h>
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

/*!
 * \brief Klasa dron
 * Deklaracja klasy dron. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji dronie.
 * Zawiera ona elementy klasy prostopadloscian i gransiatoslup6.
 * \param sciezka zmienna odpowiadająca za wyświetlanie drogi przebytej przez protopadłościan
 * \param Lacze lacze do gnuplota
 * \param korpus_orginal prostopadloscian odpowiadajacy oryginalnemu korpusowi
 * \param korpus  prostopadloscian odpowiadajacy korpusowi na którym będziemy pracować
 * \param rotor_orginal tablica oryginalnych rotorów
 * \param rotor tablica rotorów na których będziemy pracować
 * \param obr macierz obrotu drona
 * \param droga wektor przesuniecia drona
 * \param kat kat położenia drona
 * \param index numer drona
 */
class dron
{
    std::vector<Wektor3D> sciezka;
    PzG::LaczeDoGNUPlota &Lacze;
    Prostopadloscian korpus_orginal;
    Prostopadloscian korpus;
    Graniastoslup6 rotor_orginal[4];
    Graniastoslup6 rotor[4];
    Macierz3x3 obr;
    Wektor3D droga;
    double kat;
    int index;

public:
    dron(int ind, PzG::LaczeDoGNUPlota &Lacze1, Wektor3D polozenie);

    void ruch_pionowy(double pion);
    void przesuniecie(double droga);

    void obrot(double kat_obrotu);
    void obrot_rotorow();

    void zapisz();
    void akcja(char wybor);
    void przypisz_sciezke(double droga);

    Wektor3D pokaz_srodek() const;
};
/*!
 * \brief Konstruktor parametryczny klasy dron.
 * Buduje drona i tworzy pliki w których będą zapisywanie punkty. Przypisuje dronowi jego index, tworzy Lacze oraz przestawia go o zadany wektor początkowy. 
 * \param ind zmienna odpowiadająca indeksowi
 * \param Lacze1 zmienna odpowiadająca laczy do gnuplota dzięki ktoremu tworzymy lacze
 * \param polozenie wektor o jaki zostanie przestawiony dron
 * \param wek wektor o który dodatkowo przesuwamy rotor aby nie był on częściowo zawarty w korpusie drona 
 */
dron::dron(int ind, PzG::LaczeDoGNUPlota &Lacze1, Wektor3D polozenie) : Lacze(Lacze1)
{
    Wektor3D wek = {0, 0, 7.5};
    kat = 0;
    this->index = ind;
    korpus_orginal.ustaw_nazwa("../datasets/korpus" + std::to_string(index) + ".dat");
    for (int i = 0; i < 4; ++i)
    {
        rotor_orginal[i].ustaw_nazwa("../datasets/rotor" + std::to_string(index) + std::to_string(i) + ".dat");
    }
    Lacze.DodajNazwePliku(korpus_orginal.pokaz_nazwa().c_str(), PzG::RR_Ciagly, 2);
    for (int i = 0; i < 4; ++i)
    {
        Lacze.DodajNazwePliku(rotor_orginal[i].pokaz_nazwa().c_str(), PzG::RR_Ciagly, 2);
    }
    korpus = korpus_orginal;

    korpus.translacja(polozenie);
    for (int i = 0; i < 4; ++i)
    {
        rotor[i] = rotor_orginal[i];
    }
    for (int i = 0; i < 4; ++i)
    {
        rotor[i].translacja(korpus_orginal[2 * i] + polozenie + wek);
    }
    this->droga = this->droga + polozenie;
}
/*!
 * \brief Metoda odpowiadająca za ruch pionowy
 * Przesuwa drona w górę o wartość podaną przez zmienną pion.
 * \param pion mówi o ile ma przesunąć drona
 * \param tmp Wektor3D pomocniczy
 */
void dron::ruch_pionowy(double pion)
{
    Wektor3D tmp;
    tmp[2] = pion;
    this->droga = this->droga + tmp;
    korpus.rotacja(this->obr);
    korpus.translacja(this->droga);
}
/*!
 * \brief Metoda odpowiadająca za przesuniecie drona w płaszczyźnie równoległej do płaszczyzny XY
 * Przesuwa drona w płaszczyźnie XY o wartość podaną przez zmienną droga.
 * \param droga mówi o ile ma przesunąć drona
 * \param tmp Wektor3D pomocniczy
 */
void dron::przesuniecie(double droga)
{
    Wektor3D tmp;
    tmp[0] = droga * cos(kat * M_PI / 180);
    tmp[1] = droga * sin(kat * M_PI / 180);
    this->droga = this->droga + tmp;
    korpus.rotacja(this->obr);
    korpus.translacja(this->droga);
}

/*!
 * \brief Metoda odpowiadająca za obrót drona
 * Obraca drona o zadany kąt.
 * \param kat_obrotu mówi o ile ma obrócić dron 
 * \param radian kąt wyrażony w radianach
 */
void dron::obrot(double kat_obrotu)
{
    this->kat = this->kat + kat_obrotu;
    double radian;
    radian = StopienNaRadianZ(this->kat);
    Oblicz_Macierz_ObrotuZ(radian, obr);
    korpus.rotacja(obr);
    korpus.translacja(this->droga);
}
/*!
 * \brief Metoda odpowidająca za obrót rotorów
 * \param tmp1 macierz przechowująca macierz obrotu
 * \param tmp macierz obracająca rotory 1 i 3
 * \param tmp_v2 macierz obracajaca rotory 0 i 2
 * \param wek wektor o który dodatkowo przesuwamy rotor aby nie "uderzał" on w korpus drona przy obracaniu
 */
void dron::obrot_rotorow()
{
    Wektor3D wek = {0, 0, 7.5};
    static int kat = 0;
    kat += 3;
    if (kat == 360)
    {
        kat = 0;
    }
    double tab[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Macierz3x3 tmp = Macierz3x3(tab);
    Macierz3x3 tmp_v2 = Macierz3x3(tab);
    Macierz3x3 tmp1;
    double radian;
    radian = StopienNaRadianZ(kat);
    Oblicz_Macierz_ObrotuZ(radian, tmp1);
    tmp = tmp * tmp1;
    Oblicz_Macierz_ObrotuZ(-radian, tmp1);
    tmp_v2 = tmp_v2 * tmp1;
    rotor[0].rotacja(tmp_v2);
    rotor[1].rotacja(tmp);
    rotor[2].rotacja(tmp_v2);
    rotor[3].rotacja(tmp);

    for (int i = 0; i < 4; ++i)
    {
        rotor[i].translacja(korpus[2 * i] + wek);
    }
}

/*!
 * \brief Metoda zapisujaca drona do plików
 */
void dron::zapisz()
{
    korpus.zapis();
    for (int i = 0; i < 4; ++i)
    {
        rotor[i].zapis();
    }
}
/*!
 * \brief Metoda odpowiadająca za porusanie się i animację drona.
 * \param wybor informacja jaką opcję wybrał użytkownik 
 * \param droga zmienna pomocnicza do której przypisywana jest droga
 * \param kat zmienna do której użytkownik przypisuje kąt obrotu
 */
void dron::akcja(char wybor)
{
    double droga;
    double kat;
    int licz = 0;
    ++licz;
    zapisz();
    switch (wybor)
    {
    case 'o':
        std::cout << "Podaj kąt o jaki ma się obrócić dron" << std::endl;
        while (1)
        {
            std::cin >> kat;
            if (std::cin.good())
            {
                std::cout << "Przypisano kąt :)" << std::endl;
                break;
            }
            else
            {
                std::cout << "Nieprzypisano kąta :(" << std::endl;
                std::cout << "Podaj kąt jeszcze raz :(" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
            }
        }
        if (kat < 0)
        {
            for (int i = 0; i > kat; --i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(-1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(15000);
            }
        }
        else
        {
            for (int i = 0; i < kat; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(15000);
            }
        }
        break;
    case 't':
        std::cout << "Podaj długość drogi" << std::endl;
        while (1)
        {
            std::cin >> droga;
            if (std::cin.good())
            {
                std::cout << "Przypisano długość drogi :)" << std::endl;
                break;
            }
            else
            {
                std::cout << "Nieprzypisano długości drogi :(" << std::endl;
                std::cout << "Podaj długość drogi jeszcze raz :(" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
            }
        }
        std::cout << "Podaj kąt o jaki ma się obrócić dron" << std::endl;
        while (1)
        {
            std::cin >> kat;
            if (std::cin.good())
            {
                std::cout << "Przypisano kąt :)" << std::endl;
                break;
            }
            else
            {
                std::cout << "Nieprzypisano kąta :(" << std::endl;
                std::cout << "Podaj kąt jeszcze raz :(" << std::endl;
                std::cin.clear();
                std::cin.ignore(1024, '\n');
            }
        }
        std::cout << "Ustawianie..." << std::endl;
        if (kat < 0)
        {
            for (int i = 0; i > kat; --i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(-1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(15000);
            }
        }
        else
        {
            for (int i = 0; i < kat; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(15000);
            }
        }
        przypisz_sciezke(droga);
        Lacze.DodajNazwePliku("../datasets/sciezka.dat", PzG::RR_Ciagly, 1);
        std::cout << "Wznoszenie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        std::cout << "Lot..." << std::endl;
        for (int i = 0; i < droga; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        std::cout << "Lądowanie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(-1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        Lacze.UsunOstatniaNazwe();
        Lacze.Rysuj();
        break;
    case 'r':
        std::cout << "Wznoszenie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        std::cout << "Lot..." << std::endl;
        for (int i = 0; i < 50; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        for (int i = 0; i < 90; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            obrot(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        for (int i = 0; i < 25; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        for (int j = 0; j < 7; ++j)
        {
            for (int i = 0; i < 45; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(15000);
            }
            for (int i = 0; i < 25; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                przesuniecie(2 * sin(M_PI / 4));
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(15000);
            }
        }
        for (int i = 0; i < 45; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            obrot(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        for (int i = 0; i < 25; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        for (int i = 0; i < 90; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            obrot(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        for (int i = 0; i < 50; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        std::cout << "Lądowanie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(-1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(15000);
        }
        Lacze.Rysuj();
        break;
    default:
        break;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
    std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

/*!
 * \brief Metoda odpowiadjąca za budowę ścieżki lotu drona
 * \param droga długość drogi
 */
void dron::przypisz_sciezke(double droga)
{
    sciezka.clear();
    Wektor3D next = korpus.pokaz_srodek();
    next[2] = 0;
    sciezka.push_back(next);
    next[2] = 400;
    sciezka.push_back(next);
    next[0] = next[0] + droga * cos(kat * M_PI / 180);
    next[1] = next[1] + droga * sin(kat * M_PI / 180);
    sciezka.push_back(next);
    next[2] = 0;
    sciezka.push_back(next);

    std::fstream StrmPlikowy;

    StrmPlikowy.open("../datasets/sciezka.dat", std::ios::out);
    for (int i = 0; i < (int)sciezka.size(); ++i)
    {
        StrmPlikowy << sciezka[i] << std::endl;
    }
    StrmPlikowy.close();
}
/*!
 * \brief Metoda zwracająca Wektor3D będący środkiem korpusu drona.
 */
Wektor3D dron::pokaz_srodek() const
{
    return korpus.pokaz_srodek();
}
