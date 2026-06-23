#include "mul.h"
#include <string.h>

int INPUT_SIZE = sizeof(struct bench_args_t);

void run_benchmark(void *vargs) {
    struct bench_args_t *args = (struct bench_args_t *)vargs;
    mul(args->a, args->b, args->prod);
}

/* Input format:
%% Section 1
int64_t[N]: operand a
%% Section 2
int64_t[N]: operand b
*/

void input_to_data(int fd, void *vdata) {
    struct bench_args_t *data = (struct bench_args_t *)vdata;
    char *p, *s;
    int64_t tmp[N];
    int i;
    memset(vdata, 0, sizeof(struct bench_args_t));
    p = readfile(fd);

    s = find_section_start(p, 1);
    parse_int64_t_array(s, tmp, N);
    for (i = 0; i < N; i++) data->a[i] = (TYPE)tmp[i];

    s = find_section_start(p, 2);
    parse_int64_t_array(s, tmp, N);
    for (i = 0; i < N; i++) data->b[i] = (TYPE)tmp[i];
    free(p);
}

void data_to_input(int fd, void *vdata) {
    struct bench_args_t *data = (struct bench_args_t *)vdata;
    int64_t tmp[N];
    int i;

    for (i = 0; i < N; i++) tmp[i] = (int64_t)data->a[i];
    write_section_header(fd);
    write_int64_t_array(fd, tmp, N);

    for (i = 0; i < N; i++) tmp[i] = (int64_t)data->b[i];
    write_section_header(fd);
    write_int64_t_array(fd, tmp, N);
}

/* Output format:
%% Section 1
int64_t[N]: products
*/

void output_to_data(int fd, void *vdata) {
    struct bench_args_t *data = (struct bench_args_t *)vdata;
    char *p, *s;
    int64_t tmp[N];
    int i;
    p = readfile(fd);
    s = find_section_start(p, 1);
    parse_int64_t_array(s, tmp, N);
    for (i = 0; i < N; i++) data->prod[i] = (TYPE)tmp[i];
    free(p);
}

void data_to_output(int fd, void *vdata) {
    struct bench_args_t *data = (struct bench_args_t *)vdata;
    int64_t tmp[N];
    int i;
    for (i = 0; i < N; i++) tmp[i] = (int64_t)data->prod[i];
    write_section_header(fd);
    write_int64_t_array(fd, tmp, N);
}

int check_data(void *vdata, void *vref) {
    struct bench_args_t *data = (struct bench_args_t *)vdata;
    struct bench_args_t *ref  = (struct bench_args_t *)vref;
    int has_errors = 0;
    int i;
    for (i = 0; i < N; i++)
        has_errors |= (data->prod[i] != ref->prod[i]);
    return !has_errors;
}
