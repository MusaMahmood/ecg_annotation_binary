//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: downsample_250Hz.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Dec-2017 17:30:41
//

// Include Files
#include "rt_nonfinite.h"
#include "downsample_250Hz.h"

// Function Definitions

//
// Arguments    : const double X_in_data[]
//                const int X_in_size[1]
//                double Fs
//                double X_data[]
//                int X_size[2]
// Return Type  : void
//
void downsample_250Hz(const double X_in_data[], const int X_in_size[1], double
                      Fs, double X_data[], int X_size[2])
{
  int dim;
  int b_dim;
  int c_dim;
  int d_dim;
  int c;
  int ix;
  int e_dim;
  short sz[2];
  int k;
  static double y_data[32000];
  static double b_y_data[32000];
  static double c_y_data[32000];
  if (Fs == 500.0) {
    dim = 2;
    if (X_in_size[0] != 1) {
      dim = 1;
    }

    if (dim <= 1) {
      b_dim = X_in_size[0];
    } else {
      b_dim = 1;
    }

    c = (b_dim - 1) / 2 + 1;
    sz[0] = (short)X_in_size[0];
    sz[1] = 1;
    sz[dim - 1] = (short)c;
    X_size[0] = sz[0];
    X_size[1] = sz[1];
    ix = 0;
    dim = 0;
    for (k = 1; k <= c; k++) {
      X_data[dim] = X_in_data[ix];
      ix += 2;
      dim++;
    }
  } else if (Fs == 1000.0) {
    dim = 2;
    if (X_in_size[0] != 1) {
      dim = 1;
    }

    if (dim <= 1) {
      c_dim = X_in_size[0];
    } else {
      c_dim = 1;
    }

    c = (c_dim - 1) / 4 + 1;
    sz[0] = (short)X_in_size[0];
    sz[1] = 1;
    sz[dim - 1] = (short)c;
    ix = 0;
    dim = 0;
    for (k = 1; k <= c; k++) {
      y_data[dim] = X_in_data[ix];
      ix += 4;
      dim++;
    }

    X_size[0] = sz[0];
    X_size[1] = sz[1];
    dim = sz[0] * sz[1];
    for (ix = 0; ix < dim; ix++) {
      X_data[ix] = y_data[ix];
    }
  } else if (Fs == 2000.0) {
    dim = 2;
    if (X_in_size[0] != 1) {
      dim = 1;
    }

    if (dim <= 1) {
      d_dim = X_in_size[0];
    } else {
      d_dim = 1;
    }

    c = (d_dim - 1) / 8 + 1;
    sz[0] = (short)X_in_size[0];
    sz[1] = 1;
    sz[dim - 1] = (short)c;
    ix = 0;
    dim = 0;
    for (k = 1; k <= c; k++) {
      b_y_data[dim] = X_in_data[ix];
      ix += 8;
      dim++;
    }

    X_size[0] = sz[0];
    X_size[1] = sz[1];
    dim = sz[0] * sz[1];
    for (ix = 0; ix < dim; ix++) {
      X_data[ix] = b_y_data[ix];
    }
  } else if (Fs == 4000.0) {
    dim = 2;
    if (X_in_size[0] != 1) {
      dim = 1;
    }

    if (dim <= 1) {
      e_dim = X_in_size[0];
    } else {
      e_dim = 1;
    }

    c = (e_dim - 1) / 16 + 1;
    sz[0] = (short)X_in_size[0];
    sz[1] = 1;
    sz[dim - 1] = (short)c;
    ix = 0;
    dim = 0;
    for (k = 1; k <= c; k++) {
      c_y_data[dim] = X_in_data[ix];
      ix += 16;
      dim++;
    }

    X_size[0] = sz[0];
    X_size[1] = sz[1];
    dim = sz[0] * sz[1];
    for (ix = 0; ix < dim; ix++) {
      X_data[ix] = c_y_data[ix];
    }
  } else if (Fs == 250.0) {
    X_size[0] = X_in_size[0];
    X_size[1] = 1;
    dim = X_in_size[0];
    for (ix = 0; ix < dim; ix++) {
      X_data[ix] = X_in_data[ix];
    }
  } else {
    X_size[0] = 1000;
    X_size[1] = 1;
    memset(&X_data[0], 0, 1000U * sizeof(double));
  }
}

//
// Arguments    : void
// Return Type  : void
//
void downsample_250Hz_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void downsample_250Hz_terminate()
{
  // (no terminate code required)
}

//
// File trailer for downsample_250Hz.cpp
//
// [EOF]
//
