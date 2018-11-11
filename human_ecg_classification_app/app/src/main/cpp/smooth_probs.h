//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: smooth_probs.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 11-Nov-2018 15:02:20
//
#ifndef SMOOTH_PROBS_H
#define SMOOTH_PROBS_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "smooth_probs_types.h"

// Function Declarations
extern void smooth_probs(const float max_prob[10000], float max_prob_smoothed
  [10000]);
extern void smooth_probs_initialize();
extern void smooth_probs_terminate();

#endif

//
// File trailer for smooth_probs.h
//
// [EOF]
//
