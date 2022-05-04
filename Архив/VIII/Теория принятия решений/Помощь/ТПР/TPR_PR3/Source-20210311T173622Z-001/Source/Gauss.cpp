//------------------------------------------------------------------------------
//
// Module:     Gauss program (Gauss.cpp)
//
// Purpose:    Orbit determination from three observations
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

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "APC_Const.h"
#include "APC_IO.h"
#include "APC_Kepler.h"
#include "APC_Math.h"
#include "APC_PrecNut.h"
#include "APC_Spheric.h"
#include "APC_Sun.h"
#include "APC_Time.h"
#include "APC_VecMat3D.h"

#ifdef __GNUC__  // GNU C++ adaptation
#include "GNU_iomanip.h"
#endif

using namespace std;


//------------------------------------------------------------------------------
//
// Start: reads the input file and preprocesses the observational data
//
// Input:
//
//   InputFile   Name of input file
//
// Output:
//
//   Header      Comment
//   R_Sun[]     Three Sun position vectors (ecliptic coordinates)
//   e[]         Three observation direction unit vectors
//   Mjd0[]      Three observation times (Modified Julian Date)
//   T_eqx       Equinox of R_Sun and e (in Julian centuries since J2000)
//
//------------------------------------------------------------------------------
void Start ( char* InputFile,
             char* Header, 
             Vec3D R_Sun[], Vec3D e[], double Mjd0[], double& T_eqx )
{
  //
  // Variables
  //
  int       i, Year, Month, Day, deg, min;
  double    Hour, secs, year;
  double    T_eqx0, T, RA, Dec;
  ifstream  inp;

  
  inp.open(InputFile);  // Open observation file

  inp.get(Header,81);   // Read header 
  

  // Read observations
  for (i=0;i<=2;i++) {

    inp >> Year >> Month >> Day >> Hour; 
    inp >> deg >> min >> secs; 
    RA = Rad*15.0*Ddd(deg,min,secs);
    inp >> deg >> min >> secs; 
    Dec = Rad*Ddd(deg,min,secs);
    inp.ignore(81,'\n');
    Mjd0[i] = Mjd(Year,Month,Day) + Hour/24.0;
    e[i]   = Vec3D(Polar(RA,Dec));
  }
  

  // Equinox of observations and target equinox
  inp >> year; inp.ignore(81,'\n');
  T_eqx0 = (year-2000.0)/100.0;
  inp >> year; inp.ignore(81,'\n');
  T_eqx = (year-2000.0)/100.0;


  // Initial data for orbit determination 
  // (observations and Sun position referred to ecliptic and equinox of T_eqx)
  for (i=0;i<=2;i++) {
    T        = (Mjd0[i]-MJD_J2000) / 36525.0;
    e[i]     = PrecMatrix_Ecl(T_eqx0,T_eqx) * Equ2EclMatrix(T_eqx0) * e[i];
    R_Sun[i] = PrecMatrix_Ecl(T,T_eqx) * SunPos(T);
  }


  // Print summary of initial data
  cout << " Summary of orbit determination" << endl << endl
       << "  " << Header << endl  << endl
       << " Initial data (geocentric ecliptic coordinates; Equinox J" 
       << fixed << setprecision(2) << 100.0*T_eqx+2000.0 << ")" << endl
       << endl;
  cout << "  Observation" 
       << setw(25) << "1" << setw(12) << "2" << setw(12) << "3" << endl;
  cout << "  Julian Date                 ";
  for (i=0;i<=2;i++) { cout << setw(12) << Mjd0[i]+2400000.5; }; 
  cout << endl;
  cout << "  Solar longitude [deg]       " << setprecision(4);
  for (i=0;i<=2;i++) { cout << setw(12) << Deg*(R_Sun[i][phi]); }; 
  cout << endl;
  cout << "  Planet/Comet longitude [deg]";
  for (i=0;i<=2;i++) { cout << setw(12) << Deg*((e[i])[phi]); }; 
  cout << endl;
  cout << "  Planet/Comet latitude [deg] ";
  for (i=0;i<=2;i++) { cout << setw(12) << Deg*((e[i])[theta]); }; 
  cout << endl;

}


