#pragma once

#include "Prostopadloscian.hh"
#define SKALA 2

class Skarpa : public Graniastoslup
{
public:
    Skarpa(Wektor3D sro, double skala_x = 1, double skala_y = 1, double skala_z = 1, std::string nazwa = "../datasets/test_obiekt.dat");
};

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