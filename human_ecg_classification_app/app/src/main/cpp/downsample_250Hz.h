//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: downsample_250Hz.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Dec-2017 17:30:41
//
#ifndef DOWNSAMPLE_250HZ_H
#define DOWNSAMPLE_250HZ_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "downsample_250Hz_types.h"

// Function Declarations
extern void downsample_250Hz(const double X_in_data[], const int X_in_size[1],
  double Fs, double X_data[], int X_size[2]);
extern void downsample_250Hz_initialize();
extern void downsample_250Hz_terminate();

#endif

//
// File trailer for downsample_250Hz.h
//
// [EOF]
//
