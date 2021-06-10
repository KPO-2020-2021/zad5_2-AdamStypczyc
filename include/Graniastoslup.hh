#pragma once
#include "Macierz.hh"
#include "Wektor3D.hh"
#include <fstream>
#include <vector>
#include <memory>
/*!
 * \brief Klasa Graniastoslup.
 * Deklaracja klasy Graniastoslup. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na graniastoslupach, np. prostopadłościanie i graniastosłupie sześciokątnym foremnym.
 * Klasa Graniastoslup6 i klasa Prostopadloscian dziedziczą z tej klasy.
 * \param wspol deklaracja graniastoslupa jako wektory 3D. Wspol jest skrótem od współrzędna
 * \param wymiar przydatny do zapisywania środków podstaw bryły
 * \param srodek Wektor3D odpowiadający środkowi bryły
 * \param nazwa_pliku zmienna typu string w której przechowujemy nazwę pliku
 */
class Graniastoslup
{
protected:
    std::vector<Wektor3D> wspol;
    std::shared_ptr<Wektor3D> wymiar;
    Wektor3D srodek;
    std::string nazwa_pliku;

public:
    Wektor3D &operator[](int i);
    const Wektor3D operator[](int i) const;

    void ustaw_srodek(Wektor3D sro);
    void ustaw_nazwa(std::string nazwa);
    Wektor3D pokaz_srodek() const;
    std::string pokaz_nazwa() const;

    void translacja(Wektor3D translacja);
    void rotacja(Macierz3x3 obrot);

    void zapis();
};
/*!
 * \brief Przeciążenie operatora [] set.
 * Umożliwia zmianę wartości poszczególnej wszpółrzędnej graniastoslupa.
 * \return Zwraca wektor3D odpowiadający interesującej nas współrzędnej.
 */
Wektor3D &Graniastoslup::operator[](int i)
{
    return wspol[i];
}
/*!
 * \brief Przeciążenie operatora [] get.
 * Umożliwia podgląd wartości poszczególnej wszpółrzędnej graniastoslupa.
 * \return Zwraca wektor3D odpowiadający interesującej nas współrzędnej.
 */
const Wektor3D Graniastoslup::operator[](int i) const
{
    return wspol[i];
}
/*!
 * \brief Metoda ustawiająca wartość środka
 * Umożliwia przypisanie Wektora3D środkowi bryły
 * \param sro Wektor3D który przypisujemy środkowi
 */
void Graniastoslup::ustaw_srodek(Wektor3D sro)
{
    srodek = sro;
}
/*!
 * \brief Metoda ustawiająca nazwę pliku
 * Umożliwia przypisanie nazwy pliku
 * \param nazwa nazwa pliku który chcemy przypisać 
 */
void Graniastoslup::ustaw_nazwa(std::string nazwa)
{
    nazwa_pliku = nazwa;
}
/*!
 * \brief Metoda pokazująca wartość środka
 * Umożliwia podgląd wartości środka.
 * \return Zwraca wektor3D środkowi.
 */
Wektor3D Graniastoslup::pokaz_srodek() const
{
    return srodek;
}
/*!
 * \brief Metoda pokazująca nazwę pliku
 * Umożliwia podgląd nazwy pliku.
 * \return Zwraca string odpowiadający nazwie pliku.
 */
std::string Graniastoslup::pokaz_nazwa() const
{
    return nazwa_pliku;
}

/*!
 * \brief Metoda przesuwająca graniastoslup o zadany wektor3D
 * \param translacja Wektor3D odpowiadający przesunięciu
 */
void Graniastoslup::translacja(Wektor3D translacja)
{
    for (int i = 0; i < (int)wspol.size(); ++i)
    {
        wspol[i] = wspol[i] + translacja;
    }
    srodek = srodek + translacja;
}

/*!
 * \brief Metoda obracająca graniastoslup o zadaną Macierz3x3
 * \param obrot Macierz3x3 odpowiadająca obrotowi
 */
void Graniastoslup::rotacja(Macierz3x3 obrot)
{
    for (int i = 0; i < (int)wspol.size(); ++i)
    {
        wspol[i] = obrot * wspol[i];
    }
    srodek = obrot * srodek;
}

/*!
 * \brief Metoda zapisująca graniastoslup do pliku
 * \param StrmPlikowy strumień dzięki któremy zapiszemy współrzędne punktów do pliku
 * \param translacja_srodka Wektor3D który przesuwa środek bryły do góry i na dół żeby odpowiadały środkowi górnej i środkowi dolnej podstawy
 */
void Graniastoslup::zapis()
{
    std::fstream StrmPlikowy;
    Wektor3D translacja_srodka = {0, 0, (*wymiar)[2] / 2};

    StrmPlikowy.open(nazwa_pliku, std::ios::out);

    for (int i = 0; i < (int)wspol.size(); i += 2)
    {
        StrmPlikowy << srodek + translacja_srodka << std::endl;
        for (int j = 0; j < 2; ++j)
        {
            StrmPlikowy << wspol[j + i] << std::endl;
        }
        StrmPlikowy << srodek - translacja_srodka << std::endl
                    << std::endl;
    }

    StrmPlikowy << srodek + translacja_srodka << std::endl;
    StrmPlikowy << wspol[0] << std::endl;
    StrmPlikowy << wspol[1] << std::endl;
    StrmPlikowy << srodek - translacja_srodka << std::endl
                << std::endl;

    StrmPlikowy.close();
}
