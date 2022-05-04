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
/*
namespace{
std::ostream& left (std::ostream& os){os.setf(std::ios::left ,std::ios::adjustfield); return os;};
std::ostream& right(std::ostream& os){os.setf(std::ios::right,std::ios::adjustfield); return os;};
std::ostream& fixed(std::ostream& os){os.setf(std::ios::fixed,std::ios::floatfield);  return os;};
std::ostream& showpos  (std::ostream& os){os.setf(std::ios::showpos); return os;};
std::ostream& noshowpos(std::ostream& os){os.unsetf(std::ios::showpos); return os;};
}
*/