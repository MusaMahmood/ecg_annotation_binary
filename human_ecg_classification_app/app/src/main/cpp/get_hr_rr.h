//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 01-Dec-2018 17:24:48
//
#ifndef GET_HR_RR_H
#define GET_HR_RR_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "get_hr_rr_types.h"

// Function Declarations
extern void get_hr_rr(const double X_raw[7500], double *HR_mean, double
                      *Respiratory_rate);
extern void get_hr_rr_initialize();
extern void get_hr_rr_terminate();

#endif

//
// File trailer for get_hr_rr.h
//
// [EOF]
//
