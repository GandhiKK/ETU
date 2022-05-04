//------------------------------------------------------------------------------
//
// File:    Coco.cpp
//
// Purpose: Coordinate transformations
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

#include <iomanip>
#include <iostream>

#include "APC_Const.h"
#include "APC_Math.h"
#include "APC_PrecNut.h"
#include "APC_Spheric.h"
#include "APC_Sun.h"
#include "APC_Time.h"
#include "APC_VecMat3D.h"

#ifdef __GNUC__   // GNU C++ Adaptations
#include <ctype.h>
#include "GNU_iomanip.h"
#endif

using namespace std;


//
// Types
//
enum enOrigin   { Heliocentric, Geocentric };  // Origin of coordinates
enum enRefSys   { Ecliptic, Equator };         // Reference system
  

//
// Definition of class "Position"
//
class Position
{
  public:

    void Input(); // Query user for parameters
    void SetOrigin(enOrigin Origin);
    void SetRefSys(enRefSys RefSys);
    void SetEquinox(double T_Equinox);
    void Print();

  private:

    Vec3D      m_R;          // Coordinate vector
    enOrigin   m_Origin;     // Origin of coordinate system
    enRefSys   m_RefSys;     // Reference system
    double     m_TEquinox;   // Equinox (cent. since J2000)
    double     m_MjdEpoch;   // Epoch (Modif. Julian Date)
};


//
// Data input
//
void Position::Input()
{
  //
  // Variables
  //
  char c;

  
  // Header
  cout << endl << "New input:" << endl << endl;

  
  // Query reference system
  while (true) {

    cout << "  Reference system (e=ecliptic,a=equator) ... ";
    cin >> c; cin.ignore(81,'\n'); c = tolower(c);
    
    if (c=='e') { m_RefSys=Ecliptic; break; };
    if (c=='a') { m_RefSys=Equator;  break; };
  }
  
  
  // Query coordinates
  while (true) {
    
    cout << "  Format (c=cartesian,p=polar)            ... ";
    cin >> c; cin.ignore(81,'\n'); c = tolower(c);
  
    if (c=='c') { 
      double x,y,z;
      cout << "  Coordinates (x y z)                     ... ";
      cin >> x >> y >> z; 
      m_R = Vec3D(x,y,z);
      break;
    };
  
    if (c=='p') { 
    
      if (m_RefSys==Ecliptic) {

        int     d,m;
        double  s, L,B,R;
        cout << "  Coordinates (L [o ' \"] B[o ' \"] R)     ... ";
        cin >> d >> m >> s; L=Rad*Ddd(d,m,s);
        cin >> d >> m >> s; B=Rad*Ddd(d,m,s);
        cin >> R; cin.ignore(81,'\n');
        m_R = Vec3D(Polar(L,B,R));
      }
      
      else {
        
        int     d,m;
        double  s, RA,Dec,R;
        cout << "  Coordinates (RA [h m s] Dec [o ' \"] R)  ... ";
        cin >> d >> m >> s; RA=15.0*Rad*Ddd(d,m,s);
        cin >> d >> m >> s; Dec=Rad*Ddd(d,m,s);
        cin >> R; cin.ignore(81,'\n');
        m_R = Vec3D(Polar(RA,Dec,R));
      };
      
      break; 
    
    };
  
  }

  
  // Query equinox 
  double Year;
  
  cout << "  Equinox (yyyy.y)                        ... ";
  cin >> Year; cin.ignore(81,'\n');
  
  m_TEquinox = (Year-2000.0)/100.0;
  
  
  // Query origin
  while (true) {
  
    cout << "  Origin (h=heliocentric,g=geocentric)    ... ";
    cin >> c; cin.ignore(81,'\n'); c = tolower(c);
    
    if (c=='g') { m_Origin=Geocentric;   break; };
    if (c=='h') { m_Origin=Heliocentric; break; };
  }
  
  
  // Query epoch
  int    year,month,day;
  double Hour;

  cout << "  Epoch (yyyy mm dd hh.h)                 ... ";
  cin >> year >> month >> day >> Hour; cin.ignore(81,'\n');
  
  m_MjdEpoch = Mjd(year,month,day)+Hour/24.0;

  
  cout << endl; // Trailer
}


