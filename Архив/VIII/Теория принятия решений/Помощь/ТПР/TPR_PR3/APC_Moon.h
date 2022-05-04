//------------------------------------------------------------------------------
//
// APC_Moon.h
// 
// Purpose:
//
//    Computation of the Moon's position
//
// Notes:
//
//   This software is protected by national and international copyright. 
//   Any unauthorized use, reproduction or modificaton is unlawful and 
//   will be prosecuted. Commercial and non-private application of the 
//   software in any form is strictly prohibited unless otherwise granted
//   by the authors.
//   
// (c) 1999 Oliver Montenbruck, Thomas Pfleger
//
//------------------------------------------------------------------------------

#ifndef INC_APC_MOON_H
#define INC_APC_MOON_H


#include "APC_VecMat3D.h"


//------------------------------------------------------------------------------
//
// MoonPos: Computes the Moon's ecliptic position using Brown's theory
//          (Improved Lunar Ephemeris)
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// <return>:   Geocentric position of the Moon (in [km]) referred to the
//             ecliptic and equinox of date
//
// Notes: Light-time is already taken into account
//
//------------------------------------------------------------------------------
Vec3D MoonPos (double T);


//------------------------------------------------------------------------------
//
// MoonEqu: Computes the Moon's equatorial position using Brown's theory
//          (Improved Lunar Ephemeris)
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// <return>:   Geocentric equatorial position of the Moon 
//             (RA and declination in [rad], distance in [km])
//
// Notes: Light-time is already taken into account
//
//------------------------------------------------------------------------------
Vec3D MoonEqu (double T);


//------------------------------------------------------------------------------
//
// MiniMoon: Computes the Moon's RA and declination using a low precision 
//           analytical series
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// Output:
//
//   RA        Right Ascension of the Moon in [rad]
//   Dec       Declination of the Moon in [rad]
//
//------------------------------------------------------------------------------
void MiniMoon (double T, double& RA, double& Dec);


#endif   // include blocker