//------------------------------------------------------------------------------
//
// DumpElem: Formatted output of orbital elements
//
// Input:
//
//   Mjd_p     Modified Julian Date of perihelion passage
//   q         Perihelion distance in [AU]
//   e         Eccentricity
//   i         Inclination in [rad]
//   Omega     Longitude of ascending node in [rad]
//   omega     Argument of perihelion in [rad]
//   T_eqx     Reference equinox (Julian centuries since J2000)
//
//------------------------------------------------------------------------------
void DumpElem ( double Mjd_p, double q, double e, double i,
                double Omega, double omega, double T_eqx )
{
  cout << endl
       << " Orbital elements (Equinox J" 
       << fixed << setprecision(2) << 100.0*T_eqx+2000.0 << ")" << endl
       << endl
       << "  Perihelion date      tp       " 
       << setprecision(3) << DateTime(Mjd_p,DDd) << "  (JD " 
       << setprecision(3) << setw(11) << Mjd_p+2400000.5 << ")" << endl
       << "  Perihelion distance  q [AU] " 
       << setprecision(6) << setw(12)  << q << endl
       << "  Semi-major axis      a [AU] " 
       << setprecision(6) << setw(12)  << q/(1.0-e) << endl
       << "  Eccentricity         e      " 
       << setprecision(6) << setw(12) << e << endl
       << "  Inclination          i      " 
       << setprecision(4) << setw(10) << Deg*i << " deg" << endl
       << "  Ascending node       Omega  " 
       << setprecision(4) << setw(10) << Deg*Omega << " deg" << endl
       << "  Long. of perihelion  pi     " 
       << setprecision(4) << setw(10) 
       << Deg*Modulo(Omega+omega,2*pi) << " deg" << endl
       << "  Arg. of perihelion   omega  "
       << setprecision(4) << setw(10) << Deg*omega << " deg" << endl;
}


//------------------------------------------------------------------------------
//
// Retard: Light time correction and computation of time differences
//
// Input:
//
//   Mjd0[]   Times of observation (t1',t2',t3') (Modified Julian Date)
//   rho[]    Three geocentric distances in [AU]
//
// Output:
//
//   Mjd[]    Times of light emittance (t1,t2,t3) (Modified Julian Date)
//   tau[]    Scaled time differences
//
//------------------------------------------------------------------------------
void Retard ( const double Mjd0[], const double rho[], 
              double Mjd[], double tau[] ) 
{
  for (int i=0;i<=2;i++)  Mjd[i] = Mjd0[i] - rho[i]/c_light;

  tau[0] = kGauss * (Mjd[2]-Mjd[1]);
  tau[1] = kGauss * (Mjd[2]-Mjd[0]);
  tau[2] = kGauss * (Mjd[1]-Mjd[0]);
}


//------------------------------------------------------------------------------
//
// r1: Auxiliary function r1(rho) = (sigma/(rho_0-rho))^(1/3) of the 
//     Gauss-Lagrangian equation
//
// Input:
//
//   sigma    Auxiliary quantity
//   rho_0    Auxiliary quantity
//   rho      Geocentric distance
//
// <return>:
//
//   r1       Heliocentric distance 
//
//------------------------------------------------------------------------------
double r1 (double sigma, double rho_0, double rho)
{
  return pow ( sigma/(rho_0-rho), 1.0/3.0 );
}


//------------------------------------------------------------------------------
//
// r2: Auxiliary function r2(rho) = sqrt( (rho-gamma*R)^2+R^2-(gamma*R)^2 )
//     of the Gauss-Lagrangian equation
//
// Input:
//
//   gamma    Angle Sun-Earth-Body
//   R        Earth-Sun distance
//   rho      Geocentric distance
//
// <return>:
//
//   r2       Heliocentric distance 
//
//------------------------------------------------------------------------------
double r2 (double gamma, double R, double rho)
{
  double gamR = gamma*R;
  return sqrt ( (rho-gamR)*(rho-gamR) + R*R - gamR*gamR );
}


