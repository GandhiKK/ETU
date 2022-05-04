//------------------------------------------------------------------------------
//
// APC_Sun.h
// 
// Purpose:
//
//    Computation of the Sun's position
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

#ifndef INC_APC_SUN_H
#define INC_APC_SUN_H


#include "APC_VecMat3D.h"


//------------------------------------------------------------------------------
//
// SunPos: Computes the Sun's ecliptical position using analytical series
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// <return>:   Geocentric position of the Sun (in [AU]), referred to the
//             ecliptic and equinox of date
//
//------------------------------------------------------------------------------
Vec3D SunPos (double T);


//------------------------------------------------------------------------------
//
// SunEqu: Computes the Sun's equatorial position using analytical series
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// <return>:   Geocentric position of the Sun (in [AU]), referred to the
//             equator and equinox of date
//
//------------------------------------------------------------------------------
Vec3D SunEqu (double T);


//------------------------------------------------------------------------------
//
// MiniSun: Computes the Sun's RA and declination using a low precision 
//           analytical series
//
// Input:
//
//   T         Time in Julian centuries since J2000
//
// Output:
//
//   RA        Right Ascension of the Sun in [rad]
//   Dec       Declination of the Sun in [rad]
//
//------------------------------------------------------------------------------
void MiniSun (double T, double& RA, double& Dec);


#endif  // include blocker
