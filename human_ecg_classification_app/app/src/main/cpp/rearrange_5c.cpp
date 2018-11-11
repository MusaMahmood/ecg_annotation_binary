//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rearrange_5c.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 14-Sep-2018 10:16:29
//

// Include Files
#include <cstring>
#include "rt_nonfinite.h"
#include "rearrange_5c.h"

// Function Prototypes:
static void maximize_probs(const float X[10000], double max_prob[10000]);
static void sum(const double x[10000], double y[5]);


// Function Definitions

//
// Input = [2000, n], where n is the number of classes:
// Arguments    : const float X[10000]
//                double max_prob[10000]
// Return Type  : void
//
static void maximize_probs(const float X[10000], double max_prob[10000])
{
    int i;
    int ixstart;
    float mtmp;
    int itmp;
    int ix;
    boolean_T exitg1;
    memset(&max_prob[0], 0, 10000U * sizeof(double));
    for (i = 0; i < 2000; i++) {
        ixstart = 1;
        mtmp = X[i];
        itmp = 0;
        if (rtIsNaNF(X[i])) {
            ix = 2;
            exitg1 = false;
            while ((!exitg1) && (ix < 6)) {
                ixstart = ix;
                if (!rtIsNaNF(X[i + 2000 * (ix - 1)])) {
                    mtmp = X[i + 2000 * (ix - 1)];
                    itmp = ix - 1;
                    exitg1 = true;
                } else {
                    ix++;
                }
            }
        }

        if (ixstart < 5) {
            while (ixstart + 1 < 6) {
                if (X[i + 2000 * ixstart] > mtmp) {
                    mtmp = X[i + 2000 * ixstart];
                    itmp = ixstart;
                }

                ixstart++;
            }
        }

        max_prob[i + 2000 * itmp] = 1.0;
    }
}

//
// Arguments    : const double x[10000]
//                double y[5]
// Return Type  : void
//
static void sum(const double x[10000], double y[5])
{
    int i;
    int xoffset;
    double s;
    int k;
    for (i = 0; i < 5; i++) {
        xoffset = i * 2000;
        s = x[xoffset];
        for (k = 0; k < 1999; k++) {
            s += x[(xoffset + k) + 1];
        }

        y[i] = s;
    }
}


//
// get_class_bleph - input a
//  input [2000, 5] class array
// Arguments    : const float input_array[10000]
//                double *b_index
//                float scores[5]
// Return Type  : void
//
void get_class_distribution(const float input_array[4000], double *b_index,
                            float scores[2])
{
    int ixstart;
    int xoffset;
    float s;
    int ix;
    boolean_T exitg1;
    for (ixstart = 0; ixstart < 2; ixstart++) {
        xoffset = ixstart * 2000;
        s = input_array[xoffset];
        for (ix = 0; ix < 1999; ix++) {
            s += input_array[(xoffset + ix) + 1];
        }

        scores[ixstart] = s;
    }

    ixstart = 1;
    s = scores[0];
    xoffset = 1;
    if (rtIsNaNF(scores[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix < 3)) {
            ixstart = 2;
            if (!rtIsNaNF(scores[1])) {
                s = scores[1];
                xoffset = 2;
                exitg1 = true;
            } else {
                ix = 3;
            }
        }
    }

    if ((ixstart < 2) && (scores[1] > s)) {
        xoffset = 2;
    }

    *b_index = (double)xoffset - 1.0;
}


void get_class_distribution_c5(const float input_array[10000], double *b_index, float scores[5]) {
    double dv0[10000];
    double dv1[5];
    int ixstart;
    float mtmp;
    int itmp;
    int ix;
    boolean_T exitg1;
    maximize_probs(input_array, dv0);
    sum(dv0, dv1);
    for (ixstart = 0; ixstart < 5; ixstart++) {
        scores[ixstart] = (float)dv1[ixstart];
    }

    ixstart = 1;
    mtmp = scores[0];
    itmp = 1;
    if (rtIsNaNF(scores[0])) {
        ix = 2;
        exitg1 = false;
        while ((!exitg1) && (ix < 6)) {
            ixstart = ix;
            if (!rtIsNaNF(scores[ix - 1])) {
                mtmp = scores[ix - 1];
                itmp = ix;
                exitg1 = true;
            } else {
                ix++;
            }
        }
    }

    if (ixstart < 5) {
        while (ixstart + 1 < 6) {
            if (scores[ixstart] > mtmp) {
                mtmp = scores[ixstart];
                itmp = ixstart + 1;
            }

            ixstart++;
        }
    }

    *b_index = (double)itmp - 1.0;
}

// Function Definitions

//
// Arguments    : const float input_array[10000]
//                float rearranged[10000]
// Return Type  : void
//
void rearrange_5c(const float input_array[10000], float rearranged[10000]) {
    int i;
    int j;
    for (i = 0; i < 2000; i++) {
        for (j = 0; j < 5; j++) {
            rearranged[i + 2000 * j] = input_array[i * 5 + j];
        }
    }
}

void rearrange_2c(const float input_array[4000], float rearranged[4000]) {
    int i;
    int j;
    for (i = 0; i < 2000; i++) {
        for (j = 0; j < 2; j++) {
            rearranged[i + 2000 * j] = input_array[i * 2 + j];
        }
    }
}


//
// Arguments    : void
// Return Type  : void
//
void rearrange_5c_initialize() {
    rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void rearrange_5c_terminate() {
    // (no terminate code required)
}

//
// File trailer for rearrange_5c.cpp
//
// [EOF]
//