//------------------------------------------------------------------------------
//
// BiSect: Solution of the Gauss-Lagrangian equation (r1(rho)=r2(rho)) 
//         using bisection in a given interval
//
// Input:
//
//   gamma    Angle Sun-Earth-Body
//   R        Earth-Sun distance
//   rho_0    Geocentric distance
//   sigma    Auxiliary quantity
//   rho_1    Bound of search interval (r1-r2 <= 0.0)
//   rho_2    Bound of search interval (r1-r2 >= 0.0)
//
// Output:
//
//   rho      Solution
//
// Note:
//
//   rho_1 and rho_2 may themselves be roots of the Gauss-Lagrangian 
//   equation provided that an independent root rho exists within the
//   interval ]min(rho_1,rho_2), max(rho_1,rho_2)[ and that r1<=r2 between
//   rho_1 and rho and r1>=r2 between rho and rho_2. This may imply that 
//   rho_2 < rho_1!
//  
//------------------------------------------------------------------------------
void BiSect ( double gamma, double R, double rho_0, double sigma,
              double rho_1, double rho_2, double& rho )
{
  //
  // Constants
  //
  const double eps = 1.0e-9;
  
  
  //
  // Variables
  //
  double f;


  do {
    rho = (rho_1+rho_2)/2.0; 
    f = r1(sigma,rho_0,rho) - r2(gamma,R,rho);
    if (f>0.0) rho_2=rho; else rho_1=rho;
  }
  while (fabs(rho_1-rho_2) > eps);
}


//------------------------------------------------------------------------------
//
// Newton: Solution of the Gauss-Lagrangian equation (r1(rho)=r2(rho)) 
//         using Newton's iteration
//
// Input:
//
//   gamma      Angle Sun-Earth-Body
//   R          Earth-Sun distance
//   rho_0      Geocentric distance
//   sigma      Auxiliary quantity
//   rho_1      Bound of search interval (r1-r2 <= 0.0)
//   rho_2      Bound of search interval (r1-r2 >= 0.0)
//   rho_start  Initial guess
//
// Output:
//
//   rho        Solution      
//   Abort      Status code 
//
// Note:
//
//   The Newton iteration is continued as long as monotonic convergence to 
//   a solution is assured. Otherwise the abort flag is set.
//
//------------------------------------------------------------------------------
void Newton ( double gamma, double R, double rho_0, double sigma,
              double rho_start, double& rho, bool& Abort )
{
  //
  // Constants
  //
  const double eps = 1.0e-8;
  const double s   = ( (sigma>0.0)? +1.0 : -1.0 );  // Sign of sigma
  

  //
  // Variables
  //
  double r_a, r_b;    // Auxiliary quantities (heliocentric distance)
  double f, df, d2f;  // Value of Gauss-Lagrange function and derivatives
  

  // Initialization
  f=0.0; df=1.0; Abort=true; rho=rho_start;
  
  
  // Newton iteration
  while (true) {
    
    // Check for improper initial conditions 
    if ( (s*(rho-gamma*R)<0.0) || (s*(rho-rho_0)>=0.0) ) break;
    
    // Components of Gauss-Lagrange function
    r_a = r1(sigma, rho_0, rho); 
    r_b = r2(gamma, R, rho); 
    
    // Gauss-Lagrange function and derivatives
    f   = r_a-r_b;
    df  = pow(r_a,4)/(3.0*sigma) - (rho-gamma*R)/r_b;
    d2f = 4.0*pow(r_a,7) / (9.0*sigma*sigma) 
          - R*R*(1.0-gamma*gamma)/pow(r_b,3);
    
    // Check for success and/or abort
    if (fabs(f)<eps) {Abort=false; break;};
    
    // Check for abort condition based on gradient and curvature
    if ( (s*df<=0.0) || (f*d2f<=0.0) )  break;
    
    rho-= f/df; // Update 
  };
}


