#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include <ap_int.h>

// Small 4x4 integer 2D stencil (3x3 filter) for the ArithV DSP-Auto integer
// flow. Each output pixel is a 9-tap convolution -> 9 DSP multiplies + an
// inner-product adder tree, exercising the same DSP-Auto path as gemm.
#define col_size 4
#define row_size 4
#define f_size 9

#define TYPE      ap_int<16>
// 16x16 product is 32-bit, summed over 9 taps -> fits in 48 bits (DSP P width).
#define OUT_TYPE  ap_int<48>

#define MAX 1000
#define MIN 1

#define MAX_ITERATION 1

// Output holds ONLY the valid (row-2)x(col-2) convolution region, compactly
// indexed, so EVERY sol element is written. (A full row_size*col_size sol left
// the border elements undriven -> X in sim vs the golden's 0.)
#define out_rows (row_size - 2)
#define out_cols (col_size - 2)

void stencil( TYPE orig[row_size * col_size],
        OUT_TYPE sol[out_rows * out_cols],
        TYPE filter[f_size] );

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
    TYPE orig[row_size*col_size];
    OUT_TYPE sol[out_rows*out_cols];
    TYPE filter[f_size];
};
