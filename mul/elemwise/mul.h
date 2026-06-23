#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include <ap_int.h>

// 64-bit operands: exercises DSP mul_tiling on DSP48E2 (64x64=128 > 45-bit threshold)
#define TYPE      ap_int<64>
// 2N-bit product: avoids truncation of the high half of the multiplication
#define OUT_TYPE  ap_int<128>

// single multiplication
#define N 1

#define MIN 0
#define MAX 100

#define MAX_ITERATION 1

void mul(TYPE a[N], TYPE b[N], OUT_TYPE prod[N]);

////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE a[N];
  TYPE b[N];
  OUT_TYPE prod[N];
};