//------------------------------------------------------------------------------
//
// SolveGL: Finds the (up to three) solutions of the Gauss-Lagrangian 
//          equation. Only positive solutions are returned. 
//
// Input:
//  
//   gamma      Cosine of elongation from the Sun at time of 2nd observation
//   R          Earth-Sun distance at time of 2nd observation
//   rho_0      0th-order approximation of geocentric distance 
//   sigma      Auxiliary quantity
//
// Output:
//
//   rho_a      Geocentric distance at time of 2nd observation (1st solution)
//   rho_b      Geocentric distance at time of 2nd observation (2nd solution)
//   rho_c      Geocentric distance at time of 2nd observation (3rd solution)
//   n          Number of solutions actually found
//
//------------------------------------------------------------------------------
void SolveGL ( double gamma, double R, double rho_0, double sigma,
               double& rho_a, double& rho_b, double& rho_c, int& n )
{
  //
  // Constants
  //
  const double rho_min = 0.01;                    // Threshold for solutions
                                                  // of Gauss-Lagr. Eqn. [AU]
  const double s = ( (sigma>0.0)? +1.0 : -1.0 );  // Sign of sigma
  

  //
  // Variables
  //
  double rho_d, rho_e, h;
  bool   Abort_a, Abort_c;  // Flag for aborted Newton iteration 
                            // of solutions rho_a and rho_b
 
  // Initialization
  rho_a = rho_b = rho_c = 0.0;


  // Check for single/triple solution
  if (s*(rho_0-gamma*R)<=0.0) {

    // Single solution within [rho_d,rho_e]
    rho_d = rho_0 - s*pow(fabs(sigma),1.0/4.0);
    rho_e = rho_0 - sigma/pow(fabs(gamma*R-rho_d)+R,3);
    BiSect ( gamma,R,rho_0,sigma, rho_d,rho_e, rho_a ); 
    n = 1;
  }
  else {

    // Triple solution possible
    // Locate root (c)
    if ( r1(sigma,rho_0,gamma*R) >= r2(gamma,R,gamma*R) )  { 
      rho_d = gamma*R-s*pow(sigma/(rho_0-gamma*R),1.0/3.0);
      BiSect ( gamma,R,rho_0,sigma, rho_d,gamma*R,rho_c ); 
      Abort_c=false;
    }
    else Newton (gamma,R,rho_0,sigma, gamma*R,rho_c,Abort_c);
    
    // Locate root (a)
    rho_d = rho_0 - sigma/pow(fabs(rho_0-gamma*R)+R,3);
    Newton ( gamma,R,rho_0,sigma, rho_d,rho_a,Abort_a );
    
    // Locate root (b)
    if (Abort_a||Abort_c) {
      n=1; if (Abort_a) rho_a=rho_c;
    }
    else {
      n=3;
      BiSect ( gamma,R,rho_0,sigma, rho_a,rho_c,rho_b ); 
      // Sort solutions in ascending order
      if (rho_a>rho_b) {h=rho_a; rho_a=rho_c; rho_c=h;};
    };
  };
  
  
  // Cyclic shift and elimination of negative and near-Earth solutions
  while ( ((rho_a<rho_min) && (n>1)) || (n==3) ){
    n--; h=rho_a; rho_a=rho_b; rho_b=rho_c; rho_c=h;
  };
}


//------------------------------------------------------------------------------
//
// Select: Selection of a single solution rho of the Gauss-Lagrangian 
//         equation
//
// Input:
//   
//   rho_a    First solution 
//   rho_b    Second solution
//   rho_c    Third solution
//   n_sol    Total number of solutions
//   n        Number of selected solution
//
// <return>:  Selected solution rho
//
//------------------------------------------------------------------------------
double Select ( double rho_a, double rho_b, double rho_c,
                int n_sol, int n )
{
  if ( (n<1) || (n_sol<n) ) {
    cerr << " Error in Select: n = " << setw(2) << n << " n_sol = " 
         << setw(2) << n_sol << endl;
    exit(1);
  }
  else
    switch(n) {
      case 1: return rho_a; 
      case 2: return rho_b; 
      case 3: return rho_c;
    };
  return 0.0;
}                


