//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: activ_prep.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 30-Nov-2018 02:18:34
//

// Include Files
#include "rt_nonfinite.h"
#include "activ_prep.h"

// Function Declarations
static void b_power(const double a[256], double y[256]);
static void power(const double a[768], double y[768]);
static void resultant(const double X[768], double Y[256]);

// Function Definitions

//
// Arguments    : const double a[256]
//                double y[256]
// Return Type  : void
//
static void b_power(const double a[256], double y[256])
{
  int k;
  for (k = 0; k < 256; k++) {
    y[k] = std::sqrt(a[k]);
  }
}

//
// Arguments    : const double a[768]
//                double y[768]
// Return Type  : void
//
static void power(const double a[768], double y[768])
{
  int k;
  for (k = 0; k < 768; k++) {
    y[k] = a[k] * a[k];
  }
}

//
// Get Resultant. Size of input vector must be greater than 3.
// Arguments    : const double X[768]
//                double Y[256]
// Return Type  : void
//
static void resultant(const double X[768], double Y[256])
{
  double X1[768];
  int i2;
  double b_X1[256];
  power(X, X1);
  for (i2 = 0; i2 < 256; i2++) {
    b_X1[i2] = (X1[i2] + X1[256 + i2]) + X1[512 + i2];
  }

  b_power(b_X1, Y);
}

//
// ACTIV_PREP Summary of this function goes here
//    ______
//    INPUTS
//    data_in: (256, 6), 8 sec sampled at 31.25 Hz (250) x {accX, accY, accZ,
//    gyrX, gyrY, gyrZ);
//    _______
//    OUTPUTS
//    data_out: (256, 8): Rescaled and preprocessed data with resultants:
//    (Single precision as it's used for tensorflow)
// Arguments    : const double data_in[1536]
//                float Y[2048]
// Return Type  : void
//
void activ_prep(const double data_in[1536], float Y[2048])
{
  int i0;
  double x[256];
  int i1;
  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 256; i1++) {
      Y[i1 + (i0 << 8)] = (float)(data_in[i1 + (i0 << 8)] / 16.0);
    }
  }

  resultant(*(double (*)[768])&data_in[0], x);
  for (i0 = 0; i0 < 256; i0++) {
    Y[768 + i0] = (float)(x[i0] / 16.0);
  }

  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 256; i1++) {
      Y[i1 + ((4 + i0) << 8)] = (float)(data_in[i1 + ((3 + i0) << 8)] / 2000.0);
    }
  }

  resultant(*(double (*)[768])&data_in[768], x);
  for (i0 = 0; i0 < 256; i0++) {
    Y[1792 + i0] = (float)(x[i0] / 2000.0);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void activ_prep_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void activ_prep_terminate()
{
  // (no terminate code required)
}

//
// File trailer for activ_prep.cpp
//
// [EOF]
//
