//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ecg_bandstop_250Hz.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Dec-2017 17:32:21
//
#ifndef ECG_BANDSTOP_250HZ_H
#define ECG_BANDSTOP_250HZ_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "ecg_bandstop_250Hz_types.h"

// Function Declarations
extern void ecg_bandstop_250Hz(const double X_in[1000], double Y[1000]);
extern void ecg_bandstop_250Hz_initialize();
extern void ecg_bandstop_250Hz_terminate();

#endif

//
// File trailer for ecg_bandstop_250Hz.h
//
// [EOF]
//
