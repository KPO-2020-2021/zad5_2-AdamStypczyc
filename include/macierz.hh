#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "wektor.hh"
#include "Wektor3D.hh"
/*!
* \brief Szablon macierzy.
* Szablon ten jest szablonem klasy macierz. Zawiera on elementy potrzebne do utworzenia macierzy oraz wykonywania na niej różnych operacji.
* Zawiera on tablicę o rozmiarach odopowiadających naszej macierzy oraz kąty potrzebne do obrotów 2D i 3D (kąty X, Y, Z).
* \param value tablica przechowująca wartości macierzy
*/

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
class Macierz
{

private:
    Templ_Typ value[Templ_Rozmiar][Templ_Rozmiar]; // Wartosci macierzy

public:
    Macierz(Templ_Typ tmp[Templ_Rozmiar][Templ_Rozmiar]);

    Macierz();

    Macierz operator+(Macierz tmp);
    Macierz operator-(Macierz tmp);
    Macierz operator*(Macierz tmp);
    Macierz operator*(double tmp);
    Wektor3D operator*(Wektor3D tmp);

    Templ_Typ &operator()(unsigned int row, unsigned int column);

    const Templ_Typ &operator()(unsigned int row, unsigned int column) const;

    bool operator==(const Macierz tmp) const;
};

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Konstruktor parametryczny klasy macierz.
 * Konstruktor ten nadaje wartości macierzy poprzez tablicę odpowiadającą jej wymiarom.
 * \param tmp tablica poprzez którą będziemy nadawać wartości macierzy 
 */
Macierz<Templ_Typ, Templ_Rozmiar>::Macierz(Templ_Typ tmp[Templ_Rozmiar][Templ_Rozmiar])
{
    for (unsigned int index = 0; index < Templ_Rozmiar; ++index)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            value[index][j] = tmp[index][j];
        }
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Konstruktor bezparametryczny klasy macierz.
 * Konstruktor wypełnia macierz zerami.
 */
Macierz<Templ_Typ, Templ_Rozmiar>::Macierz()
{
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            value[i][j] = 0;
        }
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora dodawania.
 * Przeciążenie operatora dodawania, aby umożliwić dodawanie dwóch macierzy.
 * \param tmp macierz odpowiadająca jednej z dodawanych macierzy.
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej dodawania.
 * \return Wynik dodawania w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator+(Macierz<Templ_Typ, Templ_Rozmiar> tmp)
{
    Macierz result = Macierz();
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora odejmowania.
 * Przeciążenie operatora odejmowania, aby umożliwić odejmowanie dwóch macierzy.
 * \param tmp macierz odpowiadająca jednej z odejmowanych macierzy.
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej odejmowania.
 * \return Wynik odejmowania w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator-(Macierz<Templ_Typ, Templ_Rozmiar> tmp)
{
    Macierz result = Macierz();
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            result(i, j) = this->value[i][j] - tmp(i, j);
        }
    }
    return result;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora mnożenia Macierz*Macierz.
 * Przeciążenie operatora mnożenia, aby umożliwić mnożenie dwóch macierzy.
 * \param tmp macierz odpowiadająca jednej z mnożonych macierzy.
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej mnożenia.
 * \return Wynik mnożenia w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator*(Macierz<Templ_Typ, Templ_Rozmiar> tmp)
{
    Macierz result = Macierz();
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            for (unsigned int k = 0; k < Templ_Rozmiar; ++k)
            {
                result(i, j) += this->value[i][k] * tmp(k, j);
            }
        }
    }
    return result;
}
template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora mnożenia Macierz*Wektor3D.
 * Przeciążenie operatora mnożenia, aby umożliwić mnożenie macierzy i wektora.
 * \param tmp Wektor3D 
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej mnożenia.
 * \return Wynik mnożenia w postaci macierzy result.
 */
Wektor3D Macierz<Templ_Typ, Templ_Rozmiar>::operator*(Wektor3D tmp)
{
    assert(Templ_Rozmiar == 3);
    Wektor3D result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result[i] += value[i][j] * tmp[j];
        }
    }

    return result;
}
template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora mnożenia Macierz*double.
 * Przeciążenie operatora mnożenia, aby umożliwić mnożenie macierzy i jakiejś wartości typu double.
 * \param tmp zmienna typu double 
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej mnożenia.
 * \return Wynik mnożenia w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator*(double tmp)
{
    Macierz result;
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            result(i, j) = this->value[i][j] * tmp;
        }
    }

    return result;
}
template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora () set.
 * Umożliwia zmienienie wartości konkretnego elementu macierzy.
 * \param row odpowiednik numeru wiersza.
 * \param column odpowiednik numeru kolumny
 * \return Zwraca wartość elementu, który nas interesuje.
 */
Templ_Typ &Macierz<Templ_Typ, Templ_Rozmiar>::operator()(unsigned int row, unsigned int column)
{
    if (row >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0);
    }

    if (column >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0);
    }
    return value[row][column];
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora () get.
 * Umożliwia podgląd wartości konkretnego elementu macierzy.
 * \param row odpowiednik numeru wiersza.
 * \param column odpowiednik numeru kolumny
 * \return Zwraca wartość elementu, który nas interesuje.
 */
const Templ_Typ &Macierz<Templ_Typ, Templ_Rozmiar>::operator()(unsigned int row, unsigned int column) const
{
    if (row >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora porównania dla macierzy.
 * Przeciążenie operatora porównania umożliwiające porównywanie dwóch macierzy, potrzebne przede wszystkim do testów.
 * \param tmp macierz odpowiadająca jednej z porównywanych macierzy
 * \param liczenie ilość "punktów" odpowiadających ilości zgadzających się elementów macierzy, powinna odpowiadać ilości elementów macierzy
 * \return Zwraca true albo false w zależności czy ilośc punktów odpowiada elementom macierzy. 
 */
bool Macierz<Templ_Typ, Templ_Rozmiar>::operator==(const Macierz<Templ_Typ, Templ_Rozmiar> tmp) const
{
    int liczenie = 0;
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            if (std::abs(value[i][j] - tmp(i, j)) <= MIN_DIFF)
            {
                ++liczenie;
            }
        }
    }
    if (liczenie == pow(Templ_Rozmiar, 2))
    {
        return true;
    }
    return false;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora strumieniowego in dla macierzy.
 * Umożliwia bezpośredie wczytanie macierzy.
 * \param in strumień wejściowy 
 * \param mat macierz odpowiadająca wczytywanej macierzy
 * \return Zwraca strumień wejściowy in. 
 */
std::istream &operator>>(std::istream &in, Macierz<Templ_Typ, Templ_Rozmiar> &mat)
{
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            in >> mat(i, j);
        }
    }
    return in;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora strumieniowego out dla macierzy.
 * Umożliwia bezpośredie wyświetlenie macierzy.
 * \param out strumień wyjściowy 
 * \param mat macierz odpowiadająca wyświetlaniej macierzy
 * \return Zwraca strumień wyjściowy out. 
 */
std::ostream &operator<<(std::ostream &out, Macierz<Templ_Typ, Templ_Rozmiar> const &mat)
{
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            out << "| " << mat(i, j) << " | ";
        }
        std::cout << std::endl;
    }
    return out;
}
#endif