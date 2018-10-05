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
#include "rt_nonfinite.h"
#include "rearrange_5c.h"

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
