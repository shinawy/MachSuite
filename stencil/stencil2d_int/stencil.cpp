#include "stencil.h"

// ap_int port of the MachSuite stencil2d kernel, sized 4x4 with a 3x3 filter.
// Loop structure preserved so the C->ArithV source-loop path models orig/filter
// /sol as arrays with indexed access (the 9 DSP multiplies stay in-graph).
void stencil (TYPE orig[row_size * col_size], OUT_TYPE sol[out_rows * out_cols], TYPE filter[f_size]){
    int r, c, k1, k2;
    OUT_TYPE mul;

    stencil_label1:for (r=0; r<row_size-2; r++) {
        stencil_label2:for (c=0; c<col_size-2; c++) {
            // Declare+init the accumulator INSIDE the c-loop (like gemm's `sum`):
            // the source-loop converter materializes a loop-local declaration but
            // drops a bare `temp = 0;` reassignment between loop levels, which
            // left temp accumulating across every output pixel.
            OUT_TYPE temp = 0;
            stencil_label3:for (k1=0;k1<3;k1++){
                stencil_label4:for (k2=0;k2<3;k2++){
                    mul = filter[k1*3 + k2] * orig[(r+k1)*col_size + c+k2];
                    temp += mul;
                }
            }
            sol[(r*out_cols) + c] = temp;
        }
    }
}
