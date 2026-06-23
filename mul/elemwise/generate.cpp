#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "mul.h"

int main(int argc, char **argv)
{
    struct bench_args_t data;
    int i, fd;
    struct prng_rand_t state;

    prng_srand(1, &state);
    for (i = 0; i < N; i++) {
        data.a[i] = (TYPE)(prng_rand(&state) % (uint64_t)(MAX - MIN) + MIN);
        data.b[i] = (TYPE)(prng_rand(&state) % (uint64_t)(MAX - MIN) + MIN);
    }

    fd = open("input.data", O_WRONLY|O_CREAT|O_TRUNC,
              S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    assert(fd > 0 && "Couldn't open input data file");
    data_to_input(fd, (void *)(&data));
    close(fd);

    // Compute reference output
    mul(data.a, data.b, data.prod);

    fd = open("check.data", O_WRONLY|O_CREAT|O_TRUNC,
              S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    assert(fd > 0 && "Couldn't open check data file");
    data_to_output(fd, (void *)(&data));
    close(fd);

    return 0;
}
