/*
 * File: _coder_myNeuralNetworkFunction_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2018 20:48:46
 */

/* Include files */
#include "_coder_myNeuralNetworkFunction_api.h"

/* Function Declarations */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x1, const char
  *identifier, char y[4800]);
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char y[4800]);
static const mxArray *emlrt_marshallOut(const double u);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char ret[4800]);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void myNeuralNetworkFunction_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void myNeuralNetworkFunction_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void myNeuralNetworkFunction_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  myNeuralNetworkFunction_xil_terminate();
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void myNeuralNetworkFunction_api(const mxArray * const prhs[1], const mxArray
  *plhs[1])
{
  char x1[4800];
  double b_y1;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[0]), "x1", x1);

  /* Invoke the target function */
  b_y1 = myNeuralNetworkFunction(x1);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(b_y1);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x1
 *                const char *identifier
 *                char y[4800]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x1, const char
  *identifier, char y[4800])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  b_emlrt_marshallIn(sp, emlrtAlias(x1), &thisId, y);
  emlrtDestroyArray(&x1);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char y[4800]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char y[4800])
{
  c_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const double u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const double u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char ret[4800]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char ret[4800])
{
  int iv0[1];
  iv0[0] = 4800;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "char", false, 1U, iv0);
  emlrtImportCharArray(src, ret, 4800);
  emlrtDestroyArray(&src);
}

/*
 * File trailer for _coder_myNeuralNetworkFunction_api.c
 *
 * [EOF]
 */
