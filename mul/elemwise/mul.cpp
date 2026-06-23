#include "mul.h"

void mul(TYPE a[N], TYPE b[N], OUT_TYPE prod[N]) {
    int i;
    OUT_TYPE mult;
    mul_loop:for (i = 0; i < N; i++) {
        mult = a[i] * b[i];
        prod[i] = mult;
    }
}
