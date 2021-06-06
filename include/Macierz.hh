#pragma once

#include "macierz.hh"
#include "size.hh"
/*!
 * \brief Deklaracja Macierzy3x3
 * Deklaracja macierzy 3D.
 */
typedef Macierz<double, 3> Macierz3x3;
/*!
 * \brief Zamaina stopni na radian 3D wokół OX.
 * Funkcja zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 3D wokół osi OX.  
 */
double StopienNaRadianX(double kat_stopnieX)
{
    double kat_radianX;
    kat_radianX = kat_stopnieX * M_PI / 180;
    return kat_radianX;
}
/*!
 * \brief Zamaina stopni na radian 3D wokół OY.
 * Funkcja zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 3D wokół osi OY.  
 */
double StopienNaRadianY(double kat_stopnieY)
{
    double kat_radianY;
    kat_radianY = kat_stopnieY * M_PI / 180;
    return kat_radianY;
}
/*!
 * \brief Zamaina stopni na radian 3D wokół OZ.
 * Funkcja zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 3D wokół osi OZ.  
 */
double StopienNaRadianZ(double kat_stopnieZ)
{
    double kat_radianZ;
    kat_radianZ = kat_stopnieZ * M_PI / 180;
    return kat_radianZ;
}

/*!
 * \brief Funkcja obliczająca macierz obrotu 3D OX.
 * Funkcja umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 3D wokół osi OX. 
 */
void Oblicz_Macierz_ObrotuX(double kat_radianX, Macierz3x3 &Mac)
{
    Mac(0,0) = 1;
    Mac(0,1) = 0;
    Mac(0,2) = 0;
    Mac(1,0) = 0;
    Mac(1,1) = cos(kat_radianX);
    Mac(1,2) = -sin(kat_radianX);
    Mac(2,0) = 0;
    Mac(2,1) = sin(kat_radianX);
    Mac(2,2) = cos(kat_radianX);
}
/*!
 * \brief Funkcja obliczająca macierz obrotu 3D OY.
 * Funkcja umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 3D wokół osi OY. 
 */
void Oblicz_Macierz_ObrotuY(double kat_radianY, Macierz3x3 &Mac)
{
    Mac(0,0) = cos(kat_radianY);
    Mac(0,1) = 0;
    Mac(0,2) = sin(kat_radianY);
    Mac(1,0) = 0;
    Mac(1,1) = 1;
    Mac(1,2) = 0;
    Mac(2,0) = -sin(kat_radianY);
    Mac(2,1) = 0;
    Mac(2,2) = cos(kat_radianY);
}
/*!
 * \brief Funkcja obliczająca macierz obrotu 3D OZ.
 * Funkcja umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 3D wokół osi OZ. 
 */
void Oblicz_Macierz_ObrotuZ(double kat_radianZ, Macierz3x3 &Mac)
{
    Mac(0,0) = cos(kat_radianZ);
    Mac(0,1) = -sin(kat_radianZ);
    Mac(0,2) = 0;
    Mac(1,0) = sin(kat_radianZ);
    Mac(1,1) = cos(kat_radianZ);
    Mac(1,2) = 0;
    Mac(2,0) = 0;
    Mac(2,1) = 0;
    Mac(2,2) = 1;
}
