//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ecg_filt_rescale.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 20-Jul-2018 13:26:27
//

// Include Files
#include "rt_nonfinite.h"
#include "ecg_filt_rescale.h"

// Function Declarations
static void filter(double b[4], double a[4], const double x[2018], const double
                   zi[3], double y[2018]);
static void filtfilt(const double x_in[2000], double y_out[2000]);
static void flipud(double x[2018]);

// Function Definitions

//
// Arguments    : double b[4]
//                double a[4]
//                const double x[2018]
//                const double zi[3]
//                double y[2018]
// Return Type  : void
//
static void filter(double b[4], double a[4], const double x[2018], const double
                   zi[3], double y[2018])
{
  double a1;
  int k;
  int naxpy;
  int j;
  a1 = a[0];
  if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) && (a[0] != 1.0))
  {
    for (k = 0; k < 4; k++) {
      b[k] /= a1;
    }

    for (k = 0; k < 3; k++) {
      a[k + 1] /= a1;
    }

    a[0] = 1.0;
  }

  for (k = 0; k < 3; k++) {
    y[k] = zi[k];
  }

  memset(&y[3], 0, 2015U * sizeof(double));
  for (k = 0; k < 2018; k++) {
    naxpy = 2018 - k;
    if (!(naxpy < 4)) {
      naxpy = 4;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 2017 - k;
    if (!(naxpy < 3)) {
      naxpy = 3;
    }

    a1 = -y[k];
    for (j = 1; j <= naxpy; j++) {
      y[k + j] += a1 * a[j];
    }
  }
}

//
// Arguments    : const double x_in[2000]
//                double y_out[2000]
// Return Type  : void
//
static void filtfilt(const double x_in[2000], double y_out[2000])
{
  double d0;
  double d1;
  int i;
  double y[2018];
  double dv0[4];
  static const double dv1[4] = { 0.975179811634754, -2.9255394349042629,
    2.9255394349042629, -0.975179811634754 };

  double dv2[4];
  static const double dv3[4] = { 1.0, -2.949735839706348, 2.9007269883554381,
    -0.950975665016249 };

  double b_y[2018];
  double a[3];
  static const double b_a[3] = { -0.97517981162796985, 1.9503596232562816,
    -0.97517981162830258 };

  d0 = 2.0 * x_in[0];
  d1 = 2.0 * x_in[1999];
  for (i = 0; i < 9; i++) {
    y[i] = d0 - x_in[9 - i];
  }

  memcpy(&y[9], &x_in[0], 2000U * sizeof(double));
  for (i = 0; i < 9; i++) {
    y[i + 2009] = d1 - x_in[1998 - i];
  }

  for (i = 0; i < 4; i++) {
    dv0[i] = dv1[i];
    dv2[i] = dv3[i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 2018U * sizeof(double));
  filter(dv0, dv2, b_y, a, y);
  flipud(y);
  for (i = 0; i < 4; i++) {
    dv0[i] = dv1[i];
    dv2[i] = dv3[i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 2018U * sizeof(double));
  filter(dv0, dv2, b_y, a, y);
  flipud(y);
  memcpy(&y_out[0], &y[9], 2000U * sizeof(double));
}

//
// Arguments    : double x[2018]
// Return Type  : void
//
static void flipud(double x[2018])
{
  int i;
  double xtmp;
  for (i = 0; i < 1009; i++) {
    xtmp = x[i];
    x[i] = x[2017 - i];
    x[2017 - i] = xtmp;
  }
}

//
// Input: doubles (2000, 1)
//  Output: Y, single (2000, 1)
//  Filter is order 3, HPF @ 1 Hz, butterworth. 250 Hz Fs.
// Arguments    : const double X[2000]
//                float Y[2000]
// Return Type  : void
//
void ecg_filt_rescale(const double X[2000], float Y[2000])
{
  double b_X[2000];
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg1;
  double b_mtmp;
  filtfilt(X, b_X);
  ixstart = 1;
  mtmp = b_X[0];
  if (rtIsNaN(b_X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 2001)) {
      ixstart = ix;
      if (!rtIsNaN(b_X[ix - 1])) {
        mtmp = b_X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 2000) {
    while (ixstart + 1 < 2001) {
      if (b_X[ixstart] < mtmp) {
        mtmp = b_X[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = b_X[0];
  if (rtIsNaN(b_X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 2001)) {
      ixstart = ix;
      if (!rtIsNaN(b_X[ix - 1])) {
        b_mtmp = b_X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 2000) {
    while (ixstart + 1 < 2001) {
      if (b_X[ixstart] > b_mtmp) {
        b_mtmp = b_X[ixstart];
      }

      ixstart++;
    }
  }

  b_mtmp -= mtmp;
  for (ixstart = 0; ixstart < 2000; ixstart++) {
    Y[ixstart] = (float)((b_X[ixstart] - mtmp) / b_mtmp);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void ecg_filt_rescale_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void ecg_filt_rescale_terminate()
{
  // (no terminate code required)
}

//
// File trailer for ecg_filt_rescale.cpp
//
// [EOF]
//
