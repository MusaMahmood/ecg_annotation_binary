//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 01-Dec-2018 17:24:48
//

// Include Files
#include "rt_nonfinite.h"
#include "get_hr_rr.h"
#include "get_hr_rr_emxutil.h"

// Named Constants
#define Fs                             (250.0)

// Function Declarations
static void assignFullOutputs(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const emxArray_real_T *wxPk, const emxArray_real_T *bPk,
  emxArray_real_T *YpkOut, emxArray_real_T *XpkOut, emxArray_real_T *WpkOut,
  emxArray_real_T *PpkOut);
static void b_assignFullOutputs(const double y[7000], const int iPk_data[],
  const int iPk_size[1], const emxArray_real_T *wxPk, const emxArray_real_T *bPk,
  emxArray_real_T *YpkOut, emxArray_real_T *XpkOut, emxArray_real_T *WpkOut,
  emxArray_real_T *PpkOut);
static int b_bsearch(const emxArray_real_T *x, double xi);
static void b_combineFullPeaks(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const emxArray_real_T *wPk, const int iInf_data[], const int
  iInf_size[1], int iPkOut_data[], int iPkOut_size[1], emxArray_real_T *bPkOut,
  emxArray_real_T *bxPkOut, emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut);
static void b_do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1]);
static void b_filter(const double b[2], const double x[7506], double zi, double
                     y[7506]);
static void b_filtfilt(const double x_in[7500], double y_out[7500]);
static void b_findExtents(const double y[7000], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  emxArray_real_T *bPk, emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk);
static void b_findLeftIntercept(const double y[7000], int *idx, int borderIdx,
  double refHeight);
static void b_findRightIntercept(const double y[7000], int *idx, int borderIdx,
  double refHeight);
static void b_findpeaks(const double Yin[7500], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk);
static void b_flipud(double x[7506]);
static void b_getAllPeaksCodegen(const double y[7500], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void b_getHalfMaxBounds(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], emxArray_real_T *bounds);
static void b_getLeftBase(const double yTemp[7000], const int iPeak_data[],
  const int iPeak_size[1], const int iFinite_data[], const int iFinite_size[1],
  const int iInflect_data[], int iBase_data[], int iBase_size[1], int
  iSaddle_data[], int iSaddle_size[1]);
static void b_getPeakBase(const double yTemp[7000], const int iPk_data[], const
  int iPk_size[1], const int iFin_data[], const int iFin_size[1], const int
  iInflect_data[], const int iInflect_size[1], double peakBase_data[], int
  peakBase_size[1], int iLeftSaddle_data[], int iLeftSaddle_size[1], int
  iRightSaddle_data[], int iRightSaddle_size[1]);
static void b_getPeakWidth(const double y[7000], const int iPk_data[], const int
  iPk_size[1], const double pbPk_data[], const int pbPk_size[1], int iLB_data[],
  int iLB_size[1], int iRB_data[], int iRB_size[1], emxArray_real_T *wxPk);
static void b_keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double b_mean(const emxArray_real_T *x);
static void b_pwchcore(const emxArray_real_T *x, const emxArray_real_T *y, int
  yoffset, const emxArray_real_T *s, const emxArray_real_T *dx, const
  emxArray_real_T *divdif, emxArray_real_T *pp_breaks, emxArray_real_T *pp_coefs);
static void b_removeSmallPeaks(const double y[7500], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1]);
static void b_rescale_minmax(const double X[7000], double Y[7000]);
static void c_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void c_findpeaks(const double Yin[7000], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk);
static void c_flipud(int x_data[], int x_size[1]);
static void c_getAllPeaksCodegen(const double y[7000], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void c_keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static void c_removePeaksBelowMinPeakPromin(const double y[7500], int iPk_data[],
  int iPk_size[1], double pbPk_data[], int pbPk_size[1], int iLB_data[], int
  iLB_size[1], int iRB_data[], int iRB_size[1]);
static void c_removeSmallPeaks(const double y[7000], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1]);
static void combineFullPeaks(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const emxArray_real_T *wPk, const int iInf_data[], const int
  iInf_size[1], int iPkOut_data[], int iPkOut_size[1], emxArray_real_T *bPkOut,
  emxArray_real_T *bxPkOut, emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut);
static void conv(const double A[7500], const double B[38], double C[7463]);
static void d_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void d_removePeaksBelowMinPeakPromin(const double y[7000], int iPk_data[],
  int iPk_size[1], double pbPk_data[], int pbPk_size[1], int iLB_data[], int
  iLB_size[1], int iRB_data[], int iRB_size[1]);
static void diff(const emxArray_real_T *x, emxArray_real_T *y);
static void do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1]);
static void e_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void ecg_filt_rescale(const double X[7500], float Y[7500]);
static void fetchPeakExtents(const int idx_data[], const int idx_size[1],
  emxArray_real_T *bPk, emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk);
static void filter(const double b[4], const double a[4], const double x[7518],
                   const double zi[3], double y[7518]);
static void filtfilt(const double x_in[7500], double y_out[7500]);
static void findExtents(const double y[7500], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  emxArray_real_T *bPk, emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk);
static void findLeftIntercept(const double y[7500], int *idx, int borderIdx,
  double refHeight);
static void findRightIntercept(const double y[7500], int *idx, int borderIdx,
  double refHeight);
static void findpeaks(const double Yin[7463], double varargin_2, emxArray_real_T
                      *Ypk, emxArray_real_T *Xpk);
static void flip(emxArray_real_T *x);
static void flipud(double x[7518]);
static void getAllPeaksCodegen(const double y[7463], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void getHalfMaxBounds(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], emxArray_real_T *bounds);
static void getLeftBase(const double yTemp[7500], const int iPeak_data[], const
  int iPeak_size[1], const int iFinite_data[], const int iFinite_size[1], const
  int iInflect_data[], int iBase_data[], int iBase_size[1], int iSaddle_data[],
  int iSaddle_size[1]);
static void getPeakBase(const double yTemp[7500], const int iPk_data[], const
  int iPk_size[1], const int iFin_data[], const int iFin_size[1], const int
  iInflect_data[], const int iInflect_size[1], double peakBase_data[], int
  peakBase_size[1], int iLeftSaddle_data[], int iLeftSaddle_size[1], int
  iRightSaddle_data[], int iRightSaddle_size[1]);
static void getPeakWidth(const double y[7500], const int iPk_data[], const int
  iPk_size[1], const double pbPk_data[], const int pbPk_size[1], int iLB_data[],
  int iLB_size[1], int iRB_data[], int iRB_size[1], emxArray_real_T *wxPk);
static void interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
                    *varargin_2, double Vq[7500]);
static void keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double linterp(double xa, double xb, double ya, double yb, double yc,
                      double bc);
static double mean(const double x[7500]);
static void power(const double a[7500], double y[7500]);
static void ppval(const emxArray_real_T *pp_breaks, const emxArray_real_T
                  *pp_coefs, double x, double v_data[], int v_size[1]);
static void pwchcore(const emxArray_real_T *x, const emxArray_real_T *y, const
                     double s[2], emxArray_real_T *pp_breaks, double pp_coefs[4]);
static void removeSmallPeaks(const double y[7463], const int iFinite_data[],
  const int iFinite_size[1], double minH, int iPk_data[], int iPk_size[1]);
static void rescale_minmax(const double X[7500], double Y[7500]);
static void spline(const emxArray_real_T *x, const emxArray_real_T *y,
                   emxArray_real_T *output_breaks, emxArray_real_T *output_coefs);

// Function Definitions

//
// Arguments    : const double y[7500]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const emxArray_real_T *wxPk
//                const emxArray_real_T *bPk
//                emxArray_real_T *YpkOut
//                emxArray_real_T *XpkOut
//                emxArray_real_T *WpkOut
//                emxArray_real_T *PpkOut
// Return Type  : void
//
static void assignFullOutputs(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const emxArray_real_T *wxPk, const emxArray_real_T *bPk,
  emxArray_real_T *YpkOut, emxArray_real_T *XpkOut, emxArray_real_T *WpkOut,
  emxArray_real_T *PpkOut)
{
  int i7;
  int loop_ub;
  emxArray_real_T *r1;
  i7 = YpkOut->size[0];
  YpkOut->size[0] = iPk_size[0];
  emxEnsureCapacity((emxArray__common *)YpkOut, i7, sizeof(double));
  loop_ub = iPk_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    YpkOut->data[i7] = y[iPk_data[i7] - 1];
  }

  emxInit_real_T1(&r1, 1);
  i7 = r1->size[0];
  r1->size[0] = iPk_size[0];
  emxEnsureCapacity((emxArray__common *)r1, i7, sizeof(double));
  loop_ub = iPk_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    r1->data[i7] = (short)(1 + (short)(iPk_data[i7] - 1));
  }

  i7 = XpkOut->size[0];
  XpkOut->size[0] = r1->size[0];
  emxEnsureCapacity((emxArray__common *)XpkOut, i7, sizeof(double));
  loop_ub = r1->size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    XpkOut->data[i7] = r1->data[i7];
  }

  emxFree_real_T(&r1);
  diff(wxPk, WpkOut);
  i7 = PpkOut->size[0];
  PpkOut->size[0] = YpkOut->size[0];
  emxEnsureCapacity((emxArray__common *)PpkOut, i7, sizeof(double));
  loop_ub = YpkOut->size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    PpkOut->data[i7] = YpkOut->data[i7] - bPk->data[i7];
  }
}

//
// Arguments    : const double y[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const emxArray_real_T *wxPk
//                const emxArray_real_T *bPk
//                emxArray_real_T *YpkOut
//                emxArray_real_T *XpkOut
//                emxArray_real_T *WpkOut
//                emxArray_real_T *PpkOut
// Return Type  : void
//
static void b_assignFullOutputs(const double y[7000], const int iPk_data[],
  const int iPk_size[1], const emxArray_real_T *wxPk, const emxArray_real_T *bPk,
  emxArray_real_T *YpkOut, emxArray_real_T *XpkOut, emxArray_real_T *WpkOut,
  emxArray_real_T *PpkOut)
{
  emxArray_real_T *Ypk;
  int i16;
  int loop_ub;
  emxArray_real_T *Wpk;
  emxArray_real_T *r2;
  emxArray_real_T *r3;
  emxInit_real_T1(&Ypk, 1);
  i16 = Ypk->size[0];
  Ypk->size[0] = iPk_size[0];
  emxEnsureCapacity((emxArray__common *)Ypk, i16, sizeof(double));
  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    Ypk->data[i16] = y[iPk_data[i16] - 1];
  }

  emxInit_real_T1(&Wpk, 1);
  emxInit_real_T1(&r2, 1);
  diff(wxPk, r2);
  i16 = Wpk->size[0];
  Wpk->size[0] = r2->size[0];
  emxEnsureCapacity((emxArray__common *)Wpk, i16, sizeof(double));
  loop_ub = r2->size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    Wpk->data[i16] = r2->data[i16];
  }

  emxFree_real_T(&r2);
  i16 = YpkOut->size[0] * YpkOut->size[1];
  YpkOut->size[0] = 1;
  YpkOut->size[1] = Ypk->size[0];
  emxEnsureCapacity((emxArray__common *)YpkOut, i16, sizeof(double));
  loop_ub = Ypk->size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    YpkOut->data[YpkOut->size[0] * i16] = Ypk->data[i16];
  }

  i16 = PpkOut->size[0] * PpkOut->size[1];
  PpkOut->size[0] = 1;
  PpkOut->size[1] = Ypk->size[0];
  emxEnsureCapacity((emxArray__common *)PpkOut, i16, sizeof(double));
  loop_ub = Ypk->size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    PpkOut->data[PpkOut->size[0] * i16] = Ypk->data[i16] - bPk->data[i16];
  }

  emxFree_real_T(&Ypk);
  emxInit_real_T(&r3, 2);
  i16 = r3->size[0] * r3->size[1];
  r3->size[0] = 1;
  r3->size[1] = iPk_size[0];
  emxEnsureCapacity((emxArray__common *)r3, i16, sizeof(double));
  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    r3->data[r3->size[0] * i16] = (short)(1 + (short)(iPk_data[i16] - 1));
  }

  i16 = XpkOut->size[0] * XpkOut->size[1];
  XpkOut->size[0] = 1;
  XpkOut->size[1] = r3->size[1];
  emxEnsureCapacity((emxArray__common *)XpkOut, i16, sizeof(double));
  loop_ub = r3->size[1];
  for (i16 = 0; i16 < loop_ub; i16++) {
    XpkOut->data[XpkOut->size[0] * i16] = r3->data[r3->size[0] * i16];
  }

  emxFree_real_T(&r3);
  i16 = WpkOut->size[0] * WpkOut->size[1];
  WpkOut->size[0] = 1;
  WpkOut->size[1] = Wpk->size[0];
  emxEnsureCapacity((emxArray__common *)WpkOut, i16, sizeof(double));
  loop_ub = Wpk->size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    WpkOut->data[WpkOut->size[0] * i16] = Wpk->data[i16];
  }

  emxFree_real_T(&Wpk);
}

//
// Arguments    : const emxArray_real_T *x
//                double xi
// Return Type  : int
//
static int b_bsearch(const emxArray_real_T *x, double xi)
{
  int n;
  int low_ip1;
  int high_i;
  int mid_i;
  n = 1;
  low_ip1 = 2;
  high_i = x->size[1];
  while (high_i > low_ip1) {
    mid_i = (n >> 1) + (high_i >> 1);
    if (((n & 1) == 1) && ((high_i & 1) == 1)) {
      mid_i++;
    }

    if (xi >= x->data[mid_i - 1]) {
      n = mid_i;
      low_ip1 = mid_i + 1;
    } else {
      high_i = mid_i;
    }
  }

  return n;
}

