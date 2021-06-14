#ifndef WEKTOR_HH
#define WEKTOR_HH
#include <iostream>
#include <cassert>
#include <initializer_list>
#define MIN_DIFF 0.0000000001

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Szablon wektora.
 * Szablon ten jest szablonem klasy Wektor. Zawiera on elementy potrzebne do utworzenia wektora oraz wykonywania na nim różnych operacji.
 * Zawiera on tablicę o rozmiarach odopowiadających naszemu wektorowi.
 * \param wektorek tablica w której będą zapisywane wartości wektora
 * \param ilosc_stworzonych zmienna dzięki której jest możliwe zliczanie ile wektorów stworzyliśmy
 * \param ilosc_tymczasowych zmienna dzięki której jest możliwe zliczanie ile wektorów aktualnie istnieje
 */
class Wektor
{
    Templ_Typ_Wektor wektorek[Templ_Rozmiar_Wektor];

public:
    static int ilosc_stworzonych, ilosc_tymczasowych;
    Wektor();
    constexpr Wektor(const Wektor &vector);
    ~Wektor();
    Wektor(const std::initializer_list<Templ_Typ_Wektor> &ListaWsp);
    /*!
 * \brief Przeciążenie operatora [] get.
 * Umożliwia podgląd wartości konkretnego elementu wektora.
 * \param Index Indeks interesującej nas wartości wektora.
 * \return Zwraca wartość elementu, który nas interesuje.
 */
    Templ_Typ_Wektor operator[](unsigned int Index) const
    {
        assert(Index < Templ_Rozmiar_Wektor);
        return wektorek[Index];
    }
    /*!
 * \brief Przeciążenie operatora [] set.
 * Umożliwia zmienienie wartości konkretnego elementu wektora.
 * \param Index Indeks interesującej nas wartości wektora.
 * \return Zwraca wartość elementu, który nas interesuje.
 */
    Templ_Typ_Wektor &operator[](unsigned int Index)
    {
        assert(Index < Templ_Rozmiar_Wektor);
        return wektorek[Index];
    }

    Wektor operator+(const Wektor &v);

    Wektor operator-(const Wektor &v);

    Wektor operator*(const Templ_Typ_Wektor &tmp);

    Wektor operator/(const Templ_Typ_Wektor &tmp);

    bool operator==(const Wektor V) const;

    Wektor &operator=(const Wektor &v);
};

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przypisanie wartości początkowej zmiennej ilosc_stworzonych
 */
int Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::ilosc_stworzonych = 0;
template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przypisanie wartości początkowej zmiennej ilosc_tymczasowych
 */
int Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::ilosc_tymczasowych = 0;

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Konstruktor bezparametryczny klasy wektor.
 * Przypisuje wszystkim elementom tablicy wektorek 0.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::Wektor()
{
    ilosc_stworzonych++;
    ilosc_tymczasowych++;
    for (Templ_Typ_Wektor &wektork_i : wektorek)
    {
        wektork_i = 0;
    }
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Konstruktor kopiujący klasy wektor.
 * Przypisuje elementom klasy wektor wartość innego elementu tej samej klasy.
 */
constexpr Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::Wektor(const Wektor &vector)
{
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        wektorek[i] = vector.wektorek[i];
    }
    ilosc_tymczasowych++;
}
template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Destruktor klasy wektor.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::~Wektor()
{
    ilosc_tymczasowych--;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Konstruktor parametryczny klasy wektor.
 * Przypisuje wszystkim elementom tablicy wektorek odpowiednie wartości podane w liście.
 * \param ListaWsp lista z wartościami, które mają być przypisane do wektora.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::Wektor(const std::initializer_list<Templ_Typ_Wektor> &ListaWsp) : Wektor()
{
    assert(ListaWsp.size() <= Templ_Rozmiar_Wektor);
    int index = -1;
    for (double wartosc_i : ListaWsp)
    {
        wektorek[++index] = wartosc_i;
    }
    ilosc_stworzonych++;
    ilosc_tymczasowych++;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora dodawania dla wektora.
 * Przeciążenie umożliwiające dodawanie dwóch wektorów do siebie.
 * \param v wektor odpowiadający jednemu z dodawanych wektorów
 * \param result nowopowstały wektor będący wynikiem dodawania
 * \return Zwraca wektor result.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::operator+(const Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> &v)
{
    Wektor result;
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        result[i] = wektorek[i] + v[i];
    }
    return result;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora odejmowania dla wektora.
 * Przeciążenie umożliwiające odejmowanie dwóch wektorów od siebie.
 * \param v wektor odpowiadający jednemu z odejmowanych wektorów
 * \param result nowopowstały wektor będący wynikiem odejmowania
 * \return Zwraca wektor result.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::operator-(const Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> &v)
{
    Wektor result;
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        result[i] = wektorek[i] - v[i];
    }
    return result;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora mnożenia dla wektora.
 * Przeciążenie umożliwiające mnożenie wektora razy wartość typu odpowiadającego typowi teblicy wektorek.
 * \param tmp wartość razy która mnożymy
 * \param result nowopowstały wektor będący wynikiem mnożenia
 * \return Zwraca wektor result.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::operator*(const Templ_Typ_Wektor &tmp)
{
    Wektor result;
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        result[i] = wektorek[i] *= tmp;
    }
    return result;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora dzielenia dla wektora.
 * Przeciążenie umożliwiające dzielenie wektora przez wartość typu odpowiadającego typowi teblicy wektorek.
 * \param tmp wartość przez którą mnożymy
 * \param result nowopowstały wektor będący wynikiem dzielenia
 * \return Zwraca wektor result.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::operator/(const Templ_Typ_Wektor &tmp)
{
    Wektor result;
    if (tmp == 0)
    {
        throw "Pamiętaj cho...o nie dziel przez zero";
    }
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        result[i] = wektorek[i] /= tmp;
    }
    return result;
}
template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora przypisanie dla wektora.
 * Przeciążenie umożliwiające przypisanie wektora do innego wektora.
 * \param v wektor którego wartości chcemy przypisać
 * \return Zwraca wektor wartość *this.
 */
Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> &Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::operator=(const Wektor &v)
{
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        wektorek[i] = v.wektorek[i];
    }
    return *this;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora porównania dla wektora.
 * Przeciążenie operatora porównania umożliwiające porównywanie dwóch wektorów, potrzebne przede wszystkim do testów.
 * \param V wektor odpowiadający jednemu z porównywanych wektorów
 * \param liczenie ilość "punktów" odpowiadających ilości zgadzających się elementów wektora, powinna odpowiadać ilości elementów wektora
 * \return Zwraca true albo false w zależności czy ilośc punktów odpowiada elementom wektora. 
 */
bool Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor>::operator==(const Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> V) const
{
    int liczenie = 0;
    for (unsigned int i = 0; i < Templ_Rozmiar_Wektor; ++i)
    {
        if (std::abs(wektorek[i] - V[i]) <= MIN_DIFF)
        {
            ++liczenie;
        }
    }
    if (liczenie == Templ_Rozmiar_Wektor)
    {
        return true;
    }
    return false;
}
template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora strumieniowego out dla wektora.
 * Umożliwia bezpośrednie wyświetlenie wektora.
 * \param out strumień wyjściowy 
 * \param tmp wektor odpowiadający wyświetlanemu wektorowi
 * \return Zwraca strumień wejściowy out. 
 */
std::ostream &operator<<(std::ostream &out, Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> const &tmp)
{
    for (unsigned int Index = 0; Index < Templ_Rozmiar_Wektor; ++Index)
    {
        if (Index != Templ_Rozmiar_Wektor - 1)
        {
            out << tmp[Index] << " ";
        }
        else
        {
            out << tmp[Index];
        }
    }
    return out;
}

template <typename Templ_Typ_Wektor, unsigned int Templ_Rozmiar_Wektor>
/*!
 * \brief Przeciążenie operatora strumieniowego in dla wektora.
 * Umożliwia bezpośredie wczytanie wektora
 * \param in strumień wejściowy 
 * \param tmp wektor odpowiadający wczytywanemu wektorowi
 * \return Zwraca strumień wejściowy in. 
 */
std::istream &operator>>(std::istream &in, Wektor<Templ_Typ_Wektor, Templ_Rozmiar_Wektor> &tmp)
{
    for (unsigned int index = 0; index < Templ_Rozmiar_Wektor; ++index)
    {
        in >> tmp[index];
    }
    std::cout << std::endl;
    return in;
}
#endif