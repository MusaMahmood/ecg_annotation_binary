//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: smooth_probs.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 11-Nov-2018 15:02:20
//

// Include Files
#include "rt_nonfinite.h"
#include "smooth_probs.h"

// Function Declarations
static void ind2vec_mod(const double x[2000], double y[10000]);

static void vec2ind_mod(const float x[10000], double y[2000]);

// Function Definitions

//
// IND2VEC_MOD Summary of this function goes here
//    Detailed explanation goes here
//  n=5;
// Arguments    : const double x[2000]
//                double y[10000]
// Return Type  : void
//
static void ind2vec_mod(const double x[2000], double y[10000]) {
    int i;
    memset(&y[0], 0, 10000U * sizeof(double));
    for (i = 0; i < 2000; i++) {
        y[i + 2000 * ((int) x[i] - 1)] = 1.0;
    }
}

//
// VEC2IND_MOD Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const float x[10000]
//                double y[2000]
// Return Type  : void
//
static void vec2ind_mod(const float x[10000], double y[2000]) {
    int j;
    int ixstart;
    float mtmp;
    int itmp;
    int cindx;
    int ix;
    boolean_T exitg1;
    int iindx[2000];
    for (j = 0; j < 2000; j++) {
        ixstart = j + 1;
        mtmp = x[j];
        itmp = 1;
        cindx = 1;
        if (rtIsNaNF(x[j])) {
            ix = j + 2001;
            exitg1 = false;
            while ((!exitg1) && (ix <= j + 8001)) {
                cindx++;
                ixstart = ix;
                if (!rtIsNaNF(x[ix - 1])) {
                    mtmp = x[ix - 1];
                    itmp = cindx;
                    exitg1 = true;
                } else {
                    ix += 2000;
                }
            }
        }

        if (ixstart < j + 8001) {
            for (ix = ixstart + 1999; ix + 1 <= j + 8001; ix += 2000) {
                cindx++;
                if (x[ix] > mtmp) {
                    mtmp = x[ix];
                    itmp = cindx;
                }
            }
        }

        iindx[j] = itmp;
        y[j] = iindx[j];
    }
}

//
// SMOOTH_PROBS :: (Version with no varsize arrays);
// Arguments    : const float max_prob[10000]
//                float max_prob_smoothed[10000]
// Return Type  : void
//
void smooth_probs(const float max_prob[10000], float max_prob_smoothed[10000])
{
    double as_ind[2000];
    int sequence_start;
    double sequence_length;
    int i;
    double max_prob_smoothed_ind[2000];
    signed char seq_indices[2000];
    static double dv0[10000];

    //  Convert to indices (2000, 5)?(2000, 1)
    vec2ind_mod(max_prob, as_ind);

    //  Copy array for smoothed output:
    //  Set seq start and len:
    sequence_start = 0;
    sequence_length = 0.0;
    for (i = 0; i < 2000; i++) {
        max_prob_smoothed_ind[i] = as_ind[i];
        seq_indices[i] = 0;
    }

    for (i = 0; i < 2000; i++) {
        if ((as_ind[i] != 1.0) && (1 + i < 2000)) {
            //  index is within abnormal tags
            if (sequence_start == 0) {
                //  if new sequence
                sequence_start = 1 + i;

                //  set starting point
                seq_indices[i] = 1;
            } else {
                sequence_length++;

                //  else increment sequence length
                seq_indices[i] = 1;
            }
        } else {
            //  index is tagged normal OR we've reached end of normal tags
            if ((sequence_length < 100.0) && (sequence_start != 0)) {
                //  half a second:
                //  set all to null class, as it is not consecutive:
                if ((1 + i == 2000) && (as_ind[i] != 1.0)) {
                    seq_indices[i] = 1;
                }

                for (sequence_start = 0; sequence_start < 2000; sequence_start++) {
                    if (seq_indices[sequence_start] == 1) {
                        max_prob_smoothed_ind[sequence_start] = 1.0;
                    }
                }
            }

            //  Reset Sequences
            sequence_start = 0;
            sequence_length = 0.0;
            memset(&seq_indices[0], 0, 2000U * sizeof(signed char));
        }
    }

    //  Convert to dense float array:
    ind2vec_mod(max_prob_smoothed_ind, dv0);
    for (sequence_start = 0; sequence_start < 10000; sequence_start++) {
        max_prob_smoothed[sequence_start] = (float)dv0[sequence_start];
    }
}
//
// Arguments    : void
// Return Type  : void
//
void smooth_probs_initialize() {
    rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void smooth_probs_terminate() {
    // (no terminate code required)
}

//
// File trailer for smooth_probs.cpp
//
// [EOF]
//
