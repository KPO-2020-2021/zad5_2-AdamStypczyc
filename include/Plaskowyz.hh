#pragma once

#include "Prostopadloscian.hh"
#define SKALA 2

class Plaskowyz : public Graniastoslup
{
public:
    Plaskowyz(Wektor3D sro, double skala_x = 1, double skala_y = 1, double skala_z = 1, std::string nazwa = "../datasets/test_obiekt.dat");
    Plaskowyz(Plaskowyz &Plas);
};
Plaskowyz::Plaskowyz(Wektor3D sro, double skala_x, double skala_y, double skala_z, std::string nazwa)
{
    double w, d, h;
    w = SKALA * skala_x;
    d = SKALA * skala_y;
    h = SKALA * skala_z;
    Wektor3D proba = {w,d,h};
    wymiar = std::make_shared<Wektor3D>(proba);
    nazwa_pliku = nazwa;
    srodek = sro;
    Wektor3D tmp;

    Prostopadloscian Prosto = Prostopadloscian({0, 0, 0}, h, w, d);
    for (int i = 0; i < 8; ++i)
    {
        tmp = Prosto[i];
        wspol.push_back(tmp);
    }
}
Plaskowyz::Plaskowyz(Plaskowyz &Plas)
{
    wymiar = Plas.wymiar;
    wspol = Plas.wspol;
    srodek = Plas.srodek;
    nazwa_pliku = Plas.nazwa_pliku;
}