//
// Arguments    : const double y[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const double bPk_data[]
//                const int bPk_size[1]
//                const int iLBw_data[]
//                const int iLBw_size[1]
//                const int iRBw_data[]
//                const int iRBw_size[1]
//                const emxArray_real_T *wPk
//                const int iInf_data[]
//                const int iInf_size[1]
//                int iPkOut_data[]
//                int iPkOut_size[1]
//                emxArray_real_T *bPkOut
//                emxArray_real_T *bxPkOut
//                emxArray_real_T *byPkOut
//                emxArray_real_T *wxPkOut
// Return Type  : void
//
static void b_combineFullPeaks(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const emxArray_real_T *wPk, const int iInf_data[], const int
  iInf_size[1], int iPkOut_data[], int iPkOut_size[1], emxArray_real_T *bPkOut,
  emxArray_real_T *bxPkOut, emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut)
{
  static int c_data[15000];
  int c_size[1];
  static int ia_data[7500];
  int ia_size[1];
  static int ib_data[7500];
  int ib_size[1];
  static int b_c_data[7500];
  int b_c_size[1];
  int loop_ub;
  int u0;
  int iFinite_data[7000];
  static int iInfinite_data[7500];
  int b_iInfinite_data[7000];
  short unnamed_idx_0;
  int varargin_1_data[7000];
  int iInfR_data[7000];
  short tmp_data[7000];
  int i15;
  do_vectors(iPk_data, iPk_size, iInf_data, iInf_size, c_data, c_size, ia_data,
             ia_size, ib_data, ib_size);
  b_do_vectors(c_data, c_size, iPk_data, iPk_size, b_c_data, b_c_size, ia_data,
               ia_size, ib_data, ib_size);
  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    iFinite_data[u0] = ia_data[u0];
  }

  b_do_vectors(c_data, c_size, iInf_data, iInf_size, b_c_data, b_c_size, ia_data,
               ia_size, ib_data, ib_size);
  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    iInfinite_data[u0] = ia_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    b_iInfinite_data[u0] = ia_data[u0];
  }

  iPkOut_size[0] = c_size[0];
  loop_ub = c_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    iPkOut_data[u0] = c_data[u0];
  }

  unnamed_idx_0 = (short)iPkOut_size[0];
  u0 = bPkOut->size[0];
  bPkOut->size[0] = unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)bPkOut, u0, sizeof(double));
  loop_ub = unnamed_idx_0;
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut->data[u0] = 0.0;
  }

  loop_ub = bPk_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut->data[iFinite_data[u0] - 1] = bPk_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    varargin_1_data[u0] = iInfinite_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut->data[varargin_1_data[u0] - 1] = 0.0;
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    ia_data[u0] = iInf_data[u0] - 1;
  }

  for (loop_ub = 0; loop_ub + 1 <= (short)iInf_size[0]; loop_ub++) {
    if (ia_data[loop_ub] < 1) {
      ib_data[loop_ub] = 1;
    } else {
      ib_data[loop_ub] = ia_data[loop_ub];
    }
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    varargin_1_data[u0] = iInf_data[u0] + 1;
  }

  for (loop_ub = 0; loop_ub + 1 <= (short)iInf_size[0]; loop_ub++) {
    u0 = varargin_1_data[loop_ub];
    if (!(u0 < 7000)) {
      u0 = 7000;
    }

    iInfR_data[loop_ub] = u0;
  }

  u0 = bxPkOut->size[0] * bxPkOut->size[1];
  bxPkOut->size[0] = iPkOut_size[0];
  bxPkOut->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)bxPkOut, u0, sizeof(double));
  loop_ub = iPkOut_size[0] << 1;
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[u0] = 0.0;
  }

  loop_ub = iLBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    tmp_data[u0] = (short)(1 + (short)(iLBw_data[u0] - 1));
  }

  loop_ub = iLBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[iFinite_data[u0] - 1] = tmp_data[u0];
  }

  loop_ub = iRBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    tmp_data[u0] = (short)(1 + (short)(iRBw_data[u0] - 1));
  }

  loop_ub = iRBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[(iFinite_data[u0] + bxPkOut->size[0]) - 1] = tmp_data[u0];
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[b_iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)
      ((short)(iInf_data[u0] - 1) + (short)(ib_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[(b_iInfinite_data[u0] + bxPkOut->size[0]) - 1] = 0.5 * (double)
      (short)((short)((short)(iInf_data[u0] - 1) + (short)(iInfR_data[u0] - 1))
              + 2);
  }

  u0 = byPkOut->size[0] * byPkOut->size[1];
  byPkOut->size[0] = iPkOut_size[0];
  byPkOut->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)byPkOut, u0, sizeof(double));
  loop_ub = iPkOut_size[0] << 1;
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[u0] = 0.0;
  }

  loop_ub = iLBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[iFinite_data[u0] - 1] = y[iLBw_data[u0] - 1];
  }

  loop_ub = iRBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[(iFinite_data[u0] + byPkOut->size[0]) - 1] = y[iRBw_data[u0] -
      1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[b_iInfinite_data[u0] - 1] = y[ib_data[u0] - 1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[(b_iInfinite_data[u0] + byPkOut->size[0]) - 1] =
      y[iInfR_data[u0] - 1];
  }

  u0 = wxPkOut->size[0] * wxPkOut->size[1];
  wxPkOut->size[0] = iPkOut_size[0];
  wxPkOut->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)wxPkOut, u0, sizeof(double));
  loop_ub = iPkOut_size[0] << 1;
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[u0] = 0.0;
  }

  for (u0 = 0; u0 < 2; u0++) {
    loop_ub = wPk->size[0];
    for (i15 = 0; i15 < loop_ub; i15++) {
      wxPkOut->data[(iFinite_data[i15] + wxPkOut->size[0] * u0) - 1] = wPk->
        data[i15 + wPk->size[0] * u0];
    }
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[b_iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)
      ((short)(iInf_data[u0] - 1) + (short)(ib_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[(b_iInfinite_data[u0] + wxPkOut->size[0]) - 1] = 0.5 * (double)
      (short)((short)((short)(iInf_data[u0] - 1) + (short)(iInfR_data[u0] - 1))
              + 2);
  }
}

//
// Arguments    : const int a_data[]
//                const int a_size[1]
//                const int b_data[]
//                const int b_size[1]
//                int c_data[]
//                int c_size[1]
//                int ia_data[]
//                int ia_size[1]
//                int ib_data[]
//                int ib_size[1]
// Return Type  : void
//
static void b_do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1])
{
  int iafirst;
  int ncmax;
  int nc;
  int ialast;
  int ibfirst;
  int iblast;
  int b_ialast;
  int ak;
  int b_iblast;
  int b_ia_data[7500];
  int bk;
  iafirst = a_size[0];
  ncmax = b_size[0];
  if (iafirst < ncmax) {
    ncmax = iafirst;
  }

  c_size[0] = (short)ncmax;
  ia_size[0] = ncmax;
  ib_size[0] = ncmax;
  nc = 0;
  iafirst = 0;
  ialast = 1;
  ibfirst = 0;
  iblast = 1;
  while ((ialast <= a_size[0]) && (iblast <= b_size[0])) {
    b_ialast = ialast;
    ak = a_data[ialast - 1];
    while ((b_ialast < a_size[0]) && (a_data[b_ialast] == ak)) {
      b_ialast++;
    }

    ialast = b_ialast;
    b_iblast = iblast;
    bk = b_data[iblast - 1];
    while ((b_iblast < b_size[0]) && (b_data[b_iblast] == bk)) {
      b_iblast++;
    }

    iblast = b_iblast;
    if (ak == bk) {
      nc++;
      c_data[nc - 1] = ak;
      ia_data[nc - 1] = iafirst + 1;
      ib_data[nc - 1] = ibfirst + 1;
      ialast = b_ialast + 1;
      iafirst = b_ialast;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      ialast = b_ialast + 1;
      iafirst = b_ialast;
    } else {
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    }
  }

  if (ncmax > 0) {
    if (1 > nc) {
      iafirst = 0;
    } else {
      iafirst = nc;
    }

    for (ialast = 0; ialast < iafirst; ialast++) {
      b_ia_data[ialast] = ia_data[ialast];
    }

    ia_size[0] = iafirst;
    for (ialast = 0; ialast < iafirst; ialast++) {
      ia_data[ialast] = b_ia_data[ialast];
    }

    if (1 > nc) {
      iafirst = 0;
    } else {
      iafirst = nc;
    }

    for (ialast = 0; ialast < iafirst; ialast++) {
      b_ia_data[ialast] = ib_data[ialast];
    }

    ib_size[0] = iafirst;
    for (ialast = 0; ialast < iafirst; ialast++) {
      ib_data[ialast] = b_ia_data[ialast];
    }

    if (1 > nc) {
      iafirst = 0;
    } else {
      iafirst = nc;
    }

    for (ialast = 0; ialast < iafirst; ialast++) {
      b_ia_data[ialast] = c_data[ialast];
    }

    c_size[0] = iafirst;
    for (ialast = 0; ialast < iafirst; ialast++) {
      c_data[ialast] = b_ia_data[ialast];
    }
  }
}

//
// Arguments    : const double b[2]
//                const double x[7506]
//                double zi
//                double y[7506]
// Return Type  : void
//
static void b_filter(const double b[2], const double x[7506], double zi, double
                     y[7506])
{
  int k;
  int j;
  y[0] = zi;
  memset(&y[1], 0, 7505U * sizeof(double));
  for (k = 0; k < 2; k++) {
    for (j = k; j + 1 < 7507; j++) {
      y[j] += b[k] * x[j - k];
    }
  }
}

//
// Arguments    : const double x_in[7500]
//                double y_out[7500]
// Return Type  : void
//
static void b_filtfilt(const double x_in[7500], double y_out[7500])
{
  double d4;
  double d5;
  int i0;
  double y[7506];
  double b_y[7506];
  double dv9[2];
  d4 = 2.0 * x_in[0];
  d5 = 2.0 * x_in[7499];
  for (i0 = 0; i0 < 3; i0++) {
    y[i0] = d4 - x_in[3 - i0];
  }

  memcpy(&y[3], &x_in[0], 7500U * sizeof(double));
  for (i0 = 0; i0 < 3; i0++) {
    y[i0 + 7503] = d5 - x_in[7498 - i0];
  }

  for (i0 = 0; i0 < 2; i0++) {
    dv9[i0] = 7.8125 + -16.5625 * (double)i0;
  }

  memcpy(&b_y[0], &y[0], 7506U * sizeof(double));
  b_filter(dv9, b_y, -8.75 * y[0], y);
  b_flipud(y);
  for (i0 = 0; i0 < 2; i0++) {
    dv9[i0] = 7.8125 + -16.5625 * (double)i0;
  }

  memcpy(&b_y[0], &y[0], 7506U * sizeof(double));
  b_filter(dv9, b_y, -8.75 * y[0], y);
  b_flipud(y);
  memcpy(&y_out[0], &y[3], 7500U * sizeof(double));
}

//
// Arguments    : const double y[7000]
//                int iPk_data[]
//                int iPk_size[1]
//                const int iFin_data[]
//                const int iFin_size[1]
//                const int iInf_data[]
//                const int iInf_size[1]
//                const int iInflect_data[]
//                const int iInflect_size[1]
//                emxArray_real_T *bPk
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void b_findExtents(const double y[7000], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  emxArray_real_T *bPk, emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk)
{
  static double yFinite[7000];
  int loop_ub;
  int i23;
  static double bPk_data[7000];
  int bPk_size[1];
  static int iLB_data[7000];
  int iLB_size[1];
  static int iRB_data[7000];
  int iRB_size[1];
  int b_iPk_size[1];
  emxArray_real_T *b_wxPk;
  static int b_iPk_data[7000];
  memcpy(&yFinite[0], &y[0], 7000U * sizeof(double));
  loop_ub = iInf_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    yFinite[iInf_data[i23] - 1] = rtNaN;
  }

  b_getPeakBase(yFinite, iPk_data, iPk_size, iFin_data, iFin_size, iInflect_data,
                iInflect_size, bPk_data, bPk_size, iLB_data, iLB_size, iRB_data,
                iRB_size);
  b_iPk_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    b_iPk_data[i23] = iPk_data[i23];
  }

  emxInit_real_T(&b_wxPk, 2);
  d_removePeaksBelowMinPeakPromin(yFinite, b_iPk_data, b_iPk_size, bPk_data,
    bPk_size, iLB_data, iLB_size, iRB_data, iRB_size);
  b_getPeakWidth(yFinite, b_iPk_data, b_iPk_size, bPk_data, bPk_size, iLB_data,
                 iLB_size, iRB_data, iRB_size, b_wxPk);
  b_combineFullPeaks(y, b_iPk_data, b_iPk_size, bPk_data, bPk_size, iLB_data,
                     iLB_size, iRB_data, iRB_size, b_wxPk, iInf_data, iInf_size,
                     iPk_data, iPk_size, bPk, bxPk, byPk, wxPk);
  emxFree_real_T(&b_wxPk);
}

//
// Arguments    : const double y[7000]
//                int *idx
//                int borderIdx
//                double refHeight
// Return Type  : void
//
static void b_findLeftIntercept(const double y[7000], int *idx, int borderIdx,
  double refHeight)
{
  while ((*idx >= borderIdx) && (y[*idx - 1] > refHeight)) {
    (*idx)--;
  }
}

//
// Arguments    : const double y[7000]
//                int *idx
//                int borderIdx
//                double refHeight
// Return Type  : void
//
static void b_findRightIntercept(const double y[7000], int *idx, int borderIdx,
  double refHeight)
{
  while ((*idx <= borderIdx) && (y[*idx - 1] > refHeight)) {
    (*idx)++;
  }
}

//
// Arguments    : const double Yin[7500]
//                emxArray_real_T *Ypk
//                emxArray_real_T *Xpk
// Return Type  : void
//
static void b_findpeaks(const double Yin[7500], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk)
{
  static int iFinite_data[7500];
  int iFinite_size[1];
  static int iInfinite_data[7500];
  int iInfinite_size[1];
  static int iInflect_data[7500];
  int iInflect_size[1];
  static int tmp_data[7500];
  int tmp_size[1];
  int iPk_size[1];
  int loop_ub;
  int i3;
  emxArray_real_T *bPk;
  static int iPk_data[15000];
  emxArray_real_T *bxPk;
  emxArray_real_T *byPk;
  emxArray_real_T *wxPk;
  static int idx_data[15000];
  int b_iPk_size[1];
  emxArray_real_T *Wpk;
  static int b_iPk_data[15000];
  emxArray_real_T *Ppk;
  b_getAllPeaksCodegen(Yin, iFinite_data, iFinite_size, iInfinite_data,
                       iInfinite_size, iInflect_data, iInflect_size);
  b_removeSmallPeaks(Yin, iFinite_data, iFinite_size, tmp_data, tmp_size);
  iPk_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    iPk_data[i3] = tmp_data[i3];
  }

  emxInit_real_T1(&bPk, 1);
  emxInit_real_T(&bxPk, 2);
  emxInit_real_T(&byPk, 2);
  emxInit_real_T(&wxPk, 2);
  findExtents(Yin, iPk_data, iPk_size, iFinite_data, iFinite_size,
              iInfinite_data, iInfinite_size, iInflect_data, iInflect_size, bPk,
              bxPk, byPk, wxPk);
  d_findPeaksSeparatedByMoreThanM(iPk_size, idx_data, iFinite_size);
  b_keepAtMostNpPeaks(idx_data, iFinite_size);
  fetchPeakExtents(idx_data, iFinite_size, bPk, bxPk, byPk, wxPk);
  b_iPk_size[0] = iFinite_size[0];
  loop_ub = iFinite_size[0];
  emxFree_real_T(&byPk);
  emxFree_real_T(&bxPk);
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_iPk_data[i3] = iPk_data[idx_data[i3] - 1];
  }

  emxInit_real_T1(&Wpk, 1);
  emxInit_real_T1(&Ppk, 1);
  assignFullOutputs(Yin, b_iPk_data, b_iPk_size, wxPk, bPk, Ypk, Xpk, Wpk, Ppk);
  emxFree_real_T(&Ppk);
  emxFree_real_T(&Wpk);
  emxFree_real_T(&wxPk);
  emxFree_real_T(&bPk);
}

//
// Arguments    : double x[7506]
// Return Type  : void
//
static void b_flipud(double x[7506])
{
  int i;
  double xtmp;
  for (i = 0; i < 3753; i++) {
    xtmp = x[i];
    x[i] = x[7505 - i];
    x[7505 - i] = xtmp;
  }
}

