#include "gemm.h"

// ap_int port of MachSuite gemm/ncubed, sized 4x4 with 16-bit operands.
// Loop structure preserved so the C->ArithV source-loop path models m1/m2/prod
// as arrays with indexed access (the DSP-Auto multiplies stay in-graph).
void gemm(TYPE m1[N], TYPE m2[N], OUT_TYPE prod[N]) {
    int i, j, k;
    int i_col, k_col;
    OUT_TYPE mult;

    outer:for (i = 0; i < row_size; i++) {
        middle:for (j = 0; j < col_size; j++) {
            i_col = i * col_size;
            OUT_TYPE sum = 0;
            inner:for (k = 0; k < row_size; k++) {
                k_col = k * col_size;
                mult = m1[i_col + k] * m2[k_col + j];
                sum += mult;
            }
            prod[i_col + j] = sum;
        }
    }
}
