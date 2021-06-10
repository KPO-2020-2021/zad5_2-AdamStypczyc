#pragma once

#include "Prostopadloscian.hh"
#define SKALA 2

class Skarpa : public Graniastoslup
{
public:
    Skarpa(Wektor3D sro, double skala_x = 1, double skala_y = 1, double skala_z = 1, std::string nazwa = "../datasets/test_obiekt.dat");
    Skarpa(Skarpa &Skr);
};

Skarpa::Skarpa(Wektor3D sro, double skala_x = 1, double skala_y = 1, double skala_z = 1, std::string nazwa = "../datasets/test_obiekt.dat")
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

    for (int i = 0; i < 8; ++i)
    {
        tmp = Prosto[i];
        wspol.push_back(tmp);
    }

    wspol[0]=wspol[3];
    wspol[6]=wspol[5];
}
Skarpa::Skarpa(Skarpa &Skr)
{
    wymiar = Skr.wymiar;
    wspol = Skr.wspol;
    srodek = Skr.srodek;
    nazwa_pliku = Skr.nazwa_pliku;
}