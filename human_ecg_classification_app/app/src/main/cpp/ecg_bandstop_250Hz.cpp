//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ecg_bandstop_250Hz.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Dec-2017 17:32:21
//

// Include Files
#include "rt_nonfinite.h"
#include "ecg_bandstop_250Hz.h"

// Function Declarations
static void filter(double b[7], double a[7], const double x[1036], const double
                   zi[6], double y[1036]);
static void flipud(double x[1036]);

// Function Definitions

//
// Arguments    : double b[7]
//                double a[7]
//                const double x[1036]
//                const double zi[6]
//                double y[1036]
// Return Type  : void
//
static void filter(double b[7], double a[7], const double x[1036], const double
                   zi[6], double y[1036])
{
  double a1;
  int k;
  int naxpy;
  int j;
  a1 = a[0];
  if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) && (a[0] != 1.0))
  {
    for (k = 0; k < 7; k++) {
      b[k] /= a1;
    }

    for (k = 0; k < 6; k++) {
      a[k + 1] /= a1;
    }

    a[0] = 1.0;
  }

  for (k = 0; k < 6; k++) {
    y[k] = zi[k];
  }

  memset(&y[6], 0, 1030U * sizeof(double));
  for (k = 0; k < 1036; k++) {
    naxpy = 1036 - k;
    if (!(naxpy < 7)) {
      naxpy = 7;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 1035 - k;
    if (!(naxpy < 6)) {
      naxpy = 6;
    }

    a1 = -y[k];
    for (j = 1; j <= naxpy; j++) {
      y[k + j] += a1 * a[j];
    }
  }
}

//
// Arguments    : double x[1036]
// Return Type  : void
//
static void flipud(double x[1036])
{
  int i;
  double xtmp;
  for (i = 0; i < 518; i++) {
    xtmp = x[i];
    x[i] = x[1035 - i];
    x[1035 - i] = xtmp;
  }
}

//
// 55-65 3rd order butterworth bandstop filter @ 250Hz.
// Arguments    : const double X_in[1000]
//                double Y[1000]
// Return Type  : void
//
void ecg_bandstop_250Hz(const double X_in[1000], double Y[1000])
{
  double d0;
  double d1;
  int i;
  double y[1036];
  double dv0[7];
  static const double dv1[7] = { 0.777246521400202, -0.295149620198606,
    2.36909935327861, -0.591875563889248, 2.36909935327861, -0.295149620198606,
    0.777246521400202 };

  double dv2[7];
  static const double dv3[7] = { 1.0, -0.348004594825511, 2.53911455972459,
    -0.585595129484226, 2.14946749012577, -0.248575079976725, 0.604109699507276
  };

  double b_y[1036];
  double a[6];
  static const double b_a[6] = { 0.22275347859979613, 0.16989850397289177,
    0.33991371041886664, 0.34619414482388972, 0.12656228167104569,
    0.17313682189292717 };

  d0 = 2.0 * X_in[0];
  d1 = 2.0 * X_in[999];
  for (i = 0; i < 18; i++) {
    y[i] = d0 - X_in[18 - i];
  }

  memcpy(&y[18], &X_in[0], 1000U * sizeof(double));
  for (i = 0; i < 18; i++) {
    y[i + 1018] = d1 - X_in[998 - i];
  }

  for (i = 0; i < 7; i++) {
    dv0[i] = dv1[i];
    dv2[i] = dv3[i];
  }

  for (i = 0; i < 6; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 1036U * sizeof(double));
  filter(dv0, dv2, b_y, a, y);
  flipud(y);
  for (i = 0; i < 7; i++) {
    dv0[i] = dv1[i];
    dv2[i] = dv3[i];
  }

  for (i = 0; i < 6; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 1036U * sizeof(double));
  filter(dv0, dv2, b_y, a, y);
  flipud(y);
  memcpy(&Y[0], &y[18], 1000U * sizeof(double));
}

//
// Arguments    : void
// Return Type  : void
//
void ecg_bandstop_250Hz_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void ecg_bandstop_250Hz_terminate()
{
  // (no terminate code required)
}

//
// File trailer for ecg_bandstop_250Hz.cpp
//
// [EOF]
//
