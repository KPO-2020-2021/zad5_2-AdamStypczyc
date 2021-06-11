#pragma once

#include "Prostopadloscian.hh"
#define SKALA 2

class Ostroslup : public Graniastoslup
{
public:
    Ostroslup(Wektor3D sro, double skala_x = 1, double skala_y = 1, double skala_z = 1, std::string nazwa = "../datasets/test_obiekt.dat");
    Ostroslup(Ostroslup &Ostr);
};

Ostroslup::Ostroslup(Wektor3D sro, double skala_x, double skala_y, double skala_z, std::string nazwa)
{
    double w, d, h;
    w = SKALA * skala_x;
    d = SKALA * skala_y;
    h = SKALA * skala_z;
    wymiar = std::make_shared<Wektor3D>(w, d, h);
    nazwa_pliku = nazwa;
    srodek = sro;
    Wektor3D tmp;
    Prostopadloscian Prosto = Prostopadloscian({0, 0, 0}, h, w, d);

    for (int i = 1; i < 8; i += 2)
    {
        tmp = srodek;
        tmp[2] += h / 2;
        wspol.push_back(tmp);

        tmp = Prosto[i];
        wspol.push_back(tmp);
    }
}
Ostroslup::Ostroslup(Ostroslup &Ostr)
{
    wymiar = Ostr.wymiar;
    wspol = Ostr.wspol;
    srodek = Ostr.srodek;
    nazwa_pliku = Ostr.nazwa_pliku;
}