//
// Arguments    : const double y[7500]
//                int iPk_data[]
//                int iPk_size[1]
//                int iInf_data[]
//                int iInf_size[1]
//                int iInflect_data[]
//                int iInflect_size[1]
// Return Type  : void
//
static void b_getAllPeaksCodegen(const double y[7500], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1])
{
  int nPk;
  int nInf;
  int nInflect;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  int i4;
  nPk = 0;
  nInf = 0;
  nInflect = -1;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 7500; k++) {
    yk = y[k];
    if (rtIsNaN(y[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(y[k]) && (y[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInf_data[nInf - 1] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
        if (kfirst >= 1) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
        }
      } else if (yk < ykfirst) {
        dir = 'd';
        if ('d' != previousdir) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
          if (previousdir == 'i') {
            nPk++;
            iPk_data[nPk - 1] = kfirst;
          }
        }
      } else {
        dir = 'i';
        if ('i' != previousdir) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
        }
      }

      ykfirst = yk;
      kfirst = k + 1;
      isinfykfirst = isinfyk;
    }
  }

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect_data[nInflect] < 7500)))
  {
    nInflect++;
    iInflect_data[nInflect] = 7500;
  }

  if (1 > nPk) {
    iPk_size[0] = 0;
  } else {
    iPk_size[0] = nPk;
  }

  if (1 > nInf) {
    iInf_size[0] = 0;
  } else {
    iInf_size[0] = nInf;
  }

  if (1 > nInflect + 1) {
    i4 = -1;
  } else {
    i4 = nInflect;
  }

  iInflect_size[0] = i4 + 1;
}

//
// Arguments    : const double y[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const double base_data[]
//                const int iLB_data[]
//                const int iRB_data[]
//                emxArray_real_T *bounds
// Return Type  : void
//
static void b_getHalfMaxBounds(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], emxArray_real_T *bounds)
{
  int iLeft;
  int iRight;
  int i;
  double refHeight;
  iLeft = bounds->size[0] * bounds->size[1];
  bounds->size[0] = iPk_size[0];
  bounds->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)bounds, iLeft, sizeof(double));
  iRight = iPk_size[0] << 1;
  for (iLeft = 0; iLeft < iRight; iLeft++) {
    bounds->data[iLeft] = 0.0;
  }

  for (i = 0; i < iPk_size[0]; i++) {
    refHeight = (y[iPk_data[i] - 1] + base_data[i]) / 2.0;
    iLeft = iPk_data[i];
    b_findLeftIntercept(y, &iLeft, iLB_data[i], refHeight);
    if (iLeft < iLB_data[i]) {
      bounds->data[i] = 1.0 + ((double)iLB_data[i] - 1.0);
    } else {
      bounds->data[i] = linterp(1.0 + ((double)iLeft - 1.0), 1.0 + ((double)
        (iLeft + 1) - 1.0), y[iLeft - 1], y[iLeft], y[iPk_data[i] - 1],
        base_data[i]);
    }

    iRight = iPk_data[i];
    b_findRightIntercept(y, &iRight, iRB_data[i], refHeight);
    if (iRight > iRB_data[i]) {
      bounds->data[i + bounds->size[0]] = 1.0 + ((double)iRB_data[i] - 1.0);
    } else {
      bounds->data[i + bounds->size[0]] = linterp(1.0 + ((double)iRight - 1.0),
        1.0 + ((double)(iRight - 1) - 1.0), y[iRight - 1], y[iRight - 2],
        y[iPk_data[i] - 1], base_data[i]);
    }
  }
}

//
// Arguments    : const double yTemp[7000]
//                const int iPeak_data[]
//                const int iPeak_size[1]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                const int iInflect_data[]
//                int iBase_data[]
//                int iBase_size[1]
//                int iSaddle_data[]
//                int iSaddle_size[1]
// Return Type  : void
//
static void b_getLeftBase(const double yTemp[7000], const int iPeak_data[],
  const int iPeak_size[1], const int iFinite_data[], const int iFinite_size[1],
  const int iInflect_data[], int iBase_data[], int iBase_size[1], int
  iSaddle_data[], int iSaddle_size[1])
{
  int n;
  int i;
  static double peak_data[7000];
  static double valley_data[7000];
  int iValley_data[7000];
  int j;
  int k;
  double v;
  int iv;
  double p;
  int isv;
  iBase_size[0] = (short)iPeak_size[0];
  n = (short)iPeak_size[0];
  for (i = 0; i < n; i++) {
    iBase_data[i] = 0;
  }

  iSaddle_size[0] = (short)iPeak_size[0];
  n = (short)iPeak_size[0];
  for (i = 0; i < n; i++) {
    iSaddle_data[i] = 0;
  }

  n = (short)iFinite_size[0];
  for (i = 0; i < n; i++) {
    peak_data[i] = 0.0;
  }

  n = (short)iFinite_size[0];
  for (i = 0; i < n; i++) {
    valley_data[i] = 0.0;
  }

  n = (short)iFinite_size[0];
  for (i = 0; i < n; i++) {
    iValley_data[i] = 0;
  }

  n = -1;
  i = 0;
  j = 0;
  k = 0;
  v = rtNaN;
  iv = 1;
  while (k + 1 <= iPeak_size[0]) {
    while (iInflect_data[i] != iFinite_data[j]) {
      v = yTemp[iInflect_data[i] - 1];
      iv = iInflect_data[i];
      if (rtIsNaN(yTemp[iInflect_data[i] - 1])) {
        n = -1;
      } else {
        while ((n + 1 > 0) && (valley_data[n] > v)) {
          n--;
        }
      }

      i++;
    }

    p = yTemp[iInflect_data[i] - 1];
    while ((n + 1 > 0) && (peak_data[n] < p)) {
      if (valley_data[n] < v) {
        v = valley_data[n];
        iv = iValley_data[n];
      }

      n--;
    }

    isv = iv;
    while ((n + 1 > 0) && (peak_data[n] <= p)) {
      if (valley_data[n] < v) {
        v = valley_data[n];
        iv = iValley_data[n];
      }

      n--;
    }

    n++;
    peak_data[n] = yTemp[iInflect_data[i] - 1];
    valley_data[n] = v;
    iValley_data[n] = iv;
    if (iInflect_data[i] == iPeak_data[k]) {
      iBase_data[k] = iv;
      iSaddle_data[k] = isv;
      k++;
    }

    i++;
    j++;
  }
}

//
// Arguments    : const double yTemp[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const int iFin_data[]
//                const int iFin_size[1]
//                const int iInflect_data[]
//                const int iInflect_size[1]
//                double peakBase_data[]
//                int peakBase_size[1]
//                int iLeftSaddle_data[]
//                int iLeftSaddle_size[1]
//                int iRightSaddle_data[]
//                int iRightSaddle_size[1]
// Return Type  : void
//
static void b_getPeakBase(const double yTemp[7000], const int iPk_data[], const
  int iPk_size[1], const int iFin_data[], const int iFin_size[1], const int
  iInflect_data[], const int iInflect_size[1], double peakBase_data[], int
  peakBase_size[1], int iLeftSaddle_data[], int iLeftSaddle_size[1], int
  iRightSaddle_data[], int iRightSaddle_size[1])
{
  int iLeftBase_data[7000];
  int iLeftBase_size[1];
  int tmp_size[1];
  int loop_ub;
  int i14;
  int tmp_data[7500];
  int b_tmp_size[1];
  int b_tmp_data[7500];
  int c_tmp_size[1];
  int c_tmp_data[7500];
  int iRightBase_data[7000];
  short csz_idx_0;
  static double maxval_data[7500];
  b_getLeftBase(yTemp, iPk_data, iPk_size, iFin_data, iFin_size, iInflect_data,
                iLeftBase_data, iLeftBase_size, iLeftSaddle_data,
                iLeftSaddle_size);
  tmp_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    tmp_data[i14] = iPk_data[i14];
  }

  c_flipud(tmp_data, tmp_size);
  b_tmp_size[0] = iFin_size[0];
  loop_ub = iFin_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    b_tmp_data[i14] = iFin_data[i14];
  }

  c_flipud(b_tmp_data, b_tmp_size);
  c_tmp_size[0] = iInflect_size[0];
  loop_ub = iInflect_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    c_tmp_data[i14] = iInflect_data[i14];
  }

  c_flipud(c_tmp_data, c_tmp_size);
  b_getLeftBase(yTemp, tmp_data, tmp_size, b_tmp_data, b_tmp_size, c_tmp_data,
                iRightBase_data, c_tmp_size, iRightSaddle_data,
                iRightSaddle_size);
  tmp_size[0] = c_tmp_size[0];
  loop_ub = c_tmp_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    tmp_data[i14] = iRightBase_data[i14];
  }

  c_flipud(tmp_data, tmp_size);
  c_tmp_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    iRightBase_data[i14] = tmp_data[i14];
  }

  tmp_size[0] = iRightSaddle_size[0];
  loop_ub = iRightSaddle_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    tmp_data[i14] = iRightSaddle_data[i14];
  }

  c_flipud(tmp_data, tmp_size);
  iRightSaddle_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i14 = 0; i14 < loop_ub; i14++) {
    iRightSaddle_data[i14] = tmp_data[i14];
  }

  if (iLeftBase_size[0] <= c_tmp_size[0]) {
    csz_idx_0 = (short)iLeftBase_size[0];
  } else {
    csz_idx_0 = (short)c_tmp_size[0];
  }

  for (loop_ub = 0; loop_ub + 1 <= csz_idx_0; loop_ub++) {
    if ((yTemp[iLeftBase_data[loop_ub] - 1] > yTemp[iRightBase_data[loop_ub] - 1])
        || rtIsNaN(yTemp[iRightBase_data[loop_ub] - 1])) {
      maxval_data[loop_ub] = yTemp[iLeftBase_data[loop_ub] - 1];
    } else {
      maxval_data[loop_ub] = yTemp[iRightBase_data[loop_ub] - 1];
    }
  }

  peakBase_size[0] = csz_idx_0;
  loop_ub = csz_idx_0;
  for (i14 = 0; i14 < loop_ub; i14++) {
    peakBase_data[i14] = maxval_data[i14];
  }
}

//
// Arguments    : const double y[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const double pbPk_data[]
//                const int pbPk_size[1]
//                int iLB_data[]
//                int iLB_size[1]
//                int iRB_data[]
//                int iRB_size[1]
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void b_getPeakWidth(const double y[7000], const int iPk_data[], const int
  iPk_size[1], const double pbPk_data[], const int pbPk_size[1], int iLB_data[],
  int iLB_size[1], int iRB_data[], int iRB_size[1], emxArray_real_T *wxPk)
{
  int loop_ub;
  int i24;
  double base_data[7000];
  if (iPk_size[0] == 0) {
    iLB_size[0] = 0;
    iRB_size[0] = 0;
  } else {
    loop_ub = pbPk_size[0];
    for (i24 = 0; i24 < loop_ub; i24++) {
      base_data[i24] = pbPk_data[i24];
    }
  }

  b_getHalfMaxBounds(y, iPk_data, iPk_size, base_data, iLB_data, iRB_data, wxPk);
}

//
// Arguments    : int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void b_keepAtMostNpPeaks(int idx_data[], int idx_size[1])
{
  int b_idx_data[15000];
  int i20;
  if (idx_size[0] > 7500) {
    memcpy(&b_idx_data[0], &idx_data[0], 7500U * sizeof(int));
    idx_size[0] = 7500;
    for (i20 = 0; i20 < 7500; i20++) {
      idx_data[i20] = b_idx_data[i20];
    }
  }
}

//
// Arguments    : const emxArray_real_T *x
// Return Type  : double
//
static double b_mean(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[1] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[1]; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (double)x->size[1];
  return y;
}

//
// Arguments    : const emxArray_real_T *x
//                const emxArray_real_T *y
//                int yoffset
//                const emxArray_real_T *s
//                const emxArray_real_T *dx
//                const emxArray_real_T *divdif
//                emxArray_real_T *pp_breaks
//                emxArray_real_T *pp_coefs
// Return Type  : void
//
static void b_pwchcore(const emxArray_real_T *x, const emxArray_real_T *y, int
  yoffset, const emxArray_real_T *s, const emxArray_real_T *dx, const
  emxArray_real_T *divdif, emxArray_real_T *pp_breaks, emxArray_real_T *pp_coefs)
{
  int nx;
  int nxm1;
  int x_idx_0;
  int i11;
  short szc_idx_1;
  double dxj;
  double dzzdx;
  double dzdxdx;
  nx = x->size[0] - 1;
  nxm1 = x->size[0] - 1;
  x_idx_0 = x->size[0];
  i11 = pp_breaks->size[0] * pp_breaks->size[1];
  pp_breaks->size[0] = 1;
  pp_breaks->size[1] = x_idx_0;
  emxEnsureCapacity((emxArray__common *)pp_breaks, i11, sizeof(double));
  for (i11 = 0; i11 < x_idx_0; i11++) {
    pp_breaks->data[pp_breaks->size[0] * i11] = x->data[i11];
  }

  szc_idx_1 = (short)(x->size[0] - 1);
  i11 = pp_coefs->size[0] * pp_coefs->size[1] * pp_coefs->size[2];
  pp_coefs->size[0] = 1;
  pp_coefs->size[1] = szc_idx_1;
  pp_coefs->size[2] = 4;
  emxEnsureCapacity((emxArray__common *)pp_coefs, i11, sizeof(double));
  for (x_idx_0 = 0; x_idx_0 + 1 <= nx; x_idx_0++) {
    dxj = dx->data[x_idx_0];
    dzzdx = (divdif->data[x_idx_0] - s->data[x_idx_0]) / dxj;
    dzdxdx = (s->data[x_idx_0 + 1] - divdif->data[x_idx_0]) / dxj;
    pp_coefs->data[x_idx_0] = (dzdxdx - dzzdx) / dxj;
    pp_coefs->data[nx + x_idx_0] = 2.0 * dzzdx - dzdxdx;
    pp_coefs->data[(nxm1 << 1) + x_idx_0] = s->data[x_idx_0];
    pp_coefs->data[3 * nxm1 + x_idx_0] = y->data[yoffset + x_idx_0];
  }
}

//
// Arguments    : const double y[7500]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                int iPk_data[]
//                int iPk_size[1]
// Return Type  : void
//
static void b_removeSmallPeaks(const double y[7500], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1])
{
  int nPk;
  int k;
  double b_y;
  nPk = 0;
  for (k = 0; k + 1 <= iFinite_size[0]; k++) {
    if (y[iFinite_data[k] - 1] > rtMinusInf) {
      if ((y[iFinite_data[k] - 2] > y[iFinite_data[k]]) || rtIsNaN
          (y[iFinite_data[k]])) {
        b_y = y[iFinite_data[k] - 2];
      } else {
        b_y = y[iFinite_data[k]];
      }

      if (y[iFinite_data[k] - 1] - b_y >= 0.0) {
        nPk++;
        iPk_data[nPk - 1] = iFinite_data[k];
      }
    }
  }

  if (1 > nPk) {
    iPk_size[0] = 0;
  } else {
    iPk_size[0] = nPk;
  }
}

