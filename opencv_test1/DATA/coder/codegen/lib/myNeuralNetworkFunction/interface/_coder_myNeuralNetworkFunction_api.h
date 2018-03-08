/* 
 * File: _coder_myNeuralNetworkFunction_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 06-Mar-2018 20:48:46 
 */

#ifndef ___CODER_MYNEURALNETWORKFUNCTION_API_H__
#define ___CODER_MYNEURALNETWORKFUNCTION_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void myNeuralNetworkFunction_initialize(emlrtContext *aContext);
extern void myNeuralNetworkFunction_terminate(void);
extern void myNeuralNetworkFunction_atexit(void);
extern void myNeuralNetworkFunction_api(const mxArray * const prhs[1], const mxArray *plhs[1]);
extern double myNeuralNetworkFunction(char x1[4800]);
extern void myNeuralNetworkFunction_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_myNeuralNetworkFunction_api.h 
 *  
 * [EOF] 
 */
