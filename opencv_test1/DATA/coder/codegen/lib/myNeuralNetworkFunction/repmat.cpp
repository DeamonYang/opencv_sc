//
// File: repmat.cpp
//
// MATLAB Coder version            : 2.6
// C/C++ source code generated on  : 06-Mar-2018 20:48:46
//

// Include files
#include "rt_nonfinite.h"
#include "myNeuralNetworkFunction.h"
#include "repmat.h"

// Function Definitions

//
// Arguments    : double b[15]
// Return Type  : void
//
void repmat(double b[15])
{
  static const double a[15] = { 1.40152972268971, 1.2141242685500147,
    1.0081029333422036, -0.80136283918328732, 0.60907590641553733,
    0.40703656094223922, -0.20069287586969564, 0.018009143067705253,
    -0.17705253703054524, -0.40013517938086918, -0.60021088555560487,
    -0.80424889603431093, -1.0032595492916778, 1.2026591545340353,
    -1.4032621091931463 };

  memcpy(&b[0], &a[0], 15U * sizeof(double));
}

//
// File trailer for repmat.cpp
//
// [EOF]
//