//
// Arguments    : const double X[7000]
//                double Y[7000]
// Return Type  : void
//
static void b_rescale_minmax(const double X[7000], double Y[7000])
{
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg1;
  double b_mtmp;
  ixstart = 1;
  mtmp = X[0];
  if (rtIsNaN(X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7001)) {
      ixstart = ix;
      if (!rtIsNaN(X[ix - 1])) {
        mtmp = X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 7000) {
    while (ixstart + 1 < 7001) {
      if (X[ixstart] < mtmp) {
        mtmp = X[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = X[0];
  if (rtIsNaN(X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7001)) {
      ixstart = ix;
      if (!rtIsNaN(X[ix - 1])) {
        b_mtmp = X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 7000) {
    while (ixstart + 1 < 7001) {
      if (X[ixstart] > b_mtmp) {
        b_mtmp = X[ixstart];
      }

      ixstart++;
    }
  }

  b_mtmp -= mtmp;
  for (ixstart = 0; ixstart < 7000; ixstart++) {
    Y[ixstart] = (X[ixstart] - mtmp) / b_mtmp;
  }
}

//
// Arguments    : const int iPk_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void c_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1])
{
  int n;
  static int y_data[15000];
  int yk;
  int k;
  if (iPk_size[0] < 1) {
    n = 0;
  } else {
    n = iPk_size[0];
  }

  if (n > 0) {
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
  }

  idx_size[0] = n;
  for (yk = 0; yk < n; yk++) {
    idx_data[yk] = y_data[yk];
  }
}

//
// Arguments    : const double Yin[7000]
//                emxArray_real_T *Ypk
//                emxArray_real_T *Xpk
// Return Type  : void
//
static void c_findpeaks(const double Yin[7000], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk)
{
  static int iFinite_data[7000];
  int iFinite_size[1];
  static int iInfinite_data[7000];
  int iInfinite_size[1];
  static int iInflect_data[7000];
  int iInflect_size[1];
  static int tmp_data[7000];
  int tmp_size[1];
  int iPk_size[1];
  int loop_ub;
  int i12;
  emxArray_real_T *bPk;
  static int iPk_data[14926];
  emxArray_real_T *bxPk;
  emxArray_real_T *byPk;
  emxArray_real_T *wxPk;
  emxArray_real_T *b_bPk;
  static int idx_data[14926];
  emxArray_real_T *b_bxPk;
  emxArray_real_T *b_byPk;
  emxArray_real_T *b_wxPk;
  int b_iPk_size[1];
  emxArray_real_T *Wpk;
  static int b_iPk_data[14926];
  emxArray_real_T *Ppk;
  c_getAllPeaksCodegen(Yin, iFinite_data, iFinite_size, iInfinite_data,
                       iInfinite_size, iInflect_data, iInflect_size);
  c_removeSmallPeaks(Yin, iFinite_data, iFinite_size, tmp_data, tmp_size);
  iPk_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i12 = 0; i12 < loop_ub; i12++) {
    iPk_data[i12] = tmp_data[i12];
  }

  emxInit_real_T1(&bPk, 1);
  emxInit_real_T(&bxPk, 2);
  emxInit_real_T(&byPk, 2);
  emxInit_real_T(&wxPk, 2);
  emxInit_real_T1(&b_bPk, 1);
  b_findExtents(Yin, iPk_data, iPk_size, iFinite_data, iFinite_size,
                iInfinite_data, iInfinite_size, iInflect_data, iInflect_size,
                bPk, bxPk, byPk, wxPk);
  e_findPeaksSeparatedByMoreThanM(iPk_size, idx_data, iFinite_size);
  c_keepAtMostNpPeaks(idx_data, iFinite_size);
  i12 = b_bPk->size[0];
  b_bPk->size[0] = bPk->size[0];
  emxEnsureCapacity((emxArray__common *)b_bPk, i12, sizeof(double));
  loop_ub = bPk->size[0];
  for (i12 = 0; i12 < loop_ub; i12++) {
    b_bPk->data[i12] = bPk->data[i12];
  }

  emxFree_real_T(&bPk);
  emxInit_real_T(&b_bxPk, 2);
  i12 = b_bxPk->size[0] * b_bxPk->size[1];
  b_bxPk->size[0] = bxPk->size[0];
  b_bxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_bxPk, i12, sizeof(double));
  loop_ub = bxPk->size[0] * bxPk->size[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    b_bxPk->data[i12] = bxPk->data[i12];
  }

  emxFree_real_T(&bxPk);
  emxInit_real_T(&b_byPk, 2);
  i12 = b_byPk->size[0] * b_byPk->size[1];
  b_byPk->size[0] = byPk->size[0];
  b_byPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_byPk, i12, sizeof(double));
  loop_ub = byPk->size[0] * byPk->size[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    b_byPk->data[i12] = byPk->data[i12];
  }

  emxFree_real_T(&byPk);
  emxInit_real_T(&b_wxPk, 2);
  i12 = b_wxPk->size[0] * b_wxPk->size[1];
  b_wxPk->size[0] = wxPk->size[0];
  b_wxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_wxPk, i12, sizeof(double));
  loop_ub = wxPk->size[0] * wxPk->size[1];
  for (i12 = 0; i12 < loop_ub; i12++) {
    b_wxPk->data[i12] = wxPk->data[i12];
  }

  emxFree_real_T(&wxPk);
  fetchPeakExtents(idx_data, iFinite_size, b_bPk, b_bxPk, b_byPk, b_wxPk);
  b_iPk_size[0] = iFinite_size[0];
  loop_ub = iFinite_size[0];
  emxFree_real_T(&b_byPk);
  emxFree_real_T(&b_bxPk);
  for (i12 = 0; i12 < loop_ub; i12++) {
    b_iPk_data[i12] = iPk_data[idx_data[i12] - 1];
  }

  emxInit_real_T(&Wpk, 2);
  emxInit_real_T(&Ppk, 2);
  b_assignFullOutputs(Yin, b_iPk_data, b_iPk_size, b_wxPk, b_bPk, Ypk, Xpk, Wpk,
                      Ppk);
  emxFree_real_T(&b_wxPk);
  emxFree_real_T(&b_bPk);
  emxFree_real_T(&Ppk);
  emxFree_real_T(&Wpk);
}

//
// Arguments    : int x_data[]
//                int x_size[1]
// Return Type  : void
//
static void c_flipud(int x_data[], int x_size[1])
{
  int m;
  int md2;
  int i;
  int xtmp;
  m = x_size[0];
  md2 = x_size[0] >> 1;
  for (i = 1; i <= md2; i++) {
    xtmp = x_data[i - 1];
    x_data[i - 1] = x_data[m - i];
    x_data[m - i] = xtmp;
  }
}

//
// Arguments    : const double y[7000]
//                int iPk_data[]
//                int iPk_size[1]
//                int iInf_data[]
//                int iInf_size[1]
//                int iInflect_data[]
//                int iInflect_size[1]
// Return Type  : void
//
static void c_getAllPeaksCodegen(const double y[7000], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1])
{
  int nPk;
  int nInf;
  int nInflect;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  int i13;
  nPk = 0;
  nInf = 0;
  nInflect = -1;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 7000; k++) {
    yk = y[k];
    if (rtIsNaN(y[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(y[k]) && (y[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInf_data[nInf - 1] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
        if (kfirst >= 1) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
        }
      } else if (yk < ykfirst) {
        dir = 'd';
        if ('d' != previousdir) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
          if (previousdir == 'i') {
            nPk++;
            iPk_data[nPk - 1] = kfirst;
          }
        }
      } else {
        dir = 'i';
        if ('i' != previousdir) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
        }
      }

      ykfirst = yk;
      kfirst = k + 1;
      isinfykfirst = isinfyk;
    }
  }

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect_data[nInflect] < 7000)))
  {
    nInflect++;
    iInflect_data[nInflect] = 7000;
  }

  if (1 > nPk) {
    iPk_size[0] = 0;
  } else {
    iPk_size[0] = nPk;
  }

  if (1 > nInf) {
    iInf_size[0] = 0;
  } else {
    iInf_size[0] = nInf;
  }

  if (1 > nInflect + 1) {
    i13 = -1;
  } else {
    i13 = nInflect;
  }

  iInflect_size[0] = i13 + 1;
}

//
// Arguments    : int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void c_keepAtMostNpPeaks(int idx_data[], int idx_size[1])
{
  int b_idx_data[14926];
  int i25;
  if (idx_size[0] > 7000) {
    memcpy(&b_idx_data[0], &idx_data[0], 7000U * sizeof(int));
    idx_size[0] = 7000;
    for (i25 = 0; i25 < 7000; i25++) {
      idx_data[i25] = b_idx_data[i25];
    }
  }
}

//
// Arguments    : const double y[7500]
//                int iPk_data[]
//                int iPk_size[1]
//                double pbPk_data[]
//                int pbPk_size[1]
//                int iLB_data[]
//                int iLB_size[1]
//                int iRB_data[]
//                int iRB_size[1]
// Return Type  : void
//
static void c_removePeaksBelowMinPeakPromin(const double y[7500], int iPk_data[],
  int iPk_size[1], double pbPk_data[], int pbPk_size[1], int iLB_data[], int
  iLB_size[1], int iRB_data[], int iRB_size[1])
{
  int x_size_idx_0;
  int idx;
  int ii;
  boolean_T x_data[7500];
  boolean_T exitg1;
  int ii_data[7500];
  int idx_data[7500];
  double b_pbPk_data[7500];
  x_size_idx_0 = iPk_size[0];
  idx = iPk_size[0];
  for (ii = 0; ii < idx; ii++) {
    x_data[ii] = (y[iPk_data[ii] - 1] - pbPk_data[ii] >= 0.4);
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii <= x_size_idx_0)) {
    if (x_data[ii - 1]) {
      idx++;
      ii_data[idx - 1] = ii;
      if (idx >= x_size_idx_0) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (x_size_idx_0 == 1) {
    if (idx == 0) {
      x_size_idx_0 = 0;
    }
  } else if (1 > idx) {
    x_size_idx_0 = 0;
  } else {
    x_size_idx_0 = idx;
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    idx_data[ii] = ii_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    ii_data[ii] = iPk_data[idx_data[ii] - 1];
  }

  iPk_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    iPk_data[ii] = ii_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    b_pbPk_data[ii] = pbPk_data[idx_data[ii] - 1];
  }

  pbPk_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    pbPk_data[ii] = b_pbPk_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    ii_data[ii] = iLB_data[idx_data[ii] - 1];
  }

  iLB_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    iLB_data[ii] = ii_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    ii_data[ii] = iRB_data[idx_data[ii] - 1];
  }

  iRB_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    iRB_data[ii] = ii_data[ii];
  }
}

//
// Arguments    : const double y[7000]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                int iPk_data[]
//                int iPk_size[1]
// Return Type  : void
//
static void c_removeSmallPeaks(const double y[7000], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1])
{
  int nPk;
  int k;
  double b_y;
  nPk = 0;
  for (k = 0; k + 1 <= iFinite_size[0]; k++) {
    if (y[iFinite_data[k] - 1] > rtMinusInf) {
      if ((y[iFinite_data[k] - 2] > y[iFinite_data[k]]) || rtIsNaN
          (y[iFinite_data[k]])) {
        b_y = y[iFinite_data[k] - 2];
      } else {
        b_y = y[iFinite_data[k]];
      }

      if (y[iFinite_data[k] - 1] - b_y >= 0.0) {
        nPk++;
        iPk_data[nPk - 1] = iFinite_data[k];
      }
    }
  }

  if (1 > nPk) {
    iPk_size[0] = 0;
  } else {
    iPk_size[0] = nPk;
  }
}

//
// Arguments    : const double y[7500]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const double bPk_data[]
//                const int bPk_size[1]
//                const int iLBw_data[]
//                const int iLBw_size[1]
//                const int iRBw_data[]
//                const int iRBw_size[1]
//                const emxArray_real_T *wPk
//                const int iInf_data[]
//                const int iInf_size[1]
//                int iPkOut_data[]
//                int iPkOut_size[1]
//                emxArray_real_T *bPkOut
//                emxArray_real_T *bxPkOut
//                emxArray_real_T *byPkOut
//                emxArray_real_T *wxPkOut
// Return Type  : void
//
static void combineFullPeaks(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const emxArray_real_T *wPk, const int iInf_data[], const int
  iInf_size[1], int iPkOut_data[], int iPkOut_size[1], emxArray_real_T *bPkOut,
  emxArray_real_T *bxPkOut, emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut)
{
  static int ia_data[7500];
  int ia_size[1];
  int iInfR_data[7500];
  int iInfR_size[1];
  int iInfL_data[7500];
  int iInfL_size[1];
  int loop_ub;
  int u0;
  int iFinite_data[7500];
  int iInfinite_data[7500];
  short unnamed_idx_0;
  short tmp_data[7500];
  int i6;
  do_vectors(iPk_data, iPk_size, iInf_data, iInf_size, iPkOut_data, iPkOut_size,
             ia_data, ia_size, iInfR_data, iInfR_size);
  b_do_vectors(iPkOut_data, iPkOut_size, iPk_data, iPk_size, iInfL_data,
               iInfL_size, ia_data, ia_size, iInfR_data, iInfR_size);
  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    iFinite_data[u0] = ia_data[u0];
  }

  b_do_vectors(iPkOut_data, iPkOut_size, iInf_data, iInf_size, iInfL_data,
               iInfL_size, ia_data, ia_size, iInfR_data, iInfR_size);
  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    iInfinite_data[u0] = ia_data[u0];
  }

  loop_ub = iPkOut_size[0];
  iPkOut_size[0] = loop_ub;
  unnamed_idx_0 = (short)iPkOut_size[0];
  u0 = bPkOut->size[0];
  bPkOut->size[0] = unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)bPkOut, u0, sizeof(double));
  loop_ub = unnamed_idx_0;
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut->data[u0] = 0.0;
  }

  loop_ub = bPk_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut->data[iFinite_data[u0] - 1] = bPk_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    ia_data[u0] = iInfinite_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut->data[ia_data[u0] - 1] = 0.0;
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    ia_data[u0] = iInf_data[u0] - 1;
  }

  for (loop_ub = 0; loop_ub + 1 <= (short)iInf_size[0]; loop_ub++) {
    if (ia_data[loop_ub] < 1) {
      iInfL_data[loop_ub] = 1;
    } else {
      iInfL_data[loop_ub] = ia_data[loop_ub];
    }
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    ia_data[u0] = iInf_data[u0] + 1;
  }

  for (loop_ub = 0; loop_ub + 1 <= (short)iInf_size[0]; loop_ub++) {
    u0 = ia_data[loop_ub];
    if (!(u0 < 7500)) {
      u0 = 7500;
    }

    iInfR_data[loop_ub] = u0;
  }

  u0 = bxPkOut->size[0] * bxPkOut->size[1];
  bxPkOut->size[0] = iPkOut_size[0];
  bxPkOut->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)bxPkOut, u0, sizeof(double));
  loop_ub = iPkOut_size[0] << 1;
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[u0] = 0.0;
  }

  loop_ub = iLBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    tmp_data[u0] = (short)(1 + (short)(iLBw_data[u0] - 1));
  }

  loop_ub = iLBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[iFinite_data[u0] - 1] = tmp_data[u0];
  }

  loop_ub = iRBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    tmp_data[u0] = (short)(1 + (short)(iRBw_data[u0] - 1));
  }

  loop_ub = iRBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[(iFinite_data[u0] + bxPkOut->size[0]) - 1] = tmp_data[u0];
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)((short)
      (iInf_data[u0] - 1) + (short)(iInfL_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[(iInfinite_data[u0] + bxPkOut->size[0]) - 1] = 0.5 * (double)
      (short)((short)((short)(iInf_data[u0] - 1) + (short)(iInfR_data[u0] - 1))
              + 2);
  }

  u0 = byPkOut->size[0] * byPkOut->size[1];
  byPkOut->size[0] = iPkOut_size[0];
  byPkOut->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)byPkOut, u0, sizeof(double));
  loop_ub = iPkOut_size[0] << 1;
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[u0] = 0.0;
  }

  loop_ub = iLBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[iFinite_data[u0] - 1] = y[iLBw_data[u0] - 1];
  }

  loop_ub = iRBw_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[(iFinite_data[u0] + byPkOut->size[0]) - 1] = y[iRBw_data[u0] -
      1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[iInfinite_data[u0] - 1] = y[iInfL_data[u0] - 1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[(iInfinite_data[u0] + byPkOut->size[0]) - 1] = y[iInfR_data[u0]
      - 1];
  }

  u0 = wxPkOut->size[0] * wxPkOut->size[1];
  wxPkOut->size[0] = iPkOut_size[0];
  wxPkOut->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)wxPkOut, u0, sizeof(double));
  loop_ub = iPkOut_size[0] << 1;
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[u0] = 0.0;
  }

  for (u0 = 0; u0 < 2; u0++) {
    loop_ub = wPk->size[0];
    for (i6 = 0; i6 < loop_ub; i6++) {
      wxPkOut->data[(iFinite_data[i6] + wxPkOut->size[0] * u0) - 1] = wPk->
        data[i6 + wPk->size[0] * u0];
    }
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)((short)
      (iInf_data[u0] - 1) + (short)(iInfL_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[(iInfinite_data[u0] + wxPkOut->size[0]) - 1] = 0.5 * (double)
      (short)((short)((short)(iInf_data[u0] - 1) + (short)(iInfR_data[u0] - 1))
              + 2);
  }
}

