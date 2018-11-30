//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 19-Nov-2018 15:06:34
//

// Include Files
#include "rt_nonfinite.h"
#include "get_hr_rr.h"
#include "get_hr_rr_emxutil.h"

// Named Constants
#define Fs                             (250.0)

// Function Declarations
static void assignOutputs(const double y[2048], const double x[2048], const int
  iPk_data[], const int iPk_size[1], double YpkOut_data[], int YpkOut_size[2],
  double XpkOut_data[], int XpkOut_size[2]);
static void b_conv(const double A[7500], const double B[250], double C[7251]);
static void b_filter(const double b[2], const double x[7506], double zi, double
                     y[7506]);
static void b_filtfilt(const double x_in[7500], double y_out[7500]);
static void b_findpeaks(const double Yin[2048], double Ypk_data[], int Ypk_size
  [2], double Xpk_data[], int Xpk_size[2]);
static void b_flipud(double x[7506]);
static void b_getAllPeaksCodegen(const double y[2048], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void b_keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double b_mean(const emxArray_real_T *x);
static void b_mergesort(int idx_data[], const double x_data[], int n);
static void b_power(const double a[4096], double y[4096]);
static void b_removeSmallPeaks(const double y[2048], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1]);
static void c_filter(const double b[7], const double a[7], const double x[7536],
                     const double zi[6], double y[7536]);
static void c_filtfilt(const double x_in[7500], double y_out[7500]);
static void c_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void c_flipud(double x[7536]);
static double c_mean(const double x[4096]);
static void conv(const double A[7500], const double B[38], double C[7463]);
static void d_filtfilt(const double x_in[7500], double y_out[7500]);
static void d_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1]);
static void ecg_filt_rescale(const double X[7500], float Y[7500]);
static void fft(const double x[4096], creal_T y[4096]);
static void filter(const double b[4], const double a[4], const double x[7518],
                   const double zi[3], double y[7518]);
static void filtfilt(const double x_in[7500], double y_out[7500]);
static void findpeaks(const double Yin[7463], double varargin_2, emxArray_real_T
                      *Ypk, emxArray_real_T *Xpk);
static void flipud(double x[7518]);
static void getAllPeaksCodegen(const double y[7463], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double mean(const double x[7500]);
static void orderPeaks(const double Y[2048], const int iPk_data[], int idx_data[],
  int idx_size[1]);
static void power(const double a[7500], double y[7500]);
static void removeSmallPeaks(const double y[7463], const int iFinite_data[],
  const int iFinite_size[1], double minH, int iPk_data[], int iPk_size[1]);
static void repmat(const double a[4096], double b[4096]);
static void rescale_minmax(const double X[2048], double Y[2048]);
static void sortIdx(const double x_data[], const int x_size[1], int idx_data[],
                    int idx_size[1]);
static double sum(const double x[4096]);
static void welch_psd(const double signals[7251], const double window[4096],
                      double CSM[2048], double frequencies[2048]);

// Function Definitions

//
// Arguments    : const double y[2048]
//                const double x[2048]
//                const int iPk_data[]
//                const int iPk_size[1]
//                double YpkOut_data[]
//                int YpkOut_size[2]
//                double XpkOut_data[]
//                int XpkOut_size[2]
// Return Type  : void
//
static void assignOutputs(const double y[2048], const double x[2048], const int
  iPk_data[], const int iPk_size[1], double YpkOut_data[], int YpkOut_size[2],
  double XpkOut_data[], int XpkOut_size[2])
{
  int loop_ub;
  int i6;
  YpkOut_size[0] = 1;
  YpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i6 = 0; i6 < loop_ub; i6++) {
    YpkOut_data[i6] = y[iPk_data[i6] - 1];
  }

  XpkOut_size[0] = 1;
  XpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i6 = 0; i6 < loop_ub; i6++) {
    XpkOut_data[i6] = x[iPk_data[i6] - 1];
  }
}

