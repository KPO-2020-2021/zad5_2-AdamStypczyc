#pragma once
#include "Graniastoslup.hh"
/*!
 * \brief Klasa Prostopadloscian.
 * Deklaracja klasy prostopadłościan. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na prostopadłościanie, które są w większości dziedziczone z klasy Gransiatoslup.
 * Sama w sobie posiada swój konstruktor parametryczny
 */
class Prostopadloscian : public Graniastoslup
{
public:
    Prostopadloscian(Wektor3D sro = Wektor3D(), double h = 30, double w = 50, double d = 50, std::string nazwa = "../datasets/test_prosto.dat");
};
/*!
 * \brief Konstruktor parametryczny klasy prostopadłościan 
 * Tworzy prostopadłościan względem punktu srodka.
 * \param sro punkt odpowiadający srodkowi 
 * \param h wartość odpowiadająca wysokości korpusu prostopadłościanu, tutaj ustawiona na 30
 * \param w wartość odpowiadająca szerokości korpusu prostopadłościanu, tutaj ustawiona na 50
 * \param d wartość odpowiadająca głębokości korpusu prostopadłościanu, tutaj ustawiona na 50
 * \param nazwa nazwa pliku który przypisujemy danej bryle
 * \param tmp pomocznicy Wektor3D dzięki któremu wpisujemy wartosci współrzędnych
 */
Prostopadloscian::Prostopadloscian(Wektor3D sro, double h, double w, double d, std::string nazwa)
{
    Wektor3D proba = {w,d,h};
    wymiar = std::make_shared<Wektor3D>(proba);
    this->nazwa_pliku = nazwa;
    this->srodek = sro;
    Wektor3D tmp;
    /*    0________2
     *   /|        /|
     * 6/_|______4/ |
     * |  |      |  |
     * |  |   .ś |  |
     * |  |      |  |
     * |  |1_____|_3|
     * | /       | /
     * |/________|/
     * 7         5
     * 
     */
    tmp = {srodek[0] - (w / 2), srodek[1] + (d / 2), srodek[2] + (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] - (w / 2), srodek[1] + (d / 2), srodek[2] - (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] + (w / 2), srodek[1] + (d / 2), srodek[2] + (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] + (w / 2), srodek[1] + (d / 2), srodek[2] - (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] + (w / 2), srodek[1] - (d / 2), srodek[2] + (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] + (w / 2), srodek[1] - (d / 2), srodek[2] - (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] - (w / 2), srodek[1] - (d / 2), srodek[2] + (h / 2)};
    wspol.push_back(tmp);

    tmp = {srodek[0] - (w / 2), srodek[1] - (d / 2), srodek[2] - (h / 2)};
    wspol.push_back(tmp);
}
