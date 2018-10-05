//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ecg_filt_rescale.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 20-Jul-2018 13:26:27
//
#ifndef ECG_FILT_RESCALE_H
#define ECG_FILT_RESCALE_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ecg_filt_rescale_types.h"

// Function Declarations
extern void ecg_filt_rescale(const double X[2000], float Y[2000]);
extern void ecg_filt_rescale_initialize();
extern void ecg_filt_rescale_terminate();

#endif

//
// File trailer for ecg_filt_rescale.h
//
// [EOF]
//