//
// Arguments    : const double A[7500]
//                const double B[250]
//                double C[7251]
// Return Type  : void
//
static void b_conv(const double A[7500], const double B[250], double C[7251])
{
  int k;
  int b_k;
  memset(&C[0], 0, 7251U * sizeof(double));
  for (k = 0; k < 250; k++) {
    for (b_k = 0; b_k < 7251; b_k++) {
      C[b_k] += B[k] * A[(b_k - k) + 249];
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
  double d2;
  double d3;
  int i;
  double y[7518];
  double b_y[7518];
  double a[3];
  static const double b_a[3] = { -0.95097188792623888, 1.9019437758521933,
    -0.95097188792596821 };

  static const double dv8[4] = { 0.950971887923409, -2.8529156637702271,
    2.8529156637702271, -0.950971887923409 };

  static const double dv9[4] = { 1.0, -2.8994795946118641, 2.8039479773829989,
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
  filter(dv8, dv9, b_y, a, y);
  flipud(y);
  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv8, dv9, b_y, a, y);
  flipud(y);
  memcpy(&y_out[0], &y[9], 7500U * sizeof(double));
}

//
// Arguments    : const double Yin[2048]
//                double Ypk_data[]
//                int Ypk_size[2]
//                double Xpk_data[]
//                int Xpk_size[2]
// Return Type  : void
//
static void b_findpeaks(const double Yin[2048], double Ypk_data[], int Ypk_size
  [2], double Xpk_data[], int Xpk_size[2])
{
  int iFinite_data[2048];
  int iFinite_size[1];
  int iInfinite_data[2048];
  int iInfinite_size[1];
  int iInflect_data[2048];
  int iInflect_size[1];
  int iPk_size[1];
  int loop_ub;
  int i3;
  int iPk_data[4096];
  static int c_data[14926];
  static int ia_data[7463];
  static int ib_data[7463];
  int ib_size[1];
  int c_size[1];
  double dv16[2048];
  int b_c_data[4096];
  b_getAllPeaksCodegen(Yin, iFinite_data, iFinite_size, iInfinite_data,
                       iInfinite_size, iInflect_data, iInflect_size);
  b_removeSmallPeaks(Yin, iFinite_data, iFinite_size, iInflect_data,
                     iInflect_size);
  iPk_size[0] = iInflect_size[0];
  loop_ub = iInflect_size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    iPk_data[i3] = iInflect_data[i3];
  }

  do_vectors(iPk_data, iPk_size, iInfinite_data, iInfinite_size, c_data,
             iFinite_size, ia_data, iInflect_size, ib_data, ib_size);
  d_findPeaksSeparatedByMoreThanM(iFinite_size, iPk_data, iPk_size);
  orderPeaks(Yin, c_data, iPk_data, iPk_size);
  b_keepAtMostNpPeaks(iPk_data, iPk_size);
  for (i3 = 0; i3 < 2048; i3++) {
    dv16[i3] = 1.0 + (double)i3;
  }

  c_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_c_data[i3] = c_data[iPk_data[i3] - 1];
  }

  assignOutputs(Yin, dv16, b_c_data, c_size, Ypk_data, Ypk_size, Xpk_data,
                Xpk_size);
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
// Arguments    : const double y[2048]
//                int iPk_data[]
//                int iPk_size[1]
//                int iInf_data[]
//                int iInf_size[1]
//                int iInflect_data[]
//                int iInflect_size[1]
// Return Type  : void
//
static void b_getAllPeaksCodegen(const double y[2048], int iPk_data[], int
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
  for (k = 0; k < 2048; k++) {
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

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect_data[nInflect] < 2048)))
  {
    nInflect++;
    iInflect_data[nInflect] = 2048;
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
// Arguments    : int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void b_keepAtMostNpPeaks(int idx_data[], int idx_size[1])
{
  int i9;
  int b_idx_data[4096];
  if (idx_size[0] > 2) {
    for (i9 = 0; i9 < 2; i9++) {
      b_idx_data[i9] = idx_data[i9];
    }

    idx_size[0] = 2;
    for (i9 = 0; i9 < 2; i9++) {
      idx_data[i9] = b_idx_data[i9];
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
  int iwork_data[4096];
  for (k = 1; k <= n - 1; k += 2) {
    if ((x_data[k - 1] >= x_data[k]) || rtIsNaN(x_data[k - 1])) {
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
        if ((x_data[idx_data[b_p] - 1] >= x_data[idx_data[q - 1] - 1]) ||
            rtIsNaN(x_data[idx_data[b_p] - 1])) {
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
        idx_data[(j + k) - 1] = iwork_data[k];
      }

      j = qEnd;
    }

    i = i2;
  }
}

//
// Arguments    : const double a[4096]
//                double y[4096]
// Return Type  : void
//
static void b_power(const double a[4096], double y[4096])
{
  int k;
  for (k = 0; k < 4096; k++) {
    y[k] = a[k] * a[k];
  }
}

//
// Arguments    : const double y[2048]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                int iPk_data[]
//                int iPk_size[1]
// Return Type  : void
//
static void b_removeSmallPeaks(const double y[2048], const int iFinite_data[],
  const int iFinite_size[1], int iPk_data[], int iPk_size[1])
{
  int nPk;
  int k;
  double b_y;
  nPk = 0;
  for (k = 0; k + 1 <= iFinite_size[0]; k++) {
    if (y[iFinite_data[k] - 1] > 0.1) {
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
// Arguments    : const double b[7]
//                const double a[7]
//                const double x[7536]
//                const double zi[6]
//                double y[7536]
// Return Type  : void
//
static void c_filter(const double b[7], const double a[7], const double x[7536],
                     const double zi[6], double y[7536])
{
  int k;
  int naxpy;
  int j;
  double as;
  for (k = 0; k < 6; k++) {
    y[k] = zi[k];
  }

  memset(&y[6], 0, 7530U * sizeof(double));
  for (k = 0; k < 7536; k++) {
    naxpy = 7536 - k;
    if (!(naxpy < 7)) {
      naxpy = 7;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 7535 - k;
    if (!(naxpy < 6)) {
      naxpy = 6;
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
static void c_filtfilt(const double x_in[7500], double y_out[7500])
{
  double d4;
  double d5;
  int i0;
  double y[7506];
  double b_y[7506];
  double dv10[2];
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
    dv10[i0] = 7.8125 + -16.5625 * (double)i0;
  }

  memcpy(&b_y[0], &y[0], 7506U * sizeof(double));
  b_filter(dv10, b_y, -8.75 * y[0], y);
  b_flipud(y);
  for (i0 = 0; i0 < 2; i0++) {
    dv10[i0] = 7.8125 + -16.5625 * (double)i0;
  }

  memcpy(&b_y[0], &y[0], 7506U * sizeof(double));
  b_filter(dv10, b_y, -8.75 * y[0], y);
  b_flipud(y);
  memcpy(&y_out[0], &y[3], 7500U * sizeof(double));
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
  int y_data[14926];
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
// Arguments    : double x[7536]
// Return Type  : void
//
static void c_flipud(double x[7536])
{
  int i;
  double xtmp;
  for (i = 0; i < 3768; i++) {
    xtmp = x[i];
    x[i] = x[7535 - i];
    x[7535 - i] = xtmp;
  }
}

//
// Arguments    : const double x[4096]
// Return Type  : double
//
static double c_mean(const double x[4096])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 4095; k++) {
    y += x[k + 1];
  }

  y /= 4096.0;
  return y;
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
// Arguments    : const double x_in[7500]
//                double y_out[7500]
// Return Type  : void
//
static void d_filtfilt(const double x_in[7500], double y_out[7500])
{
  double d6;
  double d7;
  int i;
  double y[7536];
  double b_y[7536];
  double a[6];
  static const double b_a[6] = { -0.00080987995584081535,
    -0.00080997175999258182, 0.0016199317339117138, 0.0016196642833357288,
    -0.000809836948677889, -0.00080990735273475081 };

  static const double dv11[7] = { 0.00080989634324999489, 0.0, -0.00242968902975,
    0.0, 0.00242968902975, 0.0, -0.00080989634324999489 };

  static const double dv12[7] = { 1.0, -5.6021150604502674, 13.08713000005193,
    -16.320491729646289, 11.459879613995582, -4.2962286527580584,
    0.671825828913905 };

  d6 = 2.0 * x_in[0];
  d7 = 2.0 * x_in[7499];
  for (i = 0; i < 18; i++) {
    y[i] = d6 - x_in[18 - i];
  }

  memcpy(&y[18], &x_in[0], 7500U * sizeof(double));
  for (i = 0; i < 18; i++) {
    y[i + 7518] = d7 - x_in[7498 - i];
  }

  for (i = 0; i < 6; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7536U * sizeof(double));
  c_filter(dv11, dv12, b_y, a, y);
  c_flipud(y);
  for (i = 0; i < 6; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7536U * sizeof(double));
  c_filter(dv11, dv12, b_y, a, y);
  c_flipud(y);
  memcpy(&y_out[0], &y[18], 7500U * sizeof(double));
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
  int y_data[14926];
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
  int b_ia_data[7463];
  short b_ib_data[7463];
  static int b_c_data[14926];
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
// Input: doubles (2000, 1)
//  Output: Y, single (2000, 1)
//  Filter is order 3, HPF @ 1 Hz, butterworth. 250 Hz Fs.
// Arguments    : const double X[7500]
//                float Y[7500]
// Return Type  : void
//
static void ecg_filt_rescale(const double X[7500], float Y[7500])
{
  static double b_X[7500];
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg1;
  double b_mtmp;
  filtfilt(X, b_X);
  ixstart = 1;
  mtmp = b_X[0];
  if (rtIsNaN(b_X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7501)) {
      ixstart = ix;
      if (!rtIsNaN(b_X[ix - 1])) {
        mtmp = b_X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 7500) {
    while (ixstart + 1 < 7501) {
      if (b_X[ixstart] < mtmp) {
        mtmp = b_X[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = b_X[0];
  if (rtIsNaN(b_X[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7501)) {
      ixstart = ix;
      if (!rtIsNaN(b_X[ix - 1])) {
        b_mtmp = b_X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 7500) {
    while (ixstart + 1 < 7501) {
      if (b_X[ixstart] > b_mtmp) {
        b_mtmp = b_X[ixstart];
      }

      ixstart++;
    }
  }

  b_mtmp -= mtmp;
  for (ixstart = 0; ixstart < 7500; ixstart++) {
    Y[ixstart] = (float)((b_X[ixstart] - mtmp) / b_mtmp);
  }
}

//
// Arguments    : const double x[4096]
//                creal_T y[4096]
// Return Type  : void
//
static void fft(const double x[4096], creal_T y[4096])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int iheight;
  int istart;
  int j;
  double twid_re;
  static const double dv14[2049] = { 1.0, 0.99999882345170188,
    0.99999529380957619, 0.9999894110819284, 0.99998117528260111,
    0.99997058643097414, 0.9999576445519639, 0.99994234967602391,
    0.9999247018391445, 0.9999047010828529, 0.99988234745421256,
    0.99985764100582386, 0.9998305817958234, 0.99980116988788426,
    0.99976940535121528, 0.99973528826056168, 0.99969881869620425,
    0.99965999674395922, 0.99961882249517864, 0.99957529604674922,
    0.99952941750109314, 0.999481186966167, 0.99943060455546173,
    0.99937767038800285, 0.99932238458834954, 0.99926474728659442,
    0.99920475861836389, 0.99914241872481691, 0.99907772775264536,
    0.99901068585407338, 0.99894129318685687, 0.99886954991428356,
    0.99879545620517241, 0.99871901223387294, 0.99864021818026527,
    0.99855907422975931, 0.99847558057329477, 0.99838973740734016,
    0.99830154493389289, 0.99821100336047819, 0.99811811290014918,
    0.99802287377148624, 0.997925286198596, 0.99782535041111164,
    0.99772306664419164, 0.99761843513851955, 0.99751145614030345,
    0.9974021299012753, 0.99729045667869021, 0.99717643673532619,
    0.997060070339483, 0.99694135776498216, 0.99682029929116567,
    0.99669689520289606, 0.99657114579055484, 0.99644305135004263,
    0.996312612182778, 0.996179828595697, 0.996044700901252, 0.99590722941741172,
    0.99576741446765982, 0.99562525638099431, 0.99548075549192694,
    0.99533391214048228, 0.99518472667219693, 0.99503319943811863,
    0.99487933079480562, 0.9947231211043257, 0.99456457073425542,
    0.9944036800576791, 0.9942404494531879, 0.99407487930487937,
    0.99390697000235606, 0.9937367219407246, 0.9935641355205953,
    0.99338921114808065, 0.9932119492347945, 0.99303235019785141,
    0.9928504144598651, 0.992666142448948, 0.99247953459871, 0.99229059134825737,
    0.9920993131421918, 0.99190570043060933, 0.99170975366909953,
    0.9915114733187439, 0.99131085984611544, 0.99110791372327689,
    0.99090263542778, 0.99069502544266463, 0.99048508425645709,
    0.99027281236316911, 0.99005821026229712, 0.98984127845882053,
    0.98962201746320089, 0.98940042779138038, 0.989176509964781,
    0.988950264510303, 0.98872169196032378, 0.98849079285269659,
    0.98825756773074946, 0.98802201714328353, 0.98778414164457218,
    0.98754394179435923, 0.98730141815785843, 0.987056571305751,
    0.98680940181418553, 0.98655991026477541, 0.98630809724459867,
    0.98605396334619544, 0.98579750916756748, 0.98553873531217606,
    0.98527764238894122, 0.98501423101223984, 0.98474850180190421,
    0.98448045538322093, 0.984210092386929, 0.98393741344921892,
    0.98366241921173025, 0.98338511032155118, 0.98310548743121629,
    0.98282355119870524, 0.98253930228744124, 0.98225274136628937,
    0.98196386910955524, 0.98167268619698311, 0.98137919331375456,
    0.98108339115048671, 0.98078528040323043, 0.98048486177346938,
    0.98018213596811743, 0.97987710369951764, 0.97956976568544052,
    0.979260122649082, 0.9789481753190622, 0.97863392442942321,
    0.97831737071962765, 0.97799851493455714, 0.97767735782450993,
    0.97735390014520007, 0.97702814265775439, 0.97670008612871184,
    0.97636973133002114, 0.976037079039039, 0.97570213003852857,
    0.975364885116657, 0.97502534506699412, 0.97468351068851067,
    0.97433938278557586, 0.97399296216795583, 0.973644249650812,
    0.97329324605469825, 0.97293995220556018, 0.97258436893473221,
    0.97222649707893627, 0.9718663374802794, 0.97150389098625178,
    0.97113915844972509, 0.97077214072895035, 0.9704028386875555,
    0.970031253194544, 0.96965738512429245, 0.96928123535654853,
    0.96890280477642887, 0.96852209427441727, 0.96813910474636244,
    0.96775383709347551, 0.96736629222232851, 0.96697647104485207,
    0.96658437447833312, 0.9661900034454125, 0.96579335887408368,
    0.9653944416976894, 0.96499325285492032, 0.96458979328981276,
    0.96418406395174583, 0.96377606579543984, 0.963365799780954,
    0.96295326687368388, 0.96253846804435916, 0.96212140426904158,
    0.96170207652912254, 0.96128048581132064, 0.96085663310767966,
    0.96043051941556579, 0.960002145737666, 0.95957151308198452,
    0.95913862246184189, 0.9587034748958716, 0.95826607140801767,
    0.95782641302753291, 0.95738450078897586, 0.95694033573220882,
    0.9564939189023951, 0.95604525134999641, 0.95559433413077111,
    0.95514116830577078, 0.95468575494133834, 0.95422809510910567,
    0.95376818988599033, 0.95330604035419386, 0.95284164760119872,
    0.95237501271976588, 0.95190613680793235, 0.95143502096900834,
    0.95096166631157508, 0.9504860739494817, 0.950008245001843,
    0.94952818059303667, 0.94904588185270056, 0.94856134991573027,
    0.94807458592227623, 0.94758559101774109, 0.94709436635277722,
    0.94660091308328353, 0.94610523237040345, 0.94560732538052128,
    0.94510719328526061, 0.94460483726148026, 0.94410025849127266,
    0.94359345816196039, 0.94308443746609349, 0.94257319760144687,
    0.94205973977101731, 0.94154406518302081, 0.94102617505088926,
    0.9405060705932683, 0.93998375303401394, 0.93945922360218992,
    0.9389324835320646, 0.93840353406310806, 0.93787237643998989,
    0.937339011912575, 0.93680344173592156, 0.93626566717027826,
    0.93572568948108037, 0.93518350993894761, 0.93463912981968078,
    0.93409255040425887, 0.93354377297883617, 0.932992798834739,
    0.93243962926846236, 0.93188426558166815, 0.93132670908118043,
    0.93076696107898371, 0.93020502289221907, 0.92964089584318121,
    0.92907458125931586, 0.92850608047321559, 0.92793539482261789,
    0.92736252565040111, 0.92678747430458175, 0.92621024213831138,
    0.92563083050987272, 0.92504924078267758, 0.9244654743252626,
    0.92387953251128674, 0.92329141671952764, 0.92270112833387863,
    0.92210866874334518, 0.9215140393420419, 0.92091724152918952,
    0.92031827670911059, 0.91971714629122736, 0.91911385169005777,
    0.91850839432521225, 0.9179007756213905, 0.91729099700837791,
    0.9166790599210427, 0.91606496579933172, 0.91544871608826783,
    0.9148303122379462, 0.91420975570353069, 0.91358704794525081,
    0.91296219042839821, 0.91233518462332275, 0.91170603200542988,
    0.91107473405517636, 0.91044129225806725, 0.90980570810465222,
    0.90916798309052238, 0.90852811871630612, 0.90788611648766626,
    0.90724197791529582, 0.90659570451491533, 0.90594729780726846,
    0.90529675931811882, 0.90464409057824624, 0.90398929312344334,
    0.90333236849451182, 0.90267331823725883, 0.90201214390249318,
    0.901348847046022, 0.900683429228647, 0.90001589201616017,
    0.89934623697934157, 0.89867446569395382, 0.89800057974073988,
    0.89732458070541832, 0.89664647017868015, 0.89596624975618522,
    0.89528392103855758, 0.8945994856313827, 0.89391294514520325,
    0.89322430119551532, 0.89253355540276458, 0.89184070939234272,
    0.89114576479458318, 0.89044872324475788, 0.88974958638307278,
    0.88904835585466457, 0.88834503330959635, 0.88763962040285393,
    0.88693211879434219, 0.88622253014888064, 0.8855108561362,
    0.88479709843093779, 0.884081258712635, 0.88336333866573158,
    0.88264333997956279, 0.881921264348355, 0.88119711347122209,
    0.88047088905216075, 0.87974259280004741, 0.87901222642863353,
    0.87827979165654158, 0.87754529020726135, 0.87680872380914565,
    0.8760700941954066, 0.87532940310411089, 0.87458665227817611,
    0.87384184346536686, 0.87309497841829009, 0.87234605889439154,
    0.87159508665595109, 0.870842063470079, 0.87008699110871146,
    0.86932987134860684, 0.8685707059713409, 0.86780949676330332,
    0.86704624551569265, 0.866280954024513, 0.86551362409056909,
    0.86474425751946238, 0.8639728561215867, 0.86319942171212416,
    0.8624239561110405, 0.8616464611430813, 0.86086693863776731,
    0.86008539042939014, 0.85930181835700847, 0.85851622426444274,
    0.85772861000027212, 0.85693897741782876, 0.85614732837519447,
    0.855353664735196, 0.85455798836540053, 0.85376030113811141,
    0.85296060493036363, 0.85215890162391983, 0.8513551931052652,
    0.85054948126560348, 0.84974176800085255, 0.84893205521163961,
    0.84812034480329723, 0.84730663868585832, 0.84649093877405213,
    0.84567324698729907, 0.84485356524970712, 0.84403189549006641,
    0.84320823964184544, 0.84238259964318585, 0.84155497743689844,
    0.84072537497045807, 0.83989379419599952, 0.83906023707031274,
    0.83822470555483808, 0.83738720161566194, 0.836547727223512,
    0.8357062843537526, 0.83486287498638, 0.83401750110601813,
    0.83317016470191319, 0.83232086776792968, 0.83146961230254524,
    0.83061640030884631, 0.829761233794523, 0.82890411477186487,
    0.8280450452577558, 0.82718402727366913, 0.82632106284566353,
    0.82545615400437755, 0.82458930278502529, 0.82372051122739143,
    0.82284978137582643, 0.82197711527924155, 0.82110251499110465,
    0.82022598256943469, 0.819347520076797, 0.81846712958029866,
    0.81758481315158371, 0.81670057286682785, 0.81581441080673378,
    0.81492632905652662, 0.81403632970594841, 0.81314441484925359,
    0.81225058658520388, 0.81135484701706373, 0.81045719825259477,
    0.80955764240405126, 0.808656181588175, 0.80775281792619036,
    0.80684755354379933, 0.80594039057117628, 0.80503133114296366,
    0.8041203773982657, 0.80320753148064494, 0.80229279553811572,
    0.80137617172314024, 0.80045766219262282, 0.799537269107905,
    0.79861499463476093, 0.79769084094339116, 0.79676481020841883,
    0.79583690460888357, 0.794907126328237, 0.79397547755433717,
    0.79304196047944364, 0.79210657730021239, 0.7911693302176902,
    0.79023022143731, 0.78928925316888565, 0.78834642762660634,
    0.78740174702903143, 0.78645521359908577, 0.78550682956405393,
    0.78455659715557524, 0.78360451860963831, 0.78265059616657573,
    0.78169483207105939, 0.78073722857209449, 0.77977778792301455,
    0.778816512381476, 0.77785340420945315, 0.77688846567323244,
    0.77592169904340769, 0.77495310659487393, 0.7739826906068229,
    0.773010453362737, 0.77203639715038452, 0.77106052426181382,
    0.7700828369933479, 0.7691033376455797, 0.76812202852336542,
    0.7671389119358204, 0.76615399019631292, 0.765167265622459,
    0.76417874053611679, 0.76318841726338127, 0.7621962981345789,
    0.76120238548426178, 0.76020668165120242, 0.759209188978388,
    0.75820990981301528, 0.75720884650648457, 0.75620600141439454,
    0.75520137689653655, 0.75419497531688917, 0.75318679904361252,
    0.7521768504490427, 0.75116513190968637, 0.75015164580621507,
    0.74913639452345937, 0.7481193804504036, 0.74710060598018013,
    0.74608007351006378, 0.745057785441466, 0.74403374417992929,
    0.74300795213512172, 0.74198041172083107, 0.74095112535495922,
    0.7399200954595162, 0.73888732446061511, 0.737852814788466,
    0.73681656887736979, 0.73577858916571359, 0.7347388780959635,
    0.73369743811466037, 0.73265427167241282, 0.73160938122389263,
    0.73056276922782759, 0.729514438146997, 0.7284643904482252,
    0.72741262860237577, 0.726359155084346, 0.72530397237306077,
    0.724247082951467, 0.72318848930652746, 0.72212819392921535,
    0.72106619931450811, 0.72000250796138165, 0.71893712237280449,
    0.71787004505573171, 0.71680127852109954, 0.71573082528381859,
    0.71465868786276909, 0.71358486878079352, 0.71250937056469243,
    0.71143219574521643, 0.71035334685706242, 0.70927282643886569,
    0.7081906370331954, 0.70710678118654757, 0.70602126144933974,
    0.70493408037590488, 0.70384524052448494, 0.7027547444572253,
    0.70166259474016845, 0.70056879394324834, 0.69947334464028377,
    0.69837624940897292, 0.69727751083088652, 0.696177131491463,
    0.69507511398000088, 0.69397146088965389, 0.69286617481742463,
    0.69175925836415775, 0.6906507141345346, 0.68954054473706683,
    0.68842875278409044, 0.687315340891759, 0.68620031168003859,
    0.68508366777270036, 0.6839654117973154, 0.68284554638524808,
    0.68172407417164971, 0.680600997795453, 0.679476319899365,
    0.67835004312986147, 0.67722217013718033, 0.67609270357531592,
    0.674961646102012, 0.673829000378756, 0.67269476907077286,
    0.67155895484701833, 0.67042156038017309, 0.669282588346636,
    0.66814204142651845, 0.66699992230363747, 0.66585623366550972,
    0.66471097820334479, 0.66356415861203977, 0.66241577759017178,
    0.66126583783999227, 0.66011434206742048, 0.65896129298203732,
    0.65780669329707864, 0.65665054572942894, 0.65549285299961535,
    0.65433361783180044, 0.65317284295377676, 0.6520105310969595,
    0.650846684996381, 0.64968130739068319, 0.64851440102211244,
    0.64734596863651206, 0.64617601298331628, 0.64500453681554393,
    0.64383154288979139, 0.64265703396622686, 0.641481012808583,
    0.64030348218415167, 0.63912444486377573, 0.637943903621844,
    0.6367618612362842, 0.63557832048855611, 0.63439328416364549,
    0.63320675505005719, 0.63201873593980906, 0.63082922962842447,
    0.629638238914927, 0.6284457666018326, 0.62725181549514408,
    0.62605638840434352, 0.62485948814238634, 0.62366111752569453,
    0.62246127937415, 0.62125997651108755, 0.6200572117632891,
    0.61885298796097632, 0.61764730793780387, 0.61644017453085365,
    0.61523159058062682, 0.61402155893103849, 0.61281008242940971,
    0.61159716392646191, 0.61038280627630948, 0.60916701233645321,
    0.60794978496777363, 0.60673112703452448, 0.60551104140432555,
    0.604289530948156, 0.60306659854034816, 0.60184224705858, 0.600616479383869,
    0.59938929840056454, 0.59816070699634238, 0.59693070806219639,
    0.59569930449243336, 0.59446649918466443, 0.5932322950397998,
    0.591996694962041, 0.59075970185887416, 0.58952131864106394,
    0.58828154822264522, 0.587040393520918, 0.58579785745643886,
    0.58455394295301533, 0.58330865293769829, 0.58206199034077544,
    0.58081395809576453, 0.57956455913940563, 0.57831379641165559,
    0.57706167285567944, 0.57580819141784534, 0.57455335504771576,
    0.5732971666980422, 0.572039629324757, 0.57078074588696726,
    0.56952051934694714, 0.56825895267013149, 0.56699604882510868,
    0.56573181078361312, 0.5644662415205195, 0.56319934401383409,
    0.56193112124468936, 0.560661576197336, 0.55939071185913614,
    0.5581185312205561, 0.5568450372751601, 0.55557023301960218,
    0.55429412145362, 0.55301670558002747, 0.55173798840470734,
    0.55045797293660481, 0.54917666218771966, 0.54789405917310019,
    0.54661016691083486, 0.54532498842204646, 0.54403852673088382,
    0.54275078486451589, 0.54146176585312344, 0.54017147272989285,
    0.53887990853100842, 0.53758707629564539, 0.53629297906596318,
    0.53499761988709715, 0.533701001807153, 0.5324031278771979,
    0.531104001151255, 0.52980362468629461, 0.52850200154222848,
    0.52719913478190128, 0.52589502747108463, 0.524589682678469,
    0.52328310347565643, 0.52197529293715439, 0.52066625414036716,
    0.51935599016558964, 0.51804450409599934, 0.51673179901764987,
    0.51541787801946293, 0.51410274419322166, 0.512786400633563,
    0.5114688504379703, 0.51015009670676681, 0.508830142543107,
    0.50750899105297087, 0.50618664534515523, 0.50486310853126759,
    0.50353838372571758, 0.50221247404571079, 0.50088538261124071,
    0.49955711254508184, 0.49822766697278181, 0.49689704902265447,
    0.49556526182577254, 0.49423230851595967, 0.49289819222978404,
    0.4915629161065499, 0.49022648328829116, 0.48888889691976317,
    0.487550160148436, 0.48621027612448642, 0.48486924800079106,
    0.48352707893291874, 0.48218377207912272, 0.48083933060033396,
    0.47949375766015295, 0.478147056424843, 0.47679923006332209,
    0.47545028174715587, 0.47410021465054997, 0.47274903195034279,
    0.47139673682599764, 0.47004333245959562, 0.46868882203582796,
    0.46733320874198842, 0.46597649576796618, 0.46461868630623782,
    0.46325978355186015, 0.46189979070246273, 0.46053871095824,
    0.45917654752194409, 0.45781330359887717, 0.45644898239688392,
    0.45508358712634384, 0.45371712100016387, 0.45234958723377089,
    0.45098098904510386, 0.44961132965460654, 0.44824061228521989,
    0.44686884016237416, 0.44549601651398174, 0.4441221445704292,
    0.44274722756457, 0.44137126873171667, 0.43999427130963326,
    0.43861623853852766, 0.43723717366104409, 0.43585707992225547,
    0.43447596056965565, 0.43309381885315196, 0.43171065802505726,
    0.43032648134008261, 0.42894129205532949, 0.42755509343028208,
    0.42616788872679962, 0.42477968120910881, 0.42339047414379605,
    0.42200027079979968, 0.42060907444840251, 0.41921688836322391,
    0.41782371582021227, 0.41642956009763715, 0.41503442447608163,
    0.4136383122384345, 0.41224122666988289, 0.41084317105790391,
    0.40944414869225759, 0.40804416286497869, 0.40664321687036903,
    0.40524131400498986, 0.40383845756765407, 0.40243465085941843,
    0.40102989718357562, 0.39962419984564679, 0.39821756215337356,
    0.39680998741671031, 0.39540147894781635, 0.3939920400610481,
    0.39258167407295147, 0.39117038430225387, 0.38975817406985641,
    0.38834504669882625, 0.38693100551438858, 0.38551605384391885,
    0.38410019501693504, 0.38268343236508978, 0.38126576922216238,
    0.37984720892405116, 0.37842775480876556, 0.37700741021641826,
    0.37558617848921722, 0.37416406297145793, 0.37274106700951576,
    0.37131719395183749, 0.3698924471489341, 0.36846682995337232,
    0.36704034571976718, 0.36561299780477385, 0.36418478956707989,
    0.36275572436739723, 0.36132580556845428, 0.35989503653498811,
    0.35846342063373654, 0.35703096123343, 0.35559766170478385,
    0.35416352542049034, 0.35272855575521073, 0.35129275608556709,
    0.34985612979013492, 0.34841868024943456, 0.34698041084592368,
    0.34554132496398909, 0.34410142598993881, 0.34266071731199438,
    0.34121920232028236, 0.33977688440682685, 0.33833376696554113,
    0.33688985339222005, 0.3354451470845316, 0.33399965144200938,
    0.33255336986604422, 0.33110630575987643, 0.32965846252858749,
    0.3282098435790925, 0.32676045232013173, 0.32531029216226293,
    0.32385936651785285, 0.32240767880106985, 0.32095523242787521,
    0.31950203081601569, 0.31804807738501495, 0.31659337555616585,
    0.31513792875252244, 0.31368174039889152, 0.31222481392182488,
    0.31076715274961147, 0.30930876031226873, 0.30784964004153487,
    0.30638979537086092, 0.30492922973540237, 0.30346794657201132,
    0.30200594931922808, 0.30054324141727345, 0.29907982630804048,
    0.2976157074350862, 0.29615088824362379, 0.29468537218051433,
    0.29321916269425863, 0.29175226323498926, 0.29028467725446233,
    0.28881640820604948, 0.28734745954472951, 0.28587783472708062,
    0.28440753721127188, 0.28293657045705539, 0.28146493792575794,
    0.27999264308027322, 0.27851968938505306, 0.2770460803060999,
    0.27557181931095814, 0.27409690986870638, 0.272621355449949,
    0.271145159526808, 0.26966832557291509, 0.26819085706340318,
    0.26671275747489837, 0.26523403028551179, 0.26375467897483135,
    0.26227470702391359, 0.26079411791527551, 0.25931291513288623,
    0.257831102162159, 0.25634868248994291, 0.25486565960451457,
    0.25338203699557016, 0.25189781815421697, 0.25041300657296522,
    0.24892760574572015, 0.24744161916777327, 0.24595505033579459,
    0.24446790274782415, 0.24298017990326387, 0.24149188530286933,
    0.2400030224487415, 0.23851359484431842, 0.2370236059943672,
    0.23553305940497549, 0.23404195858354343, 0.23255030703877524,
    0.23105810828067111, 0.22956536582051887, 0.22807208317088573,
    0.22657826384561, 0.22508391135979283, 0.22358902922979, 0.22209362097320351,
    0.22059769010887351, 0.2191012401568698, 0.21760427463848364,
    0.21610679707621952, 0.21460881099378676, 0.21311031991609136,
    0.21161132736922755, 0.21011183688046961, 0.20861185197826349,
    0.20711137619221856, 0.20561041305309924, 0.20410896609281687,
    0.20260703884442113, 0.2011046348420919, 0.19960175762113097,
    0.19809841071795356, 0.19659459767008022, 0.19509032201612825,
    0.19358558729580361, 0.19208039704989244, 0.19057475482025274,
    0.18906866414980619, 0.1875621285825296, 0.18605515166344663,
    0.18454773693861962, 0.18303988795514095, 0.18153160826112497,
    0.18002290140569951, 0.17851377093899751, 0.17700422041214875,
    0.17549425337727143, 0.17398387338746382, 0.17247308399679595,
    0.17096188876030122, 0.16945029123396796, 0.16793829497473117,
    0.1664259035404641, 0.16491312048996992, 0.16339994938297323,
    0.16188639378011183, 0.16037245724292828, 0.15885814333386145,
    0.15734345561623825, 0.15582839765426523, 0.1543129730130201,
    0.15279718525844344, 0.15128103795733022, 0.14976453467732151,
    0.14824767898689603, 0.14673047445536175, 0.14521292465284746,
    0.14369503315029447, 0.14217680351944803, 0.14065823933284921,
    0.1391393441638262, 0.13762012158648604, 0.1361005751757062,
    0.13458070850712617, 0.13306052515713906, 0.13154002870288312,
    0.13001922272223335, 0.12849811079379317, 0.12697669649688587,
    0.12545498341154623, 0.12393297511851216, 0.1224106751992162,
    0.12088808723577708, 0.11936521481099135, 0.11784206150832498,
    0.11631863091190475, 0.11479492660651008, 0.11327095217756435,
    0.11174671121112659, 0.11022220729388306, 0.10869744401313872,
    0.10717242495680884, 0.10564715371341062, 0.10412163387205459,
    0.10259586902243628, 0.10106986275482782, 0.099543618660069319,
    0.0980171403295606, 0.096490431355252593, 0.094963495329638992,
    0.093436335845747787, 0.091908956497132724, 0.090381360877864983,
    0.0888535525825246, 0.087325535206192059, 0.0857973123444399,
    0.084268887593324071, 0.082740264549375692, 0.081211446809592441,
    0.079682437971430126, 0.078153241632794232, 0.076623861392031492,
    0.0750943008479213, 0.073564563599667426, 0.072034653246889332,
    0.070504573389613856, 0.068974327628266746, 0.067443919563664051,
    0.0659133527970038, 0.064382630929857465, 0.0628517575641614,
    0.061320736302208578, 0.059789570746639868, 0.058258264500435752,
    0.056726821166907748, 0.055195244349689941, 0.05366353765273052,
    0.052131704680283324, 0.050599749036899282, 0.049067674327418015,
    0.0475354841569593, 0.046003182130914623, 0.044470771854938668,
    0.04293825693494082, 0.041405640977076739, 0.039872927587739811,
    0.038340120373552694, 0.036807222941358832, 0.035274238898213947,
    0.03374117185137758, 0.032208025408304586, 0.030674803176636626,
    0.029141508764193722, 0.02760814577896574, 0.0260747178291039,
    0.024541228522912288, 0.023007681468839369, 0.021474080275469508,
    0.019940428551514441, 0.01840672990580482, 0.01687298794728171,
    0.0153392062849881, 0.013805388528060391, 0.012271538285719925,
    0.010737659167264491, 0.00920375478205982, 0.007669828739531097,
    0.0061358846491544753, 0.0046019261204485705, 0.0030679567629659761,
    0.0015339801862847655, 0.0, -0.0015339801862847655, -0.0030679567629659761,
    -0.0046019261204485705, -0.0061358846491544753, -0.007669828739531097,
    -0.00920375478205982, -0.010737659167264491, -0.012271538285719925,
    -0.013805388528060391, -0.0153392062849881, -0.01687298794728171,
    -0.01840672990580482, -0.019940428551514441, -0.021474080275469508,
    -0.023007681468839369, -0.024541228522912288, -0.0260747178291039,
    -0.02760814577896574, -0.029141508764193722, -0.030674803176636626,
    -0.032208025408304586, -0.03374117185137758, -0.035274238898213947,
    -0.036807222941358832, -0.038340120373552694, -0.039872927587739811,
    -0.041405640977076739, -0.04293825693494082, -0.044470771854938668,
    -0.046003182130914623, -0.0475354841569593, -0.049067674327418015,
    -0.050599749036899282, -0.052131704680283324, -0.05366353765273052,
    -0.055195244349689941, -0.056726821166907748, -0.058258264500435752,
    -0.059789570746639868, -0.061320736302208578, -0.0628517575641614,
    -0.064382630929857465, -0.0659133527970038, -0.067443919563664051,
    -0.068974327628266746, -0.070504573389613856, -0.072034653246889332,
    -0.073564563599667426, -0.0750943008479213, -0.076623861392031492,
    -0.078153241632794232, -0.079682437971430126, -0.081211446809592441,
    -0.082740264549375692, -0.084268887593324071, -0.0857973123444399,
    -0.087325535206192059, -0.0888535525825246, -0.090381360877864983,
    -0.091908956497132724, -0.093436335845747787, -0.094963495329638992,
    -0.096490431355252593, -0.0980171403295606, -0.099543618660069319,
    -0.10106986275482782, -0.10259586902243628, -0.10412163387205459,
    -0.10564715371341062, -0.10717242495680884, -0.10869744401313872,
    -0.11022220729388306, -0.11174671121112659, -0.11327095217756435,
    -0.11479492660651008, -0.11631863091190475, -0.11784206150832498,
    -0.11936521481099135, -0.12088808723577708, -0.1224106751992162,
    -0.12393297511851216, -0.12545498341154623, -0.12697669649688587,
    -0.12849811079379317, -0.13001922272223335, -0.13154002870288312,
    -0.13306052515713906, -0.13458070850712617, -0.1361005751757062,
    -0.13762012158648604, -0.1391393441638262, -0.14065823933284921,
    -0.14217680351944803, -0.14369503315029447, -0.14521292465284746,
    -0.14673047445536175, -0.14824767898689603, -0.14976453467732151,
    -0.15128103795733022, -0.15279718525844344, -0.1543129730130201,
    -0.15582839765426523, -0.15734345561623825, -0.15885814333386145,
    -0.16037245724292828, -0.16188639378011183, -0.16339994938297323,
    -0.16491312048996992, -0.1664259035404641, -0.16793829497473117,
    -0.16945029123396796, -0.17096188876030122, -0.17247308399679595,
    -0.17398387338746382, -0.17549425337727143, -0.17700422041214875,
    -0.17851377093899751, -0.18002290140569951, -0.18153160826112497,
    -0.18303988795514095, -0.18454773693861962, -0.18605515166344663,
    -0.1875621285825296, -0.18906866414980619, -0.19057475482025274,
    -0.19208039704989244, -0.19358558729580361, -0.19509032201612825,
    -0.19659459767008022, -0.19809841071795356, -0.19960175762113097,
    -0.2011046348420919, -0.20260703884442113, -0.20410896609281687,
    -0.20561041305309924, -0.20711137619221856, -0.20861185197826349,
    -0.21011183688046961, -0.21161132736922755, -0.21311031991609136,
    -0.21460881099378676, -0.21610679707621952, -0.21760427463848364,
    -0.2191012401568698, -0.22059769010887351, -0.22209362097320351,
    -0.22358902922979, -0.22508391135979283, -0.22657826384561,
    -0.22807208317088573, -0.22956536582051887, -0.23105810828067111,
    -0.23255030703877524, -0.23404195858354343, -0.23553305940497549,
    -0.2370236059943672, -0.23851359484431842, -0.2400030224487415,
    -0.24149188530286933, -0.24298017990326387, -0.24446790274782415,
    -0.24595505033579459, -0.24744161916777327, -0.24892760574572015,
    -0.25041300657296522, -0.25189781815421697, -0.25338203699557016,
    -0.25486565960451457, -0.25634868248994291, -0.257831102162159,
    -0.25931291513288623, -0.26079411791527551, -0.26227470702391359,
    -0.26375467897483135, -0.26523403028551179, -0.26671275747489837,
    -0.26819085706340318, -0.26966832557291509, -0.271145159526808,
    -0.272621355449949, -0.27409690986870638, -0.27557181931095814,
    -0.2770460803060999, -0.27851968938505306, -0.27999264308027322,
    -0.28146493792575794, -0.28293657045705539, -0.28440753721127188,
    -0.28587783472708062, -0.28734745954472951, -0.28881640820604948,
    -0.29028467725446233, -0.29175226323498926, -0.29321916269425863,
    -0.29468537218051433, -0.29615088824362379, -0.2976157074350862,
    -0.29907982630804048, -0.30054324141727345, -0.30200594931922808,
    -0.30346794657201132, -0.30492922973540237, -0.30638979537086092,
    -0.30784964004153487, -0.30930876031226873, -0.31076715274961147,
    -0.31222481392182488, -0.31368174039889152, -0.31513792875252244,
    -0.31659337555616585, -0.31804807738501495, -0.31950203081601569,
    -0.32095523242787521, -0.32240767880106985, -0.32385936651785285,
    -0.32531029216226293, -0.32676045232013173, -0.3282098435790925,
    -0.32965846252858749, -0.33110630575987643, -0.33255336986604422,
    -0.33399965144200938, -0.3354451470845316, -0.33688985339222005,
    -0.33833376696554113, -0.33977688440682685, -0.34121920232028236,
    -0.34266071731199438, -0.34410142598993881, -0.34554132496398909,
    -0.34698041084592368, -0.34841868024943456, -0.34985612979013492,
    -0.35129275608556709, -0.35272855575521073, -0.35416352542049034,
    -0.35559766170478385, -0.35703096123343, -0.35846342063373654,
    -0.35989503653498811, -0.36132580556845428, -0.36275572436739723,
    -0.36418478956707989, -0.36561299780477385, -0.36704034571976718,
    -0.36846682995337232, -0.3698924471489341, -0.37131719395183749,
    -0.37274106700951576, -0.37416406297145793, -0.37558617848921722,
    -0.37700741021641826, -0.37842775480876556, -0.37984720892405116,
    -0.38126576922216238, -0.38268343236508978, -0.38410019501693504,
    -0.38551605384391885, -0.38693100551438858, -0.38834504669882625,
    -0.38975817406985641, -0.39117038430225387, -0.39258167407295147,
    -0.3939920400610481, -0.39540147894781635, -0.39680998741671031,
    -0.39821756215337356, -0.39962419984564679, -0.40102989718357562,
    -0.40243465085941843, -0.40383845756765407, -0.40524131400498986,
    -0.40664321687036903, -0.40804416286497869, -0.40944414869225759,
    -0.41084317105790391, -0.41224122666988289, -0.4136383122384345,
    -0.41503442447608163, -0.41642956009763715, -0.41782371582021227,
    -0.41921688836322391, -0.42060907444840251, -0.42200027079979968,
    -0.42339047414379605, -0.42477968120910881, -0.42616788872679962,
    -0.42755509343028208, -0.42894129205532949, -0.43032648134008261,
    -0.43171065802505726, -0.43309381885315196, -0.43447596056965565,
    -0.43585707992225547, -0.43723717366104409, -0.43861623853852766,
    -0.43999427130963326, -0.44137126873171667, -0.44274722756457,
    -0.4441221445704292, -0.44549601651398174, -0.44686884016237416,
    -0.44824061228521989, -0.44961132965460654, -0.45098098904510386,
    -0.45234958723377089, -0.45371712100016387, -0.45508358712634384,
    -0.45644898239688392, -0.45781330359887717, -0.45917654752194409,
    -0.46053871095824, -0.46189979070246273, -0.46325978355186015,
    -0.46461868630623782, -0.46597649576796618, -0.46733320874198842,
    -0.46868882203582796, -0.47004333245959562, -0.47139673682599764,
    -0.47274903195034279, -0.47410021465054997, -0.47545028174715587,
    -0.47679923006332209, -0.478147056424843, -0.47949375766015295,
    -0.48083933060033396, -0.48218377207912272, -0.48352707893291874,
    -0.48486924800079106, -0.48621027612448642, -0.487550160148436,
    -0.48888889691976317, -0.49022648328829116, -0.4915629161065499,
    -0.49289819222978404, -0.49423230851595967, -0.49556526182577254,
    -0.49689704902265447, -0.49822766697278181, -0.49955711254508184,
    -0.50088538261124071, -0.50221247404571079, -0.50353838372571758,
    -0.50486310853126759, -0.50618664534515523, -0.50750899105297087,
    -0.508830142543107, -0.51015009670676681, -0.5114688504379703,
    -0.512786400633563, -0.51410274419322166, -0.51541787801946293,
    -0.51673179901764987, -0.51804450409599934, -0.51935599016558964,
    -0.52066625414036716, -0.52197529293715439, -0.52328310347565643,
    -0.524589682678469, -0.52589502747108463, -0.52719913478190128,
    -0.52850200154222848, -0.52980362468629461, -0.531104001151255,
    -0.5324031278771979, -0.533701001807153, -0.53499761988709715,
    -0.53629297906596318, -0.53758707629564539, -0.53887990853100842,
    -0.54017147272989285, -0.54146176585312344, -0.54275078486451589,
    -0.54403852673088382, -0.54532498842204646, -0.54661016691083486,
    -0.54789405917310019, -0.54917666218771966, -0.55045797293660481,
    -0.55173798840470734, -0.55301670558002747, -0.55429412145362,
    -0.55557023301960218, -0.5568450372751601, -0.5581185312205561,
    -0.55939071185913614, -0.560661576197336, -0.56193112124468936,
    -0.56319934401383409, -0.5644662415205195, -0.56573181078361312,
    -0.56699604882510868, -0.56825895267013149, -0.56952051934694714,
    -0.57078074588696726, -0.572039629324757, -0.5732971666980422,
    -0.57455335504771576, -0.57580819141784534, -0.57706167285567944,
    -0.57831379641165559, -0.57956455913940563, -0.58081395809576453,
    -0.58206199034077544, -0.58330865293769829, -0.58455394295301533,
    -0.58579785745643886, -0.587040393520918, -0.58828154822264522,
    -0.58952131864106394, -0.59075970185887416, -0.591996694962041,
    -0.5932322950397998, -0.59446649918466443, -0.59569930449243336,
    -0.59693070806219639, -0.59816070699634238, -0.59938929840056454,
    -0.600616479383869, -0.60184224705858, -0.60306659854034816,
    -0.604289530948156, -0.60551104140432555, -0.60673112703452448,
    -0.60794978496777363, -0.60916701233645321, -0.61038280627630948,
    -0.61159716392646191, -0.61281008242940971, -0.61402155893103849,
    -0.61523159058062682, -0.61644017453085365, -0.61764730793780387,
    -0.61885298796097632, -0.6200572117632891, -0.62125997651108755,
    -0.62246127937415, -0.62366111752569453, -0.62485948814238634,
    -0.62605638840434352, -0.62725181549514408, -0.6284457666018326,
    -0.629638238914927, -0.63082922962842447, -0.63201873593980906,
    -0.63320675505005719, -0.63439328416364549, -0.63557832048855611,
    -0.6367618612362842, -0.637943903621844, -0.63912444486377573,
    -0.64030348218415167, -0.641481012808583, -0.64265703396622686,
    -0.64383154288979139, -0.64500453681554393, -0.64617601298331628,
    -0.64734596863651206, -0.64851440102211244, -0.64968130739068319,
    -0.650846684996381, -0.6520105310969595, -0.65317284295377676,
    -0.65433361783180044, -0.65549285299961535, -0.65665054572942894,
    -0.65780669329707864, -0.65896129298203732, -0.66011434206742048,
    -0.66126583783999227, -0.66241577759017178, -0.66356415861203977,
    -0.66471097820334479, -0.66585623366550972, -0.66699992230363747,
    -0.66814204142651845, -0.669282588346636, -0.67042156038017309,
    -0.67155895484701833, -0.67269476907077286, -0.673829000378756,
    -0.674961646102012, -0.67609270357531592, -0.67722217013718033,
    -0.67835004312986147, -0.679476319899365, -0.680600997795453,
    -0.68172407417164971, -0.68284554638524808, -0.6839654117973154,
    -0.68508366777270036, -0.68620031168003859, -0.687315340891759,
    -0.68842875278409044, -0.68954054473706683, -0.6906507141345346,
    -0.69175925836415775, -0.69286617481742463, -0.69397146088965389,
    -0.69507511398000088, -0.696177131491463, -0.69727751083088652,
    -0.69837624940897292, -0.69947334464028377, -0.70056879394324834,
    -0.70166259474016845, -0.7027547444572253, -0.70384524052448494,
    -0.70493408037590488, -0.70602126144933974, -0.70710678118654757,
    -0.7081906370331954, -0.70927282643886569, -0.71035334685706242,
    -0.71143219574521643, -0.71250937056469243, -0.71358486878079352,
    -0.71465868786276909, -0.71573082528381859, -0.71680127852109954,
    -0.71787004505573171, -0.71893712237280449, -0.72000250796138165,
    -0.72106619931450811, -0.72212819392921535, -0.72318848930652746,
    -0.724247082951467, -0.72530397237306077, -0.726359155084346,
    -0.72741262860237577, -0.7284643904482252, -0.729514438146997,
    -0.73056276922782759, -0.73160938122389263, -0.73265427167241282,
    -0.73369743811466037, -0.7347388780959635, -0.73577858916571359,
    -0.73681656887736979, -0.737852814788466, -0.73888732446061511,
    -0.7399200954595162, -0.74095112535495922, -0.74198041172083107,
    -0.74300795213512172, -0.74403374417992929, -0.745057785441466,
    -0.74608007351006378, -0.74710060598018013, -0.7481193804504036,
    -0.74913639452345937, -0.75015164580621507, -0.75116513190968637,
    -0.7521768504490427, -0.75318679904361252, -0.75419497531688917,
    -0.75520137689653655, -0.75620600141439454, -0.75720884650648457,
    -0.75820990981301528, -0.759209188978388, -0.76020668165120242,
    -0.76120238548426178, -0.7621962981345789, -0.76318841726338127,
    -0.76417874053611679, -0.765167265622459, -0.76615399019631292,
    -0.7671389119358204, -0.76812202852336542, -0.7691033376455797,
    -0.7700828369933479, -0.77106052426181382, -0.77203639715038452,
    -0.773010453362737, -0.7739826906068229, -0.77495310659487393,
    -0.77592169904340769, -0.77688846567323244, -0.77785340420945315,
    -0.778816512381476, -0.77977778792301455, -0.78073722857209449,
    -0.78169483207105939, -0.78265059616657573, -0.78360451860963831,
    -0.78455659715557524, -0.78550682956405393, -0.78645521359908577,
    -0.78740174702903143, -0.78834642762660634, -0.78928925316888565,
    -0.79023022143731, -0.7911693302176902, -0.79210657730021239,
    -0.79304196047944364, -0.79397547755433717, -0.794907126328237,
    -0.79583690460888357, -0.79676481020841883, -0.79769084094339116,
    -0.79861499463476093, -0.799537269107905, -0.80045766219262282,
    -0.80137617172314024, -0.80229279553811572, -0.80320753148064494,
    -0.8041203773982657, -0.80503133114296366, -0.80594039057117628,
    -0.80684755354379933, -0.80775281792619036, -0.808656181588175,
    -0.80955764240405126, -0.81045719825259477, -0.81135484701706373,
    -0.81225058658520388, -0.81314441484925359, -0.81403632970594841,
    -0.81492632905652662, -0.81581441080673378, -0.81670057286682785,
    -0.81758481315158371, -0.81846712958029866, -0.819347520076797,
    -0.82022598256943469, -0.82110251499110465, -0.82197711527924155,
    -0.82284978137582643, -0.82372051122739143, -0.82458930278502529,
    -0.82545615400437755, -0.82632106284566353, -0.82718402727366913,
    -0.8280450452577558, -0.82890411477186487, -0.829761233794523,
    -0.83061640030884631, -0.83146961230254524, -0.83232086776792968,
    -0.83317016470191319, -0.83401750110601813, -0.83486287498638,
    -0.8357062843537526, -0.836547727223512, -0.83738720161566194,
    -0.83822470555483808, -0.83906023707031274, -0.83989379419599952,
    -0.84072537497045807, -0.84155497743689844, -0.84238259964318585,
    -0.84320823964184544, -0.84403189549006641, -0.84485356524970712,
    -0.84567324698729907, -0.84649093877405213, -0.84730663868585832,
    -0.84812034480329723, -0.84893205521163961, -0.84974176800085255,
    -0.85054948126560348, -0.8513551931052652, -0.85215890162391983,
    -0.85296060493036363, -0.85376030113811141, -0.85455798836540053,
    -0.855353664735196, -0.85614732837519447, -0.85693897741782876,
    -0.85772861000027212, -0.85851622426444274, -0.85930181835700847,
    -0.86008539042939014, -0.86086693863776731, -0.8616464611430813,
    -0.8624239561110405, -0.86319942171212416, -0.8639728561215867,
    -0.86474425751946238, -0.86551362409056909, -0.866280954024513,
    -0.86704624551569265, -0.86780949676330332, -0.8685707059713409,
    -0.86932987134860684, -0.87008699110871146, -0.870842063470079,
    -0.87159508665595109, -0.87234605889439154, -0.87309497841829009,
    -0.87384184346536686, -0.87458665227817611, -0.87532940310411089,
    -0.8760700941954066, -0.87680872380914565, -0.87754529020726135,
    -0.87827979165654158, -0.87901222642863353, -0.87974259280004741,
    -0.88047088905216075, -0.88119711347122209, -0.881921264348355,
    -0.88264333997956279, -0.88336333866573158, -0.884081258712635,
    -0.88479709843093779, -0.8855108561362, -0.88622253014888064,
    -0.88693211879434219, -0.88763962040285393, -0.88834503330959635,
    -0.88904835585466457, -0.88974958638307278, -0.89044872324475788,
    -0.89114576479458318, -0.89184070939234272, -0.89253355540276458,
    -0.89322430119551532, -0.89391294514520325, -0.8945994856313827,
    -0.89528392103855758, -0.89596624975618522, -0.89664647017868015,
    -0.89732458070541832, -0.89800057974073988, -0.89867446569395382,
    -0.89934623697934157, -0.90001589201616017, -0.900683429228647,
    -0.901348847046022, -0.90201214390249318, -0.90267331823725883,
    -0.90333236849451182, -0.90398929312344334, -0.90464409057824624,
    -0.90529675931811882, -0.90594729780726846, -0.90659570451491533,
    -0.90724197791529582, -0.90788611648766626, -0.90852811871630612,
    -0.90916798309052238, -0.90980570810465222, -0.91044129225806725,
    -0.91107473405517636, -0.91170603200542988, -0.91233518462332275,
    -0.91296219042839821, -0.91358704794525081, -0.91420975570353069,
    -0.9148303122379462, -0.91544871608826783, -0.91606496579933172,
    -0.9166790599210427, -0.91729099700837791, -0.9179007756213905,
    -0.91850839432521225, -0.91911385169005777, -0.91971714629122736,
    -0.92031827670911059, -0.92091724152918952, -0.9215140393420419,
    -0.92210866874334518, -0.92270112833387863, -0.92329141671952764,
    -0.92387953251128674, -0.9244654743252626, -0.92504924078267758,
    -0.92563083050987272, -0.92621024213831138, -0.92678747430458175,
    -0.92736252565040111, -0.92793539482261789, -0.92850608047321559,
    -0.92907458125931586, -0.92964089584318121, -0.93020502289221907,
    -0.93076696107898371, -0.93132670908118043, -0.93188426558166815,
    -0.93243962926846236, -0.932992798834739, -0.93354377297883617,
    -0.93409255040425887, -0.93463912981968078, -0.93518350993894761,
    -0.93572568948108037, -0.93626566717027826, -0.93680344173592156,
    -0.937339011912575, -0.93787237643998989, -0.93840353406310806,
    -0.9389324835320646, -0.93945922360218992, -0.93998375303401394,
    -0.9405060705932683, -0.94102617505088926, -0.94154406518302081,
    -0.94205973977101731, -0.94257319760144687, -0.94308443746609349,
    -0.94359345816196039, -0.94410025849127266, -0.94460483726148026,
    -0.94510719328526061, -0.94560732538052128, -0.94610523237040345,
    -0.94660091308328353, -0.94709436635277722, -0.94758559101774109,
    -0.94807458592227623, -0.94856134991573027, -0.94904588185270056,
    -0.94952818059303667, -0.950008245001843, -0.9504860739494817,
    -0.95096166631157508, -0.95143502096900834, -0.95190613680793235,
    -0.95237501271976588, -0.95284164760119872, -0.95330604035419386,
    -0.95376818988599033, -0.95422809510910567, -0.95468575494133834,
    -0.95514116830577078, -0.95559433413077111, -0.95604525134999641,
    -0.9564939189023951, -0.95694033573220882, -0.95738450078897586,
    -0.95782641302753291, -0.95826607140801767, -0.9587034748958716,
    -0.95913862246184189, -0.95957151308198452, -0.960002145737666,
    -0.96043051941556579, -0.96085663310767966, -0.96128048581132064,
    -0.96170207652912254, -0.96212140426904158, -0.96253846804435916,
    -0.96295326687368388, -0.963365799780954, -0.96377606579543984,
    -0.96418406395174583, -0.96458979328981276, -0.96499325285492032,
    -0.9653944416976894, -0.96579335887408368, -0.9661900034454125,
    -0.96658437447833312, -0.96697647104485207, -0.96736629222232851,
    -0.96775383709347551, -0.96813910474636244, -0.96852209427441727,
    -0.96890280477642887, -0.96928123535654853, -0.96965738512429245,
    -0.970031253194544, -0.9704028386875555, -0.97077214072895035,
    -0.97113915844972509, -0.97150389098625178, -0.9718663374802794,
    -0.97222649707893627, -0.97258436893473221, -0.97293995220556018,
    -0.97329324605469825, -0.973644249650812, -0.97399296216795583,
    -0.97433938278557586, -0.97468351068851067, -0.97502534506699412,
    -0.975364885116657, -0.97570213003852857, -0.976037079039039,
    -0.97636973133002114, -0.97670008612871184, -0.97702814265775439,
    -0.97735390014520007, -0.97767735782450993, -0.97799851493455714,
    -0.97831737071962765, -0.97863392442942321, -0.9789481753190622,
    -0.979260122649082, -0.97956976568544052, -0.97987710369951764,
    -0.98018213596811743, -0.98048486177346938, -0.98078528040323043,
    -0.98108339115048671, -0.98137919331375456, -0.98167268619698311,
    -0.98196386910955524, -0.98225274136628937, -0.98253930228744124,
    -0.98282355119870524, -0.98310548743121629, -0.98338511032155118,
    -0.98366241921173025, -0.98393741344921892, -0.984210092386929,
    -0.98448045538322093, -0.98474850180190421, -0.98501423101223984,
    -0.98527764238894122, -0.98553873531217606, -0.98579750916756748,
    -0.98605396334619544, -0.98630809724459867, -0.98655991026477541,
    -0.98680940181418553, -0.987056571305751, -0.98730141815785843,
    -0.98754394179435923, -0.98778414164457218, -0.98802201714328353,
    -0.98825756773074946, -0.98849079285269659, -0.98872169196032378,
    -0.988950264510303, -0.989176509964781, -0.98940042779138038,
    -0.98962201746320089, -0.98984127845882053, -0.99005821026229712,
    -0.99027281236316911, -0.99048508425645709, -0.99069502544266463,
    -0.99090263542778, -0.99110791372327689, -0.99131085984611544,
    -0.9915114733187439, -0.99170975366909953, -0.99190570043060933,
    -0.9920993131421918, -0.99229059134825737, -0.99247953459871,
    -0.992666142448948, -0.9928504144598651, -0.99303235019785141,
    -0.9932119492347945, -0.99338921114808065, -0.9935641355205953,
    -0.9937367219407246, -0.99390697000235606, -0.99407487930487937,
    -0.9942404494531879, -0.9944036800576791, -0.99456457073425542,
    -0.9947231211043257, -0.99487933079480562, -0.99503319943811863,
    -0.99518472667219693, -0.99533391214048228, -0.99548075549192694,
    -0.99562525638099431, -0.99576741446765982, -0.99590722941741172,
    -0.996044700901252, -0.996179828595697, -0.996312612182778,
    -0.99644305135004263, -0.99657114579055484, -0.99669689520289606,
    -0.99682029929116567, -0.99694135776498216, -0.997060070339483,
    -0.99717643673532619, -0.99729045667869021, -0.9974021299012753,
    -0.99751145614030345, -0.99761843513851955, -0.99772306664419164,
    -0.99782535041111164, -0.997925286198596, -0.99802287377148624,
    -0.99811811290014918, -0.99821100336047819, -0.99830154493389289,
    -0.99838973740734016, -0.99847558057329477, -0.99855907422975931,
    -0.99864021818026527, -0.99871901223387294, -0.99879545620517241,
    -0.99886954991428356, -0.99894129318685687, -0.99901068585407338,
    -0.99907772775264536, -0.99914241872481691, -0.99920475861836389,
    -0.99926474728659442, -0.99932238458834954, -0.99937767038800285,
    -0.99943060455546173, -0.999481186966167, -0.99952941750109314,
    -0.99957529604674922, -0.99961882249517864, -0.99965999674395922,
    -0.99969881869620425, -0.99973528826056168, -0.99976940535121528,
    -0.99980116988788426, -0.9998305817958234, -0.99985764100582386,
    -0.99988234745421256, -0.9999047010828529, -0.9999247018391445,
    -0.99994234967602391, -0.9999576445519639, -0.99997058643097414,
    -0.99998117528260111, -0.9999894110819284, -0.99999529380957619,
    -0.99999882345170188, -1.0 };

  double twid_im;
  static const double dv15[2049] = { 0.0, -0.0015339801862847655,
    -0.0030679567629659761, -0.0046019261204485705, -0.0061358846491544753,
    -0.007669828739531097, -0.00920375478205982, -0.010737659167264491,
    -0.012271538285719925, -0.013805388528060391, -0.0153392062849881,
    -0.01687298794728171, -0.01840672990580482, -0.019940428551514441,
    -0.021474080275469508, -0.023007681468839369, -0.024541228522912288,
    -0.0260747178291039, -0.02760814577896574, -0.029141508764193722,
    -0.030674803176636626, -0.032208025408304586, -0.03374117185137758,
    -0.035274238898213947, -0.036807222941358832, -0.038340120373552694,
    -0.039872927587739811, -0.041405640977076739, -0.04293825693494082,
    -0.044470771854938668, -0.046003182130914623, -0.0475354841569593,
    -0.049067674327418015, -0.050599749036899282, -0.052131704680283324,
    -0.05366353765273052, -0.055195244349689941, -0.056726821166907748,
    -0.058258264500435752, -0.059789570746639868, -0.061320736302208578,
    -0.0628517575641614, -0.064382630929857465, -0.0659133527970038,
    -0.067443919563664051, -0.068974327628266746, -0.070504573389613856,
    -0.072034653246889332, -0.073564563599667426, -0.0750943008479213,
    -0.076623861392031492, -0.078153241632794232, -0.079682437971430126,
    -0.081211446809592441, -0.082740264549375692, -0.084268887593324071,
    -0.0857973123444399, -0.087325535206192059, -0.0888535525825246,
    -0.090381360877864983, -0.091908956497132724, -0.093436335845747787,
    -0.094963495329638992, -0.096490431355252593, -0.0980171403295606,
    -0.099543618660069319, -0.10106986275482782, -0.10259586902243628,
    -0.10412163387205459, -0.10564715371341062, -0.10717242495680884,
    -0.10869744401313872, -0.11022220729388306, -0.11174671121112659,
    -0.11327095217756435, -0.11479492660651008, -0.11631863091190475,
    -0.11784206150832498, -0.11936521481099135, -0.12088808723577708,
    -0.1224106751992162, -0.12393297511851216, -0.12545498341154623,
    -0.12697669649688587, -0.12849811079379317, -0.13001922272223335,
    -0.13154002870288312, -0.13306052515713906, -0.13458070850712617,
    -0.1361005751757062, -0.13762012158648604, -0.1391393441638262,
    -0.14065823933284921, -0.14217680351944803, -0.14369503315029447,
    -0.14521292465284746, -0.14673047445536175, -0.14824767898689603,
    -0.14976453467732151, -0.15128103795733022, -0.15279718525844344,
    -0.1543129730130201, -0.15582839765426523, -0.15734345561623825,
    -0.15885814333386145, -0.16037245724292828, -0.16188639378011183,
    -0.16339994938297323, -0.16491312048996992, -0.1664259035404641,
    -0.16793829497473117, -0.16945029123396796, -0.17096188876030122,
    -0.17247308399679595, -0.17398387338746382, -0.17549425337727143,
    -0.17700422041214875, -0.17851377093899751, -0.18002290140569951,
    -0.18153160826112497, -0.18303988795514095, -0.18454773693861962,
    -0.18605515166344663, -0.1875621285825296, -0.18906866414980619,
    -0.19057475482025274, -0.19208039704989244, -0.19358558729580361,
    -0.19509032201612825, -0.19659459767008022, -0.19809841071795356,
    -0.19960175762113097, -0.2011046348420919, -0.20260703884442113,
    -0.20410896609281687, -0.20561041305309924, -0.20711137619221856,
    -0.20861185197826349, -0.21011183688046961, -0.21161132736922755,
    -0.21311031991609136, -0.21460881099378676, -0.21610679707621952,
    -0.21760427463848364, -0.2191012401568698, -0.22059769010887351,
    -0.22209362097320351, -0.22358902922979, -0.22508391135979283,
    -0.22657826384561, -0.22807208317088573, -0.22956536582051887,
    -0.23105810828067111, -0.23255030703877524, -0.23404195858354343,
    -0.23553305940497549, -0.2370236059943672, -0.23851359484431842,
    -0.2400030224487415, -0.24149188530286933, -0.24298017990326387,
    -0.24446790274782415, -0.24595505033579459, -0.24744161916777327,
    -0.24892760574572015, -0.25041300657296522, -0.25189781815421697,
    -0.25338203699557016, -0.25486565960451457, -0.25634868248994291,
    -0.257831102162159, -0.25931291513288623, -0.26079411791527551,
    -0.26227470702391359, -0.26375467897483135, -0.26523403028551179,
    -0.26671275747489837, -0.26819085706340318, -0.26966832557291509,
    -0.271145159526808, -0.272621355449949, -0.27409690986870638,
    -0.27557181931095814, -0.2770460803060999, -0.27851968938505306,
    -0.27999264308027322, -0.28146493792575794, -0.28293657045705539,
    -0.28440753721127188, -0.28587783472708062, -0.28734745954472951,
    -0.28881640820604948, -0.29028467725446233, -0.29175226323498926,
    -0.29321916269425863, -0.29468537218051433, -0.29615088824362379,
    -0.2976157074350862, -0.29907982630804048, -0.30054324141727345,
    -0.30200594931922808, -0.30346794657201132, -0.30492922973540237,
    -0.30638979537086092, -0.30784964004153487, -0.30930876031226873,
    -0.31076715274961147, -0.31222481392182488, -0.31368174039889152,
    -0.31513792875252244, -0.31659337555616585, -0.31804807738501495,
    -0.31950203081601569, -0.32095523242787521, -0.32240767880106985,
    -0.32385936651785285, -0.32531029216226293, -0.32676045232013173,
    -0.3282098435790925, -0.32965846252858749, -0.33110630575987643,
    -0.33255336986604422, -0.33399965144200938, -0.3354451470845316,
    -0.33688985339222005, -0.33833376696554113, -0.33977688440682685,
    -0.34121920232028236, -0.34266071731199438, -0.34410142598993881,
    -0.34554132496398909, -0.34698041084592368, -0.34841868024943456,
    -0.34985612979013492, -0.35129275608556709, -0.35272855575521073,
    -0.35416352542049034, -0.35559766170478385, -0.35703096123343,
    -0.35846342063373654, -0.35989503653498811, -0.36132580556845428,
    -0.36275572436739723, -0.36418478956707989, -0.36561299780477385,
    -0.36704034571976718, -0.36846682995337232, -0.3698924471489341,
    -0.37131719395183749, -0.37274106700951576, -0.37416406297145793,
    -0.37558617848921722, -0.37700741021641826, -0.37842775480876556,
    -0.37984720892405116, -0.38126576922216238, -0.38268343236508978,
    -0.38410019501693504, -0.38551605384391885, -0.38693100551438858,
    -0.38834504669882625, -0.38975817406985641, -0.39117038430225387,
    -0.39258167407295147, -0.3939920400610481, -0.39540147894781635,
    -0.39680998741671031, -0.39821756215337356, -0.39962419984564679,
    -0.40102989718357562, -0.40243465085941843, -0.40383845756765407,
    -0.40524131400498986, -0.40664321687036903, -0.40804416286497869,
    -0.40944414869225759, -0.41084317105790391, -0.41224122666988289,
    -0.4136383122384345, -0.41503442447608163, -0.41642956009763715,
    -0.41782371582021227, -0.41921688836322391, -0.42060907444840251,
    -0.42200027079979968, -0.42339047414379605, -0.42477968120910881,
    -0.42616788872679962, -0.42755509343028208, -0.42894129205532949,
    -0.43032648134008261, -0.43171065802505726, -0.43309381885315196,
    -0.43447596056965565, -0.43585707992225547, -0.43723717366104409,
    -0.43861623853852766, -0.43999427130963326, -0.44137126873171667,
    -0.44274722756457, -0.4441221445704292, -0.44549601651398174,
    -0.44686884016237416, -0.44824061228521989, -0.44961132965460654,
    -0.45098098904510386, -0.45234958723377089, -0.45371712100016387,
    -0.45508358712634384, -0.45644898239688392, -0.45781330359887717,
    -0.45917654752194409, -0.46053871095824, -0.46189979070246273,
    -0.46325978355186015, -0.46461868630623782, -0.46597649576796618,
    -0.46733320874198842, -0.46868882203582796, -0.47004333245959562,
    -0.47139673682599764, -0.47274903195034279, -0.47410021465054997,
    -0.47545028174715587, -0.47679923006332209, -0.478147056424843,
    -0.47949375766015295, -0.48083933060033396, -0.48218377207912272,
    -0.48352707893291874, -0.48486924800079106, -0.48621027612448642,
    -0.487550160148436, -0.48888889691976317, -0.49022648328829116,
    -0.4915629161065499, -0.49289819222978404, -0.49423230851595967,
    -0.49556526182577254, -0.49689704902265447, -0.49822766697278181,
    -0.49955711254508184, -0.50088538261124071, -0.50221247404571079,
    -0.50353838372571758, -0.50486310853126759, -0.50618664534515523,
    -0.50750899105297087, -0.508830142543107, -0.51015009670676681,
    -0.5114688504379703, -0.512786400633563, -0.51410274419322166,
    -0.51541787801946293, -0.51673179901764987, -0.51804450409599934,
    -0.51935599016558964, -0.52066625414036716, -0.52197529293715439,
    -0.52328310347565643, -0.524589682678469, -0.52589502747108463,
    -0.52719913478190128, -0.52850200154222848, -0.52980362468629461,
    -0.531104001151255, -0.5324031278771979, -0.533701001807153,
    -0.53499761988709715, -0.53629297906596318, -0.53758707629564539,
    -0.53887990853100842, -0.54017147272989285, -0.54146176585312344,
    -0.54275078486451589, -0.54403852673088382, -0.54532498842204646,
    -0.54661016691083486, -0.54789405917310019, -0.54917666218771966,
    -0.55045797293660481, -0.55173798840470734, -0.55301670558002747,
    -0.55429412145362, -0.55557023301960218, -0.5568450372751601,
    -0.5581185312205561, -0.55939071185913614, -0.560661576197336,
    -0.56193112124468936, -0.56319934401383409, -0.5644662415205195,
    -0.56573181078361312, -0.56699604882510868, -0.56825895267013149,
    -0.56952051934694714, -0.57078074588696726, -0.572039629324757,
    -0.5732971666980422, -0.57455335504771576, -0.57580819141784534,
    -0.57706167285567944, -0.57831379641165559, -0.57956455913940563,
    -0.58081395809576453, -0.58206199034077544, -0.58330865293769829,
    -0.58455394295301533, -0.58579785745643886, -0.587040393520918,
    -0.58828154822264522, -0.58952131864106394, -0.59075970185887416,
    -0.591996694962041, -0.5932322950397998, -0.59446649918466443,
    -0.59569930449243336, -0.59693070806219639, -0.59816070699634238,
    -0.59938929840056454, -0.600616479383869, -0.60184224705858,
    -0.60306659854034816, -0.604289530948156, -0.60551104140432555,
    -0.60673112703452448, -0.60794978496777363, -0.60916701233645321,
    -0.61038280627630948, -0.61159716392646191, -0.61281008242940971,
    -0.61402155893103849, -0.61523159058062682, -0.61644017453085365,
    -0.61764730793780387, -0.61885298796097632, -0.6200572117632891,
    -0.62125997651108755, -0.62246127937415, -0.62366111752569453,
    -0.62485948814238634, -0.62605638840434352, -0.62725181549514408,
    -0.6284457666018326, -0.629638238914927, -0.63082922962842447,
    -0.63201873593980906, -0.63320675505005719, -0.63439328416364549,
    -0.63557832048855611, -0.6367618612362842, -0.637943903621844,
    -0.63912444486377573, -0.64030348218415167, -0.641481012808583,
    -0.64265703396622686, -0.64383154288979139, -0.64500453681554393,
    -0.64617601298331628, -0.64734596863651206, -0.64851440102211244,
    -0.64968130739068319, -0.650846684996381, -0.6520105310969595,
    -0.65317284295377676, -0.65433361783180044, -0.65549285299961535,
    -0.65665054572942894, -0.65780669329707864, -0.65896129298203732,
    -0.66011434206742048, -0.66126583783999227, -0.66241577759017178,
    -0.66356415861203977, -0.66471097820334479, -0.66585623366550972,
    -0.66699992230363747, -0.66814204142651845, -0.669282588346636,
    -0.67042156038017309, -0.67155895484701833, -0.67269476907077286,
    -0.673829000378756, -0.674961646102012, -0.67609270357531592,
    -0.67722217013718033, -0.67835004312986147, -0.679476319899365,
    -0.680600997795453, -0.68172407417164971, -0.68284554638524808,
    -0.6839654117973154, -0.68508366777270036, -0.68620031168003859,
    -0.687315340891759, -0.68842875278409044, -0.68954054473706683,
    -0.6906507141345346, -0.69175925836415775, -0.69286617481742463,
    -0.69397146088965389, -0.69507511398000088, -0.696177131491463,
    -0.69727751083088652, -0.69837624940897292, -0.69947334464028377,
    -0.70056879394324834, -0.70166259474016845, -0.7027547444572253,
    -0.70384524052448494, -0.70493408037590488, -0.70602126144933974,
    -0.70710678118654757, -0.7081906370331954, -0.70927282643886569,
    -0.71035334685706242, -0.71143219574521643, -0.71250937056469243,
    -0.71358486878079352, -0.71465868786276909, -0.71573082528381859,
    -0.71680127852109954, -0.71787004505573171, -0.71893712237280449,
    -0.72000250796138165, -0.72106619931450811, -0.72212819392921535,
    -0.72318848930652746, -0.724247082951467, -0.72530397237306077,
    -0.726359155084346, -0.72741262860237577, -0.7284643904482252,
    -0.729514438146997, -0.73056276922782759, -0.73160938122389263,
    -0.73265427167241282, -0.73369743811466037, -0.7347388780959635,
    -0.73577858916571359, -0.73681656887736979, -0.737852814788466,
    -0.73888732446061511, -0.7399200954595162, -0.74095112535495922,
    -0.74198041172083107, -0.74300795213512172, -0.74403374417992929,
    -0.745057785441466, -0.74608007351006378, -0.74710060598018013,
    -0.7481193804504036, -0.74913639452345937, -0.75015164580621507,
    -0.75116513190968637, -0.7521768504490427, -0.75318679904361252,
    -0.75419497531688917, -0.75520137689653655, -0.75620600141439454,
    -0.75720884650648457, -0.75820990981301528, -0.759209188978388,
    -0.76020668165120242, -0.76120238548426178, -0.7621962981345789,
    -0.76318841726338127, -0.76417874053611679, -0.765167265622459,
    -0.76615399019631292, -0.7671389119358204, -0.76812202852336542,
    -0.7691033376455797, -0.7700828369933479, -0.77106052426181382,
    -0.77203639715038452, -0.773010453362737, -0.7739826906068229,
    -0.77495310659487393, -0.77592169904340769, -0.77688846567323244,
    -0.77785340420945315, -0.778816512381476, -0.77977778792301455,
    -0.78073722857209449, -0.78169483207105939, -0.78265059616657573,
    -0.78360451860963831, -0.78455659715557524, -0.78550682956405393,
    -0.78645521359908577, -0.78740174702903143, -0.78834642762660634,
    -0.78928925316888565, -0.79023022143731, -0.7911693302176902,
    -0.79210657730021239, -0.79304196047944364, -0.79397547755433717,
    -0.794907126328237, -0.79583690460888357, -0.79676481020841883,
    -0.79769084094339116, -0.79861499463476093, -0.799537269107905,
    -0.80045766219262282, -0.80137617172314024, -0.80229279553811572,
    -0.80320753148064494, -0.8041203773982657, -0.80503133114296366,
    -0.80594039057117628, -0.80684755354379933, -0.80775281792619036,
    -0.808656181588175, -0.80955764240405126, -0.81045719825259477,
    -0.81135484701706373, -0.81225058658520388, -0.81314441484925359,
    -0.81403632970594841, -0.81492632905652662, -0.81581441080673378,
    -0.81670057286682785, -0.81758481315158371, -0.81846712958029866,
    -0.819347520076797, -0.82022598256943469, -0.82110251499110465,
    -0.82197711527924155, -0.82284978137582643, -0.82372051122739143,
    -0.82458930278502529, -0.82545615400437755, -0.82632106284566353,
    -0.82718402727366913, -0.8280450452577558, -0.82890411477186487,
    -0.829761233794523, -0.83061640030884631, -0.83146961230254524,
    -0.83232086776792968, -0.83317016470191319, -0.83401750110601813,
    -0.83486287498638, -0.8357062843537526, -0.836547727223512,
    -0.83738720161566194, -0.83822470555483808, -0.83906023707031274,
    -0.83989379419599952, -0.84072537497045807, -0.84155497743689844,
    -0.84238259964318585, -0.84320823964184544, -0.84403189549006641,
    -0.84485356524970712, -0.84567324698729907, -0.84649093877405213,
    -0.84730663868585832, -0.84812034480329723, -0.84893205521163961,
    -0.84974176800085255, -0.85054948126560348, -0.8513551931052652,
    -0.85215890162391983, -0.85296060493036363, -0.85376030113811141,
    -0.85455798836540053, -0.855353664735196, -0.85614732837519447,
    -0.85693897741782876, -0.85772861000027212, -0.85851622426444274,
    -0.85930181835700847, -0.86008539042939014, -0.86086693863776731,
    -0.8616464611430813, -0.8624239561110405, -0.86319942171212416,
    -0.8639728561215867, -0.86474425751946238, -0.86551362409056909,
    -0.866280954024513, -0.86704624551569265, -0.86780949676330332,
    -0.8685707059713409, -0.86932987134860684, -0.87008699110871146,
    -0.870842063470079, -0.87159508665595109, -0.87234605889439154,
    -0.87309497841829009, -0.87384184346536686, -0.87458665227817611,
    -0.87532940310411089, -0.8760700941954066, -0.87680872380914565,
    -0.87754529020726135, -0.87827979165654158, -0.87901222642863353,
    -0.87974259280004741, -0.88047088905216075, -0.88119711347122209,
    -0.881921264348355, -0.88264333997956279, -0.88336333866573158,
    -0.884081258712635, -0.88479709843093779, -0.8855108561362,
    -0.88622253014888064, -0.88693211879434219, -0.88763962040285393,
    -0.88834503330959635, -0.88904835585466457, -0.88974958638307278,
    -0.89044872324475788, -0.89114576479458318, -0.89184070939234272,
    -0.89253355540276458, -0.89322430119551532, -0.89391294514520325,
    -0.8945994856313827, -0.89528392103855758, -0.89596624975618522,
    -0.89664647017868015, -0.89732458070541832, -0.89800057974073988,
    -0.89867446569395382, -0.89934623697934157, -0.90001589201616017,
    -0.900683429228647, -0.901348847046022, -0.90201214390249318,
    -0.90267331823725883, -0.90333236849451182, -0.90398929312344334,
    -0.90464409057824624, -0.90529675931811882, -0.90594729780726846,
    -0.90659570451491533, -0.90724197791529582, -0.90788611648766626,
    -0.90852811871630612, -0.90916798309052238, -0.90980570810465222,
    -0.91044129225806725, -0.91107473405517636, -0.91170603200542988,
    -0.91233518462332275, -0.91296219042839821, -0.91358704794525081,
    -0.91420975570353069, -0.9148303122379462, -0.91544871608826783,
    -0.91606496579933172, -0.9166790599210427, -0.91729099700837791,
    -0.9179007756213905, -0.91850839432521225, -0.91911385169005777,
    -0.91971714629122736, -0.92031827670911059, -0.92091724152918952,
    -0.9215140393420419, -0.92210866874334518, -0.92270112833387863,
    -0.92329141671952764, -0.92387953251128674, -0.9244654743252626,
    -0.92504924078267758, -0.92563083050987272, -0.92621024213831138,
    -0.92678747430458175, -0.92736252565040111, -0.92793539482261789,
    -0.92850608047321559, -0.92907458125931586, -0.92964089584318121,
    -0.93020502289221907, -0.93076696107898371, -0.93132670908118043,
    -0.93188426558166815, -0.93243962926846236, -0.932992798834739,
    -0.93354377297883617, -0.93409255040425887, -0.93463912981968078,
    -0.93518350993894761, -0.93572568948108037, -0.93626566717027826,
    -0.93680344173592156, -0.937339011912575, -0.93787237643998989,
    -0.93840353406310806, -0.9389324835320646, -0.93945922360218992,
    -0.93998375303401394, -0.9405060705932683, -0.94102617505088926,
    -0.94154406518302081, -0.94205973977101731, -0.94257319760144687,
    -0.94308443746609349, -0.94359345816196039, -0.94410025849127266,
    -0.94460483726148026, -0.94510719328526061, -0.94560732538052128,
    -0.94610523237040345, -0.94660091308328353, -0.94709436635277722,
    -0.94758559101774109, -0.94807458592227623, -0.94856134991573027,
    -0.94904588185270056, -0.94952818059303667, -0.950008245001843,
    -0.9504860739494817, -0.95096166631157508, -0.95143502096900834,
    -0.95190613680793235, -0.95237501271976588, -0.95284164760119872,
    -0.95330604035419386, -0.95376818988599033, -0.95422809510910567,
    -0.95468575494133834, -0.95514116830577078, -0.95559433413077111,
    -0.95604525134999641, -0.9564939189023951, -0.95694033573220882,
    -0.95738450078897586, -0.95782641302753291, -0.95826607140801767,
    -0.9587034748958716, -0.95913862246184189, -0.95957151308198452,
    -0.960002145737666, -0.96043051941556579, -0.96085663310767966,
    -0.96128048581132064, -0.96170207652912254, -0.96212140426904158,
    -0.96253846804435916, -0.96295326687368388, -0.963365799780954,
    -0.96377606579543984, -0.96418406395174583, -0.96458979328981276,
    -0.96499325285492032, -0.9653944416976894, -0.96579335887408368,
    -0.9661900034454125, -0.96658437447833312, -0.96697647104485207,
    -0.96736629222232851, -0.96775383709347551, -0.96813910474636244,
    -0.96852209427441727, -0.96890280477642887, -0.96928123535654853,
    -0.96965738512429245, -0.970031253194544, -0.9704028386875555,
    -0.97077214072895035, -0.97113915844972509, -0.97150389098625178,
    -0.9718663374802794, -0.97222649707893627, -0.97258436893473221,
    -0.97293995220556018, -0.97329324605469825, -0.973644249650812,
    -0.97399296216795583, -0.97433938278557586, -0.97468351068851067,
    -0.97502534506699412, -0.975364885116657, -0.97570213003852857,
    -0.976037079039039, -0.97636973133002114, -0.97670008612871184,
    -0.97702814265775439, -0.97735390014520007, -0.97767735782450993,
    -0.97799851493455714, -0.97831737071962765, -0.97863392442942321,
    -0.9789481753190622, -0.979260122649082, -0.97956976568544052,
    -0.97987710369951764, -0.98018213596811743, -0.98048486177346938,
    -0.98078528040323043, -0.98108339115048671, -0.98137919331375456,
    -0.98167268619698311, -0.98196386910955524, -0.98225274136628937,
    -0.98253930228744124, -0.98282355119870524, -0.98310548743121629,
    -0.98338511032155118, -0.98366241921173025, -0.98393741344921892,
    -0.984210092386929, -0.98448045538322093, -0.98474850180190421,
    -0.98501423101223984, -0.98527764238894122, -0.98553873531217606,
    -0.98579750916756748, -0.98605396334619544, -0.98630809724459867,
    -0.98655991026477541, -0.98680940181418553, -0.987056571305751,
    -0.98730141815785843, -0.98754394179435923, -0.98778414164457218,
    -0.98802201714328353, -0.98825756773074946, -0.98849079285269659,
    -0.98872169196032378, -0.988950264510303, -0.989176509964781,
    -0.98940042779138038, -0.98962201746320089, -0.98984127845882053,
    -0.99005821026229712, -0.99027281236316911, -0.99048508425645709,
    -0.99069502544266463, -0.99090263542778, -0.99110791372327689,
    -0.99131085984611544, -0.9915114733187439, -0.99170975366909953,
    -0.99190570043060933, -0.9920993131421918, -0.99229059134825737,
    -0.99247953459871, -0.992666142448948, -0.9928504144598651,
    -0.99303235019785141, -0.9932119492347945, -0.99338921114808065,
    -0.9935641355205953, -0.9937367219407246, -0.99390697000235606,
    -0.99407487930487937, -0.9942404494531879, -0.9944036800576791,
    -0.99456457073425542, -0.9947231211043257, -0.99487933079480562,
    -0.99503319943811863, -0.99518472667219693, -0.99533391214048228,
    -0.99548075549192694, -0.99562525638099431, -0.99576741446765982,
    -0.99590722941741172, -0.996044700901252, -0.996179828595697,
    -0.996312612182778, -0.99644305135004263, -0.99657114579055484,
    -0.99669689520289606, -0.99682029929116567, -0.99694135776498216,
    -0.997060070339483, -0.99717643673532619, -0.99729045667869021,
    -0.9974021299012753, -0.99751145614030345, -0.99761843513851955,
    -0.99772306664419164, -0.99782535041111164, -0.997925286198596,
    -0.99802287377148624, -0.99811811290014918, -0.99821100336047819,
    -0.99830154493389289, -0.99838973740734016, -0.99847558057329477,
    -0.99855907422975931, -0.99864021818026527, -0.99871901223387294,
    -0.99879545620517241, -0.99886954991428356, -0.99894129318685687,
    -0.99901068585407338, -0.99907772775264536, -0.99914241872481691,
    -0.99920475861836389, -0.99926474728659442, -0.99932238458834954,
    -0.99937767038800285, -0.99943060455546173, -0.999481186966167,
    -0.99952941750109314, -0.99957529604674922, -0.99961882249517864,
    -0.99965999674395922, -0.99969881869620425, -0.99973528826056168,
    -0.99976940535121528, -0.99980116988788426, -0.9998305817958234,
    -0.99985764100582386, -0.99988234745421256, -0.9999047010828529,
    -0.9999247018391445, -0.99994234967602391, -0.9999576445519639,
    -0.99997058643097414, -0.99998117528260111, -0.9999894110819284,
    -0.99999529380957619, -0.99999882345170188, -1.0, -0.99999882345170188,
    -0.99999529380957619, -0.9999894110819284, -0.99998117528260111,
    -0.99997058643097414, -0.9999576445519639, -0.99994234967602391,
    -0.9999247018391445, -0.9999047010828529, -0.99988234745421256,
    -0.99985764100582386, -0.9998305817958234, -0.99980116988788426,
    -0.99976940535121528, -0.99973528826056168, -0.99969881869620425,
    -0.99965999674395922, -0.99961882249517864, -0.99957529604674922,
    -0.99952941750109314, -0.999481186966167, -0.99943060455546173,
    -0.99937767038800285, -0.99932238458834954, -0.99926474728659442,
    -0.99920475861836389, -0.99914241872481691, -0.99907772775264536,
    -0.99901068585407338, -0.99894129318685687, -0.99886954991428356,
    -0.99879545620517241, -0.99871901223387294, -0.99864021818026527,
    -0.99855907422975931, -0.99847558057329477, -0.99838973740734016,
    -0.99830154493389289, -0.99821100336047819, -0.99811811290014918,
    -0.99802287377148624, -0.997925286198596, -0.99782535041111164,
    -0.99772306664419164, -0.99761843513851955, -0.99751145614030345,
    -0.9974021299012753, -0.99729045667869021, -0.99717643673532619,
    -0.997060070339483, -0.99694135776498216, -0.99682029929116567,
    -0.99669689520289606, -0.99657114579055484, -0.99644305135004263,
    -0.996312612182778, -0.996179828595697, -0.996044700901252,
    -0.99590722941741172, -0.99576741446765982, -0.99562525638099431,
    -0.99548075549192694, -0.99533391214048228, -0.99518472667219693,
    -0.99503319943811863, -0.99487933079480562, -0.9947231211043257,
    -0.99456457073425542, -0.9944036800576791, -0.9942404494531879,
    -0.99407487930487937, -0.99390697000235606, -0.9937367219407246,
    -0.9935641355205953, -0.99338921114808065, -0.9932119492347945,
    -0.99303235019785141, -0.9928504144598651, -0.992666142448948,
    -0.99247953459871, -0.99229059134825737, -0.9920993131421918,
    -0.99190570043060933, -0.99170975366909953, -0.9915114733187439,
    -0.99131085984611544, -0.99110791372327689, -0.99090263542778,
    -0.99069502544266463, -0.99048508425645709, -0.99027281236316911,
    -0.99005821026229712, -0.98984127845882053, -0.98962201746320089,
    -0.98940042779138038, -0.989176509964781, -0.988950264510303,
    -0.98872169196032378, -0.98849079285269659, -0.98825756773074946,
    -0.98802201714328353, -0.98778414164457218, -0.98754394179435923,
    -0.98730141815785843, -0.987056571305751, -0.98680940181418553,
    -0.98655991026477541, -0.98630809724459867, -0.98605396334619544,
    -0.98579750916756748, -0.98553873531217606, -0.98527764238894122,
    -0.98501423101223984, -0.98474850180190421, -0.98448045538322093,
    -0.984210092386929, -0.98393741344921892, -0.98366241921173025,
    -0.98338511032155118, -0.98310548743121629, -0.98282355119870524,
    -0.98253930228744124, -0.98225274136628937, -0.98196386910955524,
    -0.98167268619698311, -0.98137919331375456, -0.98108339115048671,
    -0.98078528040323043, -0.98048486177346938, -0.98018213596811743,
    -0.97987710369951764, -0.97956976568544052, -0.979260122649082,
    -0.9789481753190622, -0.97863392442942321, -0.97831737071962765,
    -0.97799851493455714, -0.97767735782450993, -0.97735390014520007,
    -0.97702814265775439, -0.97670008612871184, -0.97636973133002114,
    -0.976037079039039, -0.97570213003852857, -0.975364885116657,
    -0.97502534506699412, -0.97468351068851067, -0.97433938278557586,
    -0.97399296216795583, -0.973644249650812, -0.97329324605469825,
    -0.97293995220556018, -0.97258436893473221, -0.97222649707893627,
    -0.9718663374802794, -0.97150389098625178, -0.97113915844972509,
    -0.97077214072895035, -0.9704028386875555, -0.970031253194544,
    -0.96965738512429245, -0.96928123535654853, -0.96890280477642887,
    -0.96852209427441727, -0.96813910474636244, -0.96775383709347551,
    -0.96736629222232851, -0.96697647104485207, -0.96658437447833312,
    -0.9661900034454125, -0.96579335887408368, -0.9653944416976894,
    -0.96499325285492032, -0.96458979328981276, -0.96418406395174583,
    -0.96377606579543984, -0.963365799780954, -0.96295326687368388,
    -0.96253846804435916, -0.96212140426904158, -0.96170207652912254,
    -0.96128048581132064, -0.96085663310767966, -0.96043051941556579,
    -0.960002145737666, -0.95957151308198452, -0.95913862246184189,
    -0.9587034748958716, -0.95826607140801767, -0.95782641302753291,
    -0.95738450078897586, -0.95694033573220882, -0.9564939189023951,
    -0.95604525134999641, -0.95559433413077111, -0.95514116830577078,
    -0.95468575494133834, -0.95422809510910567, -0.95376818988599033,
    -0.95330604035419386, -0.95284164760119872, -0.95237501271976588,
    -0.95190613680793235, -0.95143502096900834, -0.95096166631157508,
    -0.9504860739494817, -0.950008245001843, -0.94952818059303667,
    -0.94904588185270056, -0.94856134991573027, -0.94807458592227623,
    -0.94758559101774109, -0.94709436635277722, -0.94660091308328353,
    -0.94610523237040345, -0.94560732538052128, -0.94510719328526061,
    -0.94460483726148026, -0.94410025849127266, -0.94359345816196039,
    -0.94308443746609349, -0.94257319760144687, -0.94205973977101731,
    -0.94154406518302081, -0.94102617505088926, -0.9405060705932683,
    -0.93998375303401394, -0.93945922360218992, -0.9389324835320646,
    -0.93840353406310806, -0.93787237643998989, -0.937339011912575,
    -0.93680344173592156, -0.93626566717027826, -0.93572568948108037,
    -0.93518350993894761, -0.93463912981968078, -0.93409255040425887,
    -0.93354377297883617, -0.932992798834739, -0.93243962926846236,
    -0.93188426558166815, -0.93132670908118043, -0.93076696107898371,
    -0.93020502289221907, -0.92964089584318121, -0.92907458125931586,
    -0.92850608047321559, -0.92793539482261789, -0.92736252565040111,
    -0.92678747430458175, -0.92621024213831138, -0.92563083050987272,
    -0.92504924078267758, -0.9244654743252626, -0.92387953251128674,
    -0.92329141671952764, -0.92270112833387863, -0.92210866874334518,
    -0.9215140393420419, -0.92091724152918952, -0.92031827670911059,
    -0.91971714629122736, -0.91911385169005777, -0.91850839432521225,
    -0.9179007756213905, -0.91729099700837791, -0.9166790599210427,
    -0.91606496579933172, -0.91544871608826783, -0.9148303122379462,
    -0.91420975570353069, -0.91358704794525081, -0.91296219042839821,
    -0.91233518462332275, -0.91170603200542988, -0.91107473405517636,
    -0.91044129225806725, -0.90980570810465222, -0.90916798309052238,
    -0.90852811871630612, -0.90788611648766626, -0.90724197791529582,
    -0.90659570451491533, -0.90594729780726846, -0.90529675931811882,
    -0.90464409057824624, -0.90398929312344334, -0.90333236849451182,
    -0.90267331823725883, -0.90201214390249318, -0.901348847046022,
    -0.900683429228647, -0.90001589201616017, -0.89934623697934157,
    -0.89867446569395382, -0.89800057974073988, -0.89732458070541832,
    -0.89664647017868015, -0.89596624975618522, -0.89528392103855758,
    -0.8945994856313827, -0.89391294514520325, -0.89322430119551532,
    -0.89253355540276458, -0.89184070939234272, -0.89114576479458318,
    -0.89044872324475788, -0.88974958638307278, -0.88904835585466457,
    -0.88834503330959635, -0.88763962040285393, -0.88693211879434219,
    -0.88622253014888064, -0.8855108561362, -0.88479709843093779,
    -0.884081258712635, -0.88336333866573158, -0.88264333997956279,
    -0.881921264348355, -0.88119711347122209, -0.88047088905216075,
    -0.87974259280004741, -0.87901222642863353, -0.87827979165654158,
    -0.87754529020726135, -0.87680872380914565, -0.8760700941954066,
    -0.87532940310411089, -0.87458665227817611, -0.87384184346536686,
    -0.87309497841829009, -0.87234605889439154, -0.87159508665595109,
    -0.870842063470079, -0.87008699110871146, -0.86932987134860684,
    -0.8685707059713409, -0.86780949676330332, -0.86704624551569265,
    -0.866280954024513, -0.86551362409056909, -0.86474425751946238,
    -0.8639728561215867, -0.86319942171212416, -0.8624239561110405,
    -0.8616464611430813, -0.86086693863776731, -0.86008539042939014,
    -0.85930181835700847, -0.85851622426444274, -0.85772861000027212,
    -0.85693897741782876, -0.85614732837519447, -0.855353664735196,
    -0.85455798836540053, -0.85376030113811141, -0.85296060493036363,
    -0.85215890162391983, -0.8513551931052652, -0.85054948126560348,
    -0.84974176800085255, -0.84893205521163961, -0.84812034480329723,
    -0.84730663868585832, -0.84649093877405213, -0.84567324698729907,
    -0.84485356524970712, -0.84403189549006641, -0.84320823964184544,
    -0.84238259964318585, -0.84155497743689844, -0.84072537497045807,
    -0.83989379419599952, -0.83906023707031274, -0.83822470555483808,
    -0.83738720161566194, -0.836547727223512, -0.8357062843537526,
    -0.83486287498638, -0.83401750110601813, -0.83317016470191319,
    -0.83232086776792968, -0.83146961230254524, -0.83061640030884631,
    -0.829761233794523, -0.82890411477186487, -0.8280450452577558,
    -0.82718402727366913, -0.82632106284566353, -0.82545615400437755,
    -0.82458930278502529, -0.82372051122739143, -0.82284978137582643,
    -0.82197711527924155, -0.82110251499110465, -0.82022598256943469,
    -0.819347520076797, -0.81846712958029866, -0.81758481315158371,
    -0.81670057286682785, -0.81581441080673378, -0.81492632905652662,
    -0.81403632970594841, -0.81314441484925359, -0.81225058658520388,
    -0.81135484701706373, -0.81045719825259477, -0.80955764240405126,
    -0.808656181588175, -0.80775281792619036, -0.80684755354379933,
    -0.80594039057117628, -0.80503133114296366, -0.8041203773982657,
    -0.80320753148064494, -0.80229279553811572, -0.80137617172314024,
    -0.80045766219262282, -0.799537269107905, -0.79861499463476093,
    -0.79769084094339116, -0.79676481020841883, -0.79583690460888357,
    -0.794907126328237, -0.79397547755433717, -0.79304196047944364,
    -0.79210657730021239, -0.7911693302176902, -0.79023022143731,
    -0.78928925316888565, -0.78834642762660634, -0.78740174702903143,
    -0.78645521359908577, -0.78550682956405393, -0.78455659715557524,
    -0.78360451860963831, -0.78265059616657573, -0.78169483207105939,
    -0.78073722857209449, -0.77977778792301455, -0.778816512381476,
    -0.77785340420945315, -0.77688846567323244, -0.77592169904340769,
    -0.77495310659487393, -0.7739826906068229, -0.773010453362737,
    -0.77203639715038452, -0.77106052426181382, -0.7700828369933479,
    -0.7691033376455797, -0.76812202852336542, -0.7671389119358204,
    -0.76615399019631292, -0.765167265622459, -0.76417874053611679,
    -0.76318841726338127, -0.7621962981345789, -0.76120238548426178,
    -0.76020668165120242, -0.759209188978388, -0.75820990981301528,
    -0.75720884650648457, -0.75620600141439454, -0.75520137689653655,
    -0.75419497531688917, -0.75318679904361252, -0.7521768504490427,
    -0.75116513190968637, -0.75015164580621507, -0.74913639452345937,
    -0.7481193804504036, -0.74710060598018013, -0.74608007351006378,
    -0.745057785441466, -0.74403374417992929, -0.74300795213512172,
    -0.74198041172083107, -0.74095112535495922, -0.7399200954595162,
    -0.73888732446061511, -0.737852814788466, -0.73681656887736979,
    -0.73577858916571359, -0.7347388780959635, -0.73369743811466037,
    -0.73265427167241282, -0.73160938122389263, -0.73056276922782759,
    -0.729514438146997, -0.7284643904482252, -0.72741262860237577,
    -0.726359155084346, -0.72530397237306077, -0.724247082951467,
    -0.72318848930652746, -0.72212819392921535, -0.72106619931450811,
    -0.72000250796138165, -0.71893712237280449, -0.71787004505573171,
    -0.71680127852109954, -0.71573082528381859, -0.71465868786276909,
    -0.71358486878079352, -0.71250937056469243, -0.71143219574521643,
    -0.71035334685706242, -0.70927282643886569, -0.7081906370331954,
    -0.70710678118654757, -0.70602126144933974, -0.70493408037590488,
    -0.70384524052448494, -0.7027547444572253, -0.70166259474016845,
    -0.70056879394324834, -0.69947334464028377, -0.69837624940897292,
    -0.69727751083088652, -0.696177131491463, -0.69507511398000088,
    -0.69397146088965389, -0.69286617481742463, -0.69175925836415775,
    -0.6906507141345346, -0.68954054473706683, -0.68842875278409044,
    -0.687315340891759, -0.68620031168003859, -0.68508366777270036,
    -0.6839654117973154, -0.68284554638524808, -0.68172407417164971,
    -0.680600997795453, -0.679476319899365, -0.67835004312986147,
    -0.67722217013718033, -0.67609270357531592, -0.674961646102012,
    -0.673829000378756, -0.67269476907077286, -0.67155895484701833,
    -0.67042156038017309, -0.669282588346636, -0.66814204142651845,
    -0.66699992230363747, -0.66585623366550972, -0.66471097820334479,
    -0.66356415861203977, -0.66241577759017178, -0.66126583783999227,
    -0.66011434206742048, -0.65896129298203732, -0.65780669329707864,
    -0.65665054572942894, -0.65549285299961535, -0.65433361783180044,
    -0.65317284295377676, -0.6520105310969595, -0.650846684996381,
    -0.64968130739068319, -0.64851440102211244, -0.64734596863651206,
    -0.64617601298331628, -0.64500453681554393, -0.64383154288979139,
    -0.64265703396622686, -0.641481012808583, -0.64030348218415167,
    -0.63912444486377573, -0.637943903621844, -0.6367618612362842,
    -0.63557832048855611, -0.63439328416364549, -0.63320675505005719,
    -0.63201873593980906, -0.63082922962842447, -0.629638238914927,
    -0.6284457666018326, -0.62725181549514408, -0.62605638840434352,
    -0.62485948814238634, -0.62366111752569453, -0.62246127937415,
    -0.62125997651108755, -0.6200572117632891, -0.61885298796097632,
    -0.61764730793780387, -0.61644017453085365, -0.61523159058062682,
    -0.61402155893103849, -0.61281008242940971, -0.61159716392646191,
    -0.61038280627630948, -0.60916701233645321, -0.60794978496777363,
    -0.60673112703452448, -0.60551104140432555, -0.604289530948156,
    -0.60306659854034816, -0.60184224705858, -0.600616479383869,
    -0.59938929840056454, -0.59816070699634238, -0.59693070806219639,
    -0.59569930449243336, -0.59446649918466443, -0.5932322950397998,
    -0.591996694962041, -0.59075970185887416, -0.58952131864106394,
    -0.58828154822264522, -0.587040393520918, -0.58579785745643886,
    -0.58455394295301533, -0.58330865293769829, -0.58206199034077544,
    -0.58081395809576453, -0.57956455913940563, -0.57831379641165559,
    -0.57706167285567944, -0.57580819141784534, -0.57455335504771576,
    -0.5732971666980422, -0.572039629324757, -0.57078074588696726,
    -0.56952051934694714, -0.56825895267013149, -0.56699604882510868,
    -0.56573181078361312, -0.5644662415205195, -0.56319934401383409,
    -0.56193112124468936, -0.560661576197336, -0.55939071185913614,
    -0.5581185312205561, -0.5568450372751601, -0.55557023301960218,
    -0.55429412145362, -0.55301670558002747, -0.55173798840470734,
    -0.55045797293660481, -0.54917666218771966, -0.54789405917310019,
    -0.54661016691083486, -0.54532498842204646, -0.54403852673088382,
    -0.54275078486451589, -0.54146176585312344, -0.54017147272989285,
    -0.53887990853100842, -0.53758707629564539, -0.53629297906596318,
    -0.53499761988709715, -0.533701001807153, -0.5324031278771979,
    -0.531104001151255, -0.52980362468629461, -0.52850200154222848,
    -0.52719913478190128, -0.52589502747108463, -0.524589682678469,
    -0.52328310347565643, -0.52197529293715439, -0.52066625414036716,
    -0.51935599016558964, -0.51804450409599934, -0.51673179901764987,
    -0.51541787801946293, -0.51410274419322166, -0.512786400633563,
    -0.5114688504379703, -0.51015009670676681, -0.508830142543107,
    -0.50750899105297087, -0.50618664534515523, -0.50486310853126759,
    -0.50353838372571758, -0.50221247404571079, -0.50088538261124071,
    -0.49955711254508184, -0.49822766697278181, -0.49689704902265447,
    -0.49556526182577254, -0.49423230851595967, -0.49289819222978404,
    -0.4915629161065499, -0.49022648328829116, -0.48888889691976317,
    -0.487550160148436, -0.48621027612448642, -0.48486924800079106,
    -0.48352707893291874, -0.48218377207912272, -0.48083933060033396,
    -0.47949375766015295, -0.478147056424843, -0.47679923006332209,
    -0.47545028174715587, -0.47410021465054997, -0.47274903195034279,
    -0.47139673682599764, -0.47004333245959562, -0.46868882203582796,
    -0.46733320874198842, -0.46597649576796618, -0.46461868630623782,
    -0.46325978355186015, -0.46189979070246273, -0.46053871095824,
    -0.45917654752194409, -0.45781330359887717, -0.45644898239688392,
    -0.45508358712634384, -0.45371712100016387, -0.45234958723377089,
    -0.45098098904510386, -0.44961132965460654, -0.44824061228521989,
    -0.44686884016237416, -0.44549601651398174, -0.4441221445704292,
    -0.44274722756457, -0.44137126873171667, -0.43999427130963326,
    -0.43861623853852766, -0.43723717366104409, -0.43585707992225547,
    -0.43447596056965565, -0.43309381885315196, -0.43171065802505726,
    -0.43032648134008261, -0.42894129205532949, -0.42755509343028208,
    -0.42616788872679962, -0.42477968120910881, -0.42339047414379605,
    -0.42200027079979968, -0.42060907444840251, -0.41921688836322391,
    -0.41782371582021227, -0.41642956009763715, -0.41503442447608163,
    -0.4136383122384345, -0.41224122666988289, -0.41084317105790391,
    -0.40944414869225759, -0.40804416286497869, -0.40664321687036903,
    -0.40524131400498986, -0.40383845756765407, -0.40243465085941843,
    -0.40102989718357562, -0.39962419984564679, -0.39821756215337356,
    -0.39680998741671031, -0.39540147894781635, -0.3939920400610481,
    -0.39258167407295147, -0.39117038430225387, -0.38975817406985641,
    -0.38834504669882625, -0.38693100551438858, -0.38551605384391885,
    -0.38410019501693504, -0.38268343236508978, -0.38126576922216238,
    -0.37984720892405116, -0.37842775480876556, -0.37700741021641826,
    -0.37558617848921722, -0.37416406297145793, -0.37274106700951576,
    -0.37131719395183749, -0.3698924471489341, -0.36846682995337232,
    -0.36704034571976718, -0.36561299780477385, -0.36418478956707989,
    -0.36275572436739723, -0.36132580556845428, -0.35989503653498811,
    -0.35846342063373654, -0.35703096123343, -0.35559766170478385,
    -0.35416352542049034, -0.35272855575521073, -0.35129275608556709,
    -0.34985612979013492, -0.34841868024943456, -0.34698041084592368,
    -0.34554132496398909, -0.34410142598993881, -0.34266071731199438,
    -0.34121920232028236, -0.33977688440682685, -0.33833376696554113,
    -0.33688985339222005, -0.3354451470845316, -0.33399965144200938,
    -0.33255336986604422, -0.33110630575987643, -0.32965846252858749,
    -0.3282098435790925, -0.32676045232013173, -0.32531029216226293,
    -0.32385936651785285, -0.32240767880106985, -0.32095523242787521,
    -0.31950203081601569, -0.31804807738501495, -0.31659337555616585,
    -0.31513792875252244, -0.31368174039889152, -0.31222481392182488,
    -0.31076715274961147, -0.30930876031226873, -0.30784964004153487,
    -0.30638979537086092, -0.30492922973540237, -0.30346794657201132,
    -0.30200594931922808, -0.30054324141727345, -0.29907982630804048,
    -0.2976157074350862, -0.29615088824362379, -0.29468537218051433,
    -0.29321916269425863, -0.29175226323498926, -0.29028467725446233,
    -0.28881640820604948, -0.28734745954472951, -0.28587783472708062,
    -0.28440753721127188, -0.28293657045705539, -0.28146493792575794,
    -0.27999264308027322, -0.27851968938505306, -0.2770460803060999,
    -0.27557181931095814, -0.27409690986870638, -0.272621355449949,
    -0.271145159526808, -0.26966832557291509, -0.26819085706340318,
    -0.26671275747489837, -0.26523403028551179, -0.26375467897483135,
    -0.26227470702391359, -0.26079411791527551, -0.25931291513288623,
    -0.257831102162159, -0.25634868248994291, -0.25486565960451457,
    -0.25338203699557016, -0.25189781815421697, -0.25041300657296522,
    -0.24892760574572015, -0.24744161916777327, -0.24595505033579459,
    -0.24446790274782415, -0.24298017990326387, -0.24149188530286933,
    -0.2400030224487415, -0.23851359484431842, -0.2370236059943672,
    -0.23553305940497549, -0.23404195858354343, -0.23255030703877524,
    -0.23105810828067111, -0.22956536582051887, -0.22807208317088573,
    -0.22657826384561, -0.22508391135979283, -0.22358902922979,
    -0.22209362097320351, -0.22059769010887351, -0.2191012401568698,
    -0.21760427463848364, -0.21610679707621952, -0.21460881099378676,
    -0.21311031991609136, -0.21161132736922755, -0.21011183688046961,
    -0.20861185197826349, -0.20711137619221856, -0.20561041305309924,
    -0.20410896609281687, -0.20260703884442113, -0.2011046348420919,
    -0.19960175762113097, -0.19809841071795356, -0.19659459767008022,
    -0.19509032201612825, -0.19358558729580361, -0.19208039704989244,
    -0.19057475482025274, -0.18906866414980619, -0.1875621285825296,
    -0.18605515166344663, -0.18454773693861962, -0.18303988795514095,
    -0.18153160826112497, -0.18002290140569951, -0.17851377093899751,
    -0.17700422041214875, -0.17549425337727143, -0.17398387338746382,
    -0.17247308399679595, -0.17096188876030122, -0.16945029123396796,
    -0.16793829497473117, -0.1664259035404641, -0.16491312048996992,
    -0.16339994938297323, -0.16188639378011183, -0.16037245724292828,
    -0.15885814333386145, -0.15734345561623825, -0.15582839765426523,
    -0.1543129730130201, -0.15279718525844344, -0.15128103795733022,
    -0.14976453467732151, -0.14824767898689603, -0.14673047445536175,
    -0.14521292465284746, -0.14369503315029447, -0.14217680351944803,
    -0.14065823933284921, -0.1391393441638262, -0.13762012158648604,
    -0.1361005751757062, -0.13458070850712617, -0.13306052515713906,
    -0.13154002870288312, -0.13001922272223335, -0.12849811079379317,
    -0.12697669649688587, -0.12545498341154623, -0.12393297511851216,
    -0.1224106751992162, -0.12088808723577708, -0.11936521481099135,
    -0.11784206150832498, -0.11631863091190475, -0.11479492660651008,
    -0.11327095217756435, -0.11174671121112659, -0.11022220729388306,
    -0.10869744401313872, -0.10717242495680884, -0.10564715371341062,
    -0.10412163387205459, -0.10259586902243628, -0.10106986275482782,
    -0.099543618660069319, -0.0980171403295606, -0.096490431355252593,
    -0.094963495329638992, -0.093436335845747787, -0.091908956497132724,
    -0.090381360877864983, -0.0888535525825246, -0.087325535206192059,
    -0.0857973123444399, -0.084268887593324071, -0.082740264549375692,
    -0.081211446809592441, -0.079682437971430126, -0.078153241632794232,
    -0.076623861392031492, -0.0750943008479213, -0.073564563599667426,
    -0.072034653246889332, -0.070504573389613856, -0.068974327628266746,
    -0.067443919563664051, -0.0659133527970038, -0.064382630929857465,
    -0.0628517575641614, -0.061320736302208578, -0.059789570746639868,
    -0.058258264500435752, -0.056726821166907748, -0.055195244349689941,
    -0.05366353765273052, -0.052131704680283324, -0.050599749036899282,
    -0.049067674327418015, -0.0475354841569593, -0.046003182130914623,
    -0.044470771854938668, -0.04293825693494082, -0.041405640977076739,
    -0.039872927587739811, -0.038340120373552694, -0.036807222941358832,
    -0.035274238898213947, -0.03374117185137758, -0.032208025408304586,
    -0.030674803176636626, -0.029141508764193722, -0.02760814577896574,
    -0.0260747178291039, -0.024541228522912288, -0.023007681468839369,
    -0.021474080275469508, -0.019940428551514441, -0.01840672990580482,
    -0.01687298794728171, -0.0153392062849881, -0.013805388528060391,
    -0.012271538285719925, -0.010737659167264491, -0.00920375478205982,
    -0.007669828739531097, -0.0061358846491544753, -0.0046019261204485705,
    -0.0030679567629659761, -0.0015339801862847655, -0.0 };

  int ihi;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 4095; i++) {
    y[iy].re = x[ix];
    y[iy].im = 0.0;
    iy = 4096;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy].re = x[ix];
  y[iy].im = 0.0;
  for (i = 0; i <= 4095; i += 2) {
    temp_re = y[i + 1].re;
    temp_im = y[i + 1].im;
    y[i + 1].re = y[i].re - y[i + 1].re;
    y[i + 1].im = y[i].im - y[i + 1].im;
    y[i].re += temp_re;
    y[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 1024;
  iheight = 4093;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = y[i + iy].re;
      temp_im = y[i + iy].im;
      y[i + iy].re = y[i].re - temp_re;
      y[i + iy].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 2048; j += ju) {
      twid_re = dv14[j];
      twid_im = dv15[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
        temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
        y[i + iy].re = y[i].re - temp_re;
        y[i + iy].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
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
  double d0;
  double d1;
  int i;
  double y[7518];
  double b_y[7518];
  double a[3];
  static const double b_a[3] = { -0.97517981162796985, 1.9503596232562816,
    -0.97517981162830258 };

  static const double dv6[4] = { 0.975179811634754, -2.9255394349042629,
    2.9255394349042629, -0.975179811634754 };

  static const double dv7[4] = { 1.0, -2.949735839706348, 2.9007269883554381,
    -0.950975665016249 };

  d0 = 2.0 * x_in[0];
  d1 = 2.0 * x_in[7499];
  for (i = 0; i < 9; i++) {
    y[i] = d0 - x_in[9 - i];
  }

  memcpy(&y[9], &x_in[0], 7500U * sizeof(double));
  for (i = 0; i < 9; i++) {
    y[i + 7509] = d1 - x_in[7498 - i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv6, dv7, b_y, a, y);
  flipud(y);
  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 7518U * sizeof(double));
  filter(dv6, dv7, b_y, a, y);
  flipud(y);
  memcpy(&y_out[0], &y[9], 7500U * sizeof(double));
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
  static int c_data[14926];
  int c_size[1];
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
             iInflect_data, iInflect_size, iFinite_data, iFinite_size);
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
// Arguments    : int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void keepAtMostNpPeaks(int idx_data[], int idx_size[1])
{
  int b_idx_data[14926];
  int i7;
  if (idx_size[0] > 7463) {
    memcpy(&b_idx_data[0], &idx_data[0], 7463U * sizeof(int));
    idx_size[0] = 7463;
    for (i7 = 0; i7 < 7463; i7++) {
      idx_data[i7] = b_idx_data[i7];
    }
  }
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
// Arguments    : const double Y[2048]
//                const int iPk_data[]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void orderPeaks(const double Y[2048], const int iPk_data[], int idx_data[],
  int idx_size[1])
{
  int Y_size[1];
  int loop_ub;
  int i8;
  static double Y_data[4096];
  int s_data[4096];
  int s_size[1];
  int b_idx_data[4096];
  if (idx_size[0] != 0) {
    Y_size[0] = idx_size[0];
    loop_ub = idx_size[0];
    for (i8 = 0; i8 < loop_ub; i8++) {
      Y_data[i8] = Y[iPk_data[idx_data[i8] - 1] - 1];
    }

    sortIdx(Y_data, Y_size, s_data, s_size);
    loop_ub = s_size[0];
    for (i8 = 0; i8 < loop_ub; i8++) {
      b_idx_data[i8] = idx_data[s_data[i8] - 1];
    }

    idx_size[0] = s_size[0];
    loop_ub = s_size[0];
    for (i8 = 0; i8 < loop_ub; i8++) {
      idx_data[i8] = b_idx_data[i8];
    }
  }
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
// Arguments    : const double a[4096]
//                double b[4096]
// Return Type  : void
//
static void repmat(const double a[4096], double b[4096])
{
  memcpy(&b[0], &a[0], sizeof(double) << 12);
}

//
// Arguments    : const double X[2048]
//                double Y[2048]
// Return Type  : void
//
static void rescale_minmax(const double X[2048], double Y[2048])
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
    while ((!exitg1) && (ix < 2049)) {
      ixstart = ix;
      if (!rtIsNaN(X[ix - 1])) {
        mtmp = X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 2048) {
    while (ixstart + 1 < 2049) {
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
    while ((!exitg1) && (ix < 2049)) {
      ixstart = ix;
      if (!rtIsNaN(X[ix - 1])) {
        b_mtmp = X[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 2048) {
    while (ixstart + 1 < 2049) {
      if (X[ixstart] > b_mtmp) {
        b_mtmp = X[ixstart];
      }

      ixstart++;
    }
  }

  b_mtmp -= mtmp;
  for (ixstart = 0; ixstart < 2048; ixstart++) {
    Y[ixstart] = (X[ixstart] - mtmp) / b_mtmp;
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
  int i5;
  idx_size[0] = (short)x_size[0];
  loop_ub = (short)x_size[0];
  for (i5 = 0; i5 < loop_ub; i5++) {
    idx_data[i5] = 0;
  }

  b_mergesort(idx_data, x_data, x_size[0]);
}

//
// Arguments    : const double x[4096]
// Return Type  : double
//
static double sum(const double x[4096])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 4095; k++) {
    y += x[k + 1];
  }

  return y;
}

//
// if size(signals,2) > size(signals,1)
//      signals = signals.';
//  end
// Arguments    : const double signals[7251]
//                const double window[4096]
//                double CSM[2048]
//                double frequencies[2048]
// Return Type  : void
//
static void welch_psd(const double signals[7251], const double window[4096],
                      double CSM[2048], double frequencies[2048])
{
  double data_taper[4096];
  int i;
  double S[2048];
  int a;
  double dv13[4096];
  double B;
  double Data_Block[4096];
  static creal_T b_Data_Block[4096];

  //  Function for spectra estimation by Welch's method
  //  Developed by Luiz A. Baccala, Fl?vio Caduda and Luciano Caldas, all from
  //  Escola Polit?cnica - Poli-USP, with cooperation of Carlos Pagani and Felipe 
  //  Amaral from Escola de Engenharia de S?o Carlos - EESC-USP.
  //
  //  Cross-spectra matrix are estimated by Welch's method with 50% overlap and
  //  the window energy loss are compasated by a factor of 1/sum(Wi.^2) where
  //  Wi are the elements of the window [1]. Then, the spectra becomes:
  //  Sxy = fft(x)*conj(fft(y))/sum(Wi.^2)
  //
  //  Code was tested with a known- spectra signal from a white noise filtered
  //  by a filter. The variance (power) of the signal checks with the integral
  //  of the PSD estimated.
  //
  //  INPUT:
  //  -- signals: matrix of signals to perform the spectra estimatino. Size is
  //  [Samples x number of sensors];
  //  -- fs: samplerate in Hertz;
  //  -- window: data taper desired. Must be a vector. For best performance it
  //  should be a power of 2. For general applications do: window=hanning(1024); 
  //
  //  OUTPUT:
  //  -- CSM: Cross Spectral Matrix: Unilateral (0:fs/2) spectra. Welch's
  //  method is used with 50% overlap. Matrix size: sensors x sensors x
  //  windowsize/2
  //  -- frequencies: vector with all frequencies corresponding to each layer
  //  (3rd layer in depth) of CSM.
  //
  //  LAST REVISION: Aug - 18 - 2016
  //  ADDED 'fs' missing term in line 82, for calibration factor
  //  [1] Trobs,M.; Heinzel,G. "Improved spectrum estimation from digitized
  //  time series on a logarithmic frequency axis"
  //  doi:10.1016/j.measurement.2005.10.010
  // must be even, best if 2^n
  // ORIGINAL;
  repmat(window, data_taper);

  //  Data segmentation into blocks of size block_samples:
  for (i = 0; i < 2048; i++) {
    frequencies[i] = 0.06103515625 * (double)i;
    S[i] = 0.0;
  }

  // ORIGINAL
  //  S = zeros(ceil(block_samples/2),number_of_signals.^2);
  for (a = 0; a < 2; a++) {
    //  Retrieve current data block
    i = a << 11;
    memcpy(&Data_Block[0], &signals[i], sizeof(double) << 12);
    B = c_mean(Data_Block);
    for (i = 0; i < 4096; i++) {
      Data_Block[i] = (Data_Block[i] - B) * data_taper[i];
    }

    // Taper it
    fft(Data_Block, b_Data_Block);

    // FFT it,
    //  bilateral DFT
    //  viii
    // ORIGINAL
    //  Data_Block = Data_Block(1:ceil(block_samples/2),:);
    // All spectral combinations:
    // ORIGINAL
    //  P = zeros(ceil(block_samples/2)/2,number_of_signals.^2);
    //  THIS IS FOR WIND TUNNEL EESC-USP BEAMFORMING CODE
    //              P(:,c) = real(Data_Block(:,b).*conj(Data_Block(:,aa)));
    //  P(:,c) = Data_Block(:,b).*conj(Data_Block(:,aa));
    //  IS FOR FAN RIG BEAMFORMING CODE
    //  P(:,c) = Data_Block(:,aa).*conj(Data_Block(:,b)); % THIS IS THE ORIGINAL LINE 
    //  Sum the spectrums up ...
    for (i = 0; i < 2048; i++) {
      S[i] += b_Data_Block[i].re * b_Data_Block[i].re - b_Data_Block[i].im *
        -b_Data_Block[i].im;
    }
  }

  b_power(window, dv13);
  B = sum(dv13) * 250.0 * 2.0;

  //  Average them out
  //  for a = 1:sensors
  for (i = 0; i < 2048; i++) {
    CSM[i] = S[i] * 2.0 / B;
  }

  //  end
  //  clear S
  CSM[0] = (CSM[0] + CSM[0]) - CSM[0];
}

//
// get_hr_rr This function uses a variant of the Pan-Tompkins Algorithm to
// detect ECG QRS features from low frequency data:
//  Input: X (raw data, floats or doubles (preferred);
//  Outputs: Y ..
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
  static const double dv2[250] = { 0.0, 0.00015917615386623618,
    0.0006366032672731059, 0.0014319773601739749, 0.002544792014212871,
    0.003974338695163393, 0.0057197072040557351, 0.0077797862567046128,
    0.010153264191269051, 0.012838629803393287, 0.015834173308397981,
    0.019137987429907632, 0.022747968614222402, 0.026661818369660528,
    0.030877044730018455, 0.035390963841217371, 0.040200701670125349,
    0.045303195834467458, 0.050695197552658888, 0.05637327371231915,
    0.062333809056150435, 0.068573008483788556, 0.075086899468161272,
    0.0818713345848141, 0.088921994152595, 0.0962343889840151,
    0.10380386324353502, 0.11162559741195721, 0.11969461135503567,
    0.12800576749435055, 0.13655377407842811, 0.14533318855202326,
    0.15433842102141959, 0.1635637378135405, 0.17300326512660535,
    0.18265099277000596, 0.19250077799102322, 0.2025463493859454,
    0.21278131089310048, 0.22319914586525774, 0.23379322121880719,
    0.24455679165707467, 0.25548300396508339, 0.266564901373027,
    0.277795427985678, 0.289167433274908, 0.30067367663246208,
    0.31230683198008807, 0.3240594924340835, 0.33592417502129335,
    0.34789332544355345, 0.35995932288754645, 0.37211448487701004,
    0.38435107216420339, 0.39666129365752345, 0.40903731138212795,
    0.42147124547041054, 0.43395517917914878, 0.44648116393013132,
    0.45904122437105377, 0.47162736345346296, 0.48423156752451435,
    0.49684581142930129, 0.5094620636205095, 0.5220722912721385,
    0.53466846539404078, 0.54724256594401566, 0.55978658693420735,
    0.57229254152855535, 0.58475246712804829, 0.59715843044054884,
    0.60950253253195652, 0.621776913855496, 0.63397375925592647,
    0.64608530294548772, 0.658103833448412, 0.67002169851085669,
    0.68183130997313057, 0.69352514860110848, 0.70509576887376357,
    0.71653580372376424, 0.72783796922812072, 0.73899506924589131,
    0.75000000000000011, 0.76084575460024229, 0.77152542750460618,
    0.78203221891606156, 0.79235943911202356, 0.80250051270372791,
    0.81244898282281364, 0.82219851523243848, 0.83174290236031889,
    0.84107606725111883, 0.85019206743567521, 0.85908509871459637,
    0.867749498853821, 0.87617975118979063, 0.88437048814193309,
    0.89231649463022722, 0.9000127113956673, 0.90745423822151694,
    0.91463633705330016, 0.92155443501554213, 0.92820412732334,
    0.93458118008690994, 0.94068153300732438, 0.94650130196172277,
    0.95203678147635129, 0.95728444708585358, 0.96224095757731609,
    0.96690315711763231, 0.97126807726283637, 0.975332938848126,
    0.97909515375736833, 0.98255232657096658, 0.98570225609103379,
    0.98854293674290616, 0.9910725598521013, 0.99328951479591054,
    0.99519239002888882, 0.99677997398159246, 0.9980512558319915,
    0.99900542614906418, 0.99964187740816568, 0.99996020437784194,
    0.99996020437784194, 0.99964187740816568, 0.99900542614906418,
    0.9980512558319915, 0.99677997398159246, 0.99519239002888882,
    0.99328951479591054, 0.9910725598521013, 0.988542936742906,
    0.98570225609103379, 0.98255232657096669, 0.97909515375736844,
    0.975332938848126, 0.97126807726283637, 0.96690315711763231,
    0.96224095757731609, 0.9572844470858537, 0.95203678147635118,
    0.94650130196172289, 0.94068153300732438, 0.93458118008691,
    0.92820412732334023, 0.92155443501554224, 0.91463633705330027,
    0.90745423822151694, 0.9000127113956673, 0.89231649463022733,
    0.88437048814193342, 0.87617975118979063, 0.86774949885382113,
    0.85908509871459637, 0.85019206743567555, 0.841076067251119,
    0.83174290236031889, 0.82219851523243859, 0.81244898282281386,
    0.802500512703728, 0.79235943911202367, 0.78203221891606189,
    0.7715254275046064, 0.76084575460024229, 0.74999999999999978,
    0.73899506924589142, 0.72783796922812083, 0.71653580372376457,
    0.70509576887376357, 0.69352514860110859, 0.68183130997313079,
    0.67002169851085713, 0.658103833448412, 0.64608530294548794,
    0.63397375925592692, 0.621776913855496, 0.6095025325319563,
    0.59715843044054873, 0.58475246712804829, 0.57229254152855547,
    0.55978658693420769, 0.54724256594401566, 0.534668465394041,
    0.52207229127213894, 0.50946206362050994, 0.49684581142930107,
    0.48423156752451413, 0.47162736345346296, 0.45904122437105388,
    0.44648116393013154, 0.43395517917914878, 0.42147124547041065,
    0.40903731138212823, 0.39666129365752389, 0.3843510721642035,
    0.37211448487701027, 0.35995932288754645, 0.34789332544355345,
    0.33592417502129313, 0.32405949243408338, 0.31230683198008807,
    0.30067367663246231, 0.28916743327490835, 0.27779542798567813,
    0.26656490137302724, 0.25548300396508367, 0.24455679165707478,
    0.23379322121880697, 0.22319914586525763, 0.21278131089310048,
    0.20254634938594557, 0.19250077799102344, 0.18265099277000596,
    0.17300326512660547, 0.16356373781354072, 0.15433842102141992,
    0.14533318855202343, 0.13655377407842806, 0.12800576749435055,
    0.11969461135503573, 0.1116255974119571, 0.10380386324353502,
    0.096234388984015151, 0.088921994152595107, 0.081871334584814326,
    0.075086899468161328, 0.068573008483788722, 0.0623338090561506,
    0.056373273712319205, 0.050695197552658833, 0.0453031958344674,
    0.040200701670125349, 0.035390963841217482, 0.030877044730018621,
    0.026661818369660528, 0.022747968614222458, 0.019137987429907688,
    0.015834173308398092, 0.012838629803393342, 0.010153264191268996,
    0.0077797862567046128, 0.0057197072040557351, 0.0039743386951633375,
    0.002544792014212871, 0.0014319773601739749, 0.0006366032672731059,
    0.00015917615386623618, 0.0 };

  static double dv3[7251];
  static const double dv4[4096] = { 0.0, 5.8856149742769759E-7,
    2.3542446042079668E-6, 5.2970451633327365E-6, 9.41695624689931E-6,
    1.4713968155444235E-5, 2.118806841866494E-5, 2.8839241794864634E-5,
    3.7667470271229853E-5, 4.7672733064052508E-5, 5.8855006618452332E-5,
    7.1214264608543409E-5, 8.4750477937711732E-5, 9.9463614738226624E-5,
    0.00011535364037190687, 0.00013242051742962113, 0.000150664205731732,
    0.00017008466232815156, 0.00019068184149834133, 0.00021245569475147885,
    0.00023540617082656867, 0.00025953321569255339, 0.00028483677254836914,
    0.0003113167818232232, 0.00033897318117676045, 0.00036780590549889691,
    0.00039781488691037481, 0.00042900005476265157, 0.00046136133563817738,
    0.00049489865335056171, 0.00052961192894462883, 0.00056550108069686189,
    0.00060256602411534743, 0.00064080667194010843, 0.00068022293414321533,
    0.00072081471792911911, 0.00076258192773470679, 0.000805524465229801,
    0.00084964222931710465, 0.0008949351161324226, 0.00094140301904527268,
    0.000989045828658719, 0.0010378634328099268, 0.001087855716570163,
    0.0011390225622454064, 0.0011913638493761813, 0.0012448794547383346,
    0.0012995692523429248, 0.0013554331134367215, 0.0014124709065024832,
    0.0014706824972591237, 0.0015300677486623226, 0.0015906265209045256,
    0.0016523586714155547, 0.0017152640548627196, 0.0017793425231512616,
    0.0018445939254246868, 0.0019110181080651545, 0.0019786149146938659,
    0.002047384186171175, 0.0021173257605974216, 0.0021884394733128754,
    0.0022607251568984021, 0.0023341826411756861, 0.0024088117532077291,
    0.0024846123172992951, 0.0025615841549971874, 0.0026397270850906929,
    0.0027190409236122481, 0.002799525483837495, 0.0028811805762860576,
    0.0029640060087216535, 0.0030480015861528709, 0.0031331671108335013,
    0.0032195023822629287, 0.00330700719718674, 0.0033956813495969462,
    0.0034855246307328724, 0.0035765368290813226, 0.0036687177303771912,
    0.0037620671176039622, 0.0038565847709942092, 0.00395227046803015,
    0.0040491239834440917, 0.0041471450892189843, 0.0042463335545891434,
    0.0043466891460404167, 0.0044482116273111272, 0.0045509007593923512,
    0.0046547563005285841, 0.004759778006218407, 0.004865965629214819,
    0.0049733189195261263, 0.0050818376244161634, 0.0051915214884052374,
    0.0053023702532705719, 0.0054143836580469729, 0.0055275614390272176,
    0.0056419033297629984, 0.0057574090610653661, 0.0058740783610055081,
    0.0059919109549150806, 0.0061109065653872641, 0.00623106491227704,
    0.0063523857127021355, 0.0064748686810435774, 0.0065985135289462482,
    0.0067233199653198294, 0.0068492876963392457, 0.0069764164254454974,
    0.007104705853346216, 0.0072341556780166072, 0.0073647655946998958,
    0.0074965352959082132, 0.0076294644714233195, 0.0077635528082971028,
    0.0078987999908528, 0.0080352057006851663, 0.0081727696166616348,
    0.0083114914149229335, 0.0084513707688838036, 0.0085924073492337771,
    0.0087346008239381767, 0.0088779508582385036, 0.0090224571146534926,
    0.0091681192529799449, 0.0093149369302932827, 0.0094629098009486046,
    0.0096120375165814065, 0.0097623197261083039, 0.0099137560757280863,
    0.010066346208922272, 0.010220089766456109, 0.01037498638637957,
    0.010531035704027802, 0.010688237352022345, 0.010846590960271907,
    0.011006096155973089, 0.011166752563611437, 0.011328559804962279,
    0.011491517499091441, 0.011655625262356584, 0.011820882708407587,
    0.011987289448187777, 0.012154845089934752, 0.012323549239181331,
    0.01249340149875644, 0.012664401468786057, 0.01283654874669421,
    0.013009842927203863, 0.013184283602337921, 0.013359870361420001,
    0.013536602791075825, 0.013714480475233659, 0.013893502995125762,
    0.014073669929289101, 0.014254980853566301, 0.014437435341106863,
    0.014621032962368108, 0.014805773285116064, 0.014991655874426524,
    0.015178680292686153, 0.01536684609959349, 0.015556152852159888,
    0.01574660010471074, 0.015938187408886362, 0.016130914313643108,
    0.016324780365254365, 0.016519785107311835, 0.016715928080726417,
    0.016913208823729209, 0.017111626871872843, 0.017311181758032479,
    0.017511873012406753, 0.017713700162519108, 0.017916662733218791,
    0.018120760246682022, 0.01832599222241299, 0.01853235817724519,
    0.01873985762534236, 0.018948490078199709, 0.019158255044645245,
    0.019369152030840553, 0.019581180540282295, 0.019794340073803152,
    0.020008630129573157, 0.020224050203100863, 0.020440599787234337,
    0.020658278372162664, 0.020877085445416887, 0.021097020491871343,
    0.021318082993744769, 0.021540272430601692, 0.021763588279353541,
    0.021988030014259863, 0.022213597106929606, 0.022440289026322391,
    0.02266810523874957, 0.022897045207875832, 0.023127108394720097,
    0.023358294257657064, 0.02359060225241838, 0.023824031832093862,
    0.024058582447132826, 0.024294253545345479, 0.02453104457190397,
    0.024768954969344115, 0.025007984177566278, 0.025248131633836823,
    0.025489396772789663, 0.025731779026427259, 0.025975277824122123,
    0.02621989259261831, 0.02646562275603237, 0.026712467735855117,
    0.026960426950952687, 0.02720949981756815, 0.027459685749322671,
    0.027710984157217067, 0.027963394449633028, 0.028216916032334671,
    0.028471548308469763, 0.028727290678571327, 0.028984142540558977,
    0.02924210328974014, 0.029501172318811775, 0.029761349017861705,
    0.030022632774369951, 0.03028502297321034, 0.03054851899665173,
    0.030813120224359669, 0.031078826033397733, 0.031345635798229243,
    0.031613548890718213, 0.0318825646801314, 0.032152682533139465,
    0.03242390181381849, 0.032696221883651622, 0.032969642101530361,
    0.033244161823756335, 0.033519780404042576, 0.033796497193515074,
    0.034074311540714552, 0.034353222791597582, 0.034633230289538519,
    0.034914333375330842, 0.035196531387188756, 0.0354798236607487,
    0.035764209529070945, 0.036049688322641216, 0.036336259369372237,
    0.036623921994605291, 0.036912675521111771, 0.037202519269094791,
    0.037493452556190909, 0.037785474697471622, 0.038078585005444976,
    0.038372782790057181, 0.038668067358694269, 0.038964438016183711,
    0.039261894064796188, 0.039560434804246869, 0.039860059531697467,
    0.04016076754175768, 0.0404625581264868, 0.040765430575395667,
    0.041069384175447976, 0.041374418211062192, 0.0416805319641132,
    0.041987724713933805, 0.042295995737316794, 0.042605344308516369,
    0.042915769699249873, 0.043227271178699567, 0.043539848013514293,
    0.043853499467811363, 0.044168224803178113, 0.044484023278673568,
    0.044800894150830606, 0.04511883667365707, 0.045437850098638155,
    0.045757933674737794, 0.046079086648400436, 0.046401308263553043,
    0.0467245977616067, 0.047048954381458286, 0.047374377359492625,
    0.047700865929583947, 0.048028419323097815, 0.048357036768893025,
    0.048686717493323262, 0.049017460720238992, 0.04934926567098924,
    0.049682131564423637, 0.050016057616893927, 0.050351043042256072,
    0.05068708705187186, 0.051024188854611185, 0.051362347656853435,
    0.0517015626624896, 0.052041833072924093, 0.052383158087076609,
    0.052725536901384262, 0.053068968709802933, 0.053413452703809761,
    0.0537589880724047, 0.054105574002112411, 0.054453209676984415,
    0.054801894278600827, 0.055151626986072289, 0.055502406976042029,
    0.055854233422687527, 0.056207105497722953, 0.05656102237040056,
    0.056915983207512955, 0.057271987173395045, 0.057629033429925924,
    0.057987121136530817, 0.058346249450183241, 0.058706417525406784,
    0.059067624514277162, 0.05942986956642432, 0.059793151829034275,
    0.060157470446851213, 0.060522824562179556, 0.060889213314885726,
    0.061256635842400542, 0.061625091279720989, 0.061994578759412278,
    0.062365097411610115, 0.062736646364022319, 0.063109224741931313,
    0.06348283166819596, 0.063857466263253615, 0.064233127645122345,
    0.064609814929402765, 0.064987527229280362, 0.0653662636555275,
    0.065746023316505531, 0.06612680531816667, 0.066508608764056509,
    0.066891432755315727, 0.067275276390682592, 0.067660138766494682,
    0.068046018976691269, 0.068432916112815545, 0.068820829264016337,
    0.069209757517050718, 0.0695996999562859, 0.0699906556637015,
    0.07038262371889159, 0.07077560319906695, 0.071169593179057133,
    0.071564592731312993, 0.071960600925908225, 0.0723576168305422,
    0.07275563951054187, 0.073154668028863834, 0.073554701446096937,
    0.073955738820463968, 0.074357779207824382, 0.074760821661676191,
    0.0751648652331583, 0.075569908971052813, 0.075975951921787022,
    0.076382993129436028, 0.076791031635724649, 0.077200066480029916,
    0.077610096699383124, 0.078021121328472332, 0.078433139399644414,
    0.078846149942907562, 0.07926015198593328, 0.079675144554058885,
    0.080091126670289892, 0.080508097355302011, 0.0809260556274437,
    0.0813450005027383, 0.081764930994886631, 0.082185846115268912,
    0.082607744872947531, 0.0830306262746689, 0.083454489324866266,
    0.0838793330256617, 0.08430515637686864, 0.084731958375994176,
    0.085159738018241338, 0.085588494296511775, 0.086018226201407588,
    0.086448932721234217, 0.086880612842002547, 0.087313265547431462,
    0.087746889818949958, 0.088181484635699914, 0.088617048974538148,
    0.08905358181003914, 0.089491082114497245, 0.089929548857928976,
    0.090368981008075888, 0.090809377530406521, 0.091250737388119174,
    0.091693059542144184, 0.092136342951146366, 0.092580586571527512,
    0.093025789357429, 0.093471950260733738, 0.09391906823106938,
    0.094367142215810162, 0.094816171160079676, 0.095266154006753423,
    0.095717089696461033, 0.096168977167588932, 0.096621815356282892,
    0.097075603196450477, 0.097530339619763373, 0.097986023555660329,
    0.0984426539313491, 0.098900229671809559, 0.0993587496997958,
    0.099818212935838924, 0.10027861829824947, 0.1007399647031198,
    0.10120225106432723, 0.10166547629353584, 0.10212963930019947,
    0.10259473899156418, 0.10306077427267102, 0.10352774404635823,
    0.10399564721326404, 0.1044644826718294, 0.1049342493183002,
    0.10540494604673029, 0.10587657174898368, 0.10634912531473756,
    0.1068226056314846, 0.10729701158453558, 0.10777234205702219,
    0.10824859592989966, 0.10872577208194911, 0.10920386938978055,
    0.10968288672783538, 0.11016282296838881, 0.11064367698155297,
    0.11112544763527915, 0.11160813379536083, 0.11209173432543601,
    0.11257624808699007, 0.11306167393935834, 0.11354801073972914,
    0.1140352573431459, 0.1145234126025102, 0.11501247536858461,
    0.11550244448999497, 0.11599331881323344, 0.1164850971826612,
    0.116977778440511, 0.1174713614268898, 0.11796584497978202,
    0.11846122793505165, 0.11895750912644537, 0.11945468738559523,
    0.11995276154202117, 0.12045173042313423, 0.12095159285423884,
    0.12145234765853596, 0.1219539936571255, 0.1224565296690095,
    0.12295995451109443, 0.12346426699819452, 0.12396946594303399,
    0.12447555015625039, 0.12498251844639685, 0.12549036961994536,
    0.12599910248128937, 0.12650871583274648, 0.12701920847456161,
    0.12753057920490946, 0.12804282681989759, 0.12855595011356896,
    0.12906994787790527, 0.1295848189028293, 0.13010056197620795,
    0.1306171758838553, 0.13113465940953495, 0.13165301133496343,
    0.13217223043981285, 0.13269231550171373, 0.13321326529625782,
    0.13373507859700123, 0.13425775417546704, 0.13478129080114842,
    0.13530568724151137, 0.13583094226199754, 0.1363570546260276,
    0.13688402309500342, 0.13741184642831178, 0.13794052338332652,
    0.1384700527154123, 0.1390004331779266, 0.13953166352222346,
    0.14006374249765585, 0.14059666885157912, 0.14113044132935348,
    0.14166505867434714, 0.14220051962793945, 0.14273682292952361,
    0.1432739673165096, 0.14381195152432757, 0.14435077428643028,
    0.14489043433429638, 0.14543093039743338, 0.14597226120338064,
    0.14651442547771226, 0.14705742194404015, 0.14760124932401697,
    0.14814590633733948, 0.14869139170175094, 0.14923770413304466,
    0.14978484234506678, 0.15033280504971946, 0.15088159095696357,
    0.15143119877482214, 0.15198162720938313, 0.15253287496480272,
    0.15308494074330803, 0.15363782324520031, 0.15419152116885826,
    0.15474603321074076, 0.15530135806538997, 0.15585749442543473,
    0.15641444098159313, 0.15697219642267596, 0.15753075943558986,
    0.15809012870533989, 0.15865030291503335, 0.15921128074588231,
    0.15977306087720688, 0.16033564198643857, 0.16089902274912288,
    0.1614632018389231, 0.16202817792762281, 0.1625939496851293,
    0.1631605157794766, 0.16372787487682894, 0.16429602564148332,
    0.16486496673587303, 0.16543469682057088, 0.16600521455429207,
    0.16657651859389755, 0.16714860759439693, 0.16772148020895217,
    0.16829513508888005, 0.16886957088365606, 0.16944478624091686,
    0.17002077980646407, 0.17059755022426715, 0.17117509613646659,
    0.17175341618337736, 0.17233250900349173, 0.1729123732334828,
    0.1734930075082074, 0.17407441046070976, 0.17465658072222429,
    0.17523951692217898, 0.17582321768819859, 0.17640768164610798,
    0.17699290741993512, 0.1775788936319147, 0.17816563890249093,
    0.17875314185032121, 0.17934140109227892, 0.17993041524345726,
    0.18052018291717203, 0.18111070272496493, 0.1817019732766072,
    0.18229399318010236, 0.18288676104169005, 0.18348027546584894,
    0.18407453505529991, 0.18466953841100986, 0.1852652841321944,
    0.18586177081632166, 0.18645899705911523, 0.18705696145455764,
    0.18765566259489352, 0.1882550990706332, 0.18885526947055575,
    0.18945617238171242, 0.19005780638942993, 0.19066017007731373,
    0.19126326202725169, 0.19186708081941689, 0.19247162503227139,
    0.19307689324256938, 0.19368288402536071, 0.19428959595399392,
    0.1948970276001199, 0.19550517753369506, 0.19611404432298501,
    0.19672362653456749, 0.19733392273333594, 0.19794493148250308,
    0.1985566513436039, 0.19916908087649948, 0.19978221863938006,
    0.20039606318876846, 0.20101061307952361, 0.20162586686484396,
    0.20224182309627065, 0.20285848032369125, 0.203475837095343,
    0.20409389195781613, 0.2047126434560575, 0.20533209013337372,
    0.20595223053143519, 0.20657306319027874, 0.20719458664831159,
    0.20781679944231451, 0.20843970010744578, 0.20906328717724376,
    0.20968755918363119, 0.21031251465691825, 0.21093815212580597,
    0.21156447011738982, 0.21219146715716319, 0.21281914176902089,
    0.2134474924752624, 0.21407651779659564, 0.21470621625214026,
    0.21533658635943115, 0.21596762663442209, 0.21659933559148897,
    0.21723171174343359, 0.21786475360148683, 0.21849845967531245,
    0.21913282847301052, 0.21976785850112091, 0.22040354826462655,
    0.22103989626695753, 0.22167690100999393, 0.2223145609940701,
    0.22295287471797748, 0.22359184067896848, 0.22423145737276012,
    0.22487172329353738, 0.22551263693395673, 0.22615419678514981,
    0.22679640133672702, 0.2274392490767807, 0.22808273849188926,
    0.22872686806712028, 0.2293716362860343, 0.23001704163068826,
    0.23066308258163942, 0.2313097576179482, 0.23195706521718262,
    0.23260500385542132, 0.23325357200725755, 0.23390276814580196,
    0.23455259074268753, 0.23520303826807171, 0.2358541091906412,
    0.23650580197761495, 0.2371581150947476, 0.23781104700633388,
    0.23846459617521121, 0.2391187610627642, 0.23977354012892771,
    0.24042893183219105, 0.24108493462960046, 0.24174154697676431,
    0.24239876732785542, 0.24305659413561564, 0.24371502585135874,
    0.24437406092497432, 0.24503369780493212, 0.24569393493828418,
    0.24635477077067014, 0.24701620374631983, 0.24767823230805747,
    0.24834085489730467, 0.24900406995408508, 0.24966787591702722,
    0.25033227122336865, 0.25099725430895936, 0.25166282360826553,
    0.25232897755437345, 0.25299571457899261, 0.25366303311246025,
    0.2543309315837442, 0.25499940842044755, 0.25566846204881089,
    0.25633809089371773, 0.25700829337869691, 0.257679067925927,
    0.25835041295623967, 0.25902232688912352, 0.25969480814272805,
    0.26036785513386673, 0.26104146627802155, 0.261715639989346,
    0.26239037468066961, 0.26306566876350068, 0.2637415206480308,
    0.26441792874313863, 0.265094891456393, 0.26577240719405715,
    0.2664504743610922, 0.2671290913611617, 0.26780825659663371,
    0.26848796846858664, 0.26916822537681129, 0.26984902571981589,
    0.27053036789482854, 0.27121225029780227, 0.27189467132341855,
    0.27257762936508989, 0.2732611228149654, 0.27394515006393316,
    0.274629709501625, 0.27531479951641935, 0.27600041849544593,
    0.27668656482458892, 0.27737323688849136, 0.27806043307055783,
    0.27874815175295975, 0.27943639131663833, 0.280125150141308,
    0.2808144266054613, 0.28150421908637163, 0.2821945259600982,
    0.28288534560148837, 0.28357667638418316, 0.28426851668061948,
    0.28496086486203553, 0.28565371929847289, 0.28634707835878204,
    0.28704094041062539, 0.28773530382048051, 0.28843016695364554,
    0.28912552817424153, 0.28982138584521733, 0.29051773832835237,
    0.29121458398426209, 0.29191192117240006, 0.29260974825106334,
    0.29330806357739492, 0.29400686550738891, 0.29470615239589393,
    0.29540592259661624, 0.29610617446212489, 0.29680690634385454,
    0.29750811659211029, 0.29820980355607035, 0.29891196558379129,
    0.29961460102221071, 0.30031770821715231, 0.3010212855133283,
    0.301725331254345, 0.30242984378270565, 0.30313482143981413,
    0.30384026256597985, 0.30454616550042063, 0.30525252858126772,
    0.30595935014556819, 0.30666662852929061, 0.30737436206732732,
    0.3080825490934998, 0.30879118794056148, 0.309500276940202,
    0.31020981442305184, 0.3109197987186848, 0.31163022815562347,
    0.31234110106134194, 0.31305241576227094, 0.31376417058380024,
    0.31447636385028421, 0.31518899388504451, 0.31590205901037488,
    0.31661555754754456, 0.31732948781680237, 0.31804384813738118,
    0.31875863682750061, 0.31947385220437263, 0.320189492584204,
    0.32090555628220158, 0.3216220416125749, 0.32233894688854148,
    0.32305627042232982, 0.32377401052518406, 0.32449216550736726,
    0.325210733678166, 0.32592971334589416, 0.32664910281789639,
    0.32736890040055333, 0.32808910439928407, 0.32880971311855156,
    0.3295307248618653, 0.33025213793178643, 0.33097395062993107,
    0.33169616125697465, 0.33241876811265575, 0.33314176949577984,
    0.33386516370422414, 0.33458894903494041, 0.33531312378396017,
    0.33603768624639774, 0.33676263471645512, 0.33748796748742493,
    0.33821368285169562, 0.33893977910075462, 0.33966625452519283,
    0.34039310741470841, 0.34112033605811071, 0.34184793874332486,
    0.34257591375739488, 0.34330425938648867, 0.34403297391590137,
    0.3447620556300599, 0.34549150281252627, 0.34622131374600262,
    0.34695148671233433, 0.34768201999251475, 0.34841291186668877,
    0.3491441606141571, 0.34987576451338054, 0.35060772184198308,
    0.35134003087675753, 0.352072689893668, 0.35280569716785526,
    0.35353905097363958, 0.3542727495845257, 0.355006791273207,
    0.35574117431156821, 0.35647589697069143, 0.35721095752085852,
    0.35794635423155652, 0.35868208537148016, 0.35941814920853776,
    0.36015454400985364, 0.36089126804177374, 0.36162831956986796,
    0.36236569685893594, 0.36310339817301041, 0.3638414217753605,
    0.36457976592849739, 0.36531842889417732, 0.366057408933406,
    0.3667967043064424, 0.36753631327280367, 0.36827623409126808,
    0.36901646501988034, 0.36975700431595432, 0.37049785023607862,
    0.3712390010361199, 0.37198045497122639, 0.37272221029583352,
    0.3734642652636665, 0.3742066181277458, 0.37494926714038967,
    0.37569221055322005, 0.3764354466171651, 0.37717897358246466,
    0.37792278969867293, 0.37866689321466396, 0.37941128237863531,
    0.38015595543811131, 0.38090091063994874, 0.38164614623033954,
    0.38239166045481621, 0.3831374515582544, 0.38388351778487873,
    0.38462985737826555, 0.38537646858134822, 0.38612334963641981,
    0.38687049878513885, 0.3876179142685327, 0.38836559432700096,
    0.38911353720032127, 0.38986174112765182, 0.39061020434753679,
    0.39135892509790937, 0.39210790161609693, 0.39285713213882434,
    0.393606614902219, 0.39435634814181358, 0.39510633009255197,
    0.39585655898879224, 0.39660703306431072, 0.39735775055230704,
    0.39810870968540746, 0.39885990869566967, 0.39961134581458607,
    0.40036301927308909, 0.40111492730155429, 0.40186706812980549,
    0.40261943998711797, 0.40337204110222324, 0.40412486970331352,
    0.40487792401804457, 0.40563120227354166, 0.40638470269640226,
    0.4071384235127013, 0.40789236294799419, 0.40864651922732237,
    0.40940089057521617, 0.41015547521570017, 0.4109102713722963,
    0.41166527726802871, 0.41242049112542811, 0.41317591116653479,
    0.41393153561290458, 0.41468736268561135, 0.41544339060525265,
    0.41619961759195229, 0.41695604186536628, 0.41771266164468557,
    0.4184694751486413, 0.41922648059550827, 0.41998367620310917,
    0.42074106018881974, 0.42149863076957134, 0.42225638616185673,
    0.4230143245817331, 0.42377244424482735, 0.42453074336633884,
    0.4252892201610452, 0.42604787284330525, 0.42680669962706425,
    0.42756569872585715, 0.42832486835281314, 0.42908420672066072,
    0.42984371204172994, 0.43060338252795888, 0.43136321639089614,
    0.4321232118417061, 0.43288336709117226, 0.43364368034970235,
    0.43440414982733178, 0.43516477373372853, 0.43592555027819668,
    0.43668647766968105, 0.43744755411677172, 0.438208777827707,
    0.4389701470103794, 0.43973165987233837, 0.44049331462079561,
    0.44125510946262808, 0.44201704260438346, 0.44277911225228395,
    0.4435413166122299, 0.44430365388980481, 0.44506612229027909,
    0.4458287200186149, 0.44659144527946915, 0.44735429627719925,
    0.44811727121586614, 0.44888036829923944, 0.44964358573080043,
    0.45040692171374774, 0.45117037445100089, 0.45193394214520421,
    0.4526976229987314, 0.45346141521368988, 0.4542253169919252,
    0.45498932653502416, 0.45575344204432078, 0.45651766172089892,
    0.45728198376559775, 0.45804640637901478, 0.45881092776151139,
    0.45957554611321633, 0.46034025963402952, 0.46110506652362754,
    0.4618699649814666, 0.46263495320678794, 0.46340002939862057,
    0.46416519175578735, 0.46493043847690768, 0.46569576776040272,
    0.46646117780449881, 0.46722666680723252, 0.46799223296645465,
    0.4687578744798338, 0.46952358954486173, 0.4702893763588567,
    0.47105523311896841, 0.47182115802218128, 0.47258714926532,
    0.47335320504505246, 0.47411932355789538, 0.47488550300021676,
    0.47565174156824197, 0.47641803745805722, 0.477184388865613,
    0.47795079398672985, 0.47871725101710144, 0.47948375815229971,
    0.48025031358777787, 0.48101691551887615, 0.48178356214082485,
    0.4825502516487496, 0.48331698223767411, 0.48408375210252635,
    0.48485055943814159, 0.48561740243926627, 0.48638427930056372,
    0.4871511882166169, 0.48791812738193391, 0.48868509499095086,
    0.48945208923803768, 0.490219108317501, 0.4909861504235894,
    0.49175321375049708, 0.49252029649236806, 0.49328739684330131,
    0.49405451299735337, 0.49482164314854443, 0.49558878549086127,
    0.4963559382182624, 0.4971230995246812, 0.49789026760403143,
    0.49865744065021061, 0.49942461685710487, 0.50019179441859263,
    0.500958971528549, 0.50172614638085067, 0.502493317169379,
    0.50326048208802543, 0.50402763933069494, 0.50479478709131087,
    0.50556192356381835, 0.50632904694218961, 0.50709615542042741,
    0.50786324719256992, 0.50863032045269418, 0.50939737339492108,
    0.51016440421341958, 0.51093141110241, 0.51169839225616975,
    0.51246534586903636, 0.51323227013541262, 0.5139991632497698,
    0.51476602340665312, 0.515532848800685, 0.51629963762656994,
    0.51706638807909833, 0.517833098353151, 0.51859976664370355,
    0.51936639114582983, 0.5201329700547076, 0.52089950156562115,
    0.52166598387396723, 0.5224324151752574, 0.52319879366512423,
    0.52396511753932407, 0.52473138499374206, 0.52549759422439613,
    0.5262637434274412, 0.52702983079917376, 0.52779585453603539,
    0.528561812834618, 0.52932770389166728, 0.53009352590408743,
    0.53085927706894465, 0.53162495558347278, 0.53239055964507587,
    0.53315608745133392, 0.533921537200006, 0.53468690708903521,
    0.53545219531655264, 0.53621740008088115, 0.53698251958054088,
    0.53774755201425217, 0.53851249558094061, 0.53927734847974063,
    0.54004210891000048, 0.54080677507128616, 0.54157134516338512,
    0.54233581738631154, 0.54310018994030962, 0.5438644610258585,
    0.54462862884367569, 0.54539269159472259, 0.54615664748020709,
    0.54692049470158965, 0.54768423146058554, 0.54844785595917067,
    0.54921136639958545, 0.54997476098433806, 0.55073803791621,
    0.5515011953982597, 0.55226423163382676, 0.55302714482653592,
    0.55378993318030212, 0.55455259489933373, 0.55531512818813777,
    0.55607753125152293, 0.556839802294605, 0.55760193952281067,
    0.55836394114188093, 0.55912580535787693, 0.55988753037718275,
    0.56064911440651055, 0.56141055565290365, 0.56217185232374256,
    0.56293300262674739, 0.56369400476998333, 0.5644548569618637,
    0.56521555741115559, 0.5659761043269832, 0.56673649591883157,
    0.56749673039655213, 0.56825680597036565, 0.56901672085086774,
    0.56977647324903136, 0.57053606137621271, 0.57129548344415426,
    0.57205473766499015, 0.57281382225124855, 0.573572735415858,
    0.57433147537215024, 0.57509004033386446, 0.5758484285151525,
    0.57660663813058177, 0.5773646673951407, 0.57812251452424135,
    0.57888017773372558, 0.57963765523986766, 0.5803949452593794,
    0.5811520460094135, 0.58190895570756873, 0.58266567257189372,
    0.58342219482089019, 0.58417852067351927, 0.5849346483492035,
    0.58569057606783259, 0.58644630204976655, 0.58720182451584058,
    0.58795714168736879, 0.588712251786149, 0.5894671530344664,
    0.59022184365509722, 0.59097632187131477, 0.59173058590689109,
    0.59248463398610363, 0.59323846433373728, 0.59399207517509034,
    0.59474546473597723, 0.59549863124273383, 0.59625157292222064,
    0.59700428800182792, 0.5977567747094793, 0.59850903127363564,
    0.59926105592330048, 0.60001284688802214, 0.6007644023979003,
    0.60151572068358794, 0.60226679997629762, 0.60301763850780332,
    0.6037682345104467, 0.60451858621714, 0.60526869186137111,
    0.60601854967720648, 0.60676815789929628, 0.60751751476287874,
    0.608266618503783, 0.609015467358435, 0.60976405956385993,
    0.61051239335768814, 0.61126046697815717, 0.61200827866411811,
    0.61275582665503814, 0.61350310919100548, 0.61425012451273309,
    0.61499687086156329, 0.61574334647947149, 0.61648954960907032,
    0.61723547849361415, 0.61798113137700283, 0.61872650650378624,
    0.61947160211916763, 0.62021641646900894, 0.6209609477998338,
    0.62170519435883242, 0.62244915439386539, 0.62319282615346749,
    0.62393620788685289, 0.62467929784391762, 0.62542209427524553,
    0.62616459543211078, 0.62690679956648343, 0.627648704931032,
    0.6283903097791288, 0.62913161236485382, 0.62987261094299818,
    0.6306133037690691, 0.63135368909929335, 0.632093765190622,
    0.63283353030073342, 0.633572982688039, 0.63431212061168551,
    0.6350509423315609, 0.63578944610829669, 0.63652763020327363,
    0.63726549287862466, 0.63800303239723966, 0.63874024702276888,
    0.639477135019628, 0.64021369465300138, 0.64094992418884633,
    0.64168582189389756, 0.64242138603567067, 0.643156614882467,
    0.64389150670337669, 0.64462605976828369, 0.64536027234786963,
    0.64609414271361731, 0.64682766913781531, 0.647560849893562,
    0.64829368325476977, 0.64902616749616826, 0.64975830089330966,
    0.6504900817225715, 0.65122150826116232, 0.65195257878712343,
    0.65268329157933525, 0.65341364491752052, 0.6541436370822471,
    0.65487326635493437, 0.65560253101785537, 0.65633142935414179,
    0.65705995964778752, 0.65778812018365307, 0.65851590924746939,
    0.65924332512584227, 0.65997036610625526, 0.66069703047707551,
    0.66142331652755626, 0.66214922254784137, 0.66287474682896952,
    0.66359988766287792, 0.66432464334240726, 0.66504901216130363,
    0.66577299241422516, 0.666496582396744, 0.66721978040535168,
    0.6679425847374616, 0.66866499369141486, 0.66938700556648345,
    0.67010861866287308, 0.67082983128172957, 0.67155064172514078,
    0.67227104829614182, 0.67299104929871811, 0.67371064303781036,
    0.67442982781931771, 0.67514860195010251, 0.67586696373799371,
    0.67658491149179056, 0.67730244352126778, 0.67801955813717829,
    0.678736253651258, 0.67945252837622927, 0.68016838062580542,
    0.68088380871469378, 0.681598810958601, 0.68231338567423561,
    0.68302753117931325, 0.68374124579255957, 0.68445452783371474,
    0.68516737562353758, 0.68587978748380873, 0.68659176173733583,
    0.687303296707956, 0.68801439072054116, 0.68872504210100072,
    0.68943524917628685, 0.69014501027439712, 0.69085432372437972,
    0.691563187856336, 0.69227160100142526, 0.69297956149186923,
    0.69368706766095423, 0.69439411784303706, 0.69510071037354726,
    0.69580684358899281, 0.69651251582696183, 0.69721772542612848,
    0.697922470726256, 0.69862675006820052, 0.69933056179391528,
    0.70003390424645418, 0.70073677576997639, 0.701439174709749,
    0.70214109941215253, 0.70284254822468317, 0.70354351949595839,
    0.70424401157571892, 0.70494402281483426, 0.70564355156530567,
    0.70634259618027062, 0.707041155014006, 0.70773922642193232,
    0.70843680876061788, 0.70913390038778268, 0.70983049966230083,
    0.7105266049442065, 0.71122221459469692, 0.71191732697613574,
    0.71261194045205722, 0.71330605338717068, 0.71399966414736293,
    0.71469277109970442, 0.71538537261245061, 0.71607746705504671,
    0.71676905279813274, 0.71746012821354543, 0.71815069167432344,
    0.71884074155471023, 0.71953027623015875, 0.720219294077335,
    0.72090779347412126, 0.72159577279962062, 0.72228323043416054,
    0.72297016475929654, 0.72365657415781615, 0.72434245701374333,
    0.72502781171234054, 0.72571263664011432, 0.72639693018481855,
    0.72708069073545789, 0.72776391668229157, 0.72844660641683778,
    0.72912875833187685, 0.72981037082145561, 0.73049144228089069,
    0.73117197110677168, 0.73185195569696693, 0.73253139445062521,
    0.7332102857681807, 0.733888628051356, 0.73456641970316661,
    0.73524365912792433, 0.735920344731241, 0.73659647492003222,
    0.73727204810252112, 0.73794706268824228, 0.738621517088045,
    0.73929540971409857, 0.73996873897989324, 0.74064150330024625,
    0.74131370109130534, 0.74198533077055118, 0.7426563907568029,
    0.74332687947021947, 0.74399679533230567, 0.7446661367659152,
    0.74533490219525356, 0.74600309004588183, 0.74667069874472214,
    0.74733772672005916, 0.74800417240154482, 0.74867003422020217,
    0.74933531060842851, 0.74999999999999989, 0.75066410083007384,
    0.75132761153519367, 0.7519905305532919, 0.752652856323694,
    0.75331458728712219, 0.7539757218856995, 0.7546362585629518,
    0.75529619576381335, 0.75595553193463, 0.7566142655231618,
    0.75727239497858856, 0.757929918751511, 0.75858683529395621,
    0.75924314305938156, 0.75989884050267731, 0.7605539260801697,
    0.76120839824962649, 0.76186225547025943, 0.76251549620272741,
    0.76316811890914127, 0.76382012205306626, 0.76447150409952713,
    0.76512226351501, 0.76577239876746717, 0.7664219083263204,
    0.76707079066246431, 0.7677190442482702, 0.7683666675575902,
    0.769013659065759, 0.76966001724959954, 0.77030574058742607,
    0.77095082755904665, 0.77159527664576832, 0.772239086330399,
    0.77288225509725217, 0.77352478143215075, 0.77416666382242982,
    0.7748079007569395, 0.77544849072605126, 0.77608843222165813,
    0.77672772373718058, 0.7773663637675694, 0.77800435080930841,
    0.7786416833604195, 0.7792783599204649, 0.77991437899055138,
    0.78054973907333358, 0.78118443867301779, 0.78181847629536461,
    0.782451850447694, 0.78308455963888723, 0.78371660237939089,
    0.78434797718122118, 0.78497868255796666, 0.7856087170247914,
    0.78623807909843957, 0.78686676729723759, 0.78749478014109942,
    0.78812211615152816, 0.7887487738516199, 0.789374751766069,
    0.79000004842116911, 0.7906246623448181, 0.79124859206652165,
    0.791871836117395, 0.79249439303016844, 0.79311626133919033,
    0.7937374395804293, 0.79435792629147917, 0.79497772001156153,
    0.79559681928152914, 0.79621522264387079, 0.79683292864271227,
    0.79744993582382162, 0.79806624273461257, 0.79868184792414687,
    0.7992967499431386, 0.79991094734395685, 0.80052443868062984,
    0.80113722250884845, 0.80174929738596878, 0.80236066187101551,
    0.80297131452468662, 0.80358125390935564, 0.80419047858907478,
    0.80479898712957987, 0.80540677809829164, 0.8060138500643208,
    0.80662020159847059, 0.80722583127324055, 0.80783073766282909,
    0.80843491934313816, 0.80903837489177488, 0.80964110288805724,
    0.81024310191301474, 0.8108443705493934, 0.81144490738165942,
    0.81204471099600128, 0.81264377998033366, 0.8132421129243006,
    0.81383970841927944, 0.81443656505838324, 0.815032681436465,
    0.81562805615011946, 0.81622268779768858, 0.81681657497926308,
    0.81740971629668635, 0.81800211035355819, 0.81859375575523674,
    0.81918465110884331, 0.81977479502326522, 0.82036418610915818,
    0.82095282297895089, 0.821540704246847, 0.8221278285288296,
    0.82271419444266369, 0.8232998006079, 0.82388464564587671,
    0.82446872817972539, 0.825052046834372, 0.825634600236541,
    0.82621638701475808, 0.82679740579935412, 0.82737765522246831,
    0.8279571339180507, 0.82853584052186524, 0.82911377367149508,
    0.829690932006343, 0.83026731416763622, 0.83084291879842975,
    0.83141774454360839, 0.83199179004989066, 0.83256505396583291,
    0.8331375349418304, 0.83370923163012223, 0.83428014268479367,
    0.83485026676177965, 0.835419602518868, 0.83598814861570236,
    0.83655590371378508, 0.83712286647648115, 0.83768903556902075,
    0.83825440965850262, 0.83881898741389693, 0.83938276750604879,
    0.83994574860768134, 0.84050792939339858, 0.84106930853968831,
    0.84162988472492639, 0.84218965662937828, 0.84274862293520314,
    0.84330678232645728, 0.84386413348909572, 0.84442067511097663,
    0.84497640588186451, 0.84553132449343227, 0.846085429639265,
    0.846638720014863, 0.84719119431764423, 0.84774285124694859,
    0.84829368950404027, 0.84884370779210971, 0.84939290481627916,
    0.84994127928360363, 0.85048882990307473, 0.85103555538562348,
    0.85158145444412359, 0.85212652579339454, 0.85267076815020437,
    0.85321418023327245, 0.85375676076327323, 0.85429850846283861,
    0.85483942205656116, 0.85537950027099752, 0.85591874183467032,
    0.85645714547807239, 0.85699470993366933, 0.85753143393590192,
    0.85806731622119, 0.858602355527935, 0.85913655059652216,
    0.85966990016932554, 0.86020240299070883, 0.860734057807029,
    0.86126486336664065, 0.86179481841989625, 0.86232392171915151,
    0.862852172018767, 0.86337956807511151, 0.86390610864656525,
    0.86443179249352209, 0.86495661837839277, 0.86548058506560821,
    0.866003691321622, 0.866525935914913, 0.86704731761598963,
    0.86756783519739045, 0.86808748743368913, 0.86860627310149674,
    0.86912419097946414, 0.86964123984828512, 0.87015741849069961,
    0.8706727256914959, 0.8711871602375143, 0.87170072091764927,
    0.87221340652285251, 0.872725215846136, 0.87323614768257507,
    0.87374620082931009, 0.87425537408555054, 0.87476366625257729,
    0.87527107613374577, 0.87577760253448822, 0.87628324426231685,
    0.87678800012682656, 0.877291868939698, 0.87779484951469988,
    0.87829694066769259, 0.87879814121662969, 0.8792984499815617,
    0.879797865784639, 0.880296387450114, 0.88079401380434363,
    0.88129074367579352, 0.881786575895039, 0.88228150929476934,
    0.88277554270978953, 0.8832686749770231, 0.88376090493551573,
    0.88425223142643672, 0.884742653293083, 0.88523216938088056,
    0.88572077853738806, 0.88620847961229965, 0.886695271457447,
    0.88718115292680211, 0.88766612287648061, 0.888150180164744,
    0.88863332365200209, 0.88911555220081684, 0.88959686467590315,
    0.89007725994413289, 0.89055673687453785, 0.89103529433831108,
    0.891512931208811, 0.89198964636156264, 0.8924654386742612,
    0.89294030702677463, 0.89341425030114618, 0.8938872673815963,
    0.894359357154527, 0.89483051850852247, 0.89530075033435308,
    0.89577005152497757, 0.89623842097554518, 0.89670585758339927,
    0.897172360248079, 0.89763792787132246, 0.89810255935706884,
    0.89856625361146125, 0.89902900954284926, 0.89949082606179209,
    0.89995170208105957, 0.900411636515636, 0.90087062828272324,
    0.90132867630174118, 0.9017857794943327, 0.90224193678436393,
    0.90269714709792837, 0.90315140936334926, 0.90360472251118151,
    0.904057085474214, 0.90450849718747373, 0.90495895658822589,
    0.90540846261597863, 0.90585701421248388, 0.90630461032174092,
    0.90675124988999856, 0.90719693186575734, 0.90764165519977213,
    0.908085418845055, 0.908528221756877, 0.908970062892771, 0.90941094121253485,
    0.9098508556782321, 0.91028980525419567, 0.91072778890703088,
    0.91116480560561586, 0.91160085432110638, 0.91203593402693606,
    0.91247004369882034, 0.91290318231475842, 0.91333534885503553,
    0.91376654230222487, 0.91419676164119135, 0.91462600585909282,
    0.91505427394538263, 0.91548156489181265, 0.91590787769243454,
    0.91633321134360313, 0.91675756484397863, 0.91718093719452831,
    0.91760332739852968, 0.91802473446157218, 0.91844515739155974,
    0.91886459519871388, 0.91928304689557439, 0.91970051149700294,
    0.9201169880201856, 0.92053247548463379, 0.92094697291218819,
    0.92136047932701959, 0.92177299375563215, 0.92218451522686573,
    0.92259504277189741, 0.92300457542424419, 0.92341311221976574,
    0.92382065219666565, 0.92422719439549472, 0.9246327378591529,
    0.92503728163289067, 0.92544082476431244, 0.92584336630337893,
    0.92624490530240777, 0.9266454408160778, 0.92704497190142976,
    0.92744349761786893, 0.92784101702716815, 0.92823752919346869,
    0.92863303318328339, 0.92902752806549871, 0.92942101291137647,
    0.92981348679455678, 0.93020494879105931, 0.93059539797928637,
    0.93098483344002458, 0.931373254256447, 0.93176065951411546,
    0.93214704830098261, 0.93253241970739442, 0.93291677282609153,
    0.93330010675221242, 0.93368242058329465, 0.93406371341927719,
    0.9344439843625032, 0.93482323251772126, 0.9352014569920879,
    0.93557865689516961, 0.935954831338945, 0.936329979437807, 0.936704100308565,
    0.93707719307044568, 0.9374492568450975, 0.93782029075659068,
    0.93819029393142017, 0.93855926549850721, 0.9389272045892022,
    0.939294110337286, 0.93965998187897237, 0.94002481835290919,
    0.94038861890018222, 0.94075138266431524, 0.941113108791273,
    0.94147379642946349, 0.94183344472973907, 0.94219205284539909,
    0.94254961993219211, 0.94290614514831717, 0.94326162765442612,
    0.94361606661362574, 0.94396946119147929, 0.9443218105560095,
    0.944673113877699, 0.94502337032949324, 0.94537257908680261,
    0.94572073932750378, 0.94606785023194173, 0.946413910982932,
    0.94675892076576262, 0.94710287876819566, 0.94744578418046932,
    0.94778763619529993, 0.94812843400788371, 0.94846817681589868,
    0.94880686381950685, 0.94914449422135594, 0.94948106722658054,
    0.94981658204280506, 0.95015103788014521, 0.95048443395120952,
    0.95081676947110183, 0.95114804365742245, 0.95147825573027045,
    0.95180740491224547, 0.95213549042844936, 0.952462511506488,
    0.95278846737647327, 0.95311335727102509, 0.9534371804252727,
    0.95375993607685661, 0.95408162346593062, 0.95440224183516364,
    0.95472179042974115, 0.95504026849736678, 0.95535767528826521,
    0.95567401005518282, 0.95598927205338935, 0.95630346054068094,
    0.95661657477738038, 0.95692861402633966, 0.95723957755294187,
    0.95754946462510215, 0.95785827451327032, 0.95816600649043182,
    0.95847265983210961, 0.95877823381636684, 0.959082727723807,
    0.95938614083757612, 0.95968847244336541, 0.95998972182941211,
    0.96028988828650075, 0.96058897110796571, 0.96088696958969244,
    0.96118388303011937, 0.96147971073023908, 0.96177445199360045,
    0.96206810612630989, 0.9623606724370336, 0.96265215023699824,
    0.9629425388399937, 0.96323183756237363, 0.96352004572305727,
    0.96380716264353239, 0.96409318764785468, 0.96437812006265111,
    0.96466195921712061, 0.96494470444303593, 0.96522635507474552,
    0.96550691044917425, 0.96578636990582578, 0.96606473278678384,
    0.96634199843671387, 0.96661816620286412, 0.96689323543506778,
    0.9671672054857442, 0.96744007570990065, 0.96771184546513334,
    0.96798251411162939, 0.96825208101216842, 0.96852054553212352,
    0.96878790703946294, 0.96905416490475249, 0.969319318501155,
    0.96958336720443417, 0.96984631039295421, 0.970108147447682,
    0.97036887775218916, 0.970628500692652, 0.9708870156578544,
    0.97114442203918849, 0.97140071923065652, 0.97165590662887147,
    0.9719099836330598, 0.97216294964506167, 0.97241480406933278,
    0.97266554631294588, 0.97291517578559206, 0.97316369189958207,
    0.97341109406984794, 0.973657381713944, 0.97390255425204875,
    0.97414661110696554, 0.97438955170412456, 0.97463137547158385,
    0.97487208184003082, 0.97511167024278333, 0.97535014011579158,
    0.97558749089763874, 0.97582372202954271, 0.976058832955357,
    0.97629282312157306, 0.9765256919773202, 0.97675743897436818,
    0.97698806356712709, 0.97721756521265035, 0.9774459433706344,
    0.977673197503421, 0.97789932707599769, 0.9781243315560002,
    0.97834821041371256, 0.97857096312206882, 0.97879258915665424,
    0.97901308799570685, 0.9792324591201178, 0.97945070201343376,
    0.97966781616185727, 0.9798838010542481, 0.98009865618212455,
    0.98031238103966523, 0.98052497512370884, 0.98073643793375687,
    0.98094676897197353, 0.98115596774318825, 0.98136403375489534,
    0.98157096651725639, 0.98177676554310067, 0.98198143034792662,
    0.98218496044990311, 0.9823873553698701, 0.98258861463134017,
    0.98278873776049946, 0.98298772428620906, 0.98318557374000548,
    0.98338228565610275, 0.98357785957139243, 0.98377229502544539,
    0.98396559156051278, 0.98415774872152717, 0.98434876605610322,
    0.98453864311453887, 0.98472737944981725, 0.98491497461760646,
    0.98510142817626123, 0.985286739686824, 0.985470908713026, 0.985653934821288,
    0.98583581758072159, 0.98601655656312981, 0.98619615134300875,
    0.98637460149754819, 0.9865519066066325, 0.98672806625284193,
    0.98690308002145311, 0.98707694750044084, 0.98724966828047811,
    0.98742124195493786, 0.9875916681198933, 0.98776094637411949,
    0.98792907631909377, 0.98809605755899677, 0.9882618897007136,
    0.98842657235383458, 0.98859010513065626, 0.98875248764618229,
    0.98891371951812435, 0.98907380036690284, 0.989232729815648,
    0.989390507490201, 0.98954713301911434, 0.9897026060336529,
    0.989856926167795, 0.99001009305823318, 0.99016210634437463,
    0.990312965668343, 0.99046267067497817, 0.99061122101183774,
    0.99075861632919771, 0.9909048562800532, 0.99104994052011941,
    0.99119386870783233, 0.99133664050434978, 0.99147825557355151,
    0.99161871358204112, 0.99175801419914555, 0.99189615709691736,
    0.9920331419501337, 0.99216896843629887, 0.99230363623564377,
    0.99243714503112734, 0.9925694945084369, 0.99270068435598935,
    0.99283071426493152, 0.992959583929141, 0.9930872930452268,
    0.99321384131253021, 0.99333922843312583, 0.99346345411182124,
    0.99358651805615861, 0.99370841997641524, 0.993829159585604,
    0.99394873659947425, 0.9940671507365122, 0.99418440171794165,
    0.9943004892677253, 0.99441541311256421, 0.99452917298189969,
    0.99464176860791265, 0.99475319972552556, 0.99486346607240206,
    0.994972567388948, 0.99508050341831211, 0.9951872739063865,
    0.99529287860180715, 0.99539731725595448, 0.99550058962295429,
    0.99560269545967794, 0.9957036345257434, 0.99580340658351507,
    0.99590201139810519, 0.99599944873737356, 0.99609571837192878,
    0.99619082007512838, 0.99628475362307978, 0.99637751879464009,
    0.99646911537141736, 0.99655954313777073, 0.996648801880811,
    0.996736891390401, 0.99682381145915655, 0.99690956188244617,
    0.99699414245839257, 0.99707755298787215, 0.997159793274516,
    0.99724086312471, 0.99732076234759637, 0.99739949075507217,
    0.9974770481617915, 0.99755343438516531, 0.99762864924536132,
    0.99770269256530553, 0.99777556417068158, 0.997847263889932,
    0.99791779155425775, 0.99798714699761959, 0.99805533005673741,
    0.998122340571092, 0.99818817838292373, 0.99825284333723441,
    0.99831633528178676, 0.99837865406710491, 0.99843979954647555,
    0.99849977157594694, 0.99855857001433, 0.99861619472319907,
    0.99867264556689128, 0.99872792241250741, 0.99878202512991221,
    0.99883495359173446, 0.99888670767336762, 0.99893728725297,
    0.99898669221146474, 0.99903492243254022, 0.999081977802651,
    0.99912785821101668, 0.99917256354962392, 0.99921609371322517,
    0.99925844859933977, 0.99929962810825379, 0.9993396321430208,
    0.99937846060946112, 0.99941611341616332, 0.99945259047448309,
    0.99948789169854479, 0.99952201700524035, 0.99955496631423069,
    0.99958673954794486, 0.99961733663158081, 0.99964675749310572,
    0.99967500206325544, 0.99970207027553526, 0.99972796206622,
    0.99975267737435414, 0.99977621614175161, 0.99979857831299657,
    0.99981976383544269, 0.99983977265921431, 0.99985860473720545,
    0.999876260025081, 0.99989273848127591, 0.999908040066996,
    0.99992216474621753, 0.99993511248568734, 0.99994688325492354,
    0.99995747702621474, 0.99996689377462045, 0.99997513347797151,
    0.99998219611686956, 0.99998808167468756, 0.99999279013756914,
    0.99999632149442974, 0.99999867573695544, 0.99999985285960391,
    0.99999985285960391, 0.99999867573695544, 0.99999632149442974,
    0.99999279013756914, 0.99998808167468756, 0.99998219611686956,
    0.99997513347797151, 0.99996689377462045, 0.99995747702621474,
    0.99994688325492354, 0.99993511248568734, 0.99992216474621753,
    0.999908040066996, 0.99989273848127591, 0.999876260025081,
    0.99985860473720545, 0.99983977265921431, 0.99981976383544269,
    0.99979857831299657, 0.99977621614175161, 0.99975267737435414,
    0.99972796206622, 0.99970207027553526, 0.99967500206325544,
    0.99964675749310572, 0.99961733663158081, 0.99958673954794486,
    0.99955496631423069, 0.99952201700524035, 0.99948789169854479,
    0.99945259047448309, 0.99941611341616332, 0.99937846060946112,
    0.9993396321430208, 0.99929962810825379, 0.99925844859933977,
    0.99921609371322517, 0.99917256354962392, 0.99912785821101668,
    0.99908197780265084, 0.99903492243254022, 0.99898669221146474,
    0.99893728725297, 0.99888670767336762, 0.99883495359173446,
    0.9987820251299121, 0.99872792241250741, 0.99867264556689128,
    0.99861619472319907, 0.99855857001433, 0.99849977157594694,
    0.99843979954647555, 0.998378654067105, 0.99831633528178676,
    0.99825284333723441, 0.99818817838292373, 0.998122340571092,
    0.99805533005673752, 0.99798714699761959, 0.99791779155425775,
    0.997847263889932, 0.99777556417068158, 0.99770269256530553,
    0.99762864924536132, 0.99755343438516531, 0.9974770481617915,
    0.99739949075507217, 0.99732076234759637, 0.99724086312471016,
    0.997159793274516, 0.99707755298787215, 0.99699414245839257,
    0.99690956188244617, 0.99682381145915655, 0.996736891390401,
    0.996648801880811, 0.99655954313777073, 0.99646911537141736,
    0.99637751879464009, 0.99628475362307978, 0.99619082007512838,
    0.99609571837192878, 0.99599944873737356, 0.99590201139810519,
    0.99580340658351507, 0.9957036345257434, 0.99560269545967794,
    0.99550058962295429, 0.99539731725595448, 0.99529287860180715,
    0.9951872739063865, 0.99508050341831211, 0.994972567388948,
    0.99486346607240206, 0.99475319972552556, 0.99464176860791276,
    0.99452917298189969, 0.99441541311256421, 0.9943004892677253,
    0.99418440171794176, 0.9940671507365122, 0.99394873659947425,
    0.99382915958560414, 0.99370841997641524, 0.99358651805615872,
    0.99346345411182124, 0.99333922843312583, 0.99321384131253032,
    0.9930872930452268, 0.992959583929141, 0.99283071426493152,
    0.99270068435598935, 0.9925694945084369, 0.99243714503112734,
    0.99230363623564377, 0.99216896843629887, 0.99203314195013381,
    0.99189615709691736, 0.99175801419914555, 0.99161871358204112,
    0.99147825557355151, 0.99133664050434978, 0.99119386870783233,
    0.99104994052011941, 0.9909048562800532, 0.99075861632919771,
    0.99061122101183785, 0.99046267067497817, 0.99031296566834293,
    0.99016210634437463, 0.99001009305823318, 0.989856926167795,
    0.9897026060336529, 0.98954713301911434, 0.98939050749020119,
    0.989232729815648, 0.98907380036690284, 0.98891371951812435,
    0.9887524876461824, 0.98859010513065626, 0.98842657235383458,
    0.98826188970071349, 0.98809605755899677, 0.98792907631909377,
    0.98776094637411949, 0.98759166811989341, 0.987421241954938,
    0.98724966828047811, 0.98707694750044084, 0.98690308002145311,
    0.98672806625284193, 0.98655190660663261, 0.9863746014975483,
    0.98619615134300886, 0.98601655656312981, 0.98583581758072159,
    0.985653934821288, 0.985470908713026, 0.985286739686824, 0.98510142817626123,
    0.98491497461760646, 0.98472737944981736, 0.984538643114539,
    0.98434876605610322, 0.98415774872152717, 0.98396559156051289,
    0.98377229502544539, 0.98357785957139243, 0.98338228565610275,
    0.98318557374000548, 0.98298772428620906, 0.98278873776049946,
    0.98258861463134006, 0.9823873553698701, 0.98218496044990311,
    0.98198143034792662, 0.98177676554310067, 0.98157096651725628,
    0.98136403375489545, 0.98115596774318825, 0.98094676897197353,
    0.98073643793375687, 0.98052497512370884, 0.98031238103966523,
    0.98009865618212466, 0.9798838010542481, 0.97966781616185727,
    0.97945070201343387, 0.9792324591201178, 0.97901308799570685,
    0.97879258915665435, 0.97857096312206893, 0.97834821041371267,
    0.9781243315560002, 0.97789932707599769, 0.977673197503421,
    0.9774459433706344, 0.97721756521265046, 0.9769880635671272,
    0.97675743897436818, 0.97652569197732042, 0.97629282312157306,
    0.976058832955357, 0.97582372202954271, 0.97558749089763874,
    0.97535014011579169, 0.97511167024278345, 0.97487208184003082,
    0.97463137547158385, 0.97438955170412456, 0.97414661110696554,
    0.97390255425204875, 0.97365738171394411, 0.97341109406984794,
    0.97316369189958218, 0.97291517578559206, 0.97266554631294588,
    0.97241480406933278, 0.97216294964506178, 0.97190998363305992,
    0.97165590662887158, 0.97140071923065641, 0.9711444220391886,
    0.9708870156578544, 0.97062850069265194, 0.97036887775218916,
    0.97010814744768215, 0.96984631039295421, 0.96958336720443428,
    0.969319318501155, 0.96905416490475249, 0.96878790703946316,
    0.96852054553212352, 0.96825208101216842, 0.9679825141116295,
    0.96771184546513345, 0.96744007570990076, 0.96716720548574431,
    0.96689323543506767, 0.96661816620286412, 0.96634199843671387,
    0.966064732786784, 0.96578636990582578, 0.96550691044917425,
    0.96522635507474563, 0.96494470444303615, 0.96466195921712061,
    0.96437812006265122, 0.96409318764785479, 0.9638071626435325,
    0.96352004572305738, 0.96323183756237352, 0.96294253883999381,
    0.96265215023699846, 0.96236067243703372, 0.96206810612631,
    0.96177445199360045, 0.96147971073023908, 0.96118388303011948,
    0.96088696958969244, 0.96058897110796559, 0.96028988828650075,
    0.95998972182941211, 0.95968847244336553, 0.95938614083757612,
    0.95908272772380687, 0.958778233816367, 0.95847265983210983,
    0.95816600649043171, 0.95785827451327044, 0.95754946462510226,
    0.95723957755294187, 0.95692861402633977, 0.95661657477738027,
    0.956303460540681, 0.95598927205338946, 0.95567401005518282,
    0.95535767528826532, 0.95504026849736678, 0.954721790429741,
    0.95440224183516376, 0.95408162346593062, 0.95375993607685661,
    0.95343718042527281, 0.9531133572710252, 0.95278846737647349,
    0.952462511506488, 0.95213549042844936, 0.95180740491224558,
    0.95147825573027056, 0.95114804365742245, 0.95081676947110183,
    0.95048443395120952, 0.95015103788014521, 0.94981658204280506,
    0.94948106722658054, 0.949144494221356, 0.94880686381950707,
    0.94846817681589879, 0.94812843400788371, 0.94778763619529993,
    0.94744578418046932, 0.94710287876819577, 0.94675892076576273,
    0.946413910982932, 0.94606785023194173, 0.94572073932750378,
    0.94537257908680283, 0.94502337032949335, 0.94467311387769892,
    0.94432181055600961, 0.94396946119147951, 0.94361606661362563,
    0.94326162765442612, 0.94290614514831717, 0.94254961993219222,
    0.9421920528453992, 0.941833444729739, 0.94147379642946349,
    0.94111310879127319, 0.94075138266431524, 0.94038861890018222,
    0.9400248183529093, 0.93965998187897237, 0.93929411033728616,
    0.93892720458920231, 0.93855926549850721, 0.93819029393142017,
    0.93782029075659068, 0.93744925684509761, 0.93707719307044579,
    0.93670410030856488, 0.93632997943780727, 0.93595483133894519,
    0.93557865689516961, 0.9352014569920879, 0.93482323251772126,
    0.93444398436250331, 0.93406371341927741, 0.93368242058329454,
    0.93330010675221253, 0.93291677282609164, 0.93253241970739453,
    0.93214704830098272, 0.93176065951411546, 0.931373254256447,
    0.93098483344002469, 0.93059539797928648, 0.93020494879105931,
    0.92981348679455689, 0.92942101291137658, 0.92902752806549882,
    0.9286330331832835, 0.92823752919346858, 0.92784101702716826,
    0.927443497617869, 0.92704497190142965, 0.9266454408160778,
    0.92624490530240788, 0.92584336630337893, 0.92544082476431266,
    0.92503728163289067, 0.924632737859153, 0.92422719439549494,
    0.92382065219666576, 0.92341311221976574, 0.92300457542424419,
    0.92259504277189741, 0.922184515226866, 0.92177299375563226,
    0.92136047932701959, 0.92094697291218819, 0.92053247548463391,
    0.92011698802018571, 0.91970051149700294, 0.91928304689557427,
    0.918864595198714, 0.91844515739156, 0.91802473446157218,
    0.91760332739852979, 0.91718093719452842, 0.91675756484397875,
    0.91633321134360335, 0.91590787769243454, 0.91548156489181265,
    0.91505427394538286, 0.91462600585909293, 0.91419676164119146,
    0.913766542302225, 0.91333534885503553, 0.91290318231475864,
    0.91247004369882045, 0.91203593402693606, 0.91160085432110649,
    0.91116480560561608, 0.91072778890703088, 0.91028980525419578,
    0.909850855678232, 0.909410941212535, 0.90897006289277127,
    0.90852822175687686, 0.90808541884505511, 0.90764165519977225,
    0.90719693186575734, 0.90675124988999878, 0.90630461032174092,
    0.90585701421248377, 0.90540846261597863, 0.904958956588226,
    0.90450849718747373, 0.90405708547421426, 0.9036047225111814,
    0.90315140936334948, 0.90269714709792859, 0.90224193678436382,
    0.90178577949433281, 0.9013286763017414, 0.90087062828272335,
    0.90041163651563616, 0.89995170208105946, 0.8994908260617922,
    0.89902900954284948, 0.89856625361146114, 0.89810255935706884,
    0.89763792787132257, 0.89717236024807911, 0.89670585758339949,
    0.89623842097554518, 0.89577005152497746, 0.89530075033435319,
    0.89483051850852258, 0.894359357154527, 0.89388726738159641,
    0.89341425030114607, 0.89294030702677474, 0.89246543867426142,
    0.89198964636156264, 0.89151293120881125, 0.8910352943383113,
    0.890556736874538, 0.89007725994413289, 0.889596864675903, 0.889115552200817,
    0.88863332365200232, 0.888150180164744, 0.88766612287648072,
    0.88718115292680211, 0.886695271457447, 0.8862084796123, 0.88572077853738818,
    0.88523216938088045, 0.8847426532930831, 0.88425223142643683,
    0.88376090493551573, 0.8832686749770231, 0.88277554270978942,
    0.88228150929476956, 0.88178657589503917, 0.88129074367579352,
    0.88079401380434375, 0.880296387450114, 0.879797865784639,
    0.8792984499815617, 0.87879814121662958, 0.8782969406676927,
    0.8777948495147001, 0.87729186893969813, 0.87678800012682667,
    0.876283244262317, 0.87577760253448833, 0.87527107613374611,
    0.8747636662525774, 0.87425537408555054, 0.8737462008293102,
    0.87323614768257518, 0.87272521584613627, 0.87221340652285262,
    0.87170072091764927, 0.87118716023751452, 0.87067272569149612,
    0.87015741849069961, 0.86964123984828534, 0.86912419097946425,
    0.86860627310149685, 0.86808748743368924, 0.86756783519739034,
    0.86704731761598963, 0.86652593591491323, 0.866003691321622,
    0.86548058506560832, 0.86495661837839288, 0.86443179249352209,
    0.86390610864656547, 0.86337956807511151, 0.862852172018767,
    0.86232392171915162, 0.86179481841989625, 0.86126486336664065,
    0.86073405780702927, 0.86020240299070871, 0.85966990016932576,
    0.85913655059652239, 0.85860235552793485, 0.85806731622119026,
    0.85753143393590214, 0.85699470993366944, 0.8564571454780725,
    0.85591874183467032, 0.85537950027099763, 0.85483942205656138,
    0.85429850846283872, 0.85375676076327334, 0.85321418023327256,
    0.85267076815020437, 0.85212652579339476, 0.85158145444412359,
    0.85103555538562348, 0.85048882990307484, 0.84994127928360375,
    0.84939290481627927, 0.84884370779210983, 0.84829368950404016,
    0.84774285124694893, 0.84719119431764445, 0.84663872001486284,
    0.84608542963926514, 0.84553132449343238, 0.84497640588186462,
    0.84442067511097663, 0.84386413348909561, 0.84330678232645728,
    0.84274862293520347, 0.84218965662937839, 0.8416298847249265,
    0.84106930853968853, 0.84050792939339858, 0.83994574860768156,
    0.8393827675060489, 0.83881898741389693, 0.83825440965850273,
    0.83768903556902086, 0.83712286647648138, 0.83655590371378508,
    0.83598814861570236, 0.83541960251886827, 0.83485026676177987,
    0.83428014268479367, 0.83370923163012223, 0.8331375349418304,
    0.83256505396583291, 0.83199179004989077, 0.83141774454360817,
    0.83084291879842986, 0.83026731416763644, 0.829690932006343,
    0.82911377367149519, 0.82853584052186546, 0.82795713391805059,
    0.82737765522246853, 0.82679740579935435, 0.82621638701475841,
    0.82563460023654089, 0.825052046834372, 0.82446872817972539,
    0.8238846456458766, 0.8232998006079, 0.82271419444266392,
    0.82212782852882982, 0.82154070424684722, 0.82095282297895089,
    0.8203641861091584, 0.81977479502326522, 0.81918465110884342,
    0.81859375575523674, 0.81800211035355808, 0.81740971629668646,
    0.81681657497926341, 0.81622268779768881, 0.81562805615011968,
    0.81503268143646479, 0.81443656505838313, 0.81383970841927966,
    0.81324211292430082, 0.81264377998033366, 0.8120447109960014,
    0.81144490738165953, 0.81084437054939351, 0.810243101913015,
    0.80964110288805724, 0.809038374891775, 0.80843491934313794,
    0.80783073766282909, 0.80722583127324077, 0.80662020159847092,
    0.806013850064321, 0.80540677809829186, 0.80479898712958,
    0.80419047858907466, 0.80358125390935564, 0.80297131452468684,
    0.80236066187101562, 0.80174929738596878, 0.80113722250884867,
    0.80052443868063039, 0.79991094734395718, 0.79929674994313882,
    0.79868184792414687, 0.79806624273461257, 0.79744993582382162,
    0.79683292864271238, 0.7962152226438709, 0.79559681928152948,
    0.79497772001156153, 0.79435792629147928, 0.79373743958042942,
    0.79311626133919044, 0.79249439303016855, 0.79187183611739487,
    0.79124859206652154, 0.79062466234481832, 0.79000004842116955,
    0.7893747517660693, 0.78874877385162012, 0.78812211615152783,
    0.78749478014109942, 0.786866767297238, 0.78623807909843968,
    0.78560871702479163, 0.78497868255796677, 0.7843479771812214,
    0.78371660237939089, 0.78308455963888757, 0.782451850447694,
    0.78181847629536472, 0.78118443867301779, 0.78054973907333358,
    0.7799143789905516, 0.77927835992046512, 0.77864168336041972,
    0.77800435080930863, 0.77736636376756962, 0.77672772373718058,
    0.77608843222165835, 0.77544849072605126, 0.77480790075693973,
    0.77416666382242971, 0.77352478143215087, 0.77288225509725261,
    0.77223908633039917, 0.77159527664576855, 0.77095082755904665,
    0.770305740587426, 0.76966001724959943, 0.769013659065759,
    0.7683666675575902, 0.76771904424827053, 0.76707079066246453,
    0.76642190832632051, 0.76577239876746772, 0.76512226351501011,
    0.76447150409952713, 0.76382012205306637, 0.763168118909141,
    0.76251549620272729, 0.76186225547025965, 0.76120839824962694,
    0.76055392608016992, 0.759898840502677, 0.75924314305938156,
    0.75858683529395643, 0.757929918751511, 0.75727239497858867,
    0.75661426552316224, 0.75595553193463016, 0.75529619576381346,
    0.75463625856295213, 0.75397572188569939, 0.75331458728712231,
    0.75265285632369394, 0.75199053055329168, 0.7513276115351939,
    0.75066410083007418, 0.75000000000000022, 0.74933531060842884,
    0.74867003422020229, 0.74800417240154449, 0.74733772672005916,
    0.74667069874472225, 0.746003090045882, 0.74533490219525345,
    0.74466613676591531, 0.74399679533230623, 0.7433268794702198,
    0.74265639075680312, 0.74198533077055129, 0.74131370109130534,
    0.74064150330024625, 0.73996873897989335, 0.73929540971409868,
    0.73862151708804535, 0.73794706268824228, 0.73727204810252123,
    0.73659647492003266, 0.73592034473124113, 0.73524365912792444,
    0.73456641970316672, 0.73388862805135591, 0.73321028576818059,
    0.73253139445062554, 0.73185195569696726, 0.731171971106772,
    0.7304914422808908, 0.72981037082145561, 0.72912875833187718,
    0.728446606416838, 0.72776391668229168, 0.72708069073545789,
    0.72639693018481866, 0.72571263664011443, 0.72502781171234087,
    0.72434245701374322, 0.72365657415781626, 0.72297016475929643,
    0.72228323043416043, 0.721595772799621, 0.72090779347412159,
    0.72021929407733531, 0.71953027623015908, 0.71884074155471045,
    0.71815069167432311, 0.71746012821354554, 0.71676905279813286,
    0.71607746705504682, 0.71538537261245061, 0.71469277109970453,
    0.71399966414736349, 0.7133060533871709, 0.71261194045205756,
    0.71191732697613563, 0.71122221459469692, 0.7105266049442065,
    0.709830499662301, 0.70913390038778279, 0.70843680876061821,
    0.70773922642193254, 0.70704115501400611, 0.70634259618027118,
    0.70564355156530578, 0.70494402281483426, 0.70424401157571892,
    0.70354351949595828, 0.70284254822468317, 0.70214109941215286,
    0.70143917470974926, 0.70073677576997662, 0.70003390424645451,
    0.69933056179391506, 0.69862675006820074, 0.69792247072625624,
    0.6972177254261287, 0.69651251582696183, 0.69580684358899281,
    0.69510071037354737, 0.6943941178430374, 0.69368706766095467,
    0.69297956149186912, 0.69227160100142537, 0.69156318785633586,
    0.69085432372438, 0.69014501027439745, 0.68943524917628707,
    0.68872504210100094, 0.68801439072054116, 0.68730329670795576,
    0.68659176173733594, 0.685879787483809, 0.68516737562353758,
    0.68445452783371485, 0.68374124579255957, 0.68302753117931325,
    0.682313385674236, 0.68159881095860131, 0.68088380871469378,
    0.6801683806258052, 0.67945252837622916, 0.67873625365125823,
    0.67801955813717851, 0.677302443521268, 0.67658491149179079,
    0.67586696373799371, 0.67514860195010273, 0.67442982781931782,
    0.67371064303781036, 0.67299104929871811, 0.67227104829614182,
    0.67155064172514078, 0.67082983128173, 0.67010861866287341,
    0.66938700556648367, 0.66866499369141519, 0.66794258473746138,
    0.66721978040535135, 0.66649658239674425, 0.66577299241422527,
    0.66504901216130374, 0.66432464334240726, 0.66359988766287814,
    0.66287474682897, 0.6621492225478417, 0.66142331652755626,
    0.66069703047707551, 0.65997036610625526, 0.659243325125842,
    0.65851590924746972, 0.65778812018365329, 0.65705995964778774,
    0.656331429354142, 0.65560253101785515, 0.65487326635493448,
    0.65414363708224721, 0.65341364491752052, 0.65268329157933536,
    0.65195257878712343, 0.65122150826116221, 0.650490081722572,
    0.64975830089330988, 0.64902616749616815, 0.64829368325476966,
    0.64756084989356189, 0.64682766913781553, 0.64609414271361754,
    0.64536027234786986, 0.64462605976828391, 0.6438915067033768,
    0.643156614882467, 0.64242138603567078, 0.64168582189389756,
    0.64094992418884633, 0.64021369465300126, 0.639477135019628,
    0.63874024702276921, 0.63800303239723988, 0.637265492878625,
    0.636527630203274, 0.63578944610829657, 0.63505094233156056,
    0.63431212061168574, 0.633572982688039, 0.63283353030073353,
    0.632093765190622, 0.63135368909929346, 0.63061330376906954,
    0.62987261094299862, 0.62913161236485382, 0.6283903097791288,
    0.62764870493103186, 0.62690679956648321, 0.62616459543211112,
    0.62542209427524575, 0.62467929784391785, 0.62393620788685289,
    0.62319282615346772, 0.6224491543938655, 0.62170519435883254,
    0.62096094779983391, 0.62021641646900894, 0.61947160211916763,
    0.61872650650378613, 0.61798113137700328, 0.61723547849361449,
    0.61648954960907021, 0.61574334647947138, 0.61499687086156318,
    0.61425012451273342, 0.6135031091910057, 0.61275582665503836,
    0.61200827866411822, 0.61126046697815728, 0.61051239335768814,
    0.60976405956386, 0.609015467358435, 0.608266618503783, 0.60751751476287863,
    0.60676815789929628, 0.60601854967720681, 0.60526869186137144,
    0.6045185862171405, 0.60376823451044692, 0.6030176385078031,
    0.60226679997629728, 0.60151572068358816, 0.60076440239790041,
    0.60001284688802226, 0.59926105592330048, 0.59850903127363586,
    0.59775677470947974, 0.59700428800182836, 0.59625157292222064,
    0.59549863124273372, 0.59474546473597711, 0.59399207517509023,
    0.59323846433373761, 0.59248463398610385, 0.59173058590689132,
    0.59097632187131488, 0.59022184365509744, 0.58946715303446651,
    0.58871225178614917, 0.5879571416873689, 0.58720182451584058,
    0.58644630204976655, 0.58569057606783259, 0.584934648349204,
    0.58417852067351961, 0.58342219482089053, 0.5826656725718935,
    0.58190895570756862, 0.58115204600941373, 0.58039494525937951,
    0.57963765523986788, 0.5788801777337258, 0.57812251452424146,
    0.5773646673951407, 0.57660663813058188, 0.5758484285151525,
    0.57509004033386446, 0.57433147537215012, 0.573572735415858,
    0.57281382225124888, 0.57205473766499038, 0.57129548344415459,
    0.57053606137621293, 0.56977647324903113, 0.56901672085086741,
    0.56825680597036587, 0.56749673039655224, 0.56673649591883168,
    0.5659761043269832, 0.5652155574111557, 0.56445485696186415,
    0.56369400476998366, 0.56293300262674739, 0.56217185232374245,
    0.56141055565290354, 0.56064911440651033, 0.55988753037718308,
    0.55912580535787726, 0.55836394114188115, 0.55760193952281079,
    0.55683980229460517, 0.556077531251523, 0.55531512818813777,
    0.55455259489933384, 0.55378993318030212, 0.55302714482653592,
    0.55226423163382665, 0.55150119539826015, 0.55073803791621034,
    0.5499747609843384, 0.54921136639958523, 0.54844785595917056,
    0.54768423146058576, 0.54692049470158977, 0.54615664748020731,
    0.5453926915947227, 0.5446286288436758, 0.5438644610258585,
    0.54310018994031017, 0.54233581738631165, 0.54157134516338523,
    0.54080677507128616, 0.54004210891000048, 0.539277348479741,
    0.53851249558094083, 0.53774755201425251, 0.53698251958054111,
    0.53621740008088092, 0.5354521953165523, 0.53468690708903543,
    0.53392153720000612, 0.533156087451334, 0.532390559645076,
    0.53162495558347278, 0.53085927706894509, 0.53009352590408776,
    0.52932770389166728, 0.52856181283461789, 0.52779585453603528,
    0.52702983079917354, 0.52626374342744153, 0.52549759422439635,
    0.52473138499374228, 0.52396511753932429, 0.52319879366512434,
    0.52243241517525751, 0.52166598387396723, 0.52089950156562126,
    0.5201329700547076, 0.51936639114582983, 0.51859976664370344,
    0.51783309835315139, 0.51706638807909866, 0.51629963762657027,
    0.51553284880068484, 0.5147660234066529, 0.51399916324977,
    0.51323227013541273, 0.51246534586903658, 0.51169839225616987,
    0.51093141110241014, 0.51016440421341958, 0.50939737339492164,
    0.50863032045269418, 0.50786324719256992, 0.50709615542042741,
    0.5063290469421895, 0.50556192356381868, 0.50479478709131109,
    0.50402763933069528, 0.50326048208802565, 0.50249331716937917,
    0.50172614638085034, 0.50095897152854918, 0.50019179441859274,
    0.499424616857105, 0.49865744065021073, 0.49789026760403143,
    0.49712309952468164, 0.49635593821826279, 0.49558878549086133,
    0.49482164314854438, 0.49405451299735326, 0.49328739684330108,
    0.49252029649236845, 0.4917532137504973, 0.49098615042358967,
    0.49021910831750121, 0.48945208923803779, 0.488685094990951,
    0.48791812738193391, 0.487151188216617, 0.48638427930056372,
    0.48561740243926627, 0.48485055943814148, 0.4840837521025268,
    0.4833169822376745, 0.48255025164874982, 0.48178356214082479,
    0.481016915518876, 0.48025031358777814, 0.47948375815229988,
    0.47871725101710172, 0.47795079398672996, 0.4771843888656131,
    0.47641803745805722, 0.47565174156824253, 0.47488550300021676,
    0.47411932355789527, 0.47335320504505252, 0.47258714926531986,
    0.47182115802218161, 0.47105523311896869, 0.47028937635885704,
    0.469523589544862, 0.468757874479834, 0.46799223296645437,
    0.46722666680723274, 0.46646117780449892, 0.46569576776040278,
    0.46493043847690779, 0.46416519175578741, 0.463400029398621,
    0.46263495320678827, 0.46186996498146704, 0.46110506652362743,
    0.46034025963402941, 0.45957554611321616, 0.45881092776151172,
    0.45804640637901506, 0.45728198376559787, 0.45651766172089914,
    0.45575344204432089, 0.45498932653502427, 0.4542253169919252,
    0.45346141521369, 0.4526976229987314, 0.45193394214520421,
    0.45117037445100094, 0.45040692171374824, 0.44964358573080077,
    0.44888036829923966, 0.44811727121586603, 0.447354296277199,
    0.44659144527946937, 0.445828720018615, 0.44506612229027931,
    0.44430365388980492, 0.44354131661223, 0.44277911225228406,
    0.442017042604384, 0.44125510946262808, 0.44049331462079555,
    0.43973165987233842, 0.43897014701037934, 0.43820877782770734,
    0.43744755411677194, 0.43668647766968138, 0.4359255502781969,
    0.43516477373372875, 0.43440414982733155, 0.43364368034970247,
    0.43288336709117237, 0.4321232118417061, 0.43136321639089625,
    0.43060338252795893, 0.42984371204173039, 0.42908420672066105,
    0.42832486835281364, 0.42756569872585704, 0.42680669962706413,
    0.42604787284330514, 0.42528922016104542, 0.42453074336633906,
    0.42377244424482746, 0.42301432458173338, 0.42225638616185684,
    0.42149863076957145, 0.42074106018881979, 0.41998367620310928,
    0.41922648059550827, 0.4184694751486413, 0.41771266164468557,
    0.41695604186536661, 0.41619961759195262, 0.41544339060525287,
    0.41468736268561124, 0.41393153561290436, 0.413175911166535,
    0.41242049112542822, 0.41166527726802893, 0.41091027137229641,
    0.41015547521570028, 0.40940089057521634, 0.40864651922732281,
    0.40789236294799419, 0.40713842351270119, 0.40638470269640226,
    0.40563120227354155, 0.4048779240180449, 0.40412486970331374,
    0.40337204110222358, 0.40261943998711819, 0.40186706812980572,
    0.40111492730155407, 0.4003630192730892, 0.39961134581458618,
    0.39885990869566967, 0.39810870968540757, 0.3973577505523071,
    0.39660703306431117, 0.39585655898879257, 0.39510633009255242,
    0.39435634814181353, 0.39360661490221877, 0.39285713213882423,
    0.39210790161609715, 0.39135892509790959, 0.3906102043475369,
    0.38986174112765204, 0.38911353720032138, 0.38836559432700152,
    0.3876179142685327, 0.38687049878513896, 0.38612334963641981,
    0.38537646858134811, 0.38462985737826555, 0.38388351778487906,
    0.38313745155825474, 0.38239166045481643, 0.38164614623033943,
    0.38090091063994852, 0.38015595543811154, 0.37941128237863542,
    0.37866689321466418, 0.37792278969867305, 0.37717897358246466,
    0.37643544661716521, 0.3756922105532205, 0.37494926714038967,
    0.37420661812774569, 0.3734642652636665, 0.37272221029583341,
    0.37198045497122673, 0.37123900103612012, 0.37049785023607895,
    0.36975700431595454, 0.36901646501988045, 0.36827623409126786,
    0.36753631327280378, 0.36679670430644251, 0.366057408933406,
    0.36531842889417743, 0.36457976592849745, 0.36384142177536094,
    0.36310339817301074, 0.36236569685893638, 0.36162831956986785,
    0.36089126804177352, 0.36015454400985358, 0.359418149208538,
    0.35868208537148039, 0.35794635423155663, 0.3572109575208588,
    0.3564758969706916, 0.35574117431156876, 0.355006791273207,
    0.35427274958452581, 0.35353905097363958, 0.3528056971678552,
    0.352072689893668, 0.35134003087675786, 0.35060772184198341,
    0.34987576451338076, 0.34914416061415743, 0.3484129118666886,
    0.34768201999251497, 0.34695148671233456, 0.34622131374600273,
    0.34549150281252639, 0.3447620556300599, 0.34403297391590149,
    0.34330425938648912, 0.34257591375739488, 0.34184793874332481,
    0.34112033605811076, 0.34039310741470835, 0.33966625452519317,
    0.33893977910075496, 0.33821368285169584, 0.33748796748742516,
    0.33676263471645523, 0.33603768624639752, 0.33531312378396028,
    0.33458894903494052, 0.3338651637042242, 0.33314176949578,
    0.3324187681126558, 0.3316961612569751, 0.33097395062993151,
    0.33025213793178676, 0.32953072486186519, 0.32880971311855134,
    0.32808910439928396, 0.32736890040055355, 0.32664910281789661,
    0.32592971334589427, 0.32521073367816622, 0.32449216550736737,
    0.32377401052518462, 0.32305627042233, 0.32233894688854148,
    0.3216220416125749, 0.32090555628220152, 0.32018949258420404,
    0.31947385220437297, 0.31875863682750094, 0.3180438481373814,
    0.3173294878168027, 0.31661555754754434, 0.3159020590103751,
    0.31518899388504473, 0.31447636385028432, 0.31376417058380035,
    0.31305241576227094, 0.31234110106134205, 0.31163022815562391,
    0.31091979871868525, 0.31020981442305179, 0.30950027694020205,
    0.30879118794056137, 0.30808254909349975, 0.3073743620673276,
    0.30666662852929083, 0.30595935014556841, 0.30525252858126783,
    0.30454616550042046, 0.30384026256597996, 0.30313482143981424,
    0.30242984378270565, 0.30172533125434509, 0.30102128551332835,
    0.3003177082171522, 0.2996146010222111, 0.29891196558379157,
    0.2982098035560703, 0.29750811659211013, 0.29680690634385443,
    0.29610617446212506, 0.29540592259661647, 0.29470615239589404,
    0.29400686550738914, 0.29330806357739503, 0.29260974825106334,
    0.29191192117240017, 0.29121458398426209, 0.29051773832835243,
    0.28982138584521722, 0.28912552817424153, 0.28843016695364587,
    0.28773530382048085, 0.28704094041062556, 0.28634707835878237,
    0.28565371929847272, 0.2849608648620352, 0.2842685166806197,
    0.28357667638418327, 0.28288534560148848, 0.2821945259600982,
    0.28150421908637174, 0.28081442660546169, 0.28012515014130845,
    0.27943639131663828, 0.27874815175295975, 0.27806043307055778,
    0.27737323688849114, 0.2766865648245892, 0.27600041849544615,
    0.27531479951641952, 0.27462970950162513, 0.27394515006393333,
    0.27326112281496551, 0.27257762936509, 0.2718946713234186,
    0.27121225029780238, 0.27053036789482854, 0.26984902571981578,
    0.26916822537681173, 0.26848796846858691, 0.26780825659663365,
    0.26712909136116147, 0.26645047436109215, 0.26577240719405731,
    0.2650948914563932, 0.26441792874313885, 0.263741520648031,
    0.26306566876350079, 0.26239037468066967, 0.2617156399893461,
    0.26104146627802155, 0.26036785513386673, 0.259694808142728,
    0.25902232688912352, 0.25835041295623995, 0.25767906792592732,
    0.25700829337869718, 0.25633809089371795, 0.25566846204881072,
    0.25499940842044727, 0.25433093158374442, 0.25366303311246036,
    0.25299571457899273, 0.25232897755437345, 0.25166282360826564,
    0.25099725430895981, 0.2503322712233691, 0.24966787591702722,
    0.24900406995408503, 0.24834085489730456, 0.2476782323080573,
    0.24701620374632011, 0.24635477077067036, 0.24569393493828434,
    0.24503369780493223, 0.24437406092497455, 0.24371502585135885,
    0.24305659413561576, 0.24239876732785554, 0.24174154697676431,
    0.24108493462960046, 0.24042893183219094, 0.2397735401289281,
    0.23911876106276453, 0.23846459617521149, 0.23781104700633371,
    0.23715811509474749, 0.23650580197761512, 0.23585410919064143,
    0.23520303826807187, 0.23455259074268758, 0.23390276814580208,
    0.23325357200725755, 0.23260500385542143, 0.23195706521718262,
    0.2313097576179482, 0.23066308258163937, 0.23001704163068826,
    0.22937163628603457, 0.22872686806712056, 0.22808273849188954,
    0.22743924907678092, 0.22679640133672685, 0.22615419678514964,
    0.22551263693395684, 0.2248717232935375, 0.22423145737276018,
    0.22359184067896853, 0.22295287471797748, 0.22231456099407049,
    0.22167690100999432, 0.22103989626695747, 0.22040354826462649,
    0.21976785850112079, 0.21913282847301047, 0.21849845967531267,
    0.217864753601487, 0.21723171174343375, 0.21659933559148914,
    0.21596762663442221, 0.21533658635943126, 0.21470621625214037,
    0.2140765177965957, 0.21344749247526246, 0.21281914176902089,
    0.21219146715716319, 0.2115644701173901, 0.21093815212580624,
    0.21031251465691853, 0.20968755918363108, 0.2090632871772436,
    0.20843970010744595, 0.20781679944231474, 0.2071945866483117,
    0.20657306319027885, 0.2059522305314353, 0.20533209013337383,
    0.2047126434560575, 0.20409389195781613, 0.203475837095343,
    0.20285848032369125, 0.20224182309627059, 0.20162586686484424,
    0.20101061307952389, 0.20039606318876868, 0.19978221863938028,
    0.19916908087649932, 0.19855665134360373, 0.19794493148250314,
    0.197333922733336, 0.19672362653456754, 0.19611404432298507,
    0.19550517753369512, 0.19489702760012023, 0.19428959595399425,
    0.19368288402536071, 0.19307689324256938, 0.19247162503227133,
    0.19186708081941678, 0.19126326202725186, 0.19066017007731395,
    0.19005780638943004, 0.18945617238171253, 0.18885526947055586,
    0.18825509907063331, 0.18765566259489358, 0.18705696145455769,
    0.18645899705911528, 0.18586177081632166, 0.1852652841321944,
    0.18466953841101008, 0.18407453505530014, 0.18348027546584916,
    0.18288676104168994, 0.18229399318010225, 0.18170197327660736,
    0.1811107027249651, 0.18052018291717215, 0.17993041524345743,
    0.17934140109227903, 0.17875314185032121, 0.17816563890249132,
    0.1775788936319147, 0.17699290741993512, 0.17640768164610793,
    0.17582321768819853, 0.17523951692217926, 0.17465658072222456,
    0.17407441046071004, 0.17349300750820762, 0.17291237323348257,
    0.17233250900349151, 0.17175341618337747, 0.1711750961364667,
    0.1705975502242672, 0.17002077980646413, 0.16944478624091691,
    0.16886957088365639, 0.16829513508888044, 0.16772148020895217,
    0.16714860759439687, 0.16657651859389744, 0.16600521455429196,
    0.1654346968205711, 0.1648649667358732, 0.16429602564148343,
    0.16372787487682905, 0.16316051577947677, 0.16259394968512936,
    0.16202817792762286, 0.16146320183892315, 0.16089902274912293,
    0.16033564198643852, 0.15977306087720683, 0.15921128074588253,
    0.15865030291503363, 0.15809012870534017, 0.15753075943558975,
    0.15697219642267585, 0.15641444098159329, 0.15585749442543489,
    0.15530135806539014, 0.15474603321074082, 0.15419152116885831,
    0.15363782324520037, 0.15308494074330836, 0.15253287496480272,
    0.15198162720938319, 0.15143119877482214, 0.15088159095696352,
    0.15033280504971969, 0.14978484234506706, 0.14923770413304488,
    0.14869139170175111, 0.14814590633733959, 0.1476012493240168,
    0.1470574219440402, 0.14651442547771232, 0.14597226120338075,
    0.14543093039743349, 0.14489043433429644, 0.14435077428643062,
    0.14381195152432791, 0.1432739673165096, 0.1427368229295235,
    0.14220051962793939, 0.14166505867434703, 0.14113044132935365,
    0.14059666885157929, 0.14006374249765602, 0.13953166352222357,
    0.13900043317792671, 0.13847005271541241, 0.13794052338332663,
    0.13741184642831178, 0.13688402309500347, 0.13635705462602754,
    0.13583094226199754, 0.1353056872415116, 0.13478129080114865,
    0.13425775417546726, 0.13373507859700112, 0.13321326529625771,
    0.1326923155017139, 0.13217223043981297, 0.13165301133496354,
    0.131134659409535, 0.1306171758838553, 0.130100561976208,
    0.12958481890282963, 0.12906994787790527, 0.12855595011356896,
    0.12804282681989754, 0.1275305792049094, 0.12701920847456183,
    0.1265087158327467, 0.12599910248128954, 0.12549036961994553,
    0.12498251844639696, 0.12447555015625017, 0.1239694659430341,
    0.12346426699819463, 0.12295995451109454, 0.12245652966900955,
    0.12195399365712556, 0.12145234765853624, 0.12095159285423912,
    0.12045173042313445, 0.11995276154202111, 0.11945468738559512,
    0.11895750912644532, 0.11846122793505187, 0.11796584497978219,
    0.11747136142688996, 0.1169777784405111, 0.11648509718266131,
    0.11599331881323355, 0.11550244448999503, 0.11501247536858461,
    0.1145234126025102, 0.11403525734314585, 0.11354801073972909,
    0.11306167393935862, 0.11257624808699024, 0.11209173432543618,
    0.11160813379536078, 0.1111254476352791, 0.11064367698155309,
    0.11016282296838892, 0.10968288672783544, 0.10920386938978066,
    0.10872577208194917, 0.10824859592989966, 0.10777234205702246,
    0.10729701158453558, 0.1068226056314846, 0.10634912531473756,
    0.10587657174898368, 0.10540494604673045, 0.10493424931830037,
    0.10446448267182951, 0.10399564721326421, 0.10352774404635834,
    0.10306077427267085, 0.10259473899156429, 0.10212963930019953,
    0.10166547629353589, 0.10120225106432729, 0.10073996470311986,
    0.10027861829824969, 0.099818212935839146, 0.099358749699796023,
    0.098900229671809448, 0.098442653931348989, 0.097986023555660218,
    0.09753033961976354, 0.097075603196450644, 0.096621815356283058,
    0.096168977167589043, 0.095717089696461088, 0.095266154006753756,
    0.094816171160079732, 0.094367142215810162, 0.09391906823106938,
    0.093471950260733738, 0.093025789357428945, 0.09258058657152779,
    0.092136342951146588, 0.091693059542144351, 0.091250737388119063,
    0.09080937753040641, 0.090368981008075944, 0.089929548857929031,
    0.0894910821144973, 0.089053581810039251, 0.0886170489745382,
    0.088181484635699969, 0.087746889818950236, 0.087313265547431462,
    0.086880612842002547, 0.086448932721234162, 0.086018226201407533,
    0.085588494296511941, 0.0851597380182415, 0.084731958375994287,
    0.084305156376868751, 0.0838793330256618, 0.0834544893248661,
    0.083030626274669, 0.082607744872947586, 0.082185846115268968,
    0.081764930994886631, 0.0813450005027383, 0.080926055627443927,
    0.080508097355302233, 0.080091126670290114, 0.07967514455405883,
    0.079260151985933169, 0.0788461499429075, 0.07843313939964458,
    0.078021121328472443, 0.077610096699383235, 0.077200066480029972,
    0.0767910316357247, 0.0763829931294363, 0.075975951921787077,
    0.075569908971052813, 0.0751648652331583, 0.074760821661676191,
    0.074357779207824382, 0.07395573882046419, 0.0735547014460971,
    0.073154668028864056, 0.072755639510542036, 0.072357616830542093,
    0.071960600925908336, 0.071564592731313048, 0.071169593179057244,
    0.070775603199067, 0.070382623718891646, 0.069990655663701551,
    0.069599699956286176, 0.069209757517050718, 0.068820829264016281,
    0.068432916112815489, 0.068046018976691269, 0.067660138766494793,
    0.0672752763906827, 0.0668914327553159, 0.06650860876405662,
    0.066126805318166781, 0.06574602331650542, 0.065366263655527612,
    0.064987527229280417, 0.064609814929402765, 0.064233127645122345,
    0.063857466263253615, 0.063482831668196182, 0.063109224741931536,
    0.062736646364022541, 0.06236509741161006, 0.061994578759412222,
    0.061625091279720934, 0.061256635842400653, 0.060889213314885837,
    0.060522824562179611, 0.060157470446851324, 0.05979315182903433,
    0.0594298695664246, 0.059067624514277217, 0.058706417525406784,
    0.058346249450183241, 0.057987121136530817, 0.057629033429925869,
    0.057271987173395211, 0.056915983207513121, 0.056561022370400671,
    0.056207105497723064, 0.055854233422687471, 0.055502406976042085,
    0.0551516269860724, 0.054801894278600882, 0.054453209676984471,
    0.054105574002112466, 0.0537589880724047, 0.053413452703809983,
    0.053068968709803155, 0.052725536901384207, 0.052383158087076609,
    0.052041833072924037, 0.051701562662489708, 0.0513623476568536,
    0.051024188854611352, 0.050687087051871971, 0.050351043042256127,
    0.050016057616893816, 0.049682131564423693, 0.049349265670989295,
    0.049017460720238992, 0.048686717493323317, 0.04835703676889308,
    0.048028419323098037, 0.047700865929584113, 0.047374377359492792,
    0.04704895438145823, 0.04672459776160659, 0.046401308263552987,
    0.046079086648400547, 0.04575793367473785, 0.045437850098638266,
    0.045118836673657126, 0.044800894150830606, 0.04448402327867379,
    0.044168224803178113, 0.043853499467811419, 0.043539848013514293,
    0.043227271178699511, 0.042915769699249873, 0.042605344308516535,
    0.04229599573731696, 0.041987724713933916, 0.04168053196411331,
    0.041374418211062136, 0.041069384175448087, 0.040765430575395778,
    0.040462558126486858, 0.04016076754175768, 0.039860059531697523,
    0.039560434804246869, 0.039261894064796354, 0.038964438016183878,
    0.038668067358694214, 0.038372782790057125, 0.03807858500544492,
    0.037785474697471733, 0.03749345255619102, 0.037202519269094847,
    0.036912675521111826, 0.036623921994605346, 0.036336259369372181,
    0.036049688322641271, 0.035764209529070945, 0.0354798236607487,
    0.035196531387188756, 0.034914333375330842, 0.034633230289538519,
    0.034353222791597693, 0.034074311540714664, 0.033796497193515018,
    0.033519780404042521, 0.03324416182375628, 0.032969642101530472,
    0.032696221883651677, 0.032423901813818545, 0.032152682533139521,
    0.031882564680131453, 0.031613548890718213, 0.031345635798229243,
    0.031078826033397788, 0.030813120224359669, 0.030548518996651675,
    0.03028502297321034, 0.030022632774370117, 0.029761349017861816,
    0.029501172318811886, 0.029242103289740196, 0.028984142540558866,
    0.028727290678571271, 0.028471548308469818, 0.028216916032334727,
    0.027963394449633083, 0.027710984157217122, 0.027459685749322726,
    0.027209499817568317, 0.026960426950952854, 0.026712467735855117,
    0.02646562275603237, 0.026219892592618255, 0.025975277824122123,
    0.025731779026427315, 0.025489396772789719, 0.025248131633836879,
    0.025007984177566334, 0.02476895496934417, 0.024531044571904026,
    0.024294253545345479, 0.024058582447132826, 0.023824031832093862,
    0.02359060225241838, 0.023358294257657064, 0.023127108394720208,
    0.022897045207875943, 0.022668105238749514, 0.022440289026322335,
    0.022213597106929606, 0.021988030014259974, 0.021763588279353596,
    0.021540272430601748, 0.021318082993744825, 0.021097020491871343,
    0.020877085445416943, 0.020658278372162719, 0.020440599787234337,
    0.020224050203100863, 0.020008630129573157, 0.019794340073803152,
    0.019581180540282406, 0.019369152030840664, 0.019158255044645356,
    0.01894849007819982, 0.018739857625342249, 0.018532358177245079,
    0.018325992222413046, 0.018120760246682077, 0.017916662733218847,
    0.017713700162519108, 0.017511873012406753, 0.01731118175803259,
    0.017111626871872954, 0.016913208823729153, 0.016715928080726361,
    0.016519785107311835, 0.016324780365254365, 0.016130914313643163,
    0.015938187408886417, 0.015746600104710795, 0.015556152852159943,
    0.01536684609959349, 0.015178680292686209, 0.014991655874426524,
    0.014805773285116064, 0.014621032962368163, 0.014437435341106863,
    0.014254980853566301, 0.014073669929289156, 0.013893502995125873,
    0.01371448047523377, 0.013536602791075769, 0.013359870361419945,
    0.013184283602337921, 0.013009842927203918, 0.012836548746694265,
    0.012664401468786113, 0.012493401498756496, 0.012323549239181386,
    0.012154845089934807, 0.011987289448187777, 0.011820882708407587,
    0.011655625262356584, 0.011491517499091441, 0.011328559804962335,
    0.011166752563611493, 0.011006096155973144, 0.010846590960271962,
    0.010688237352022345, 0.010531035704027747, 0.01037498638637957,
    0.010220089766456164, 0.010066346208922272, 0.0099137560757280863,
    0.00976231972610836, 0.0096120375165815175, 0.0094629098009487156,
    0.0093149369302932827, 0.00916811925297989, 0.0090224571146534926,
    0.0088779508582384481, 0.0087346008239382322, 0.0085924073492338326,
    0.0084513707688838036, 0.008311491414922989, 0.00817276961666169,
    0.0080352057006851663, 0.0078987999908528, 0.0077635528082971583,
    0.0076294644714233195, 0.0074965352959082132, 0.0073647655946998958,
    0.0072341556780166627, 0.0071047058533462715, 0.006976416425445553,
    0.0068492876963392457, 0.0067233199653198294, 0.0065985135289463037,
    0.0064748686810435774, 0.006352385712702191, 0.00623106491227704,
    0.0061109065653872641, 0.0059919109549151361, 0.0058740783610055636,
    0.0057574090610653661, 0.0056419033297629984, 0.0055275614390271621,
    0.0054143836580469173, 0.0053023702532706274, 0.0051915214884052929,
    0.0050818376244161634, 0.0049733189195261263, 0.004865965629214819,
    0.0047597780062183515, 0.00465475630052864, 0.0045509007593923512,
    0.0044482116273111272, 0.0043466891460404167, 0.0042463335545891434,
    0.00414714508921904, 0.0040491239834441473, 0.00395227046803015,
    0.0038565847709942092, 0.0037620671176039622, 0.0036687177303771912,
    0.0035765368290813782, 0.003485524630732928, 0.0033956813495970017,
    0.00330700719718674, 0.0032195023822629842, 0.0031331671108335568,
    0.0030480015861528709, 0.0029640060087216535, 0.0028811805762860576,
    0.002799525483837495, 0.0027190409236122481, 0.0026397270850907484,
    0.0025615841549971874, 0.0024846123172993506, 0.0024088117532077291,
    0.0023341826411756861, 0.0022607251568984021, 0.0021884394733129309,
    0.0021173257605974771, 0.0020473841861712305, 0.0019786149146938659,
    0.00191101810806521, 0.0018445939254247423, 0.0017793425231512616,
    0.0017152640548627196, 0.0016523586714155547, 0.0015906265209045256,
    0.0015300677486623226, 0.0014706824972591237, 0.0014124709065024832,
    0.001355433113436777, 0.0012995692523429803, 0.0012448794547383346,
    0.0011913638493762368, 0.0011390225622454064, 0.001087855716570163,
    0.0010378634328099268, 0.000989045828658719, 0.00094140301904527268,
    0.0008949351161324226, 0.00084964222931704914, 0.000805524465229801,
    0.00076258192773470679, 0.0007208147179290636, 0.00068022293414321533,
    0.00064080667194010843, 0.00060256602411534743, 0.00056550108069686189,
    0.00052961192894462883, 0.00049489865335056171, 0.00046136133563817738,
    0.00042900005476265157, 0.00039781488691037481, 0.00036780590549889691,
    0.00033897318117676045, 0.0003113167818232232, 0.00028483677254836914,
    0.00025953321569255339, 0.00023540617082656867, 0.00021245569475147885,
    0.00019068184149834133, 0.00017008466232815156, 0.000150664205731732,
    0.00013242051742962113, 0.00011535364037190687, 9.9463614738226624E-5,
    8.4750477937711732E-5, 7.1214264608543409E-5, 5.8855006618452332E-5,
    4.7672733064052508E-5, 3.7667470271229853E-5, 2.8839241794864634E-5,
    2.118806841866494E-5, 1.4713968155499746E-5, 9.41695624689931E-6,
    5.2970451633327365E-6, 2.3542446042079668E-6, 5.8856149742769759E-7, 0.0 };

  double csm[2048];
  double f[2048];
  double dv5[2048];
  static double relevant_frequencies_data[4096];
  int relevant_frequencies_size[2];
  static double Locs_data[4096];
  int Locs_size[2];
  int n;
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
  //  @ 0.5 Hz:
  b_filtfilt(X, X0);

  //  2.1 Divide by max value to acheive peak of 1
  //  X0 = X0/ max( abs( X0 ) );
  //  3. Derivative Filter:
  c_filtfilt(X0, X);

  //  X2 = X2/max(X2);
  //  4. Square to accentuate ecg waveformsS
  //  5. Convolution filtering to smooth peaks:
  //  conv_filter = ones(1, round(0.150*62.5)) / round(0.150*62.5);
  //  Custom: Use Hann Window as filter - better defined peaks.
  //  conv_filter = [0;0.146446609406726;0.500000000000000;0.853553390593274;1;0.853553390593274;0.500000000000000;0.146446609406726;0]; 
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

  //  TODO: Redo RR Algorithm
  d_filtfilt(X_raw, X);

  //  b_deriv = [7.812500000000000,-8.750000000000000];
  c_filtfilt(X, X0);
  b_conv(X0, dv2, dv3);
  welch_psd(dv3, dv4, csm, f);
  rescale_minmax(csm, dv5);
  b_findpeaks(dv5, relevant_frequencies_data, relevant_frequencies_size,
              Locs_data, Locs_size);
  ix = Locs_size[0] * Locs_size[1];
  emxFree_real_T(&dist);
  for (i = 0; i < ix; i++) {
    relevant_frequencies_data[i] = f[(int)Locs_data[i] - 1];
  }

  i = 1;
  n = Locs_size[1];
  mtmp = f[(int)Locs_data[0] - 1];
  if (Locs_size[1] > 1) {
    if (rtIsNaN(f[(int)Locs_data[0] - 1])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        i = ix;
        if (!rtIsNaN(relevant_frequencies_data[ix - 1])) {
          mtmp = relevant_frequencies_data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (i < Locs_size[1]) {
      while (i + 1 <= n) {
        if (relevant_frequencies_data[i] < mtmp) {
          mtmp = relevant_frequencies_data[i];
        }

        i++;
      }
    }
  }

  *Respiratory_rate = mtmp * 60.0;

  //  X_rr_sq = X_rr_drv.^2;
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
