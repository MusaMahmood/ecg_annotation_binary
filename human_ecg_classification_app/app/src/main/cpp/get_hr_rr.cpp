//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Dec-2018 18:36:01
//

// Include Files
#include "rt_nonfinite.h"
#include "get_hr_rr.h"
#include "get_hr_rr_emxutil.h"

// Type Definitions
#ifndef struct_emxArray_int32_T_14926
#define struct_emxArray_int32_T_14926

struct emxArray_int32_T_14926
{
  int data[14926];
  int size[1];
};

#endif                                 //struct_emxArray_int32_T_14926

// Named Constants
#define Fs                             (250.0)

// Function Declarations
static void assignFullOutputs(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const emxArray_real_T *wxPk, const double bPk_data[], double
  YpkOut_data[], int YpkOut_size[1], double XpkOut_data[], int XpkOut_size[1],
  double WpkOut_data[], int WpkOut_size[1], double PpkOut_data[], int
  PpkOut_size[1]);
static void b_assignFullOutputs(const double y[7000], const int iPk_data[],
  const int iPk_size[1], const emxArray_real_T *wxPk, const double bPk_data[],
  double YpkOut_data[], int YpkOut_size[2], double XpkOut_data[], int
  XpkOut_size[2], double WpkOut_data[], int WpkOut_size[2], double PpkOut_data[],
  int PpkOut_size[2]);
static int b_bsearch(const double x_data[], const int x_size[2], double xi);
static void b_combineFullPeaks(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const double wPk_data[], const int wPk_size[2], const int
  iInf_data[], const int iInf_size[1], int iPkOut_data[], int iPkOut_size[1],
  double bPkOut_data[], int bPkOut_size[1], emxArray_real_T *bxPkOut,
  emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut);
static void b_do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1]);
static void b_filter(const double b[2], const double x[7506], double zi, double
                     y[7506]);
static void b_filtfilt(const double x_in[7500], double y_out[7500]);
static void b_findExtents(const double y[7000], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  double bPk_data[], int bPk_size[1], emxArray_real_T *bxPk, emxArray_real_T
  *byPk, emxArray_real_T *wxPk);
static void b_findLeftIntercept(const double y[7000], int *idx, int borderIdx,
  double refHeight);
static void b_findRightIntercept(const double y[7000], int *idx, int borderIdx,
  double refHeight);
static void b_findpeaks(const double Yin[7500], double Ypk_data[], int Ypk_size
  [1], double Xpk_data[], int Xpk_size[1]);
static void b_flipud(double x[7506]);
static void b_getAllPeaksCodegen(const double y[7500], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void b_getHalfMaxBounds(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], double bounds_data[], int bounds_size[2]);
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
  int iLB_size[1], int iRB_data[], int iRB_size[1], double wxPk_data[], int
  wxPk_size[2]);
static void b_keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double b_mean(const double x_data[], const int x_size[2]);
static void b_mergesort(int idx_data[], const double x_data[], int n);
static void b_pwchcore(const double x_data[], const int x_size[1], const double
  y_data[], int yoffset, const double s_data[], const double dx_data[], const
  double divdif_data[], double pp_breaks_data[], int pp_breaks_size[2],
  emxArray_real_T *pp_coefs);
static void b_removeSmallPeaks(const double y[7500], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1]);
static void b_rescale_minmax(const double X[7000], double Y[7000]);
static void b_sortIdx(int x_data[], int x_size[1], int idx_data[], int idx_size
                      [1]);
static void c_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void c_findpeaks(const double Yin[7000], double Ypk_data[], int Ypk_size
  [2], double Xpk_data[], int Xpk_size[2]);
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
  iRBw_size[1], const double wPk_data[], const int wPk_size[2], const int
  iInf_data[], const int iInf_size[1], int iPkOut_data[], int iPkOut_size[1],
  double bPkOut_data[], int bPkOut_size[1], emxArray_real_T *bxPkOut,
  emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut);
static void conv(const double A[7500], const double B[38], double C[7463]);
static void d_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void d_removePeaksBelowMinPeakPromin(const double y[7000], int iPk_data[],
  int iPk_size[1], double pbPk_data[], int pbPk_size[1], int iLB_data[], int
  iLB_size[1], int iRB_data[], int iRB_size[1]);
static void diff(const emxArray_real_T *x, double y_data[], int y_size[1]);
static void do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1]);
static void e_findPeaksSeparatedByMoreThanM(const double y[7000], const int
  iPk_data[], const int iPk_size[1], int idx_data[], int idx_size[1]);
static void ecg_filt_rescale(const double X[7500], float Y[7500]);
static void fetchPeakExtents(const int idx_data[], const int idx_size[1], double
  bPk_data[], int bPk_size[1], emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk);
static void filter(const double b[4], const double a[4], const double x[7518],
                   const double zi[3], double y[7518]);
static void filtfilt(const double x_in[7500], double y_out[7500]);
static void findExtents(const double y[7500], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  double bPk_data[], int bPk_size[1], emxArray_real_T *bxPk, emxArray_real_T
  *byPk, emxArray_real_T *wxPk);
static void findLeftIntercept(const double y[7500], int *idx, int borderIdx,
  double refHeight);
static void findRightIntercept(const double y[7500], int *idx, int borderIdx,
  double refHeight);
static void findpeaks(const double Yin[7463], double varargin_2, double
                      Ypk_data[], int Ypk_size[1], double Xpk_data[], int
                      Xpk_size[1]);
static void flip(double x_data[], int x_size[1]);
static void flipud(double x[7518]);
static void getAllPeaksCodegen(const double y[7463], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void getHalfMaxBounds(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], double bounds_data[], int bounds_size[2]);
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
  int iLB_size[1], int iRB_data[], int iRB_size[1], double wxPk_data[], int
  wxPk_size[2]);
static void interp1(const double varargin_1_data[], const int varargin_1_size[1],
                    const double varargin_2_data[], const int varargin_2_size[1],
                    double Vq[7500]);
static void keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double linterp(double xa, double xb, double ya, double yb, double yc,
                      double bc);
static double mean(const double x[7500]);
static void merge(int idx_data[], int x_data[], int offset, int np, int nq, int
                  iwork_data[], int xwork_data[]);
static void merge_block(int idx_data[], int x_data[], int offset, int n, int
  preSortLevel, int iwork_data[], int xwork_data[]);
static void merge_pow2_block(int idx_data[], int x_data[], int offset);
static int nonSingletonDim(const int x_size[1]);
static void power(const double a[7500], double y[7500]);
static void ppval(const double pp_breaks_data[], const int pp_breaks_size[2],
                  const emxArray_real_T *pp_coefs, double x, double v_data[],
                  int v_size[1]);
static void pwchcore(const double x_data[], const int x_size[1], const double
                     y_data[], const double s[2], double pp_breaks_data[], int
                     pp_breaks_size[2], double pp_coefs[4]);
static void removeSmallPeaks(const double y[7463], const int iFinite_data[],
  const int iFinite_size[1], double minH, int iPk_data[], int iPk_size[1]);
static void rescale_minmax(const double X[7500], double Y[7500]);
static void sort(int x_data[], int x_size[1]);
static void sortIdx(const double x_data[], const int x_size[1], int idx_data[],
                    int idx_size[1]);
static void spline(const double x_data[], const int x_size[1], const double
                   y_data[], const int y_size[2], double output_breaks_data[],
                   int output_breaks_size[2], emxArray_real_T *output_coefs);

// Function Definitions

//
// Arguments    : const double y[7500]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const emxArray_real_T *wxPk
//                const double bPk_data[]
//                double YpkOut_data[]
//                int YpkOut_size[1]
//                double XpkOut_data[]
//                int XpkOut_size[1]
//                double WpkOut_data[]
//                int WpkOut_size[1]
//                double PpkOut_data[]
//                int PpkOut_size[1]
// Return Type  : void
//
static void assignFullOutputs(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const emxArray_real_T *wxPk, const double bPk_data[], double
  YpkOut_data[], int YpkOut_size[1], double XpkOut_data[], int XpkOut_size[1],
  double WpkOut_data[], int WpkOut_size[1], double PpkOut_data[], int
  PpkOut_size[1])
{
  int loop_ub;
  int i7;
  short tmp_data[15000];
  YpkOut_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    YpkOut_data[i7] = y[iPk_data[i7] - 1];
  }

  loop_ub = iPk_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    tmp_data[i7] = (short)(1 + (short)(iPk_data[i7] - 1));
  }

  XpkOut_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    XpkOut_data[i7] = tmp_data[i7];
  }

  diff(wxPk, WpkOut_data, WpkOut_size);
  PpkOut_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    PpkOut_data[i7] = YpkOut_data[i7] - bPk_data[i7];
  }
}

