#pragma once
#include "Graniastoslup.hh"
/*!
 * \brief Klasa Graniastoslup6.
 * Deklaracja klasy Graniastoslup6. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na Graniastoslup6, które są w większości dziedziczone z klasy Gransiatoslup.
 * Sama w sobie posiada swój konstruktor parametryczny.
 */
class Graniastoslup6 : public Graniastoslup
{
public:
    Graniastoslup6(Wektor3D sro = Wektor3D(), double h = 15, double r = 20, std::string nazwa = "../datasets/test_gr.dat");
};
/*!
 * \brief Konstruktor parametryczny klasy Graniastoslup6 
 * Tworzy Graniastoslup6 względem punktu srodka.
 * \param sro punkt odpowiadający srodkowi 
 * \param h wartość odpowiadająca wysokości rotora, tutaj ustawiona na 15
 * \param r promień okręgu na którym zbudowane są podstawy górne i dolna rotora tutaj ustawiona na 20
 * \param nazwa nazwa pliku który przypisujemy danej bryle
 * \param tmp pomocznicy Wektor3D dzięki któremu wpisujemy wartosci współrzędnych
 */
Graniastoslup6::Graniastoslup6(Wektor3D sro, double h, double r, std::string nazwa)
{
    double radian = 60 * M_PI / 180;
    Wektor3D proba = {0,0,h};
    wymiar = std::make_shared<Wektor3D>(proba);
    this->nazwa_pliku = nazwa;
    this->srodek = sro;
    Wektor3D tmp;
    for (int i = 0; i < 6; ++i)
    {
        tmp = {r * cos(i * radian), r * sin(i * radian), srodek[2] + (h / 2)};
        wspol.push_back(tmp);
        tmp = {r * cos(i * radian), r * sin(i * radian), srodek[2] - (h / 2)};
        wspol.push_back(tmp);
    }
}