//
// Arguments    : const double A[7500]
//                const double B[38]
//                double C[7463]
// Return Type  : void
//
static void conv(const double A[7500], const double B[38], double C[7463])
{
  int k;
  int b_k;
  memset(&C[0], 0, 7463U * sizeof(double));
  for (k = 0; k < 38; k++) {
    for (b_k = 0; b_k < 7463; b_k++) {
      C[b_k] += B[k] * A[(b_k - k) + 37];
    }
  }
}

//
// Arguments    : const int iPk_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void d_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1])
{
  int n;
  int y_data[15000];
  int yk;
  int k;
  if (iPk_size[0] < 1) {
    n = 0;
  } else {
    n = iPk_size[0];
  }

  if (n > 0) {
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
  }

  idx_size[0] = n;
  for (yk = 0; yk < n; yk++) {
    idx_data[yk] = y_data[yk];
  }
}

//
// Arguments    : const double y[7000]
//                int iPk_data[]
//                int iPk_size[1]
//                double pbPk_data[]
//                int pbPk_size[1]
//                int iLB_data[]
//                int iLB_size[1]
//                int iRB_data[]
//                int iRB_size[1]
// Return Type  : void
//
static void d_removePeaksBelowMinPeakPromin(const double y[7000], int iPk_data[],
  int iPk_size[1], double pbPk_data[], int pbPk_size[1], int iLB_data[], int
  iLB_size[1], int iRB_data[], int iRB_size[1])
{
  int x_size_idx_0;
  int idx;
  int ii;
  boolean_T x_data[7500];
  boolean_T exitg1;
  int ii_data[7500];
  int i_data[7500];
  int b_iPk_data[7000];
  double b_pbPk_data[7000];
  x_size_idx_0 = iPk_size[0];
  idx = iPk_size[0];
  for (ii = 0; ii < idx; ii++) {
    x_data[ii] = (y[iPk_data[ii] - 1] - pbPk_data[ii] >= 0.2); // MinPeakProminence
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii <= x_size_idx_0)) {
    if (x_data[ii - 1]) {
      idx++;
      ii_data[idx - 1] = ii;
      if (idx >= x_size_idx_0) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (x_size_idx_0 == 1) {
    if (idx == 0) {
      x_size_idx_0 = 0;
    }
  } else if (1 > idx) {
    x_size_idx_0 = 0;
  } else {
    x_size_idx_0 = idx;
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    i_data[ii] = ii_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    b_iPk_data[ii] = iPk_data[i_data[ii] - 1];
  }

  iPk_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    iPk_data[ii] = b_iPk_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    b_pbPk_data[ii] = pbPk_data[i_data[ii] - 1];
  }

  pbPk_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    pbPk_data[ii] = b_pbPk_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    b_iPk_data[ii] = iLB_data[i_data[ii] - 1];
  }

  iLB_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    iLB_data[ii] = b_iPk_data[ii];
  }

  for (ii = 0; ii < x_size_idx_0; ii++) {
    b_iPk_data[ii] = iRB_data[i_data[ii] - 1];
  }

  iRB_size[0] = x_size_idx_0;
  for (ii = 0; ii < x_size_idx_0; ii++) {
    iRB_data[ii] = b_iPk_data[ii];
  }
}

//
// Arguments    : const emxArray_real_T *x
//                emxArray_real_T *y
// Return Type  : void
//
static void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int stride;
  int ix;
  int iy;
  int s;
  stride = y->size[0];
  y->size[0] = (short)x->size[0];
  emxEnsureCapacity((emxArray__common *)y, stride, sizeof(double));
  if (!(y->size[0] == 0)) {
    stride = x->size[0];
    ix = 0;
    iy = 0;
    for (s = 1; s <= stride; s++) {
      y->data[iy] = x->data[ix + stride] - x->data[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : const int a_data[]
//                const int a_size[1]
//                const int b_data[]
//                const int b_size[1]
//                int c_data[]
//                int c_size[1]
//                int ia_data[]
//                int ia_size[1]
//                int ib_data[]
//                int ib_size[1]
// Return Type  : void
//
static void do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1])
{
  int na;
  int nb;
  int ncmax;
  int nc;
  int nia;
  int nib;
  int iafirst;
  int ialast;
  int ibfirst;
  int iblast;
  int b_ialast;
  int ak;
  int b_iblast;
  int bk;
  int b_ia_data[7500];
  short b_ib_data[7500];
  static int b_c_data[15000];
  na = a_size[0];
  nb = b_size[0];
  ncmax = a_size[0] + b_size[0];
  c_size[0] = (short)ncmax;
  ia_size[0] = a_size[0];
  ib_size[0] = b_size[0];
  nc = -1;
  nia = -1;
  nib = 0;
  iafirst = 1;
  ialast = 1;
  ibfirst = 0;
  iblast = 1;
  while ((ialast <= na) && (iblast <= nb)) {
    b_ialast = ialast;
    ak = a_data[ialast - 1];
    while ((b_ialast < a_size[0]) && (a_data[b_ialast] == ak)) {
      b_ialast++;
    }

    ialast = b_ialast;
    b_iblast = iblast;
    bk = b_data[iblast - 1];
    while ((b_iblast < b_size[0]) && (b_data[b_iblast] == bk)) {
      b_iblast++;
    }

    iblast = b_iblast;
    if (ak == bk) {
      nc++;
      c_data[nc] = ak;
      nia++;
      ia_data[nia] = iafirst;
      ialast = b_ialast + 1;
      iafirst = b_ialast + 1;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      nc++;
      nia++;
      c_data[nc] = ak;
      ia_data[nia] = iafirst;
      ialast = b_ialast + 1;
      iafirst = b_ialast + 1;
    } else {
      nc++;
      nib++;
      c_data[nc] = bk;
      ib_data[nib - 1] = ibfirst + 1;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    }
  }

  while (ialast <= na) {
    b_ialast = ialast;
    while ((b_ialast < a_size[0]) && (a_data[b_ialast] == a_data[ialast - 1])) {
      b_ialast++;
    }

    nc++;
    nia++;
    c_data[nc] = a_data[ialast - 1];
    ia_data[nia] = ialast;
    ialast = b_ialast + 1;
  }

  while (iblast <= nb) {
    b_iblast = iblast;
    while ((b_iblast < b_size[0]) && (b_data[b_iblast] == b_data[iblast - 1])) {
      b_iblast++;
    }

    nc++;
    nib++;
    c_data[nc] = b_data[iblast - 1];
    ib_data[nib - 1] = iblast;
    iblast = b_iblast + 1;
  }

  if (a_size[0] > 0) {
    if (1 > nia + 1) {
      nb = -1;
    } else {
      nb = nia;
    }

    for (nia = 0; nia <= nb; nia++) {
      b_ia_data[nia] = ia_data[nia];
    }

    ia_size[0] = nb + 1;
    nb++;
    for (nia = 0; nia < nb; nia++) {
      ia_data[nia] = b_ia_data[nia];
    }
  }

  if (b_size[0] > 0) {
    if (1 > nib) {
      nb = 0;
    } else {
      nb = nib;
    }

    na = b_size[0];
    for (nia = 0; nia < na; nia++) {
      b_ib_data[nia] = (short)ib_data[nia];
    }

    ib_size[0] = nb;
    for (nia = 0; nia < nb; nia++) {
      ib_data[nia] = b_ib_data[nia];
    }
  }

  if (ncmax > 0) {
    if (1 > nc + 1) {
      nb = -1;
    } else {
      nb = nc;
    }

    for (nia = 0; nia <= nb; nia++) {
      b_c_data[nia] = c_data[nia];
    }

    c_size[0] = nb + 1;
    nb++;
    for (nia = 0; nia < nb; nia++) {
      c_data[nia] = b_c_data[nia];
    }
  }
}

//
// Arguments    : const int iPk_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void e_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1])
{
  int n;
  int y_data[15000];
  int yk;
  int k;
  if (iPk_size[0] < 1) {
    n = 0;
  } else {
    n = iPk_size[0];
  }

  if (n > 0) {
    y_data[0] = 1;
    yk = 1;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
  }

  idx_size[0] = n;
  for (yk = 0; yk < n; yk++) {
    idx_data[yk] = y_data[yk];
  }
}

//
// Input: doubles (2000, 1)
//  Output: Y, single (2000, 1)
//  Filter is order 3, HPF @ 1 Hz, butterworth. 250 Hz Fs.
// Arguments    : const double X[7500]
//                float Y[7500]
// Return Type  : void
//
static void ecg_filt_rescale(const double X[7500], float Y[7500])
{
  double d0;
  double d1;
  int i;
  double y[7518];
  double b_y[7518];
  double a[3];
  static const double b_a[3] = { -0.97517981162796985, 1.9503596232562816,
    -0.97517981162830258 };

  static const double dv4[4] = { 0.975179811634754, -2.9255394349042629,
    2.9255394349042629, -0.975179811634754 };

  static const double dv5[4] = { 1.0, -2.949735839706348, 2.9007269883554381,
    -0.950975665016249 };

  double dv6[7500];
  d0 = 2.0 * X[0];
  d1 = 2.0 * X[7499];
  for (i = 0; i < 9; i++) {
    y[i] = d0 - X[9 - i];
  }

  memcpy(&y[9], &X[0], 7500U * sizeof(double));
  for (i = 0; i < 9; i++) {
    y[i + 7509] = d1 - X[7498 - i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv4, dv5, b_y, a, y);
  flipud(y);
  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv4, dv5, b_y, a, y);
  flipud(y);
  rescale_minmax(*(double (*)[7500])&y[9], dv6);
  for (i = 0; i < 7500; i++) {
    Y[i] = (float)dv6[i];
  }
}

//
// Arguments    : const int idx_data[]
//                const int idx_size[1]
//                emxArray_real_T *bPk
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void fetchPeakExtents(const int idx_data[], const int idx_size[1],
  emxArray_real_T *bPk, emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk)
{
  emxArray_real_T *b_bPk;
  int i21;
  int loop_ub;
  emxArray_real_T *b_bxPk;
  int i22;
  emxArray_real_T *b_byPk;
  emxArray_real_T *b_wxPk;
  emxInit_real_T1(&b_bPk, 1);
  i21 = b_bPk->size[0];
  b_bPk->size[0] = idx_size[0];
  emxEnsureCapacity((emxArray__common *)b_bPk, i21, sizeof(double));
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_bPk->data[i21] = bPk->data[idx_data[i21] - 1];
  }

  i21 = bPk->size[0];
  bPk->size[0] = b_bPk->size[0];
  emxEnsureCapacity((emxArray__common *)bPk, i21, sizeof(double));
  loop_ub = b_bPk->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    bPk->data[i21] = b_bPk->data[i21];
  }

  emxFree_real_T(&b_bPk);
  emxInit_real_T(&b_bxPk, 2);
  i21 = b_bxPk->size[0] * b_bxPk->size[1];
  b_bxPk->size[0] = idx_size[0];
  b_bxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_bxPk, i21, sizeof(double));
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < 2; i21++) {
    for (i22 = 0; i22 < loop_ub; i22++) {
      b_bxPk->data[i22 + b_bxPk->size[0] * i21] = bxPk->data[(idx_data[i22] +
        bxPk->size[0] * i21) - 1];
    }
  }

  i21 = bxPk->size[0] * bxPk->size[1];
  bxPk->size[0] = b_bxPk->size[0];
  bxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)bxPk, i21, sizeof(double));
  for (i21 = 0; i21 < 2; i21++) {
    loop_ub = b_bxPk->size[0];
    for (i22 = 0; i22 < loop_ub; i22++) {
      bxPk->data[i22 + bxPk->size[0] * i21] = b_bxPk->data[i22 + b_bxPk->size[0]
        * i21];
    }
  }

  emxFree_real_T(&b_bxPk);
  emxInit_real_T(&b_byPk, 2);
  i21 = b_byPk->size[0] * b_byPk->size[1];
  b_byPk->size[0] = idx_size[0];
  b_byPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_byPk, i21, sizeof(double));
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < 2; i21++) {
    for (i22 = 0; i22 < loop_ub; i22++) {
      b_byPk->data[i22 + b_byPk->size[0] * i21] = byPk->data[(idx_data[i22] +
        byPk->size[0] * i21) - 1];
    }
  }

  i21 = byPk->size[0] * byPk->size[1];
  byPk->size[0] = b_byPk->size[0];
  byPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)byPk, i21, sizeof(double));
  for (i21 = 0; i21 < 2; i21++) {
    loop_ub = b_byPk->size[0];
    for (i22 = 0; i22 < loop_ub; i22++) {
      byPk->data[i22 + byPk->size[0] * i21] = b_byPk->data[i22 + b_byPk->size[0]
        * i21];
    }
  }

  emxFree_real_T(&b_byPk);
  emxInit_real_T(&b_wxPk, 2);
  i21 = b_wxPk->size[0] * b_wxPk->size[1];
  b_wxPk->size[0] = idx_size[0];
  b_wxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_wxPk, i21, sizeof(double));
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < 2; i21++) {
    for (i22 = 0; i22 < loop_ub; i22++) {
      b_wxPk->data[i22 + b_wxPk->size[0] * i21] = wxPk->data[(idx_data[i22] +
        wxPk->size[0] * i21) - 1];
    }
  }

  i21 = wxPk->size[0] * wxPk->size[1];
  wxPk->size[0] = b_wxPk->size[0];
  wxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)wxPk, i21, sizeof(double));
  for (i21 = 0; i21 < 2; i21++) {
    loop_ub = b_wxPk->size[0];
    for (i22 = 0; i22 < loop_ub; i22++) {
      wxPk->data[i22 + wxPk->size[0] * i21] = b_wxPk->data[i22 + b_wxPk->size[0]
        * i21];
    }
  }

  emxFree_real_T(&b_wxPk);
}

