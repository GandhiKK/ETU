//------------------------------------------------------------------------------
//
// APC_IO.h
// 
// Purpose:
//
//    File I/O utilities
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

#ifndef INC_APC_IO_H
#define INC_APC_IO_H


//
// Constants
//
const int APC_MaxFilename = 256;


//------------------------------------------------------------------------------
//
// FileExists: Checks for existence of file
//
// Input:
//
//   Filename   Name of file to check for
//
//  <return>    Flag indicating existence of file
//
//------------------------------------------------------------------------------
bool FileExists(char* Filename);


//------------------------------------------------------------------------------
//
// GetFilenames: Evaluates command line arguments and checks for file names
//
// Input:
//
//   argc           Argument count as defined by main()
//   argv           Argument vector as defined by main()
//   DefInputFile   Filename to be used when no command line argument is given
//
// Output:
//
//   InputFile        Name of input file if found
//   FoundInputFile   Flag indicating whether input file could be found
//   OutputFile       Name of output file if found
//   FoundOutputFile  Flag indicating whether input file could be found
//
// Notes: File names are limited to max. APC_MaxFilename characters
//
//------------------------------------------------------------------------------
void GetFilenames( int argc, char* argv[], 
                   char* DefInputFile, 
                   char* InputFile,  bool& FoundInputFile,
                   char* OutputFile, bool& FoundOutputFile );

#endif  // include blocker