//
// Change of origin
//
void Position::SetOrigin(enOrigin Origin)
{
  //
  // Variables
  //
  double T_Epoch;
  Vec3D  R_Sun;

  if (Origin!=m_Origin) {

    // Geocentric coordinates of the Sun at epoch w.r.t. 
    // given reference system and equinox
    T_Epoch = (m_MjdEpoch-MJD_J2000)/36525.0;
    if (m_RefSys==Ecliptic)
      R_Sun = PrecMatrix_Ecl(T_Epoch,m_TEquinox) * SunPos(T_Epoch);
    else
      R_Sun = Ecl2EquMatrix(m_TEquinox) *
              PrecMatrix_Ecl(T_Epoch,m_TEquinox) * SunPos(T_Epoch);
    
    // Change origin
    if (m_Origin==Heliocentric) { 
      m_R += R_Sun; m_Origin = Geocentric;
    }
    else { 
      m_R -= R_Sun; m_Origin = Heliocentric;
    };

  };
}


//
// Change of reference system
//
void Position::SetRefSys(enRefSys RefSys)
{
  if (RefSys!=m_RefSys) {
    if (m_RefSys==Equator) {
      m_R = Equ2EclMatrix(m_TEquinox) * m_R;  m_RefSys = Ecliptic;
    }
    else {
      m_R = Ecl2EquMatrix(m_TEquinox) * m_R;  m_RefSys = Equator;
    }
  };
}


//
// Change of equinox
//
void Position::SetEquinox(double T_Equinox) 
{
  if (T_Equinox!=m_TEquinox) {
    if (m_RefSys==Equator)
      m_R = PrecMatrix_Equ(m_TEquinox,T_Equinox) * m_R;  
    else
      m_R = PrecMatrix_Ecl(m_TEquinox,T_Equinox) * m_R;  
    m_TEquinox = T_Equinox; 
  };
}


//
// Output
//
void Position::Print()
{
  cout << endl;
  cout << (( m_Origin==Heliocentric )?  "Heliocentric " : "Geocentric ");
  cout << (( m_RefSys==Equator )?  "equatorial " : "ecliptic ");
  cout << "coordinates" << endl;

  cout << "(Equinox J" << fixed << setprecision(1) 
       << 2000.0+m_TEquinox*100.0 << ",  ";
  
  cout << "Epoch " << DateTime(m_MjdEpoch,HHh) << ")" << endl;
  cout << endl;

  cout << "  (x,y,z) = " << fixed << setprecision(8) << setw(12) << m_R << endl;

  if ( m_RefSys==Equator ) {
    cout << "         h  m  s               o  '  \"" << endl;
    cout << "  RA = " << setprecision(2) << setw(11)
         << Angle(Deg*m_R[phi]/15.0,DMMSSs);
    cout << "    Dec = " << setprecision(1) << showpos << setw(11) 
         << Angle(Deg*m_R[theta],DMMSSs) << noshowpos;
  }
  else {
    cout << "         o  '  \"             o  '  \"" << endl;
    cout << "  L = " << setprecision(2) << setw(12)
         << Angle(Deg*m_R[phi],DMMSSs);
    cout << "    B = " << setprecision(1) << showpos << setw(11) 
         << Angle(Deg*m_R[theta],DMMSSs) << noshowpos;
  }
  cout << "    R = " << setprecision(8) << setw(12) 
       << m_R[r] << endl;
  cout << endl << endl;
}


//------------------------------------------------------------------------------
//
// Main program
//
//------------------------------------------------------------------------------
void main() {

  //
  // Variables
  //
  Position  Pos;
  char      c;
  bool      End = false;
  double    Year;

  
  // Header
  cout << endl
       << "                COCO: coordinate conversions       " << endl
       << "        (c) 1999 Oliver Montenbruck, Thomas Pfleger" << endl
       << endl;

  
  // Initialization   
  Pos.Input();
  Pos.Print();

  
  // Command loop
  do {

    // Command input
    cout << "Enter command (?=Help) ... ";
    cin >> c; cin.ignore(81,'\n'); c=tolower(c);

    // Actions
    switch (c) {
      
      case 'x':  
        End = true;  break;
      
      case 'a':
        Pos.SetRefSys(Equator); Pos.Print();  break;
      
      case 'e':
        Pos.SetRefSys(Ecliptic); Pos.Print();  break;
      
      case 'g':
        Pos.SetOrigin(Geocentric); Pos.Print();  break;
      
      case 'h':
        Pos.SetOrigin(Heliocentric); Pos.Print();  break;
      
      case 'n':
        Pos.Input(); Pos.Print();  break;

      case 'p': 
        cout << "New equinox (yyyy.y)   ... ";
        cin >> Year; cin.ignore(81,'\n');
        
        Pos.SetEquinox( (Year-2000.0)/100.0 );
        Pos.Print();
        
        break;
      
      default:
        // Display help text
        cout << endl
             << "Available commands" << endl
             << "  e=ecliptic,   a=equatorial,   p=precession, " << endl
             << "  g=geocentric, h=heliocentric, n=new input,  " << endl
             << "  x=exit                                      " << endl 
             << endl;
        break;
    }
  }
  while (!End);

  cout << endl;
}