//
// Arguments    : const double b[4]
//                const double a[4]
//                const double x[7518]
//                const double zi[3]
//                double y[7518]
// Return Type  : void
//
static void filter(const double b[4], const double a[4], const double x[7518],
                   const double zi[3], double y[7518])
{
  int k;
  int naxpy;
  int j;
  double as;
  for (k = 0; k < 3; k++) {
    y[k] = zi[k];
  }

  memset(&y[3], 0, 7515U * sizeof(double));
  for (k = 0; k < 7518; k++) {
    naxpy = 7518 - k;
    if (!(naxpy < 4)) {
      naxpy = 4;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 7517 - k;
    if (!(naxpy < 3)) {
      naxpy = 3;
    }

    as = -y[k];
    for (j = 1; j <= naxpy; j++) {
      y[k + j] += as * a[j];
    }
  }
}

//
// Arguments    : const double x_in[7500]
//                double y_out[7500]
// Return Type  : void
//
static void filtfilt(const double x_in[7500], double y_out[7500])
{
  double d2;
  double d3;
  int i;
  double y[7518];
  double b_y[7518];
  double a[3];
  static const double b_a[3] = { -0.95097188792623888, 1.9019437758521933,
    -0.95097188792596821 };

  static const double dv7[4] = { 0.950971887923409, -2.8529156637702271,
    2.8529156637702271, -0.950971887923409 };

  static const double dv8[4] = { 1.0, -2.8994795946118641, 2.8039479773829989,
    -0.904347531392409 };

  d2 = 2.0 * x_in[0];
  d3 = 2.0 * x_in[7499];
  for (i = 0; i < 9; i++) {
    y[i] = d2 - x_in[9 - i];
  }

  memcpy(&y[9], &x_in[0], 7500U * sizeof(double));
  for (i = 0; i < 9; i++) {
    y[i + 7509] = d3 - x_in[7498 - i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv7, dv8, b_y, a, y);
  flipud(y);
  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv7, dv8, b_y, a, y);
  flipud(y);
  memcpy(&y_out[0], &y[9], 7500U * sizeof(double));
}

//
// Arguments    : const double y[7500]
//                int iPk_data[]
//                int iPk_size[1]
//                const int iFin_data[]
//                const int iFin_size[1]
//                const int iInf_data[]
//                const int iInf_size[1]
//                const int iInflect_data[]
//                const int iInflect_size[1]
//                emxArray_real_T *bPk
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void findExtents(const double y[7500], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  emxArray_real_T *bPk, emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk)
{
  static double yFinite[7500];
  int loop_ub;
  int i18;
  static double bPk_data[7500];
  int bPk_size[1];
  static int iLB_data[7500];
  int iLB_size[1];
  static int iRB_data[7500];
  int iRB_size[1];
  int b_iPk_size[1];
  emxArray_real_T *b_wxPk;
  static int b_iPk_data[7500];
  memcpy(&yFinite[0], &y[0], 7500U * sizeof(double));
  loop_ub = iInf_size[0];
  for (i18 = 0; i18 < loop_ub; i18++) {
    yFinite[iInf_data[i18] - 1] = rtNaN;
  }

  getPeakBase(yFinite, iPk_data, iPk_size, iFin_data, iFin_size, iInflect_data,
              iInflect_size, bPk_data, bPk_size, iLB_data, iLB_size, iRB_data,
              iRB_size);
  b_iPk_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i18 = 0; i18 < loop_ub; i18++) {
    b_iPk_data[i18] = iPk_data[i18];
  }

  emxInit_real_T(&b_wxPk, 2);
  c_removePeaksBelowMinPeakPromin(yFinite, b_iPk_data, b_iPk_size, bPk_data,
    bPk_size, iLB_data, iLB_size, iRB_data, iRB_size);
  getPeakWidth(yFinite, b_iPk_data, b_iPk_size, bPk_data, bPk_size, iLB_data,
               iLB_size, iRB_data, iRB_size, b_wxPk);
  combineFullPeaks(y, b_iPk_data, b_iPk_size, bPk_data, bPk_size, iLB_data,
                   iLB_size, iRB_data, iRB_size, b_wxPk, iInf_data, iInf_size,
                   iPk_data, iPk_size, bPk, bxPk, byPk, wxPk);
  emxFree_real_T(&b_wxPk);
}

//
// Arguments    : const double y[7500]
//                int *idx
//                int borderIdx
//                double refHeight
// Return Type  : void
//
static void findLeftIntercept(const double y[7500], int *idx, int borderIdx,
  double refHeight)
{
  while ((*idx >= borderIdx) && (y[*idx - 1] > refHeight)) {
    (*idx)--;
  }
}

//
// Arguments    : const double y[7500]
//                int *idx
//                int borderIdx
//                double refHeight
// Return Type  : void
//
static void findRightIntercept(const double y[7500], int *idx, int borderIdx,
  double refHeight)
{
  while ((*idx <= borderIdx) && (y[*idx - 1] > refHeight)) {
    (*idx)++;
  }
}

//
// Arguments    : const double Yin[7463]
//                double varargin_2
//                emxArray_real_T *Ypk
//                emxArray_real_T *Xpk
// Return Type  : void
//
static void findpeaks(const double Yin[7463], double varargin_2, emxArray_real_T
                      *Ypk, emxArray_real_T *Xpk)
{
  int iFinite_data[7463];
  int iFinite_size[1];
  int iInfinite_data[7463];
  int iInfinite_size[1];
  int iInflect_data[7463];
  int iInflect_size[1];
  int iPk_size[1];
  int loop_ub;
  int i1;
  static int iPk_data[14926];
  static int c_data[15000];
  int c_size[1];
  int ia_data[7500];
  int ib_data[7500];
  static int idx_data[14926];
  emxArray_real_T *r0;
  getAllPeaksCodegen(Yin, iFinite_data, iFinite_size, iInfinite_data,
                     iInfinite_size, iInflect_data, iInflect_size);
  removeSmallPeaks(Yin, iFinite_data, iFinite_size, varargin_2, iInflect_data,
                   iInflect_size);
  iPk_size[0] = iInflect_size[0];
  loop_ub = iInflect_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    iPk_data[i1] = iInflect_data[i1];
  }

  do_vectors(iPk_data, iPk_size, iInfinite_data, iInfinite_size, c_data, c_size,
             ia_data, iFinite_size, ib_data, iInflect_size);
  c_findPeaksSeparatedByMoreThanM(c_size, idx_data, iFinite_size);
  keepAtMostNpPeaks(idx_data, iFinite_size);
  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    iPk_data[i1] = c_data[idx_data[i1] - 1];
  }

  i1 = Ypk->size[0];
  Ypk->size[0] = iFinite_size[0];
  emxEnsureCapacity((emxArray__common *)Ypk, i1, sizeof(double));
  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Ypk->data[i1] = Yin[iPk_data[i1] - 1];
  }

  emxInit_real_T1(&r0, 1);
  i1 = r0->size[0];
  r0->size[0] = iFinite_size[0];
  emxEnsureCapacity((emxArray__common *)r0, i1, sizeof(double));
  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    r0->data[i1] = (short)(1 + (short)(iPk_data[i1] - 1));
  }

  i1 = Xpk->size[0];
  Xpk->size[0] = r0->size[0];
  emxEnsureCapacity((emxArray__common *)Xpk, i1, sizeof(double));
  loop_ub = r0->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Xpk->data[i1] = r0->data[i1];
  }

  emxFree_real_T(&r0);
}

//
// Arguments    : emxArray_real_T *x
// Return Type  : void
//
static void flip(emxArray_real_T *x)
{
  int n;
  int nd2;
  int k;
  double tmp;
  if ((!(x->size[0] == 0)) && (x->size[0] > 1)) {
    n = x->size[0];
    nd2 = x->size[0] >> 1;
    for (k = 1; k <= nd2; k++) {
      tmp = x->data[k - 1];
      x->data[k - 1] = x->data[n - k];
      x->data[n - k] = tmp;
    }
  }
}

//
// Arguments    : double x[7518]
// Return Type  : void
//
static void flipud(double x[7518])
{
  int i;
  double xtmp;
  for (i = 0; i < 3759; i++) {
    xtmp = x[i];
    x[i] = x[7517 - i];
    x[7517 - i] = xtmp;
  }
}

//
// Arguments    : const double y[7463]
//                int iPk_data[]
//                int iPk_size[1]
//                int iInf_data[]
//                int iInf_size[1]
//                int iInflect_data[]
//                int iInflect_size[1]
// Return Type  : void
//
static void getAllPeaksCodegen(const double y[7463], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1])
{
  int nPk;
  int nInf;
  int nInflect;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  int i2;
  nPk = 0;
  nInf = 0;
  nInflect = -1;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 7463; k++) {
    yk = y[k];
    if (rtIsNaN(y[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(y[k]) && (y[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInf_data[nInf - 1] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
        if (kfirst >= 1) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
        }
      } else if (yk < ykfirst) {
        dir = 'd';
        if ('d' != previousdir) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
          if (previousdir == 'i') {
            nPk++;
            iPk_data[nPk - 1] = kfirst;
          }
        }
      } else {
        dir = 'i';
        if ('i' != previousdir) {
          nInflect++;
          iInflect_data[nInflect] = kfirst;
        }
      }

      ykfirst = yk;
      kfirst = k + 1;
      isinfykfirst = isinfyk;
    }
  }

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect_data[nInflect] < 7463)))
  {
    nInflect++;
    iInflect_data[nInflect] = 7463;
  }

  if (1 > nPk) {
    iPk_size[0] = 0;
  } else {
    iPk_size[0] = nPk;
  }

  if (1 > nInf) {
    iInf_size[0] = 0;
  } else {
    iInf_size[0] = nInf;
  }

  if (1 > nInflect + 1) {
    i2 = -1;
  } else {
    i2 = nInflect;
  }

  iInflect_size[0] = i2 + 1;
}

//
// Arguments    : const double y[7500]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const double base_data[]
//                const int iLB_data[]
//                const int iRB_data[]
//                emxArray_real_T *bounds
// Return Type  : void
//
static void getHalfMaxBounds(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], emxArray_real_T *bounds)
{
  int iLeft;
  int iRight;
  int i;
  double refHeight;
  iLeft = bounds->size[0] * bounds->size[1];
  bounds->size[0] = iPk_size[0];
  bounds->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)bounds, iLeft, sizeof(double));
  iRight = iPk_size[0] << 1;
  for (iLeft = 0; iLeft < iRight; iLeft++) {
    bounds->data[iLeft] = 0.0;
  }

  for (i = 0; i < iPk_size[0]; i++) {
    refHeight = (y[iPk_data[i] - 1] + base_data[i]) / 2.0;
    iLeft = iPk_data[i];
    findLeftIntercept(y, &iLeft, iLB_data[i], refHeight);
    if (iLeft < iLB_data[i]) {
      bounds->data[i] = 1.0 + ((double)iLB_data[i] - 1.0);
    } else {
      bounds->data[i] = linterp(1.0 + ((double)iLeft - 1.0), 1.0 + ((double)
        (iLeft + 1) - 1.0), y[iLeft - 1], y[iLeft], y[iPk_data[i] - 1],
        base_data[i]);
    }

    iRight = iPk_data[i];
    findRightIntercept(y, &iRight, iRB_data[i], refHeight);
    if (iRight > iRB_data[i]) {
      bounds->data[i + bounds->size[0]] = 1.0 + ((double)iRB_data[i] - 1.0);
    } else {
      bounds->data[i + bounds->size[0]] = linterp(1.0 + ((double)iRight - 1.0),
        1.0 + ((double)(iRight - 1) - 1.0), y[iRight - 1], y[iRight - 2],
        y[iPk_data[i] - 1], base_data[i]);
    }
  }
}

//
// Arguments    : const double yTemp[7500]
//                const int iPeak_data[]
//                const int iPeak_size[1]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                const int iInflect_data[]
//                int iBase_data[]
//                int iBase_size[1]
//                int iSaddle_data[]
//                int iSaddle_size[1]
// Return Type  : void
//
static void getLeftBase(const double yTemp[7500], const int iPeak_data[], const
  int iPeak_size[1], const int iFinite_data[], const int iFinite_size[1], const
  int iInflect_data[], int iBase_data[], int iBase_size[1], int iSaddle_data[],
  int iSaddle_size[1])
{
  int n;
  int i;
  static double peak_data[7500];
  static double valley_data[7500];
  int iValley_data[7500];
  int j;
  int k;
  double v;
  int iv;
  double p;
  int isv;
  iBase_size[0] = (short)iPeak_size[0];
  n = (short)iPeak_size[0];
  for (i = 0; i < n; i++) {
    iBase_data[i] = 0;
  }

  iSaddle_size[0] = (short)iPeak_size[0];
  n = (short)iPeak_size[0];
  for (i = 0; i < n; i++) {
    iSaddle_data[i] = 0;
  }

  n = (short)iFinite_size[0];
  for (i = 0; i < n; i++) {
    peak_data[i] = 0.0;
  }

  n = (short)iFinite_size[0];
  for (i = 0; i < n; i++) {
    valley_data[i] = 0.0;
  }

  n = (short)iFinite_size[0];
  for (i = 0; i < n; i++) {
    iValley_data[i] = 0;
  }

  n = -1;
  i = 0;
  j = 0;
  k = 0;
  v = rtNaN;
  iv = 1;
  while (k + 1 <= iPeak_size[0]) {
    while (iInflect_data[i] != iFinite_data[j]) {
      v = yTemp[iInflect_data[i] - 1];
      iv = iInflect_data[i];
      if (rtIsNaN(yTemp[iInflect_data[i] - 1])) {
        n = -1;
      } else {
        while ((n + 1 > 0) && (valley_data[n] > v)) {
          n--;
        }
      }

      i++;
    }

    p = yTemp[iInflect_data[i] - 1];
    while ((n + 1 > 0) && (peak_data[n] < p)) {
      if (valley_data[n] < v) {
        v = valley_data[n];
        iv = iValley_data[n];
      }

      n--;
    }

    isv = iv;
    while ((n + 1 > 0) && (peak_data[n] <= p)) {
      if (valley_data[n] < v) {
        v = valley_data[n];
        iv = iValley_data[n];
      }

      n--;
    }

    n++;
    peak_data[n] = yTemp[iInflect_data[i] - 1];
    valley_data[n] = v;
    iValley_data[n] = iv;
    if (iInflect_data[i] == iPeak_data[k]) {
      iBase_data[k] = iv;
      iSaddle_data[k] = isv;
      k++;
    }

    i++;
    j++;
  }
}