//
// Arguments    : const double y[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                const emxArray_real_T *wxPk
//                const double bPk_data[]
//                double YpkOut_data[]
//                int YpkOut_size[2]
//                double XpkOut_data[]
//                int XpkOut_size[2]
//                double WpkOut_data[]
//                int WpkOut_size[2]
//                double PpkOut_data[]
//                int PpkOut_size[2]
// Return Type  : void
//
static void b_assignFullOutputs(const double y[7000], const int iPk_data[],
  const int iPk_size[1], const emxArray_real_T *wxPk, const double bPk_data[],
  double YpkOut_data[], int YpkOut_size[2], double XpkOut_data[], int
  XpkOut_size[2], double WpkOut_data[], int WpkOut_size[2], double PpkOut_data[],
  int PpkOut_size[2])
{
  int loop_ub;
  int i16;
  static double tmp_data[15000];
  int tmp_size[1];
  static double Ypk_data[14926];
  double Wpk_data[14926];
  short b_tmp_data[14926];
  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    Ypk_data[i16] = y[iPk_data[i16] - 1];
  }

  diff(wxPk, tmp_data, tmp_size);
  loop_ub = tmp_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    Wpk_data[i16] = tmp_data[i16];
  }

  YpkOut_size[0] = 1;
  YpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    YpkOut_data[i16] = Ypk_data[i16];
  }

  PpkOut_size[0] = 1;
  PpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    PpkOut_data[i16] = Ypk_data[i16] - bPk_data[i16];
  }

  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    b_tmp_data[i16] = (short)(1 + (short)(iPk_data[i16] - 1));
  }

  XpkOut_size[0] = 1;
  XpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    XpkOut_data[i16] = b_tmp_data[i16];
  }

  WpkOut_size[0] = 1;
  WpkOut_size[1] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    WpkOut_data[i16] = Wpk_data[i16];
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[2]
//                double xi
// Return Type  : int
//
static int b_bsearch(const double x_data[], const int x_size[2], double xi)
{
  int n;
  int low_ip1;
  int high_i;
  int mid_i;
  n = 1;
  low_ip1 = 2;
  high_i = x_size[1];
  while (high_i > low_ip1) {
    mid_i = (n >> 1) + (high_i >> 1);
    if ((n & 1) == 1 && (high_i & 1) == 1) {
      mid_i++;
    }

    if (xi >= x_data[mid_i - 1]) {
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
//                const double wPk_data[]
//                const int wPk_size[2]
//                const int iInf_data[]
//                const int iInf_size[1]
//                int iPkOut_data[]
//                int iPkOut_size[1]
//                double bPkOut_data[]
//                int bPkOut_size[1]
//                emxArray_real_T *bxPkOut
//                emxArray_real_T *byPkOut
//                emxArray_real_T *wxPkOut
// Return Type  : void
//
static void b_combineFullPeaks(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const double wPk_data[], const int wPk_size[2], const int
  iInf_data[], const int iInf_size[1], int iPkOut_data[], int iPkOut_size[1],
  double bPkOut_data[], int bPkOut_size[1], emxArray_real_T *bxPkOut,
  emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut)
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
  int i14;
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
  bPkOut_size[0] = unnamed_idx_0;
  loop_ub = unnamed_idx_0;
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut_data[u0] = 0.0;
  }

  loop_ub = bPk_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut_data[iFinite_data[u0] - 1] = bPk_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    varargin_1_data[u0] = iInfinite_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut_data[varargin_1_data[u0] - 1] = 0.0;
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
    bxPkOut->data[iFinite_data[u0] + bxPkOut->size[0] - 1] = tmp_data[u0];
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[b_iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)
      ((short)(iInf_data[u0] - 1) + (short)(ib_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[b_iInfinite_data[u0] + bxPkOut->size[0] - 1] = 0.5 * (double)
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
    byPkOut->data[iFinite_data[u0] + byPkOut->size[0] - 1] = y[iRBw_data[u0] - 1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[b_iInfinite_data[u0] - 1] = y[ib_data[u0] - 1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[b_iInfinite_data[u0] + byPkOut->size[0] - 1] = y[iInfR_data[u0]
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

  loop_ub = wPk_size[0];
  for (u0 = 0; u0 < 2; u0++) {
    for (i14 = 0; i14 < loop_ub; i14++) {
      wxPkOut->data[iFinite_data[i14] + wxPkOut->size[0] * u0 - 1] =
        wPk_data[i14 + wPk_size[0] * u0];
    }
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[b_iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)
      ((short)(iInf_data[u0] - 1) + (short)(ib_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[b_iInfinite_data[u0] + wxPkOut->size[0] - 1] = 0.5 * (double)
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
  while (ialast <= a_size[0] && iblast <= b_size[0]) {
    b_ialast = ialast;
    ak = a_data[ialast - 1];
    while (b_ialast < a_size[0] && a_data[b_ialast] == ak) {
      b_ialast++;
    }

    ialast = b_ialast;
    b_iblast = iblast;
    bk = b_data[iblast - 1];
    while (b_iblast < b_size[0] && b_data[b_iblast] == bk) {
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
//                double bPk_data[]
//                int bPk_size[1]
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void b_findExtents(const double y[7000], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  double bPk_data[], int bPk_size[1], emxArray_real_T *bxPk, emxArray_real_T
  *byPk, emxArray_real_T *wxPk)
{
  static double yFinite[7000];
  int loop_ub;
  int i23;
  static double b_bPk_data[7000];
  int b_bPk_size[1];
  static int iLB_data[7000];
  int iLB_size[1];
  static int iRB_data[7000];
  int iRB_size[1];
  int b_iPk_size[1];
  static int b_iPk_data[7000];
  static double wxPk_data[14000];
  int wxPk_size[2];
  memcpy(&yFinite[0], &y[0], 7000U * sizeof(double));
  loop_ub = iInf_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    yFinite[iInf_data[i23] - 1] = rtNaN;
  }

  b_getPeakBase(yFinite, iPk_data, iPk_size, iFin_data, iFin_size, iInflect_data,
                iInflect_size, b_bPk_data, b_bPk_size, iLB_data, iLB_size,
                iRB_data, iRB_size);
  b_iPk_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    b_iPk_data[i23] = iPk_data[i23];
  }

  d_removePeaksBelowMinPeakPromin(yFinite, b_iPk_data, b_iPk_size, b_bPk_data,
    b_bPk_size, iLB_data, iLB_size, iRB_data, iRB_size);
  b_getPeakWidth(yFinite, b_iPk_data, b_iPk_size, b_bPk_data, b_bPk_size,
                 iLB_data, iLB_size, iRB_data, iRB_size, wxPk_data, wxPk_size);
  b_combineFullPeaks(y, b_iPk_data, b_iPk_size, b_bPk_data, b_bPk_size, iLB_data,
                     iLB_size, iRB_data, iRB_size, wxPk_data, wxPk_size,
                     iInf_data, iInf_size, iPk_data, iPk_size, bPk_data,
                     bPk_size, bxPk, byPk, wxPk);
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
  while (*idx >= borderIdx && y[*idx - 1] > refHeight) {
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
  while (*idx <= borderIdx && y[*idx - 1] > refHeight) {
    (*idx)++;
  }
}

//
// Arguments    : const double Yin[7500]
//                double Ypk_data[]
//                int Ypk_size[1]
//                double Xpk_data[]
//                int Xpk_size[1]
// Return Type  : void
//
static void b_findpeaks(const double Yin[7500], double Ypk_data[], int Ypk_size
  [1], double Xpk_data[], int Xpk_size[1])
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
  emxArray_real_T *bxPk;
  static int iPk_data[15000];
  emxArray_real_T *byPk;
  emxArray_real_T *wxPk;
  static double bPk_data[15000];
  int bPk_size[1];
  static int idx_data[15000];
  int b_iPk_size[1];
  static int b_iPk_data[15000];
  static double Wpk_data[15000];
  static double Ppk_data[15000];
  b_getAllPeaksCodegen(Yin, iFinite_data, iFinite_size, iInfinite_data,
                       iInfinite_size, iInflect_data, iInflect_size);
  b_removeSmallPeaks(Yin, iFinite_data, iFinite_size, tmp_data, tmp_size);
  iPk_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    iPk_data[i3] = tmp_data[i3];
  }

  emxInit_real_T(&bxPk, 2);
  emxInit_real_T(&byPk, 2);
  emxInit_real_T(&wxPk, 2);
  findExtents(Yin, iPk_data, iPk_size, iFinite_data, iFinite_size,
              iInfinite_data, iInfinite_size, iInflect_data, iInflect_size,
              bPk_data, bPk_size, bxPk, byPk, wxPk);
  d_findPeaksSeparatedByMoreThanM(iPk_size, idx_data, tmp_size);
  b_keepAtMostNpPeaks(idx_data, tmp_size);
  fetchPeakExtents(idx_data, tmp_size, bPk_data, bPk_size, bxPk, byPk, wxPk);
  b_iPk_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  emxFree_real_T(&byPk);
  emxFree_real_T(&bxPk);
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_iPk_data[i3] = iPk_data[idx_data[i3] - 1];
  }

  assignFullOutputs(Yin, b_iPk_data, b_iPk_size, wxPk, bPk_data, Ypk_data,
                    Ypk_size, Xpk_data, Xpk_size, Wpk_data, tmp_size, Ppk_data,
                    iFinite_size);
  emxFree_real_T(&wxPk);
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
    } else if (rtIsInf(y[k]) && y[k] > 0.0) {
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

  if (!isinfykfirst && (nInflect + 1 == 0 || iInflect_data[nInflect] < 7500)) {
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
//                double bounds_data[]
//                int bounds_size[2]
// Return Type  : void
//
static void b_getHalfMaxBounds(const double y[7000], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], double bounds_data[], int bounds_size[2])
{
  int iLeft;
  int iRight;
  int i;
  double refHeight;
  bounds_size[0] = iPk_size[0];
  bounds_size[1] = 2;
  iLeft = iPk_size[0] << 1;
  for (iRight = 0; iRight < iLeft; iRight++) {
    bounds_data[iRight] = 0.0;
  }

  for (i = 0; i < iPk_size[0]; i++) {
    refHeight = (y[iPk_data[i] - 1] + base_data[i]) / 2.0;
    iLeft = iPk_data[i];
    b_findLeftIntercept(y, &iLeft, iLB_data[i], refHeight);
    if (iLeft < iLB_data[i]) {
      bounds_data[i] = 1.0 + ((double)iLB_data[i] - 1.0);
    } else {
      bounds_data[i] = linterp(1.0 + ((double)iLeft - 1.0), 1.0 + ((double)
        (iLeft + 1) - 1.0), y[iLeft - 1], y[iLeft], y[iPk_data[i] - 1],
        base_data[i]);
    }

    iRight = iPk_data[i];
    b_findRightIntercept(y, &iRight, iRB_data[i], refHeight);
    if (iRight > iRB_data[i]) {
      bounds_data[i + bounds_size[0]] = 1.0 + ((double)iRB_data[i] - 1.0);
    } else {
      bounds_data[i + bounds_size[0]] = linterp(1.0 + ((double)iRight - 1.0),
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
        while (n + 1 > 0 && valley_data[n] > v) {
          n--;
        }
      }

      i++;
    }

    p = yTemp[iInflect_data[i] - 1];
    while (n + 1 > 0 && peak_data[n] < p) {
      if (valley_data[n] < v) {
        v = valley_data[n];
        iv = iValley_data[n];
      }

      n--;
    }

    isv = iv;
    while (n + 1 > 0 && peak_data[n] <= p) {
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
  int i13;
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
  for (i13 = 0; i13 < loop_ub; i13++) {
    tmp_data[i13] = iPk_data[i13];
  }

  c_flipud(tmp_data, tmp_size);
  b_tmp_size[0] = iFin_size[0];
  loop_ub = iFin_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    b_tmp_data[i13] = iFin_data[i13];
  }

  c_flipud(b_tmp_data, b_tmp_size);
  c_tmp_size[0] = iInflect_size[0];
  loop_ub = iInflect_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    c_tmp_data[i13] = iInflect_data[i13];
  }

  c_flipud(c_tmp_data, c_tmp_size);
  b_getLeftBase(yTemp, tmp_data, tmp_size, b_tmp_data, b_tmp_size, c_tmp_data,
                iRightBase_data, c_tmp_size, iRightSaddle_data,
                iRightSaddle_size);
  tmp_size[0] = c_tmp_size[0];
  loop_ub = c_tmp_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    tmp_data[i13] = iRightBase_data[i13];
  }

  c_flipud(tmp_data, tmp_size);
  c_tmp_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    iRightBase_data[i13] = tmp_data[i13];
  }

  tmp_size[0] = iRightSaddle_size[0];
  loop_ub = iRightSaddle_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    tmp_data[i13] = iRightSaddle_data[i13];
  }

  c_flipud(tmp_data, tmp_size);
  iRightSaddle_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    iRightSaddle_data[i13] = tmp_data[i13];
  }

  if (iLeftBase_size[0] <= c_tmp_size[0]) {
    csz_idx_0 = (short)iLeftBase_size[0];
  } else {
    csz_idx_0 = (short)c_tmp_size[0];
  }

  for (loop_ub = 0; loop_ub + 1 <= csz_idx_0; loop_ub++) {
    if (yTemp[iLeftBase_data[loop_ub] - 1] > yTemp[iRightBase_data[loop_ub] - 1]
        || rtIsNaN(yTemp[iRightBase_data[loop_ub] - 1])) {
      maxval_data[loop_ub] = yTemp[iLeftBase_data[loop_ub] - 1];
    } else {
      maxval_data[loop_ub] = yTemp[iRightBase_data[loop_ub] - 1];
    }
  }

  peakBase_size[0] = csz_idx_0;
  loop_ub = csz_idx_0;
  for (i13 = 0; i13 < loop_ub; i13++) {
    peakBase_data[i13] = maxval_data[i13];
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
//                double wxPk_data[]
//                int wxPk_size[2]
// Return Type  : void
//
static void b_getPeakWidth(const double y[7000], const int iPk_data[], const int
  iPk_size[1], const double pbPk_data[], const int pbPk_size[1], int iLB_data[],
  int iLB_size[1], int iRB_data[], int iRB_size[1], double wxPk_data[], int
  wxPk_size[2])
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

  b_getHalfMaxBounds(y, iPk_data, iPk_size, base_data, iLB_data, iRB_data,
                     wxPk_data, wxPk_size);
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
// Arguments    : const double x_data[]
//                const int x_size[2]
// Return Type  : double
//
static double b_mean(const double x_data[], const int x_size[2])
{
  double y;
  int k;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[1]; k++) {
      y += x_data[k - 1];
    }
  }

  y /= (double)x_size[1];
  return y;
}

//
// Arguments    : int idx_data[]
//                const double x_data[]
//                int n
// Return Type  : void
//
static void b_mergesort(int idx_data[], const double x_data[], int n)
{
  int k;
  boolean_T p;
  int i;
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  int iwork_data[14926];
  for (k = 1; k <= n - 1; k += 2) {
    if (x_data[k - 1] >= x_data[k] || rtIsNaN(x_data[k - 1])) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      idx_data[k - 1] = k;
      idx_data[k] = k + 1;
    } else {
      idx_data[k - 1] = k + 1;
      idx_data[k] = k;
    }
  }

  if ((n & 1) != 0) {
    idx_data[n - 1] = n;
  }

  i = 2;
  while (i < n) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < n + 1; pEnd = qEnd + i) {
      b_p = j - 1;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > n + 1) {
        qEnd = n + 1;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if (x_data[idx_data[b_p] - 1] >= x_data[idx_data[q - 1] - 1] || rtIsNaN
            (x_data[idx_data[b_p] - 1])) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          iwork_data[k] = idx_data[b_p];
          b_p++;
          if (b_p + 1 == pEnd) {
            while (q < qEnd) {
              k++;
              iwork_data[k] = idx_data[q - 1];
              q++;
            }
          }
        } else {
          iwork_data[k] = idx_data[q - 1];
          q++;
          if (q == qEnd) {
            while (b_p + 1 < pEnd) {
              k++;
              iwork_data[k] = idx_data[b_p];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx_data[j + k - 1] = iwork_data[k];
      }

      j = qEnd;
    }

    i = i2;
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double y_data[]
//                int yoffset
//                const double s_data[]
//                const double dx_data[]
//                const double divdif_data[]
//                double pp_breaks_data[]
//                int pp_breaks_size[2]
//                emxArray_real_T *pp_coefs
// Return Type  : void
//
static void b_pwchcore(const double x_data[], const int x_size[1], const double
  y_data[], int yoffset, const double s_data[], const double dx_data[], const
  double divdif_data[], double pp_breaks_data[], int pp_breaks_size[2],
  emxArray_real_T *pp_coefs)
{
  int nx;
  int nxm1;
  int loop_ub;
  int i10;
  double dzzdx;
  double dzdxdx;
  nx = x_size[0] - 1;
  nxm1 = x_size[0] - 1;
  pp_breaks_size[0] = 1;
  pp_breaks_size[1] = x_size[0];
  loop_ub = x_size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    pp_breaks_data[pp_breaks_size[0] * i10] = x_data[i10];
  }

  i10 = pp_coefs->size[0] * pp_coefs->size[1] * pp_coefs->size[2];
  pp_coefs->size[0] = 1;
  pp_coefs->size[1] = (short)(x_size[0] - 1);
  pp_coefs->size[2] = 4;
  emxEnsureCapacity((emxArray__common *)pp_coefs, i10, sizeof(double));
  for (loop_ub = 0; loop_ub + 1 <= nx; loop_ub++) {
    dzzdx = (divdif_data[loop_ub] - s_data[loop_ub]) / dx_data[loop_ub];
    dzdxdx = (s_data[loop_ub + 1] - divdif_data[loop_ub]) / dx_data[loop_ub];
    pp_coefs->data[loop_ub] = (dzdxdx - dzzdx) / dx_data[loop_ub];
    pp_coefs->data[nx + loop_ub] = 2.0 * dzzdx - dzdxdx;
    pp_coefs->data[(nxm1 << 1) + loop_ub] = s_data[loop_ub];
    pp_coefs->data[3 * nxm1 + loop_ub] = y_data[yoffset + loop_ub];
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
      if (y[iFinite_data[k] - 2] > y[iFinite_data[k]] || rtIsNaN
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
    while (!exitg1 && ix < 7001) {
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
    while (!exitg1 && ix < 7001) {
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
// Arguments    : int x_data[]
//                int x_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void b_sortIdx(int x_data[], int x_size[1], int idx_data[], int idx_size
                      [1])
{
  short unnamed_idx_0;
  int nQuartets;
  int nDone;
  int n;
  int i;
  int x4[4];
  short idx4[4];
  static int iwork_data[14926];
  int xwork_data[14926];
  int nLeft;
  signed char perm[4];
  int i2;
  int i3;
  int i4;
  unnamed_idx_0 = (short)x_size[0];
  idx_size[0] = unnamed_idx_0;
  nQuartets = unnamed_idx_0;
  for (nDone = 0; nDone < nQuartets; nDone++) {
    idx_data[nDone] = 0;
  }

  n = x_size[0];
  for (i = 0; i < 4; i++) {
    x4[i] = 0;
    idx4[i] = 0;
  }

  nQuartets = unnamed_idx_0;
  for (nDone = 0; nDone < nQuartets; nDone++) {
    iwork_data[nDone] = 0;
  }

  nQuartets = (short)x_size[0];
  for (nDone = 0; nDone < nQuartets; nDone++) {
    xwork_data[nDone] = 0;
  }

  nQuartets = x_size[0] >> 2;
  for (nDone = 1; nDone <= nQuartets; nDone++) {
    i = nDone - 1 << 2;
    idx4[0] = (short)(i + 1);
    idx4[1] = (short)(i + 2);
    idx4[2] = (short)(i + 3);
    idx4[3] = (short)(i + 4);
    x4[0] = x_data[i];
    x4[1] = x_data[i + 1];
    x4[2] = x_data[i + 2];
    x4[3] = x_data[i + 3];
    if (x_data[i] <= x_data[i + 1]) {
      nLeft = 1;
      i2 = 2;
    } else {
      nLeft = 2;
      i2 = 1;
    }

    if (x_data[i + 2] <= x_data[i + 3]) {
      i3 = 3;
      i4 = 4;
    } else {
      i3 = 4;
      i4 = 3;
    }

    if (x4[nLeft - 1] <= x4[i3 - 1]) {
      if (x4[i2 - 1] <= x4[i3 - 1]) {
        perm[0] = (signed char)nLeft;
        perm[1] = (signed char)i2;
        perm[2] = (signed char)i3;
        perm[3] = (signed char)i4;
      } else if (x4[i2 - 1] <= x4[i4 - 1]) {
        perm[0] = (signed char)nLeft;
        perm[1] = (signed char)i3;
        perm[2] = (signed char)i2;
        perm[3] = (signed char)i4;
      } else {
        perm[0] = (signed char)nLeft;
        perm[1] = (signed char)i3;
        perm[2] = (signed char)i4;
        perm[3] = (signed char)i2;
      }
    } else if (x4[nLeft - 1] <= x4[i4 - 1]) {
      if (x4[i2 - 1] <= x4[i4 - 1]) {
        perm[0] = (signed char)i3;
        perm[1] = (signed char)nLeft;
        perm[2] = (signed char)i2;
        perm[3] = (signed char)i4;
      } else {
        perm[0] = (signed char)i3;
        perm[1] = (signed char)nLeft;
        perm[2] = (signed char)i4;
        perm[3] = (signed char)i2;
      }
    } else {
      perm[0] = (signed char)i3;
      perm[1] = (signed char)i4;
      perm[2] = (signed char)nLeft;
      perm[3] = (signed char)i2;
    }

    idx_data[i] = idx4[perm[0] - 1];
    idx_data[i + 1] = idx4[perm[1] - 1];
    idx_data[i + 2] = idx4[perm[2] - 1];
    idx_data[i + 3] = idx4[perm[3] - 1];
    x_data[i] = x4[perm[0] - 1];
    x_data[i + 1] = x4[perm[1] - 1];
    x_data[i + 2] = x4[perm[2] - 1];
    x_data[i + 3] = x4[perm[3] - 1];
  }

  nDone = nQuartets << 2;
  nLeft = x_size[0] - nDone;
  if (nLeft > 0) {
    for (nQuartets = 1; nQuartets <= nLeft; nQuartets++) {
      idx4[nQuartets - 1] = (short)(nDone + nQuartets);
      x4[nQuartets - 1] = x_data[nDone + nQuartets - 1];
    }

    for (i = 0; i < 4; i++) {
      perm[i] = 0;
    }

    if (nLeft == 1) {
      perm[0] = 1;
    } else if (nLeft == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }

    for (nQuartets = 1; nQuartets <= nLeft; nQuartets++) {
      idx_data[nDone + nQuartets - 1] = idx4[perm[nQuartets - 1] - 1];
      x_data[nDone + nQuartets - 1] = x4[perm[nQuartets - 1] - 1];
    }
  }

  nQuartets = 2;
  if (n > 1) {
    if (n >= 256) {
      nQuartets = n >> 8;
      for (nDone = 1; nDone <= nQuartets; nDone++) {
        merge_pow2_block(idx_data, x_data, nDone - 1 << 8);
      }

      nQuartets <<= 8;
      nDone = n - nQuartets;
      if (nDone > 0) {
        merge_block(idx_data, x_data, nQuartets, nDone, 2, iwork_data,
                    xwork_data);
      }

      nQuartets = 8;
    }

    merge_block(idx_data, x_data, 0, n, nQuartets, iwork_data, xwork_data);
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
//                double Ypk_data[]
//                int Ypk_size[2]
//                double Xpk_data[]
//                int Xpk_size[2]
// Return Type  : void
//
static void c_findpeaks(const double Yin[7000], double Ypk_data[], int Ypk_size
  [2], double Xpk_data[], int Xpk_size[2])
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
  int i11;
  emxArray_real_T *bxPk;
  static int iPk_data[14926];
  emxArray_real_T *byPk;
  emxArray_real_T *wxPk;
  static double bPk_data[14926];
  int bPk_size[1];
  static int idx_data[14926];
  int b_bPk_size[1];
  emxArray_real_T *b_bxPk;
  static double b_bPk_data[15000];
  emxArray_real_T *b_byPk;
  emxArray_real_T *b_wxPk;
  int b_iPk_size[1];
  static int b_iPk_data[14926];
  int Wpk_size[2];
  static double Ppk_data[14926];
  int Ppk_size[2];
  c_getAllPeaksCodegen(Yin, iFinite_data, iFinite_size, iInfinite_data,
                       iInfinite_size, iInflect_data, iInflect_size);
  c_removeSmallPeaks(Yin, iFinite_data, iFinite_size, tmp_data, tmp_size);
  iPk_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i11 = 0; i11 < loop_ub; i11++) {
    iPk_data[i11] = tmp_data[i11];
  }

  emxInit_real_T(&bxPk, 2);
  emxInit_real_T(&byPk, 2);
  emxInit_real_T(&wxPk, 2);
  b_findExtents(Yin, iPk_data, iPk_size, iFinite_data, iFinite_size,
                iInfinite_data, iInfinite_size, iInflect_data, iInflect_size,
                bPk_data, bPk_size, bxPk, byPk, wxPk);
  e_findPeaksSeparatedByMoreThanM(Yin, iPk_data, iPk_size, idx_data,
    iFinite_size);
  c_keepAtMostNpPeaks(idx_data, iFinite_size);
  b_bPk_size[0] = bPk_size[0];
  loop_ub = bPk_size[0];
  for (i11 = 0; i11 < loop_ub; i11++) {
    b_bPk_data[i11] = bPk_data[i11];
  }

  emxInit_real_T(&b_bxPk, 2);
  i11 = b_bxPk->size[0] * b_bxPk->size[1];
  b_bxPk->size[0] = bxPk->size[0];
  b_bxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_bxPk, i11, sizeof(double));
  loop_ub = bxPk->size[0] * bxPk->size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    b_bxPk->data[i11] = bxPk->data[i11];
  }

  emxFree_real_T(&bxPk);
  emxInit_real_T(&b_byPk, 2);
  i11 = b_byPk->size[0] * b_byPk->size[1];
  b_byPk->size[0] = byPk->size[0];
  b_byPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_byPk, i11, sizeof(double));
  loop_ub = byPk->size[0] * byPk->size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    b_byPk->data[i11] = byPk->data[i11];
  }

  emxFree_real_T(&byPk);
  emxInit_real_T(&b_wxPk, 2);
  i11 = b_wxPk->size[0] * b_wxPk->size[1];
  b_wxPk->size[0] = wxPk->size[0];
  b_wxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_wxPk, i11, sizeof(double));
  loop_ub = wxPk->size[0] * wxPk->size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    b_wxPk->data[i11] = wxPk->data[i11];
  }

  emxFree_real_T(&wxPk);
  fetchPeakExtents(idx_data, iFinite_size, b_bPk_data, b_bPk_size, b_bxPk,
                   b_byPk, b_wxPk);
  b_iPk_size[0] = iFinite_size[0];
  loop_ub = iFinite_size[0];
  emxFree_real_T(&b_byPk);
  emxFree_real_T(&b_bxPk);
  for (i11 = 0; i11 < loop_ub; i11++) {
    b_iPk_data[i11] = iPk_data[idx_data[i11] - 1];
  }

  b_assignFullOutputs(Yin, b_iPk_data, b_iPk_size, b_wxPk, b_bPk_data, Ypk_data,
                      Ypk_size, Xpk_data, Xpk_size, bPk_data, Wpk_size, Ppk_data,
                      Ppk_size);
  emxFree_real_T(&b_wxPk);
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
  int i12;
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
    } else if (rtIsInf(y[k]) && y[k] > 0.0) {
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

  if (!isinfykfirst && (nInflect + 1 == 0 || iInflect_data[nInflect] < 7000)) {
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
    i12 = -1;
  } else {
    i12 = nInflect;
  }

  iInflect_size[0] = i12 + 1;
}

//
// Arguments    : int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void c_keepAtMostNpPeaks(int idx_data[], int idx_size[1])
{
  int b_idx_data[14926];
  int i26;
  if (idx_size[0] > 7000) {
    memcpy(&b_idx_data[0], &idx_data[0], 7000U * sizeof(int));
    idx_size[0] = 7000;
    for (i26 = 0; i26 < 7000; i26++) {
      idx_data[i26] = b_idx_data[i26];
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
    x_data[ii] = y[iPk_data[ii] - 1] - pbPk_data[ii] >= 0.3;
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while (!exitg1 && ii <= x_size_idx_0) {
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
      if (y[iFinite_data[k] - 2] > y[iFinite_data[k]] || rtIsNaN
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
//                const double wPk_data[]
//                const int wPk_size[2]
//                const int iInf_data[]
//                const int iInf_size[1]
//                int iPkOut_data[]
//                int iPkOut_size[1]
//                double bPkOut_data[]
//                int bPkOut_size[1]
//                emxArray_real_T *bxPkOut
//                emxArray_real_T *byPkOut
//                emxArray_real_T *wxPkOut
// Return Type  : void
//
static void combineFullPeaks(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double bPk_data[], const int bPk_size[1], const int
  iLBw_data[], const int iLBw_size[1], const int iRBw_data[], const int
  iRBw_size[1], const double wPk_data[], const int wPk_size[2], const int
  iInf_data[], const int iInf_size[1], int iPkOut_data[], int iPkOut_size[1],
  double bPkOut_data[], int bPkOut_size[1], emxArray_real_T *bxPkOut,
  emxArray_real_T *byPkOut, emxArray_real_T *wxPkOut)
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
  bPkOut_size[0] = unnamed_idx_0;
  loop_ub = unnamed_idx_0;
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut_data[u0] = 0.0;
  }

  loop_ub = bPk_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut_data[iFinite_data[u0] - 1] = bPk_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    ia_data[u0] = iInfinite_data[u0];
  }

  loop_ub = ia_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bPkOut_data[ia_data[u0] - 1] = 0.0;
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
    bxPkOut->data[iFinite_data[u0] + bxPkOut->size[0] - 1] = tmp_data[u0];
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)((short)
      (iInf_data[u0] - 1) + (short)(iInfL_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    bxPkOut->data[iInfinite_data[u0] + bxPkOut->size[0] - 1] = 0.5 * (double)
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
    byPkOut->data[iFinite_data[u0] + byPkOut->size[0] - 1] = y[iRBw_data[u0] - 1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[iInfinite_data[u0] - 1] = y[iInfL_data[u0] - 1];
  }

  loop_ub = (short)iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    byPkOut->data[iInfinite_data[u0] + byPkOut->size[0] - 1] = y[iInfR_data[u0]
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

  loop_ub = wPk_size[0];
  for (u0 = 0; u0 < 2; u0++) {
    for (i6 = 0; i6 < loop_ub; i6++) {
      wxPkOut->data[iFinite_data[i6] + wxPkOut->size[0] * u0 - 1] = wPk_data[i6
        + wPk_size[0] * u0];
    }
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[iInfinite_data[u0] - 1] = 0.5 * (double)(short)((short)((short)
      (iInf_data[u0] - 1) + (short)(iInfL_data[u0] - 1)) + 2);
  }

  loop_ub = iInf_size[0];
  for (u0 = 0; u0 < loop_ub; u0++) {
    wxPkOut->data[iInfinite_data[u0] + wxPkOut->size[0] - 1] = 0.5 * (double)
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
      C[b_k] += B[k] * A[b_k - k + 37];
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
    x_data[ii] = y[iPk_data[ii] - 1] - pbPk_data[ii] >= 0.3;
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while (!exitg1 && ii <= x_size_idx_0) {
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
//                double y_data[]
//                int y_size[1]
// Return Type  : void
//
static void diff(const emxArray_real_T *x, double y_data[], int y_size[1])
{
  int stride;
  int ix;
  int iy;
  int s;
  y_size[0] = (short)x->size[0];
  if (!(y_size[0] == 0)) {
    stride = x->size[0];
    ix = 0;
    iy = 0;
    for (s = 1; s <= stride; s++) {
      y_data[iy] = x->data[ix + stride] - x->data[ix];
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
  while (ialast <= na && iblast <= nb) {
    b_ialast = ialast;
    ak = a_data[ialast - 1];
    while (b_ialast < a_size[0] && a_data[b_ialast] == ak) {
      b_ialast++;
    }

    ialast = b_ialast;
    b_iblast = iblast;
    bk = b_data[iblast - 1];
    while (b_iblast < b_size[0] && b_data[b_iblast] == bk) {
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
    while (b_ialast < a_size[0] && a_data[b_ialast] == a_data[ialast - 1]) {
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
    while (b_iblast < b_size[0] && b_data[b_iblast] == b_data[iblast - 1]) {
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
// Arguments    : const double y[7000]
//                const int iPk_data[]
//                const int iPk_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void e_findPeaksSeparatedByMoreThanM(const double y[7000], const int
  iPk_data[], const int iPk_size[1], int idx_data[], int idx_size[1])
{
  int loop_ub;
  int partialTrueCount;
  int y_size[1];
  short locs_data[14926];
  static double y_data[14926];
  static int sortIdx_data[14926];
  int sortIdx_size[1];
  short locs_temp_data[14926];
  int i;
  boolean_T idelete_data[14926];
  int trueCount;
  boolean_T tmp_data[14926];
  short b_tmp_data[14926];
  if (iPk_size[0] == 0) {
    idx_size[0] = 0;
  } else {
    loop_ub = iPk_size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      locs_data[partialTrueCount] = (short)(1 + (short)
        (iPk_data[partialTrueCount] - 1));
    }

    y_size[0] = iPk_size[0];
    loop_ub = iPk_size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      y_data[partialTrueCount] = y[iPk_data[partialTrueCount] - 1];
    }

    sortIdx(y_data, y_size, sortIdx_data, sortIdx_size);
    loop_ub = sortIdx_size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      locs_temp_data[partialTrueCount] = locs_data[sortIdx_data[partialTrueCount]
        - 1];
    }

    loop_ub = (short)sortIdx_size[0];
    for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
      idelete_data[partialTrueCount] = false;
    }

    for (i = 0; i < sortIdx_size[0]; i++) {
      if (!idelete_data[i]) {
        loop_ub = sortIdx_size[0];
        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          tmp_data[partialTrueCount] = locs_temp_data[partialTrueCount] >=
            locs_data[sortIdx_data[i] - 1] - 500 &&
            locs_temp_data[partialTrueCount] <= locs_data[sortIdx_data[i] - 1] +
            500;
        }

        loop_ub = (short)sortIdx_size[0];
        for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount
             ++) {
          idelete_data[partialTrueCount] = idelete_data[partialTrueCount] ||
            tmp_data[partialTrueCount];
        }

        idelete_data[i] = false;
      }
    }

    loop_ub = (short)sortIdx_size[0] - 1;
    trueCount = 0;
    for (i = 0; i <= loop_ub; i++) {
      if (!idelete_data[i]) {
        trueCount++;
      }
    }

    partialTrueCount = 0;
    for (i = 0; i <= loop_ub; i++) {
      if (!idelete_data[i]) {
        b_tmp_data[partialTrueCount] = (short)(i + 1);
        partialTrueCount++;
      }
    }

    idx_size[0] = trueCount;
    for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount++)
    {
      idx_data[partialTrueCount] = sortIdx_data[b_tmp_data[partialTrueCount] - 1];
    }

    sort(idx_data, idx_size);
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
//                double bPk_data[]
//                int bPk_size[1]
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void fetchPeakExtents(const int idx_data[], const int idx_size[1], double
  bPk_data[], int bPk_size[1], emxArray_real_T *bxPk, emxArray_real_T *byPk,
  emxArray_real_T *wxPk)
{
  int loop_ub;
  int i21;
  double b_bPk_data[15000];
  emxArray_real_T *b_bxPk;
  int i22;
  emxArray_real_T *b_byPk;
  emxArray_real_T *b_wxPk;
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_bPk_data[i21] = bPk_data[idx_data[i21] - 1];
  }

  bPk_size[0] = idx_size[0];
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    bPk_data[i21] = b_bPk_data[i21];
  }

  emxInit_real_T(&b_bxPk, 2);
  i21 = b_bxPk->size[0] * b_bxPk->size[1];
  b_bxPk->size[0] = idx_size[0];
  b_bxPk->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_bxPk, i21, sizeof(double));
  loop_ub = idx_size[0];
  for (i21 = 0; i21 < 2; i21++) {
    for (i22 = 0; i22 < loop_ub; i22++) {
      b_bxPk->data[i22 + b_bxPk->size[0] * i21] = bxPk->data[idx_data[i22] +
        bxPk->size[0] * i21 - 1];
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
      b_byPk->data[i22 + b_byPk->size[0] * i21] = byPk->data[idx_data[i22] +
        byPk->size[0] * i21 - 1];
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
      b_wxPk->data[i22 + b_wxPk->size[0] * i21] = wxPk->data[idx_data[i22] +
        wxPk->size[0] * i21 - 1];
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
//                double bPk_data[]
//                int bPk_size[1]
//                emxArray_real_T *bxPk
//                emxArray_real_T *byPk
//                emxArray_real_T *wxPk
// Return Type  : void
//
static void findExtents(const double y[7500], int iPk_data[], int iPk_size[1],
  const int iFin_data[], const int iFin_size[1], const int iInf_data[], const
  int iInf_size[1], const int iInflect_data[], const int iInflect_size[1],
  double bPk_data[], int bPk_size[1], emxArray_real_T *bxPk, emxArray_real_T
  *byPk, emxArray_real_T *wxPk)
{
  static double yFinite[7500];
  int loop_ub;
  int i18;
  static double b_bPk_data[7500];
  int b_bPk_size[1];
  static int iLB_data[7500];
  int iLB_size[1];
  static int iRB_data[7500];
  int iRB_size[1];
  int b_iPk_size[1];
  static int b_iPk_data[7500];
  static double wxPk_data[15000];
  int wxPk_size[2];
  memcpy(&yFinite[0], &y[0], 7500U * sizeof(double));
  loop_ub = iInf_size[0];
  for (i18 = 0; i18 < loop_ub; i18++) {
    yFinite[iInf_data[i18] - 1] = rtNaN;
  }

  getPeakBase(yFinite, iPk_data, iPk_size, iFin_data, iFin_size, iInflect_data,
              iInflect_size, b_bPk_data, b_bPk_size, iLB_data, iLB_size,
              iRB_data, iRB_size);
  b_iPk_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i18 = 0; i18 < loop_ub; i18++) {
    b_iPk_data[i18] = iPk_data[i18];
  }

  c_removePeaksBelowMinPeakPromin(yFinite, b_iPk_data, b_iPk_size, b_bPk_data,
    b_bPk_size, iLB_data, iLB_size, iRB_data, iRB_size);
  getPeakWidth(yFinite, b_iPk_data, b_iPk_size, b_bPk_data, b_bPk_size, iLB_data,
               iLB_size, iRB_data, iRB_size, wxPk_data, wxPk_size);
  combineFullPeaks(y, b_iPk_data, b_iPk_size, b_bPk_data, b_bPk_size, iLB_data,
                   iLB_size, iRB_data, iRB_size, wxPk_data, wxPk_size, iInf_data,
                   iInf_size, iPk_data, iPk_size, bPk_data, bPk_size, bxPk, byPk,
                   wxPk);
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
  while (*idx >= borderIdx && y[*idx - 1] > refHeight) {
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
  while (*idx <= borderIdx && y[*idx - 1] > refHeight) {
    (*idx)++;
  }
}

//
// Arguments    : const double Yin[7463]
//                double varargin_2
//                double Ypk_data[]
//                int Ypk_size[1]
//                double Xpk_data[]
//                int Xpk_size[1]
// Return Type  : void
//
static void findpeaks(const double Yin[7463], double varargin_2, double
                      Ypk_data[], int Ypk_size[1], double Xpk_data[], int
                      Xpk_size[1])
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
  static int ia_data[7500];
  int ib_data[7500];
  static int idx_data[14926];
  short tmp_data[14926];
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

  Ypk_size[0] = iFinite_size[0];
  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Ypk_data[i1] = Yin[iPk_data[i1] - 1];
  }

  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    tmp_data[i1] = (short)(1 + (short)(iPk_data[i1] - 1));
  }

  Xpk_size[0] = iFinite_size[0];
  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Xpk_data[i1] = tmp_data[i1];
  }
}

//
// Arguments    : double x_data[]
//                int x_size[1]
// Return Type  : void
//
static void flip(double x_data[], int x_size[1])
{
  int n;
  int nd2;
  int k;
  double tmp;
  if (!(x_size[0] == 0) && x_size[0] > 1) {
    n = x_size[0];
    nd2 = x_size[0] >> 1;
    for (k = 1; k <= nd2; k++) {
      tmp = x_data[k - 1];
      x_data[k - 1] = x_data[n - k];
      x_data[n - k] = tmp;
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
    } else if (rtIsInf(y[k]) && y[k] > 0.0) {
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

  if (!isinfykfirst && (nInflect + 1 == 0 || iInflect_data[nInflect] < 7463)) {
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
//                double bounds_data[]
//                int bounds_size[2]
// Return Type  : void
//
static void getHalfMaxBounds(const double y[7500], const int iPk_data[], const
  int iPk_size[1], const double base_data[], const int iLB_data[], const int
  iRB_data[], double bounds_data[], int bounds_size[2])
{
  int iLeft;
  int iRight;
  int i;
  double refHeight;
  bounds_size[0] = iPk_size[0];
  bounds_size[1] = 2;
  iLeft = iPk_size[0] << 1;
  for (iRight = 0; iRight < iLeft; iRight++) {
    bounds_data[iRight] = 0.0;
  }

  for (i = 0; i < iPk_size[0]; i++) {
    refHeight = (y[iPk_data[i] - 1] + base_data[i]) / 2.0;
    iLeft = iPk_data[i];
    findLeftIntercept(y, &iLeft, iLB_data[i], refHeight);
    if (iLeft < iLB_data[i]) {
      bounds_data[i] = 1.0 + ((double)iLB_data[i] - 1.0);
    } else {
      bounds_data[i] = linterp(1.0 + ((double)iLeft - 1.0), 1.0 + ((double)
        (iLeft + 1) - 1.0), y[iLeft - 1], y[iLeft], y[iPk_data[i] - 1],
        base_data[i]);
    }

    iRight = iPk_data[i];
    findRightIntercept(y, &iRight, iRB_data[i], refHeight);
    if (iRight > iRB_data[i]) {
      bounds_data[i + bounds_size[0]] = 1.0 + ((double)iRB_data[i] - 1.0);
    } else {
      bounds_data[i + bounds_size[0]] = linterp(1.0 + ((double)iRight - 1.0),
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
        while (n + 1 > 0 && valley_data[n] > v) {
          n--;
        }
      }

      i++;
    }

    p = yTemp[iInflect_data[i] - 1];
    while (n + 1 > 0 && peak_data[n] < p) {
      if (valley_data[n] < v) {
        v = valley_data[n];
        iv = iValley_data[n];
      }

      n--;
    }

    isv = iv;
    while (n + 1 > 0 && peak_data[n] <= p) {
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
    if (yTemp[iLeftBase_data[loop_ub] - 1] > yTemp[iRightBase_data[loop_ub] - 1]
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
//                double wxPk_data[]
//                int wxPk_size[2]
// Return Type  : void
//
static void getPeakWidth(const double y[7500], const int iPk_data[], const int
  iPk_size[1], const double pbPk_data[], const int pbPk_size[1], int iLB_data[],
  int iLB_size[1], int iRB_data[], int iRB_size[1], double wxPk_data[], int
  wxPk_size[2])
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

  getHalfMaxBounds(y, iPk_data, iPk_size, base_data, iLB_data, iRB_data,
                   wxPk_data, wxPk_size);
}

//
// Arguments    : const double varargin_1_data[]
//                const int varargin_1_size[1]
//                const double varargin_2_data[]
//                const int varargin_2_size[1]
//                double Vq[7500]
// Return Type  : void
//
static void interp1(const double varargin_1_data[], const int varargin_1_size[1],
                    const double varargin_2_data[], const int varargin_2_size[1],
                    double Vq[7500])
{
  int y_size[1];
  int loop_ub;
  int i8;
  int x_size[1];
  static double y_data[15000];
  int nx;
  static double x_data[15000];
  emxArray_real_T *pp_coefs;
  int exitg1;
  int b_y_size[2];
  double xtmp;
  static double b_y_data[15000];
  static double pp_breaks_data[15000];
  int pp_breaks_size[2];
  double tmp_data[1];
  y_size[0] = varargin_2_size[0];
  loop_ub = varargin_2_size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    y_data[i8] = varargin_2_data[i8];
  }

  x_size[0] = varargin_1_size[0];
  loop_ub = varargin_1_size[0];
  for (i8 = 0; i8 < loop_ub; i8++) {
    x_data[i8] = varargin_1_data[i8];
  }

  nx = varargin_1_size[0];
  memset(&Vq[0], 0, 7500U * sizeof(double));
  loop_ub = 1;
  emxInit_real_T1(&pp_coefs, 3);
  do {
    exitg1 = 0;
    if (loop_ub <= nx) {
      if (rtIsNaN(varargin_1_data[loop_ub - 1])) {
        exitg1 = 1;
      } else {
        loop_ub++;
      }
    } else {
      if (varargin_1_data[1] < varargin_1_data[0]) {
        i8 = nx >> 1;
        for (loop_ub = 1; loop_ub <= i8; loop_ub++) {
          xtmp = x_data[loop_ub - 1];
          x_data[loop_ub - 1] = x_data[nx - loop_ub];
          x_data[nx - loop_ub] = xtmp;
        }

        flip(y_data, y_size);
      }

      b_y_size[0] = 1;
      b_y_size[1] = y_size[0];
      loop_ub = y_size[0];
      for (i8 = 0; i8 < loop_ub; i8++) {
        b_y_data[i8] = y_data[i8];
      }

      spline(x_data, x_size, b_y_data, b_y_size, pp_breaks_data, pp_breaks_size,
             pp_coefs);
      for (loop_ub = 0; loop_ub < 7500; loop_ub++) {
        ppval(pp_breaks_data, pp_breaks_size, pp_coefs, 1.0 + ((double)loop_ub +
               1.0 - 1.0), tmp_data, y_size);
        Vq[loop_ub] = tmp_data[0];
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&pp_coefs);
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
// Arguments    : int idx_data[]
//                int x_data[]
//                int offset
//                int np
//                int nq
//                int iwork_data[]
//                int xwork_data[]
// Return Type  : void
//
static void merge(int idx_data[], int x_data[], int offset, int np, int nq, int
                  iwork_data[], int xwork_data[])
{
  int n;
  int qend;
  int p;
  int iout;
  int exitg1;
  if (nq != 0) {
    n = np + nq;
    for (qend = 0; qend + 1 <= n; qend++) {
      iwork_data[qend] = idx_data[offset + qend];
      xwork_data[qend] = x_data[offset + qend];
    }

    p = 0;
    n = np;
    qend = np + nq;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] <= xwork_data[n]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[n];
        x_data[iout] = xwork_data[n];
        if (n + 1 < qend) {
          n++;
        } else {
          n = iout - p + 1;
          while (p + 1 <= np) {
            idx_data[n + p] = iwork_data[p];
            x_data[n + p] = xwork_data[p];
            p++;
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : int idx_data[]
//                int x_data[]
//                int offset
//                int n
//                int preSortLevel
//                int iwork_data[]
//                int xwork_data[]
// Return Type  : void
//
static void merge_block(int idx_data[], int x_data[], int offset, int n, int
  preSortLevel, int iwork_data[], int xwork_data[])
{
  int nPairs;
  int bLen;
  int tailOffset;
  int nTail;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx_data, x_data, offset + tailOffset, bLen, nTail - bLen,
              iwork_data, xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 1; nTail <= nPairs; nTail++) {
      merge(idx_data, x_data, offset + (nTail - 1) * tailOffset, bLen, bLen,
            iwork_data, xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    merge(idx_data, x_data, offset, bLen, n - bLen, iwork_data, xwork_data);
  }
}

//
// Arguments    : int idx_data[]
//                int x_data[]
//                int offset
// Return Type  : void
//
static void merge_pow2_block(int idx_data[], int x_data[], int offset)
{
  int b;
  int bLen;
  int bLen2;
  int nPairs;
  int k;
  int blockOffset;
  int q;
  int p;
  int iwork[256];
  int xwork[256];
  int exitg1;
  for (b = 0; b < 6; b++) {
    bLen = 1 << b + 2;
    bLen2 = bLen << 1;
    nPairs = 256 >> b + 3;
    for (k = 1; k <= nPairs; k++) {
      blockOffset = offset + (k - 1) * bLen2 - 1;
      for (q = 1; q <= bLen2; q++) {
        iwork[q - 1] = idx_data[blockOffset + q];
        xwork[q - 1] = x_data[blockOffset + q];
      }

      p = 0;
      q = bLen;
      do {
        exitg1 = 0;
        blockOffset++;
        if (xwork[p] <= xwork[q]) {
          idx_data[blockOffset] = iwork[p];
          x_data[blockOffset] = xwork[p];
          if (p + 1 < bLen) {
            p++;
          } else {
            exitg1 = 1;
          }
        } else {
          idx_data[blockOffset] = iwork[q];
          x_data[blockOffset] = xwork[q];
          if (q + 1 < bLen2) {
            q++;
          } else {
            q = blockOffset - p;
            while (p + 1 <= bLen) {
              idx_data[q + p + 1] = iwork[p];
              x_data[q + p + 1] = xwork[p];
              p++;
            }

            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
    }
  }
}

//
// Arguments    : const int x_size[1]
// Return Type  : int
//
static int nonSingletonDim(const int x_size[1])
{
  int dim;
  dim = 2;
  if (x_size[0] != 1) {
    dim = 1;
  }

  return dim;
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
// Arguments    : const double pp_breaks_data[]
//                const int pp_breaks_size[2]
//                const emxArray_real_T *pp_coefs
//                double x
//                double v_data[]
//                int v_size[1]
// Return Type  : void
//
static void ppval(const double pp_breaks_data[], const int pp_breaks_size[2],
                  const emxArray_real_T *pp_coefs, double x, double v_data[],
                  int v_size[1])
{
  int ip;
  double v;
  double xloc;
  int ic;
  v_size[0] = 1;
  if (pp_coefs->size[2] > 1 && rtIsNaN(x)) {
    v = x;
  } else {
    ip = b_bsearch(pp_breaks_data, pp_breaks_size, x) - 1;
    xloc = x - pp_breaks_data[ip];
    v = pp_coefs->data[ip];
    for (ic = 2; ic <= pp_coefs->size[2]; ic++) {
      v = xloc * v + pp_coefs->data[ip + (ic - 1) * (pp_breaks_size[1] - 1)];
    }
  }

  v_data[0] = v;
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double y_data[]
//                const double s[2]
//                double pp_breaks_data[]
//                int pp_breaks_size[2]
//                double pp_coefs[4]
// Return Type  : void
//
static void pwchcore(const double x_data[], const int x_size[1], const double
                     y_data[], const double s[2], double pp_breaks_data[], int
                     pp_breaks_size[2], double pp_coefs[4])
{
  int loop_ub;
  int i9;
  double dxj;
  double divdifij;
  double dzzdx;
  pp_breaks_size[0] = 1;
  pp_breaks_size[1] = x_size[0];
  loop_ub = x_size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    pp_breaks_data[i9] = x_data[i9];
  }

  for (loop_ub = 1; loop_ub < x_size[0]; loop_ub++) {
    dxj = x_data[loop_ub] - x_data[loop_ub - 1];
    divdifij = (y_data[loop_ub + 1] - y_data[loop_ub]) / dxj;
    dzzdx = (divdifij - s[loop_ub - 1]) / dxj;
    divdifij = (s[1] - divdifij) / dxj;
    pp_coefs[loop_ub - 1] = (divdifij - dzzdx) / dxj;
    pp_coefs[loop_ub] = 2.0 * dzzdx - divdifij;
    pp_coefs[loop_ub + 1] = s[loop_ub - 1];
    pp_coefs[3] = y_data[loop_ub];
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
      if (y[iFinite_data[k] - 2] > y[iFinite_data[k]] || rtIsNaN
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
    while (!exitg1 && ix < 7501) {
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
    while (!exitg1 && ix < 7501) {
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
// Arguments    : int x_data[]
//                int x_size[1]
// Return Type  : void
//
static void sort(int x_data[], int x_size[1])
{
  int dim;
  int i25;
  int vwork_size[1];
  int vstride;
  int k;
  static int vwork_data[14926];
  static emxArray_int32_T_14926 b_vwork_data;
  dim = nonSingletonDim(x_size);
  if (dim <= 1) {
    i25 = x_size[0];
  } else {
    i25 = 1;
  }

  vwork_size[0] = (short)i25;
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x_size[0];
    k = 2;
  }

  for (dim = 0; dim + 1 <= vstride; dim++) {
    for (k = 0; k + 1 <= i25; k++) {
      vwork_data[k] = x_data[dim + k * vstride];
    }

    b_sortIdx(vwork_data, vwork_size, b_vwork_data.data, b_vwork_data.size);
    for (k = 0; k + 1 <= i25; k++) {
      x_data[dim + k * vstride] = vwork_data[k];
    }
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void sortIdx(const double x_data[], const int x_size[1], int idx_data[],
                    int idx_size[1])
{
  int loop_ub;
  int i15;
  idx_size[0] = (short)x_size[0];
  loop_ub = (short)x_size[0];
  for (i15 = 0; i15 < loop_ub; i15++) {
    idx_data[i15] = 0;
  }

  b_mergesort(idx_data, x_data, x_size[0]);
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double y_data[]
//                const int y_size[2]
//                double output_breaks_data[]
//                int output_breaks_size[2]
//                emxArray_real_T *output_coefs
// Return Type  : void
//
static void spline(const double x_data[], const int x_size[1], const double
                   y_data[], const int y_size[2], double output_breaks_data[],
                   int output_breaks_size[2], emxArray_real_T *output_coefs)
{
  int nx;
  boolean_T has_endslopes;
  emxArray_real_T *t2_coefs;
  double c_data[2];
  int yoffset;
  double d31;
  int k;
  double dnnm2;
  static double s_data[15000];
  int t2_breaks_size[2];
  double t0_coefs[4];
  double b_c_data[3];
  static double dx_data[14999];
  double dvdf_data[14999];
  static double md_data[15000];
  double r;
  static double t2_breaks_data[15000];
  nx = x_size[0] - 1;
  has_endslopes = y_size[1] == x_size[0] + 2;
  if (x_size[0] <= 2) {
    if (has_endslopes) {
      c_data[0] = y_data[0];
      c_data[1] = y_data[y_size[1] - 1];
      pwchcore(x_data, x_size, y_data, c_data, s_data, t2_breaks_size, t0_coefs);
      output_breaks_size[0] = 1;
      output_breaks_size[1] = t2_breaks_size[1];
      nx = t2_breaks_size[0] * t2_breaks_size[1];
      for (yoffset = 0; yoffset < nx; yoffset++) {
        output_breaks_data[yoffset] = s_data[yoffset];
      }

      yoffset = output_coefs->size[0] * output_coefs->size[1] *
        output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = 4;
      output_coefs->size[2] = 1;
      emxEnsureCapacity((emxArray__common *)output_coefs, yoffset, sizeof(double));
      for (yoffset = 0; yoffset < 4; yoffset++) {
        output_coefs->data[yoffset] = t0_coefs[yoffset];
      }
    } else {
      c_data[0] = (y_data[1] - y_data[0]) / (x_data[1] - x_data[0]);
      c_data[1] = y_data[0];
      nx = x_size[0];
      for (yoffset = 0; yoffset < nx; yoffset++) {
        s_data[yoffset] = x_data[yoffset];
      }

      output_breaks_size[0] = 1;
      output_breaks_size[1] = x_size[0];
      nx = x_size[0];
      for (yoffset = 0; yoffset < nx; yoffset++) {
        output_breaks_data[yoffset] = s_data[yoffset];
      }

      yoffset = output_coefs->size[0] * output_coefs->size[1] *
        output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = 1;
      output_coefs->size[2] = 2;
      emxEnsureCapacity((emxArray__common *)output_coefs, yoffset, sizeof(double));
      for (yoffset = 0; yoffset < 2; yoffset++) {
        output_coefs->data[yoffset] = c_data[yoffset];
      }
    }
  } else {
    emxInit_real_T1(&t2_coefs, 3);
    if (x_size[0] == 3 && !has_endslopes) {
      d31 = x_data[1] - x_data[0];
      dnnm2 = (y_data[1] - y_data[0]) / d31;
      b_c_data[0] = ((y_data[2] - y_data[1]) / (x_data[2] - x_data[1]) - dnnm2) /
        (x_data[2] - x_data[0]);
      b_c_data[1] = dnnm2 - b_c_data[0] * d31;
      b_c_data[2] = y_data[0];
      c_data[0] = x_data[0];
      c_data[1] = x_data[2];
      output_breaks_size[0] = 1;
      output_breaks_size[1] = 2;
      for (yoffset = 0; yoffset < 2; yoffset++) {
        output_breaks_data[output_breaks_size[0] * yoffset] = c_data[yoffset];
      }

      yoffset = output_coefs->size[0] * output_coefs->size[1] *
        output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = 1;
      output_coefs->size[2] = 3;
      emxEnsureCapacity((emxArray__common *)output_coefs, yoffset, sizeof(double));
      for (yoffset = 0; yoffset < 3; yoffset++) {
        output_coefs->data[yoffset] = b_c_data[yoffset];
      }
    } else {
      yoffset = has_endslopes;
      for (k = 0; k + 1 <= nx; k++) {
        dx_data[k] = x_data[k + 1] - x_data[k];
        dvdf_data[k] = (y_data[yoffset + k + 1] - y_data[yoffset + k]) /
          dx_data[k];
      }

      for (k = 1; k + 1 <= nx; k++) {
        s_data[k] = 3.0 * (dx_data[k] * dvdf_data[k - 1] + dx_data[k - 1] *
                           dvdf_data[k]);
      }

      if (has_endslopes) {
        d31 = 0.0;
        dnnm2 = 0.0;
        s_data[0] = dx_data[1] * y_data[0];
        s_data[x_size[0] - 1] = dx_data[x_size[0] - 3] * y_data[x_size[0] + 1];
      } else {
        d31 = x_data[2] - x_data[0];
        dnnm2 = x_data[x_size[0] - 1] - x_data[x_size[0] - 3];
        s_data[0] = ((dx_data[0] + 2.0 * d31) * dx_data[1] * dvdf_data[0] +
                     dx_data[0] * dx_data[0] * dvdf_data[1]) / d31;
        s_data[x_size[0] - 1] = ((dx_data[x_size[0] - 2] + 2.0 * dnnm2) *
          dx_data[x_size[0] - 3] * dvdf_data[x_size[0] - 2] + dx_data[x_size[0]
          - 2] * dx_data[x_size[0] - 2] * dvdf_data[x_size[0] - 3]) / dnnm2;
      }

      md_data[0] = dx_data[1];
      md_data[x_size[0] - 1] = dx_data[x_size[0] - 3];
      for (k = 1; k + 1 <= nx; k++) {
        md_data[k] = 2.0 * (dx_data[k] + dx_data[k - 1]);
      }

      r = dx_data[1] / md_data[0];
      md_data[1] -= r * d31;
      s_data[1] -= r * s_data[0];
      for (k = 2; k + 1 <= nx; k++) {
        r = dx_data[k] / md_data[k - 1];
        md_data[k] -= r * dx_data[k - 2];
        s_data[k] -= r * s_data[k - 1];
      }

      r = dnnm2 / md_data[x_size[0] - 2];
      md_data[x_size[0] - 1] -= r * dx_data[x_size[0] - 3];
      s_data[x_size[0] - 1] -= r * s_data[x_size[0] - 2];
      s_data[x_size[0] - 1] /= md_data[x_size[0] - 1];
      for (k = x_size[0] - 2; k + 1 > 1; k--) {
        s_data[k] = (s_data[k] - dx_data[k - 1] * s_data[k + 1]) / md_data[k];
      }

      s_data[0] = (s_data[0] - d31 * s_data[1]) / md_data[0];
      b_pwchcore(x_data, x_size, y_data, yoffset, s_data, dx_data, dvdf_data,
                 t2_breaks_data, t2_breaks_size, t2_coefs);
      output_breaks_size[0] = 1;
      output_breaks_size[1] = t2_breaks_size[1];
      nx = t2_breaks_size[0] * t2_breaks_size[1];
      for (yoffset = 0; yoffset < nx; yoffset++) {
        output_breaks_data[yoffset] = t2_breaks_data[yoffset];
      }

      yoffset = output_coefs->size[0] * output_coefs->size[1] *
        output_coefs->size[2];
      output_coefs->size[0] = 1;
      output_coefs->size[1] = t2_coefs->size[1];
      output_coefs->size[2] = 4;
      emxEnsureCapacity((emxArray__common *)output_coefs, yoffset, sizeof(double));
      nx = t2_coefs->size[0] * t2_coefs->size[1] * t2_coefs->size[2];
      for (yoffset = 0; yoffset < nx; yoffset++) {
        output_coefs->data[yoffset] = t2_coefs->data[yoffset];
      }
    }

    emxFree_real_T(&t2_coefs);
  }
}

//
// get_hr_rr This function uses a variant of the Pan-Tompkins Algorithm to
// detect ECG QRS features from low frequency data:
//  Input: X (raw data, floats or doubles (preferred);
//  Outputs: Y .. (TODO);
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
  static double Peaks_data[14926];
  int Peaks_size[1];
  static double Locations_data[14926];
  int Locations_size[1];
  int dist_size[2];
  static double dist_data[14925];
  static double dv2[7500];
  static double pk_rr_n_data[15000];
  static double loc_rr_n_data[15000];
  static double dv3[7000];
  int pk_vout_size[2];
  int loc_vout_size[2];
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
  //  @ Equivalent to: [b, a] = butter(3, 2*2/Fs, 'high');
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
    while (!exitg1 && ix < 7464) {
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

  //  [Peaks, Locations] = findpeaks(X4,'MinPeakProminence',0.3656836669*max_peak); 
  findpeaks(X4, 0.3656836669 * mtmp, Peaks_data, Peaks_size, Locations_data,
            Locations_size);

  //  Output = [Peaks; Locations];
  //  calculate distance between fiducial markers:
  dist_size[0] = 1;
  dist_size[1] = Peaks_size[0] - 1;
  ix = Peaks_size[0] - 1;
  for (i = 0; i < ix; i++) {
    dist_data[i] = 0.0;
  }

  for (i = 0; i <= Locations_size[0] - 2; i++) {
    dist_data[i] = Locations_data[i + 1] - Locations_data[i];
  }

  mtmp = b_mean(dist_data, dist_size);

  //  average in seconds:
  *HR_mean = 60.0 / (mtmp / Fs);

  //  RR Interp:
  rescale_minmax(X0, dv2);
  for (i = 0; i < 7500; i++) {
    X[i] = 1.0 - dv2[i];
  }

  b_findpeaks(X, pk_rr_n_data, Peaks_size, loc_rr_n_data, Locations_size);
  interp1(loc_rr_n_data, Locations_size, pk_rr_n_data, Peaks_size, X);

  //  Truncate 1/2 sec on either side:
  b_rescale_minmax(*(double (*)[7000])&X[250], dv3);
  c_findpeaks(dv3, Peaks_data, pk_vout_size, Locations_data, loc_vout_size);
  dist_size[0] = 1;
  dist_size[1] = pk_vout_size[1] - 1;
  ix = pk_vout_size[1] - 1;
  for (i = 0; i < ix; i++) {
    dist_data[i] = 0.0;
  }

  for (i = 0; i <= loc_vout_size[1] - 2; i++) {
    dist_data[i] = Locations_data[i + 1] - Locations_data[i];
  }

  mtmp = b_mean(dist_data, dist_size);
  *Respiratory_rate = 60.0 / (mtmp / Fs);
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