//------------------------------------------------------------------------------
//
// GaussMethod: Orbit determination using Gauss's method
//
// Input:
//
//   R_Sun[]   Three Sun position vectors (ecliptic coordinates)
//   e[]       Three observation direction unit vectors
//   Mjd0[]    Three observation times (Modified Julian Date)
//
// Output:
//
//   N_run     Number of current run (=selected number of solution of 
//             the Gauss-Lagrangian equation)
//   N_sol     Total number of solutions of the Gauss-Lagrangian equation
//   Mjd_p     Modified Julian Date of perihelion passage
//   q         Perihelion distance [AU]
//   ecc       Eccentricity
//   inc       Inclination [rad]
//   Omega     Longitude of ascending node [rad]
//   omega     Argument of perihelion [rad]
//
//------------------------------------------------------------------------------
void GaussMethod ( const Vec3D R_Sun[], const Vec3D e[], const double Mjd0[],
                   int& N_run, int& N_sol, 
                   double& Mjd_p, double& q, double& ecc, 
                   double& inc, double& Omega, double& omega )
{
  //
  // Constants
  //
  const double eps_rho = 1.0e-8;
  const int    maxit   = 20;


  //
  // Variables
  //
  int     i,j,iterat;
  double  rho_old;
  double  Det,l,L,gamma;
  double  rho_max,rho_mean,rho_min;
  double  Mjd[3],rho[3],n[3],n0[3],tau[3],eta[3];
  double  mu[3];
  Vec3D   d[3],r[3];
  double  D[3][3];

     
  // Matrix D and determinant Det
  d[0] = Cross(e[1],e[2]);  
  d[1] = Cross(e[2],e[0]);  
  d[2] = Cross(e[0],e[1]);  

  for (i=0;i<=2;i++) for (j=0;j<=2;j++)  D[i][j] = Dot(d[i],R_Sun[j]);

  Det = Dot(e[2],d[2]);  


  // Direction cosine of observation unit vector with respect to the Sun
  // direction at time of second observation
  gamma  = Dot(e[1],R_Sun[1])/Norm(R_Sun[1]);


  // Time differences tau[i] and initial approximations of mu[0] and mu[2]
  tau[0] = kGauss*(Mjd0[2]-Mjd0[1]);
  tau[1] = kGauss*(Mjd0[2]-Mjd0[0]);
  tau[2] = kGauss*(Mjd0[1]-Mjd0[0]);

  mu[0] = (1.0/6.0) * tau[0]*tau[2] * (1.0+tau[0]/tau[1]);
  mu[2] = (1.0/6.0) * tau[0]*tau[2] * (1.0+tau[2]/tau[1]);


  // Header
  cout << endl << endl
       << " Solution No." << setw(1) << N_run << endl << endl
       << " Iteration of the geocentric distances " << endl
       << " Solutions (rho_2 in [AU]) of the Gauss-Lagrangian equation" 
       << endl << endl;
  cout << "  Iteration             Number   1st Sol.    2nd Sol.    3rd Sol."
       << endl;

  
  // Iterative improvement of tau[i] and mu[i]
  rho[1] = 0.0;
  iterat = 0;

  do {
   
    // Save previous value and increment iteration count
    rho_old = rho[1];
    iterat++;


    // Determine geocentric distance rho at time of second observation
    // from the Gauss-Lagrangian equation
    n0[0] = tau[0]/tau[1];
    n0[2] = tau[2]/tau[1];
    
    L = - ( n0[0]*D[1][0]-D[1][1]+n0[2]*D[1][2] ) / Det; 
    l =   ( mu[0]*D[1][0]    +    mu[2]*D[1][2] ) / Det; 

    SolveGL (gamma,Norm(R_Sun[1]),L,l,rho_min,rho_mean,rho_max,N_sol); 

    rho[1] = Select ( rho_min,rho_mean,rho_max, N_sol,N_run );
    r[1]   = rho[1]*e[1] - R_Sun[1];

    cout << setw(4) << iterat << setw(23) << N_sol << fixed << setprecision(8)
         << setw(15) << rho_min << setw(12) << rho_mean 
         << setw(12) << rho_max << endl;

    // Compute n1 and n3 
    n[0] = n0[0] + mu[0]/pow(Norm(r[1]),3); 
    n[2] = n0[2] + mu[2]/pow(Norm(r[1]),3); 


    // Geocentric distances rho_1 and rho_3 from n_1 and n_3
    rho[0] = ( n[0]*D[0][0] - D[0][1] + n[2]*D[0][2] ) / (n[0]*Det);
    rho[2] = ( n[0]*D[2][0] - D[2][1] + n[2]*D[2][2] ) / (n[2]*Det);


    // Apply light time correction and compute scaled time differences
    Retard ( Mjd0, rho, Mjd, tau );


    // Heliocentric coordinate vector
    for (i=0;i<=2;i++) 
      r[i] = rho[i]*e[i] - R_Sun[i];


    // Sector/triangle ratios eta_i
    eta[0] = FindEta ( r[1],r[2], tau[0] );
    eta[1] = FindEta ( r[0],r[2], tau[1] );
    eta[2] = FindEta ( r[0],r[1], tau[2] );
    

    // Improved values of mu_1, mu_3
    mu[0] = ( eta[1]/eta[0] - 1.0 ) * (tau[0]/tau[1]) * pow(Norm(r[1]),3);
    mu[2] = ( eta[1]/eta[2] - 1.0 ) * (tau[2]/tau[1]) * pow(Norm(r[1]),3);

    if (maxit<=iterat) { 
      cerr << "   (Convergence problems; iteration stopped after "
           << setw(2) << maxit << " steps)"
           << endl;
      break;
    }
  }
  while (fabs(rho[1]-rho_old) > eps_rho);


  cout << endl
       << " Geocentric and heliocentric distances" << endl 
       << endl;
  cout << "  Observation" 
       << setw(25) << "1" << setw(12) << "2" << setw(12) << "3" << endl;
  cout << "  rho [AU]" << setw(20) << " " << fixed << setprecision(8);
  for (i=0;i<=2;i++) cout << setw(12) << rho[i]; cout << endl;
  cout << "  r [AU]" << setw(22) << " " << fixed << setprecision(8);
  for (i=0;i<=2;i++) cout << setw(12) << Norm(r[i]); cout << endl;
       

  // Derive orbital elements from first and third observation
  Elements ( GM_Sun, Mjd[0], Mjd[2], r[0], r[2], 
             Mjd_p, q, ecc, inc, Omega, omega );
}
             

