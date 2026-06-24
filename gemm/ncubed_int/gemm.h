#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include <ap_int.h>

// 4x4 integer matrix multiply with 16-bit operands. Exercises the DSP 16x16
// multiply plus the inner-product (row_size-term) adder tree on DSP48E2.
#define TYPE      ap_int<16>
// 16x16 product is 32-bit; summed over row_size terms -> fits in 48 bits
// (the DSP48E2 P accumulator width), no truncation of the accumulated result.
#define OUT_TYPE  ap_int<48>

#define row_size 4
#define col_size 4
#define N (row_size*col_size)

#define MIN 0
#define MAX 100

#define MAX_ITERATION 1

void gemm(TYPE m1[N], TYPE m2[N], OUT_TYPE prod[N]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE m1[N];
  TYPE m2[N];
  OUT_TYPE prod[N];
};
