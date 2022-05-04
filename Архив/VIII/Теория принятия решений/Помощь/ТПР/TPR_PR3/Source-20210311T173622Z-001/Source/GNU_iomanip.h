//------------------------------------------------------------------------------
//
// GNU_iomanip.h
//
// Purpose:    
//
//    Temporaray implementation of ostream manipulators from the 
//    C++ Standard Library, which are not contained in <iomanip> 
//    as provided with GNU C++.
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

namespace{
ostream& left (ostream& os){os.setf(ios::left ,ios::adjustfield); return os;};
ostream& right(ostream& os){os.setf(ios::right,ios::adjustfield); return os;};
ostream& fixed(ostream& os){os.setf(ios::fixed,ios::floatfield);  return os;};
ostream& showpos  (ostream& os){os.setf(ios::showpos); return os;};
ostream& noshowpos(ostream& os){os.unsetf(ios::showpos); return os;};
}
