#pragma once

#include "Prostopadloscian.hh"
#define SKALA 2

/*!
 * \brief Klasa Skarpa.
 * Deklaracja klasy Skarpa. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na Skarpa, które są w większości dziedziczone z klasy Gransiatoslup.
 * Sama w sobie posiada swój konstruktor parametryczny.
 */
class Skarpa : public Graniastoslup
{
public:
    Skarpa(Wektor3D sro, double skala_x = 1, double skala_y = 1, double skala_z = 1, std::string nazwa = "../datasets/test_obiekt.dat");
};

/*!
 * \brief Konstruktor parametryczny klasy Skarpa 
 * Tworzy Skarpa względem punktu srodka.
 * \param sro punkt odpowiadający srodkowi 
 * \param skala_x wartość o jaką zostanie przemnożona szerokość
 * \param skala_y wartość o jaką zostanie przemnożony głębokość
 * \param skala_z wartość o jaką zostanie przemnożony wysokość
 * \param nazwa nazwa pliku który przypisujemy danej bryle
 * \param tmp pomocznicy Wektor3D dzięki któremu wpisujemy wartosci współrzędnych
 * \param proba również pomocniczy Wektor3D
 * \param w szerokość
 * \param d głębokość
 * \param h wysokosć
 */
Skarpa::Skarpa(Wektor3D sro, double skala_x, double skala_y, double skala_z, std::string nazwa)
{
    double w, d, h;
    w = SKALA * skala_x;
    d = SKALA * skala_y;
    h = SKALA * skala_z;

    Wektor3D proba = {w, d, h};
    wymiar = std::make_shared<Wektor3D>(proba);
    nazwa_pliku = nazwa;
    sro[2] += skala_z;
    srodek = sro;
    srodek[0] += skala_x;
    srodek[1] += skala_y;
    Wektor3D tmp;

    Prostopadloscian Prosto = Prostopadloscian(sro, h, w, d);

    for (int i = 0; i < 8; ++i)
    {
        if (i == 6)
        {
            tmp = Prosto[7];
            wspol.push_back(tmp);
        }
        else if (i == 4)
        {
            tmp = Prosto[5];
            wspol.push_back(tmp);
        }
        else
        {
            tmp = Prosto[i];
            wspol.push_back(tmp);
        }
    }
}