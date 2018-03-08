//
// File: bsxfun.cpp
//
// MATLAB Coder version            : 2.6
// C/C++ source code generated on  : 05-Mar-2018 19:52:01
//

// Include files
#include "rt_nonfinite.h"
#include "myNeuralNetworkFunction.h"
#include "bsxfun.h"

// Function Definitions

//
// Arguments    : const double a[4800]
//                const double b[4800]
//                double c[4800]
// Return Type  : void
//
void b_bsxfun(const double a[4800], const double b[4800], double c[4800])
{
  int k;
  for (k = 0; k < 4800; k++) {
    c[k] = a[k] * b[k];
  }
}

//
// Arguments    : const char a[4800]
//                const double b[4800]
//                double c[4800]
// Return Type  : void
//
void bsxfun(const char a[4800], const double b[4800], double c[4800])
{
  int k;
  for (k = 0; k < 4800; k++) {
    c[k] = (double)a[k] - b[k];
  }
}

//
// Arguments    : const double a[4800]
//                double b
//                double c[4800]
// Return Type  : void
//
void c_bsxfun(const double a[4800], double b, double c[4800])
{
  int k;
  for (k = 0; k < 4800; k++) {
    c[k] = a[k] + b;
  }
}

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