//
// Arguments    : const double yTemp[7500]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const int iFin_data[]
//                const int iFin_size[1]
//                const int iInflect_data[]
//                const int iInflect_size[1]
//                double peakBase_data[]
//                int peakBase_size[1]
//                int iLeftSaddle_data[]
//                int iLeftSaddle_size[1]
//                int iRightSaddle_data[]
//                int iRightSaddle_size[1]
// Return Type  : void
//
static void getPeakBase(const double yTemp[7500], const int iPk_data[], const
  int iPk_size[1], const int iFin_data[], const int iFin_size[1], const int
  iInflect_data[], const int iInflect_size[1], double peakBase_data[], int
  peakBase_size[1], int iLeftSaddle_data[], int iLeftSaddle_size[1], int
  iRightSaddle_data[], int iRightSaddle_size[1])
{
  int iLeftBase_data[7500];
  int iLeftBase_size[1];
  int tmp_size[1];
  int loop_ub;
  int i5;
  int tmp_data[7500];
  int b_tmp_size[1];
  int b_tmp_data[7500];
  int c_tmp_size[1];
  int c_tmp_data[7500];
  int iRightBase_data[7500];
  short csz_idx_0;
  getLeftBase(yTemp, iPk_data, iPk_size, iFin_data, iFin_size, iInflect_data,
              iLeftBase_data, iLeftBase_size, iLeftSaddle_data, iLeftSaddle_size);
  tmp_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    tmp_data[i5] = iPk_data[i5];
  }

  c_flipud(tmp_data, tmp_size);
  b_tmp_size[0] = iFin_size[0];
  loop_ub = iFin_size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    b_tmp_data[i5] = iFin_data[i5];
  }

  c_flipud(b_tmp_data, b_tmp_size);
  c_tmp_size[0] = iInflect_size[0];
  loop_ub = iInflect_size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    c_tmp_data[i5] = iInflect_data[i5];
  }

  c_flipud(c_tmp_data, c_tmp_size);
  getLeftBase(yTemp, tmp_data, tmp_size, b_tmp_data, b_tmp_size, c_tmp_data,
              iRightBase_data, c_tmp_size, iRightSaddle_data, iRightSaddle_size);
  c_flipud(iRightBase_data, c_tmp_size);
  c_flipud(iRightSaddle_data, iRightSaddle_size);
  if (iLeftBase_size[0] <= c_tmp_size[0]) {
    csz_idx_0 = (short)iLeftBase_size[0];
    peakBase_size[0] = (short)iLeftBase_size[0];
  } else {
    csz_idx_0 = (short)c_tmp_size[0];
    peakBase_size[0] = (short)c_tmp_size[0];
  }

  for (loop_ub = 0; loop_ub + 1 <= csz_idx_0; loop_ub++) {
    if ((yTemp[iLeftBase_data[loop_ub] - 1] > yTemp[iRightBase_data[loop_ub] - 1])
        || rtIsNaN(yTemp[iRightBase_data[loop_ub] - 1])) {
      peakBase_data[loop_ub] = yTemp[iLeftBase_data[loop_ub] - 1];
    } else {
      peakBase_data[loop_ub] = yTemp[iRightBase_data[loop_ub] - 1];
    }
  }
}

//
// Arguments    : const double y[7500]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const double pbPk_data[]
//                const int pbPk_size[1]
//                int iLB_data[]
//                int iLB_size[1]
//                int iRB_data[]
//                int iRB_size[1]
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void getPeakWidth(const double y[7500], const int iPk_data[], const int
  iPk_size[1], const double pbPk_data[], const int pbPk_size[1], int iLB_data[],
  int iLB_size[1], int iRB_data[], int iRB_size[1], emxArray_real_T *wxPk)
{
  int loop_ub;
  int i19;
  double base_data[7500];
  if (iPk_size[0] == 0) {
    iLB_size[0] = 0;
    iRB_size[0] = 0;
  } else {
    loop_ub = pbPk_size[0];
    for (i19 = 0; i19 < loop_ub; i19++) {
      base_data[i19] = pbPk_data[i19];
    }
  }

  getHalfMaxBounds(y, iPk_data, iPk_size, base_data, iLB_data, iRB_data, wxPk);
}

//
// Arguments    : const emxArray_real_T *varargin_1
//                const emxArray_real_T *varargin_2
//                double Vq[7500]
// Return Type  : void
//
static void interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
                    *varargin_2, double Vq[7500])
{
  emxArray_real_T *y;
  int i8;
  int loop_ub;
  emxArray_real_T *x;
  int nx;
  emxArray_real_T *pp_breaks;
  emxArray_real_T *pp_coefs;
  emxArray_real_T *b_y;
  int exitg1;
  double xtmp;
  double tmp_data[1];
  int tmp_size[1];
  emxInit_real_T1(&y, 1);
  i8 = y->size[0];
  y->size[0] = varargin_2->size[0];
  emxEnsureCapacity((emxArray__common *)y, i8, sizeof(double));
  loop_ub = varargin_2->size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    y->data[i8] = varargin_2->data[i8];
  }

  emxInit_real_T1(&x, 1);
  i8 = x->size[0];
  x->size[0] = varargin_1->size[0];
  emxEnsureCapacity((emxArray__common *)x, i8, sizeof(double));
  loop_ub = varargin_1->size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    x->data[i8] = varargin_1->data[i8];
  }

  nx = varargin_1->size[0];
  memset(&Vq[0], 0, 7500U * sizeof(double));
  loop_ub = 1;
  emxInit_real_T(&pp_breaks, 2);
  emxInit_real_T2(&pp_coefs, 3);
  emxInit_real_T(&b_y, 2);
  do {
    exitg1 = 0;
    if (loop_ub <= nx) {
      if (rtIsNaN(varargin_1->data[loop_ub - 1])) {
        exitg1 = 1;
      } else {
        loop_ub++;
      }
    } else {
      if (varargin_1->data[1] < varargin_1->data[0]) {
        i8 = nx >> 1;
        for (loop_ub = 1; loop_ub <= i8; loop_ub++) {
          xtmp = x->data[loop_ub - 1];
          x->data[loop_ub - 1] = x->data[nx - loop_ub];
          x->data[nx - loop_ub] = xtmp;
        }

        flip(y);
      }

      loop_ub = y->size[0];
      i8 = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = loop_ub;
      emxEnsureCapacity((emxArray__common *)b_y, i8, sizeof(double));
      for (i8 = 0; i8 < loop_ub; i8++) {
        b_y->data[b_y->size[0] * i8] = y->data[i8];
      }

      spline(x, b_y, pp_breaks, pp_coefs);
      for (loop_ub = 0; loop_ub < 7500; loop_ub++) {
        ppval(pp_breaks, pp_coefs, 1.0 + (((double)loop_ub + 1.0) - 1.0),
              tmp_data, tmp_size);
        Vq[loop_ub] = tmp_data[0];
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&b_y);
  emxFree_real_T(&pp_coefs);
  emxFree_real_T(&pp_breaks);
  emxFree_real_T(&x);
  emxFree_real_T(&y);
}

//
// Arguments    : int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void keepAtMostNpPeaks(int idx_data[], int idx_size[1])
{
  static int b_idx_data[14926];
  int i17;
  if (idx_size[0] > 7463) {
    memcpy(&b_idx_data[0], &idx_data[0], 7463U * sizeof(int));
    idx_size[0] = 7463;
    for (i17 = 0; i17 < 7463; i17++) {
      idx_data[i17] = b_idx_data[i17];
    }
  }
}

//
// Arguments    : double xa
//                double xb
//                double ya
//                double yb
//                double yc
//                double bc
// Return Type  : double
//
static double linterp(double xa, double xb, double ya, double yb, double yc,
                      double bc)
{
  double xc;
  xc = xa + (xb - xa) * (0.5 * (yc + bc) - ya) / (yb - ya);
  if (rtIsNaN(xc)) {
    if (rtIsInf(bc)) {
      xc = 0.5 * (xa + xb);
    } else {
      xc = xb;
    }
  }

  return xc;
}

//
// Arguments    : const double x[7500]
// Return Type  : double
//
static double mean(const double x[7500])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 7499; k++) {
    y += x[k + 1];
  }

  y /= 7500.0;
  return y;
}

//
// Arguments    : const double a[7500]
//                double y[7500]
// Return Type  : void
//
static void power(const double a[7500], double y[7500])
{
  int k;
  for (k = 0; k < 7500; k++) {
    y[k] = a[k] * a[k];
  }
}

//
// Arguments    : const emxArray_real_T *pp_breaks
//                const emxArray_real_T *pp_coefs
//                double x
//                double v_data[]
//                int v_size[1]
// Return Type  : void
//
static void ppval(const emxArray_real_T *pp_breaks, const emxArray_real_T
                  *pp_coefs, double x, double v_data[], int v_size[1])
{
  int ip;
  double v;
  double xloc;
  int ic;
  v_size[0] = 1;
  if ((pp_coefs->size[2] > 1) && rtIsNaN(x)) {
    v = x;
  } else {
    ip = b_bsearch(pp_breaks, x) - 1;
    xloc = x - pp_breaks->data[ip];
    v = pp_coefs->data[ip];
    for (ic = 2; ic <= pp_coefs->size[2]; ic++) {
      v = xloc * v + pp_coefs->data[ip + (ic - 1) * (pp_breaks->size[1] - 1)];
    }
  }

  v_data[0] = v;
}

//
// Arguments    : const emxArray_real_T *x
//                const emxArray_real_T *y
//                const double s[2]
//                emxArray_real_T *pp_breaks
//                double pp_coefs[4]
// Return Type  : void
//
static void pwchcore(const emxArray_real_T *x, const emxArray_real_T *y, const
                     double s[2], emxArray_real_T *pp_breaks, double pp_coefs[4])
{
  int x_idx_0;
  int i10;
  double dxj;
  double divdifij;
  double dzzdx;
  x_idx_0 = x->size[0];
  i10 = pp_breaks->size[0] * pp_breaks->size[1];
  pp_breaks->size[0] = 1;
  pp_breaks->size[1] = x_idx_0;
  emxEnsureCapacity((emxArray__common *)pp_breaks, i10, sizeof(double));
  for (i10 = 0; i10 < x_idx_0; i10++) {
    pp_breaks->data[pp_breaks->size[0] * i10] = x->data[i10];
  }

  for (x_idx_0 = 1; x_idx_0 < x->size[0]; x_idx_0++) {
    dxj = x->data[x_idx_0] - x->data[x_idx_0 - 1];
    divdifij = (y->data[x_idx_0 + 1] - y->data[x_idx_0]) / dxj;
    dzzdx = (divdifij - s[x_idx_0 - 1]) / dxj;
    divdifij = (s[1] - divdifij) / dxj;
    pp_coefs[x_idx_0 - 1] = (divdifij - dzzdx) / dxj;
    pp_coefs[x_idx_0] = 2.0 * dzzdx - divdifij;
    pp_coefs[x_idx_0 + 1] = s[x_idx_0 - 1];
    pp_coefs[3] = y->data[x_idx_0];
  }
}

//
// Arguments    : const double y[7463]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                double minH
//                int iPk_data[]
//                int iPk_size[1]
// Return Type  : void
//
static void removeSmallPeaks(const double y[7463], const int iFinite_data[],
  const int iFinite_size[1], double minH, int iPk_data[], int iPk_size[1])
{
  int nPk;
  int k;
  double b_y;
  nPk = 0;
  for (k = 0; k + 1 <= iFinite_size[0]; k++) {
    if (y[iFinite_data[k] - 1] > minH) {
      if ((y[iFinite_data[k] - 2] > y[iFinite_data[k]]) || rtIsNaN
          (y[iFinite_data[k]])) {
        b_y = y[iFinite_data[k] - 2];
      } else {
        b_y = y[iFinite_data[k]];
      }

      if (y[iFinite_data[k] - 1] - b_y >= 0.0) {
        nPk++;
        iPk_data[nPk - 1] = iFinite_data[k];
      }
    }
  }

  if (1 > nPk) {
    iPk_size[0] = 0;
  } else {
    iPk_size[0] = nPk;
  }
}