//------------------------------------------------------------------------------
//
// Main program
//
//------------------------------------------------------------------------------

void main(int argc, char* argv[])
{
  //
  // Variables
  //
  char      Header[81];
  int       N_run, N_sol;
  double    T_eqx;
  double    Mjd0[3];
  Vec3D     R_Sun[3],e[3];
  double    Mjd_p, q, ecc, inc, Omega, omega;
  char      InputFile[APC_MaxFilename] = "";
  char      OutputFile[APC_MaxFilename] = "";
  bool      FoundInputfile = false;
  bool      FoundOutputfile = false;
  ofstream  OutFile;

  
  // Title
  cout << endl
       << "      GAUSS: orbit determination from three observations " 
       << endl
       << "             (c) 1999 Oliver Montenbruck, Thomas Pfleger " 
       << endl << endl;


  // Find input and optional output files
  GetFilenames( argc, argv, "Gauss.dat", InputFile, FoundInputfile,
                OutputFile, FoundOutputfile );
  
  // Terminate program if input file could not be found
  if (!FoundInputfile) {
    cerr << " Terminating program." << endl;
    exit(-1);
  }

  
  // Redirect output if output file shall be created
  if (FoundOutputfile) {
    OutFile.open(OutputFile);
    if (OutFile.is_open())
      cout = OutFile;
  }

  
  // Initialization
  Start ( InputFile, Header, R_Sun, e, Mjd0, T_eqx );

  
  // Handle all solutions 
  N_run = 0;
  N_sol = 1;
  
  do {
  
    N_run++;
  
    // Determine the orbit using Gauss's method for solution N_run of the 
    // Gauss-Lagrangian equation
    GaussMethod ( R_Sun, e, Mjd0, N_run, N_sol, Mjd_p,q,ecc,inc,Omega,omega );
  
    // Print orbital elements
    DumpElem ( Mjd_p,q,ecc,inc,Omega,omega, T_eqx );
  
  }
  while (N_run<N_sol);

  if (OutFile.is_open()) OutFile.close();
}
