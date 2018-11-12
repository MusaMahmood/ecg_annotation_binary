//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: get_hr_rr.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 11-Nov-2018 18:21:04
//

// Include Files
#include "rt_nonfinite.h"
#include "get_hr_rr.h"

// Named Constants
#define Fs                             (250.0)

// Function Declarations
static void b_filter(const double b[2], const double x[2006], double zi, double
                     y[2006]);
static void b_filtfilt(const double x_in[2000], double y_out[2000]);
static void b_flipud(double x[2006]);
static double b_mean(const double x_data[], const int x_size[2]);
static void c_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1]);
static void conv(const double A[2000], const double B[38], double C[1963]);
static void do_vectors(const int a_data[], const int a_size[1], const int
  b_data[], const int b_size[1], int c_data[], int c_size[1], int ia_data[], int
  ia_size[1], int ib_data[], int ib_size[1]);
static void filter(const double b[4], const double a[4], const double x[2018],
                   const double zi[3], double y[2018]);
static void filtfilt(const double x_in[2000], double y_out[2000]);
static void findpeaks(const double Yin[1963], double varargin_2, double
                      Ypk_data[], int Ypk_size[1], double Xpk_data[], int
                      Xpk_size[1]);
static void flipud(double x[2018]);
static void getAllPeaksCodegen(const double y[1963], int iPk_data[], int
  iPk_size[1], int iInf_data[], int iInf_size[1], int iInflect_data[], int
  iInflect_size[1]);
static void keepAtMostNpPeaks(int idx_data[], int idx_size[1]);
static double mean(const double x[2000]);
static void power(const double a[2000], double y[2000]);
static void removeSmallPeaks(const double y[1963], const int iFinite_data[],
  const int iFinite_size[1], double minH, int iPk_data[], int iPk_size[1]);

// Function Definitions

//
// Arguments    : const double b[2]
//                const double x[2006]
//                double zi
//                double y[2006]
// Return Type  : void
//
static void b_filter(const double b[2], const double x[2006], double zi, double
                     y[2006])
{
  int k;
  int j;
  y[0] = zi;
  memset(&y[1], 0, 2005U * sizeof(double));
  for (k = 0; k < 2; k++) {
    for (j = k; j + 1 < 2007; j++) {
      y[j] += b[k] * x[j - k];
    }
  }
}

//
// Arguments    : const double x_in[2000]
//                double y_out[2000]
// Return Type  : void
//
static void b_filtfilt(const double x_in[2000], double y_out[2000])
{
  double d2;
  double d3;
  int i0;
  double y[2006];
  double b_y[2006];
  double dv4[2];
  d2 = 2.0 * x_in[0];
  d3 = 2.0 * x_in[1999];
  for (i0 = 0; i0 < 3; i0++) {
    y[i0] = d2 - x_in[3 - i0];
  }

  memcpy(&y[3], &x_in[0], 2000U * sizeof(double));
  for (i0 = 0; i0 < 3; i0++) {
    y[i0 + 2003] = d3 - x_in[1998 - i0];
  }

  for (i0 = 0; i0 < 2; i0++) {
    dv4[i0] = 7.8125 + -16.5625 * (double)i0;
  }

  memcpy(&b_y[0], &y[0], 2006U * sizeof(double));
  b_filter(dv4, b_y, -8.75 * y[0], y);
  b_flipud(y);
  for (i0 = 0; i0 < 2; i0++) {
    dv4[i0] = 7.8125 + -16.5625 * (double)i0;
  }

  memcpy(&b_y[0], &y[0], 2006U * sizeof(double));
  b_filter(dv4, b_y, -8.75 * y[0], y);
  b_flipud(y);
  memcpy(&y_out[0], &y[3], 2000U * sizeof(double));
}