//
// Arguments    : const double X[7500]
//                double Y[7500]
// Return Type  : void
//
static void rescale_minmax(const double X[7500], double Y[7500])
{
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg1;
  double b_mtmp;
  ixstart = 1;
  mtmp = X[0];
  if (rtIsNaN(X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7501)) {
      ixstart = ix;
      if (!rtIsNaN(X[ix - 1])) {
        mtmp = X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 7500) {
    while (ixstart + 1 < 7501) {
      if (X[ixstart] < mtmp) {
        mtmp = X[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = X[0];
  if (rtIsNaN(X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7501)) {
      ixstart = ix;
      if (!rtIsNaN(X[ix - 1])) {
        b_mtmp = X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 7500) {
    while (ixstart + 1 < 7501) {
      if (X[ixstart] > b_mtmp) {
        b_mtmp = X[ixstart];
      }

      ixstart++;
    }
  }

  b_mtmp -= mtmp;
  for (ixstart = 0; ixstart < 7500; ixstart++) {
    Y[ixstart] = (X[ixstart] - mtmp) / b_mtmp;
  }
}

//
// Arguments    : const emxArray_real_T *x
//                const emxArray_real_T *y
//                emxArray_real_T *output_breaks
//                emxArray_real_T *output_coefs
// Return Type  : void
//
static void spline(const emxArray_real_T *x, const emxArray_real_T *y,
                   emxArray_real_T *output_breaks, emxArray_real_T *output_coefs)
{
  int nx;
  boolean_T has_endslopes;
  emxArray_real_T *dx;
  emxArray_real_T *dvdf;
  emxArray_real_T *s;
  double szdvdf[2];
  emxArray_real_T *md;
  emxArray_real_T *t2_breaks;
  int k;
  double t0_coefs[4];
  emxArray_real_T *t2_coefs;
  int i9;
  double d31;
  double dnnm2;
  short szs[2];
  double c_data[3];
  int yoffset;
  double r;
  nx = x->size[0] - 1;
  has_endslopes = (y->size[1] == x->size[0] + 2);
  if (x->size[0] <= 2) {
    if (has_endslopes) {
      emxInit_real_T(&dx, 2);
      szdvdf[0] = y->data[0];
      szdvdf[1] = y->data[y->size[1] - 1];
      pwchcore(x, y, szdvdf, dx, t0_coefs);
      i9 = output_breaks->size[0] * output_breaks->size[1];
      output_breaks->size[0] = 1;
      output_breaks->size[1] = dx->size[1];
      emxEnsureCapacity((emxArray__common *)output_breaks, i9, sizeof(double));
      k = dx->size[0] * dx->size[1];
      for (i9 = 0; i9 < k; i9++) {
        output_breaks->data[i9] = dx->data[i9];
      }

      emxFree_real_T(&dx);
      i9 = output_coefs->size[0] * output_coefs->size[1] * output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = 4;
      output_coefs->size[2] = 1;
      emxEnsureCapacity((emxArray__common *)output_coefs, i9, sizeof(double));
      for (i9 = 0; i9 < 4; i9++) {
        output_coefs->data[i9] = t0_coefs[i9];
      }
    } else {
      emxInit_real_T(&dx, 2);
      szdvdf[0] = (y->data[1] - y->data[0]) / (x->data[1] - x->data[0]);
      szdvdf[1] = y->data[0];
      k = x->size[0];
      i9 = dx->size[0] * dx->size[1];
      dx->size[0] = 1;
      dx->size[1] = k;
      emxEnsureCapacity((emxArray__common *)dx, i9, sizeof(double));
      for (i9 = 0; i9 < k; i9++) {
        dx->data[dx->size[0] * i9] = x->data[i9];
      }

      i9 = output_breaks->size[0] * output_breaks->size[1];
      output_breaks->size[0] = 1;
      output_breaks->size[1] = dx->size[1];
      emxEnsureCapacity((emxArray__common *)output_breaks, i9, sizeof(double));
      k = dx->size[0] * dx->size[1];
      for (i9 = 0; i9 < k; i9++) {
        output_breaks->data[i9] = dx->data[i9];
      }

      emxFree_real_T(&dx);
      i9 = output_coefs->size[0] * output_coefs->size[1] * output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = 1;
      output_coefs->size[2] = 2;
      emxEnsureCapacity((emxArray__common *)output_coefs, i9, sizeof(double));
      for (i9 = 0; i9 < 2; i9++) {
        output_coefs->data[i9] = szdvdf[i9];
      }
    }
  } else {
    emxInit_real_T1(&dx, 1);
    emxInit_real_T(&dvdf, 2);
    emxInit_real_T(&s, 2);
    emxInit_real_T1(&md, 1);
    emxInit_real_T(&t2_breaks, 2);
    emxInit_real_T2(&t2_coefs, 3);
    if ((x->size[0] == 3) && (!has_endslopes)) {
      d31 = x->data[1] - x->data[0];
      dnnm2 = (y->data[1] - y->data[0]) / d31;
      c_data[0] = ((y->data[2] - y->data[1]) / (x->data[2] - x->data[1]) - dnnm2)
        / (x->data[2] - x->data[0]);
      c_data[1] = dnnm2 - c_data[0] * d31;
      c_data[2] = y->data[0];
      szdvdf[0] = x->data[0];
      szdvdf[1] = x->data[2];
      i9 = output_breaks->size[0] * output_breaks->size[1];
      output_breaks->size[0] = 1;
      output_breaks->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)output_breaks, i9, sizeof(double));
      for (i9 = 0; i9 < 2; i9++) {
        output_breaks->data[output_breaks->size[0] * i9] = szdvdf[i9];
      }

      i9 = output_coefs->size[0] * output_coefs->size[1] * output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = 1;
      output_coefs->size[2] = 3;
      emxEnsureCapacity((emxArray__common *)output_coefs, i9, sizeof(double));
      for (i9 = 0; i9 < 3; i9++) {
        output_coefs->data[i9] = c_data[i9];
      }
    } else {
      if (has_endslopes) {
        szdvdf[1] = (double)y->size[1] - 3.0;
        szs[1] = (short)(y->size[1] - 2);
        yoffset = 1;
      } else {
        szdvdf[1] = (double)y->size[1] - 1.0;
        for (i9 = 0; i9 < 2; i9++) {
          szs[i9] = (short)y->size[i9];
        }

        yoffset = 0;
      }

      i9 = x->size[0] - 1;
      k = dx->size[0];
      dx->size[0] = i9;
      emxEnsureCapacity((emxArray__common *)dx, k, sizeof(double));
      i9 = dvdf->size[0] * dvdf->size[1];
      dvdf->size[0] = 1;
      dvdf->size[1] = (int)szdvdf[1];
      emxEnsureCapacity((emxArray__common *)dvdf, i9, sizeof(double));
      i9 = s->size[0] * s->size[1];
      s->size[0] = 1;
      s->size[1] = szs[1];
      emxEnsureCapacity((emxArray__common *)s, i9, sizeof(double));
      for (k = 0; k + 1 <= nx; k++) {
        dx->data[k] = x->data[k + 1] - x->data[k];
        d31 = y->data[(yoffset + k) + 1] - y->data[yoffset + k];
        dvdf->data[k] = d31 / dx->data[k];
      }

      for (k = 1; k + 1 <= nx; k++) {
        s->data[k] = 3.0 * (dx->data[k] * dvdf->data[k - 1] + dx->data[k - 1] *
                            dvdf->data[k]);
      }

      if (has_endslopes) {
        d31 = 0.0;
        dnnm2 = 0.0;
        s->data[0] = dx->data[1] * y->data[0];
        s->data[x->size[0] - 1] = dx->data[x->size[0] - 3] * y->data[x->size[0]
          + 1];
      } else {
        d31 = x->data[2] - x->data[0];
        dnnm2 = x->data[x->size[0] - 1] - x->data[x->size[0] - 3];
        s->data[0] = ((dx->data[0] + 2.0 * d31) * dx->data[1] * dvdf->data[0] +
                      dx->data[0] * dx->data[0] * dvdf->data[1]) / d31;
        s->data[x->size[0] - 1] = ((dx->data[x->size[0] - 2] + 2.0 * dnnm2) *
          dx->data[x->size[0] - 3] * dvdf->data[x->size[0] - 2] + dx->data
          [x->size[0] - 2] * dx->data[x->size[0] - 2] * dvdf->data[x->size[0] -
          3]) / dnnm2;
      }

      i9 = md->size[0];
      md->size[0] = x->size[0];
      emxEnsureCapacity((emxArray__common *)md, i9, sizeof(double));
      md->data[0] = dx->data[1];
      md->data[x->size[0] - 1] = dx->data[x->size[0] - 3];
      for (k = 1; k + 1 <= nx; k++) {
        md->data[k] = 2.0 * (dx->data[k] + dx->data[k - 1]);
      }

      r = dx->data[1] / md->data[0];
      md->data[1] -= r * d31;
      s->data[1] -= r * s->data[0];
      for (k = 2; k + 1 <= nx; k++) {
        r = dx->data[k] / md->data[k - 1];
        md->data[k] -= r * dx->data[k - 2];
        s->data[k] -= r * s->data[k - 1];
      }

      r = dnnm2 / md->data[x->size[0] - 2];
      md->data[x->size[0] - 1] -= r * dx->data[x->size[0] - 3];
      s->data[x->size[0] - 1] -= r * s->data[x->size[0] - 2];
      s->data[x->size[0] - 1] /= md->data[x->size[0] - 1];
      for (k = x->size[0] - 2; k + 1 > 1; k--) {
        s->data[k] = (s->data[k] - dx->data[k - 1] * s->data[k + 1]) / md->
          data[k];
      }

      s->data[0] = (s->data[0] - d31 * s->data[1]) / md->data[0];
      b_pwchcore(x, y, yoffset, s, dx, dvdf, t2_breaks, t2_coefs);
      i9 = output_breaks->size[0] * output_breaks->size[1];
      output_breaks->size[0] = 1;
      output_breaks->size[1] = t2_breaks->size[1];
      emxEnsureCapacity((emxArray__common *)output_breaks, i9, sizeof(double));
      k = t2_breaks->size[0] * t2_breaks->size[1];
      for (i9 = 0; i9 < k; i9++) {
        output_breaks->data[i9] = t2_breaks->data[i9];
      }

      i9 = output_coefs->size[0] * output_coefs->size[1] * output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = t2_coefs->size[1];
      output_coefs->size[2] = 4;
      emxEnsureCapacity((emxArray__common *)output_coefs, i9, sizeof(double));
      k = t2_coefs->size[0] * t2_coefs->size[1] * t2_coefs->size[2];
      for (i9 = 0; i9 < k; i9++) {
        output_coefs->data[i9] = t2_coefs->data[i9];
      }
    }

    emxFree_real_T(&t2_coefs);
    emxFree_real_T(&t2_breaks);
    emxFree_real_T(&md);
    emxFree_real_T(&s);
    emxFree_real_T(&dvdf);
    emxFree_real_T(&dx);
  }
}

//
// get_hr_rr This function uses a variant of the Pan-Tompkins Algorithm to
// detect ECG QRS features from low frequency data:
//  Input: X (raw data, floats or doubles (preferred);
//  Outputs: Y
//  0. Get X:
// Arguments    : const double X_raw[7500]
//                double *HR_mean
//                double *Respiratory_rate
// Return Type  : void
//
void get_hr_rr(const double X_raw[7500], double *HR_mean, double
               *Respiratory_rate)
{
  static float fv0[7500];
  int i;
  static double X[7500];
  double mtmp;
  static double X0[7500];
  static double dv0[7500];
  static const double dv1[38] = { 0.0, 0.0071920448261457715,
    0.028561277269457896, 0.063492943419405923, 0.11098212284078024,
    0.16966263830495926, 0.23784635822138417, 0.31357176110984569,
    0.3946603650021368, 0.47877939840192579, 0.56350890987343938,
    0.646411385638275, 0.72510187240883672, 0.79731658815214335,
    0.86097804697726221, 0.91425482462192109, 0.95561424519406779,
    0.98386647346674949, 0.99819874427126321, 0.99819874427126321,
    0.98386647346674949, 0.9556142451940679, 0.9142548246219212,
    0.86097804697726232, 0.79731658815214324, 0.72510187240883683,
    0.64641138563827516, 0.5635089098734396, 0.4787793984019259,
    0.39466036500213669, 0.3135717611098458, 0.23784635822138445,
    0.16966263830495942, 0.11098212284078024, 0.063492943419405812,
    0.028561277269457952, 0.007192044826145827, 0.0 };

  static double X4[7463];
  int ix;
  boolean_T exitg1;
  emxArray_real_T *dist;
  emxArray_real_T *Peaks;
  emxArray_real_T *Locations;
  static double dv2[7500];
  emxArray_real_T *pk_rr_n;
  emxArray_real_T *loc_rr_n;
  emxArray_real_T *pk_vout;
  emxArray_real_T *loc_vout;
  static double Vout_n[7000];
  ecg_filt_rescale(X_raw, fv0);
  for (i = 0; i < 7500; i++) {
    X[i] = fv0[i];
  }

  //  1. Remove Mean:
  mtmp = mean(X);
  for (i = 0; i < 7500; i++) {
    X[i] -= mtmp;
  }

  //  2. Remove baseline drift (Butterworth, high pass: [b, a] = butter(3, 0.5*2/62.5, 'high');  
  //  @ 5 hz
  //  b = [0.601580928135908,-1.804742784407724,1.804742784407724,-0.601580928135908]; 
  //  a = [1,-2.003797477370017,1.447054019489380,-0.361795928227867];
  //  @ Equivalent to: [b, a] = butter(3, 2*2/250, 'high');
  filtfilt(X, X0);

  //  2.1 Divide by max value to acheive peak of 1
  //  X0 = X0/ max( abs( X0 ) );
  //  3. Derivative Filter:
  b_filtfilt(X0, X);

  //  X2 = X2/max(X2);
  //  4. Square to accentuate ecg waveformsS
  //  5. Convolution filtering to smooth peaks:
  //  conv_filter = ones(1, round(0.150*62.5)) / round(0.150*62.5);
  //  Custom: Use Hann Window as filter - better defined peaks.
  power(X, dv0);
  conv(dv0, dv1, X4);

  // rescale_minmax
  //  Extract fiducial markers (peaks);
  i = 1;
  mtmp = X4[0];
  if (rtIsNaN(X4[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7464)) {
      i = ix;
      if (!rtIsNaN(X4[ix - 1])) {
        mtmp = X4[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (i < 7463) {
    while (i + 1 < 7464) {
      if (X4[i] > mtmp) {
        mtmp = X4[i];
      }

      i++;
    }
  }

  emxInit_real_T(&dist, 2);
  emxInit_real_T1(&Peaks, 1);
  emxInit_real_T1(&Locations, 1);

  //  [Peaks, Locations] = findpeaks(X4,'MinPeakProminence',0.3656836669*max_peak); 
  findpeaks(X4, 0.3656836669 * mtmp, Peaks, Locations);

  //  Output = [Peaks; Locations];
  //  calculate distance between fiducial markers:
  i = dist->size[0] * dist->size[1];
  dist->size[0] = 1;
  dist->size[1] = Peaks->size[0] - 1;
  emxEnsureCapacity((emxArray__common *)dist, i, sizeof(double));
  ix = Peaks->size[0] - 1;
  emxFree_real_T(&Peaks);
  for (i = 0; i < ix; i++) {
    dist->data[i] = 0.0;
  }

  for (i = 0; i <= Locations->size[0] - 2; i++) {
    dist->data[i] = Locations->data[i + 1] - Locations->data[i];
  }

  emxFree_real_T(&Locations);
  mtmp = b_mean(dist);

  //  average in seconds:
  *HR_mean = 60.0 / (mtmp / Fs);

  rescale_minmax(X0, dv2);
  for (i = 0; i < 7500; i++) {
    X[i] = 1.0 - dv2[i];
  }

  emxInit_real_T1(&pk_rr_n, 1);
  emxInit_real_T1(&loc_rr_n, 1);
  emxInit_real_T(&pk_vout, 2);
  emxInit_real_T(&loc_vout, 2);
  b_findpeaks(X, pk_rr_n, loc_rr_n);
  interp1(loc_rr_n, pk_rr_n, X);

  //  Truncate 1/2 sec on either side:
  b_rescale_minmax(*(double (*)[7000])&X[250], Vout_n);
  c_findpeaks(Vout_n, pk_vout, loc_vout);
  i = dist->size[0] * dist->size[1];
  dist->size[0] = 1;
  dist->size[1] = pk_vout->size[1] - 1;
  emxEnsureCapacity((emxArray__common *)dist, i, sizeof(double));
  ix = pk_vout->size[1] - 1;
  emxFree_real_T(&pk_vout);
  emxFree_real_T(&loc_rr_n);
  emxFree_real_T(&pk_rr_n);
  for (i = 0; i < ix; i++) {
    dist->data[i] = 0.0;
  }

  for (i = 0; i <= loc_vout->size[1] - 2; i++) {
    dist->data[i] = loc_vout->data[i + 1] - loc_vout->data[i];
  }

  emxFree_real_T(&loc_vout);
  mtmp = b_mean(dist);
  *Respiratory_rate = 60.0 / (mtmp / 250.0);

  emxFree_real_T(&dist);
}

//
// Arguments    : void
// Return Type  : void
//
void get_hr_rr_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void get_hr_rr_terminate()
{
  // (no terminate code required)
}

//
// File trailer for get_hr_rr.cpp
//
// [EOF]
//