//
// Arguments    : double x[2006]
// Return Type  : void
//
static void b_flipud(double x[2006])
{
  int i;
  double xtmp;
  for (i = 0; i < 1003; i++) {
    xtmp = x[i];
    x[i] = x[2005 - i];
    x[2005 - i] = xtmp;
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
// Arguments    : const int iPk_size[1]
//                int idx_data[]
//                int idx_size[1]
// Return Type  : void
//
static void c_findPeaksSeparatedByMoreThanM(const int iPk_size[1], int idx_data[],
  int idx_size[1])
{
  int n;
  int y_data[3926];
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
// Arguments    : const double A[2000]
//                const double B[38]
//                double C[1963]
// Return Type  : void
//
static void conv(const double A[2000], const double B[38], double C[1963])
{
  int k;
  int b_k;
  memset(&C[0], 0, 1963U * sizeof(double));
  for (k = 0; k < 38; k++) {
    for (b_k = 0; b_k < 1963; b_k++) {
      C[b_k] += B[k] * A[(b_k - k) + 37];
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
  int b_ia_data[1963];
  short b_ib_data[1963];
  int b_c_data[3926];
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
// Arguments    : const double b[4]
//                const double a[4]
//                const double x[2018]
//                const double zi[3]
//                double y[2018]
// Return Type  : void
//
static void filter(const double b[4], const double a[4], const double x[2018],
                   const double zi[3], double y[2018])
{
  int k;
  int naxpy;
  int j;
  double as;
  for (k = 0; k < 3; k++) {
    y[k] = zi[k];
  }

  memset(&y[3], 0, 2015U * sizeof(double));
  for (k = 0; k < 2018; k++) {
    naxpy = 2018 - k;
    if (!(naxpy < 4)) {
      naxpy = 4;
    }

    for (j = 0; j + 1 <= naxpy; j++) {
      y[k + j] += x[k] * b[j];
    }

    naxpy = 2017 - k;
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
// Arguments    : const double x_in[2000]
//                double y_out[2000]
// Return Type  : void
//
static void filtfilt(const double x_in[2000], double y_out[2000])
{
  double d0;
  double d1;
  int i;
  double y[2018];
  double b_y[2018];
  double a[3];
  static const double b_a[3] = { -0.95097188792623888, 1.9019437758521933,
    -0.95097188792596821 };

  static const double dv2[4] = { 0.950971887923409, -2.8529156637702271,
    2.8529156637702271, -0.950971887923409 };

  static const double dv3[4] = { 1.0, -2.8994795946118641, 2.8039479773829989,
    -0.904347531392409 };

  d0 = 2.0 * x_in[0];
  d1 = 2.0 * x_in[1999];
  for (i = 0; i < 9; i++) {
    y[i] = d0 - x_in[9 - i];
  }

  memcpy(&y[9], &x_in[0], 2000U * sizeof(double));
  for (i = 0; i < 9; i++) {
    y[i + 2009] = d1 - x_in[1998 - i];
  }

  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 2018U * sizeof(double));
  filter(dv2, dv3, b_y, a, y);
  flipud(y);
  for (i = 0; i < 3; i++) {
    a[i] = b_a[i] * y[0];
  }

  memcpy(&b_y[0], &y[0], 2018U * sizeof(double));
  filter(dv2, dv3, b_y, a, y);
  flipud(y);
  memcpy(&y_out[0], &y[9], 2000U * sizeof(double));
}

//
// Arguments    : const double Yin[1963]
//                double varargin_2
//                double Ypk_data[]
//                int Ypk_size[1]
//                double Xpk_data[]
//                int Xpk_size[1]
// Return Type  : void
//
static void findpeaks(const double Yin[1963], double varargin_2, double
                      Ypk_data[], int Ypk_size[1], double Xpk_data[], int
                      Xpk_size[1])
{
  int iFinite_data[1963];
  int iFinite_size[1];
  int iInfinite_data[1963];
  int iInfinite_size[1];
  int iInflect_data[1963];
  int iInflect_size[1];
  int iPk_size[1];
  int loop_ub;
  int i1;
  int iPk_data[3926];
  int c_data[3926];
  int c_size[1];
  int idx_data[3926];
  short tmp_data[3926];
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
// Arguments    : double x[2018]
// Return Type  : void
//
static void flipud(double x[2018])
{
  int i;
  double xtmp;
  for (i = 0; i < 1009; i++) {
    xtmp = x[i];
    x[i] = x[2017 - i];
    x[2017 - i] = xtmp;
  }
}

//
// Arguments    : const double y[1963]
//                int iPk_data[]
//                int iPk_size[1]
//                int iInf_data[]
//                int iInf_size[1]
//                int iInflect_data[]
//                int iInflect_size[1]
// Return Type  : void
//
static void getAllPeaksCodegen(const double y[1963], int iPk_data[], int
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
  for (k = 0; k < 1963; k++) {
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

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect_data[nInflect] < 1963)))
  {
    nInflect++;
    iInflect_data[nInflect] = 1963;
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
  int b_idx_data[3926];
  int i3;
  if (idx_size[0] > 1963) {
    memcpy(&b_idx_data[0], &idx_data[0], 1963U * sizeof(int));
    idx_size[0] = 1963;
    for (i3 = 0; i3 < 1963; i3++) {
      idx_data[i3] = b_idx_data[i3];
    }
  }
}

//
// Arguments    : const double x[2000]
// Return Type  : double
//
static double mean(const double x[2000])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 1999; k++) {
    y += x[k + 1];
  }

  y /= 2000.0;
  return y;
}

//
// Arguments    : const double a[2000]
//                double y[2000]
// Return Type  : void
//
static void power(const double a[2000], double y[2000])
{
  int k;
  for (k = 0; k < 2000; k++) {
    y[k] = a[k] * a[k];
  }
}

//
// Arguments    : const double y[1963]
//                const int iFinite_data[]
//                const int iFinite_size[1]
//                double minH
//                int iPk_data[]
//                int iPk_size[1]
// Return Type  : void
//
static void removeSmallPeaks(const double y[1963], const int iFinite_data[],
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
// get_hr_rr This function uses a variant of the Pan-Tompkins Algorithm to
// detect ECG QRS features from low frequency data:
//  Input: X (raw data, floats or doubles (preferred);
//  Outputs: Y .. (TODO);
//  Fs = 62.5;
//  1. Remove Mean:
// Arguments    : double X[2000]
//                double *HR_mean
//                double *Respiratory_rate
// Return Type  : void
//
void get_hr_rr(double X[2000], double *HR_mean, double *Respiratory_rate)
{
  double mtmp;
  int ixstart;
  double X0[2000];
  double X2[2000];
  double dv0[2000];
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

  double X4[1963];
  int ix;
  boolean_T exitg1;
  static double Peaks_data[3926];
  int Peaks_size[1];
  static double Locations_data[3926];
  int Locations_size[1];
  int dist_size[2];
  static double dist_data[3925];
  mtmp = mean(X);
  for (ixstart = 0; ixstart < 2000; ixstart++) {
    X[ixstart] -= mtmp;
  }

  //  2. Remove baseline drift (Butterworth, high pass: [b, a] = butter(3, 0.5*2/62.5, 'high');  
  //  @ 5 hz
  //  b = [0.601580928135908,-1.804742784407724,1.804742784407724,-0.601580928135908]; 
  //  a = [1,-2.003797477370017,1.447054019489380,-0.361795928227867];
  //  @ 0.5 Hz:
  filtfilt(X, X0);

  //  2.1 Divide by max value to acheive peak of 1
  //  X0 = X0/ max( abs( X0 ) );
  //  3. Derivative Filter:
  b_filtfilt(X0, X2);

  //  X2 = X2/max(X2);
  //  4. Square to accentuate ecg waveformsS
  //  5. Convolution filtering to smooth peaks:
  //  conv_filter = ones(1, round(0.150*62.5)) / round(0.150*62.5);
  //  Custom: Use Hann Window as filter - better defined peaks.
  //  conv_filter = [0;0.146446609406726;0.500000000000000;0.853553390593274;1;0.853553390593274;0.500000000000000;0.146446609406726;0]; 
  power(X2, dv0);
  conv(dv0, dv1, X4);

  // rescale_minmax
  //  Extract fiducial markers (peaks);
  ixstart = 1;
  mtmp = X4[0];
  if (rtIsNaN(X4[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 1964)) {
      ixstart = ix;
      if (!rtIsNaN(X4[ix - 1])) {
        mtmp = X4[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1963) {
    while (ixstart + 1 < 1964) {
      if (X4[ixstart] > mtmp) {
        mtmp = X4[ixstart];
      }

      ixstart++;
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
  for (ixstart = 0; ixstart < ix; ixstart++) {
    dist_data[ixstart] = 0.0;
  }

  for (ixstart = 0; ixstart <= Locations_size[0] - 2; ixstart++) {
    dist_data[ixstart] = Locations_data[ixstart + 1] - Locations_data[ixstart];
  }

  mtmp = b_mean(dist_data, dist_size);

  //  average in seconds:
  *HR_mean = 60.0 / (mtmp / Fs);

  //  TODO: Get RR:
  *Respiratory_rate = 0.0;
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
