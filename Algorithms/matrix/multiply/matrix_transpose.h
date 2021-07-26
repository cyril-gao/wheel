#ifndef MATRIX_TRANSPOSE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define MATRIX_TRANSPOSE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include "matrix.h"


template <typename T>
matrix<T> transpose(matrix<T> const& input)
{
    size_t M = rows(input);
    size_t N = cols(input);

    auto result = new_instance<T>(M, N);
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result[j][i] = input[i][j];
        }
    }
    return result;
}


template <size_t BATCH_SIZE, typename T>
matrix<T> transpose(matrix<T> const & input)
{
    const size_t M = rows(input);
    const size_t N = cols(input);
    auto result = new_instance<T>(M, N);

    const size_t MB = M/BATCH_SIZE, MR = M%BATCH_SIZE, MI = MB * BATCH_SIZE;
    const size_t NB = N/BATCH_SIZE, NR = N%BATCH_SIZE, NI = NB * BATCH_SIZE;

    for (size_t r = 0; r < MB; ++r) {
        size_t ri = r * BATCH_SIZE;
        for (size_t c = 0; c < NB; ++c) {
            size_t ci = c * BATCH_SIZE;
            for (size_t i = 0; i < BATCH_SIZE; ++i) {
                size_t ii = ri + i;
                for (size_t j = 0; j < BATCH_SIZE; ++j) {
                    size_t ji = ci + j;
                    result[ji][ii] = input[ii][ji];
                }
            }
        }
        if (NR != 0) {
            for (size_t i = 0; i < BATCH_SIZE; ++i) {
                size_t ii = ri + i;
                for (size_t j = NI; j < N; ++j) {
                    result[j][ii] = input[ii][j];
                }
            }
        }
    }
    if (MR != 0) {
        for (size_t c = 0; c < NB; ++c) {
            size_t ci = c * BATCH_SIZE;
            for (size_t i = MI; i < M; ++i) {
                for (size_t j = 0; j < BATCH_SIZE; ++j) {
                    size_t ji = ci + j;
                    result[ji][i] = input[i][ji];
                }
            }
        }
        if (NR != 0) {
            for (size_t i = MI; i < M; ++i) {
                for (size_t j = NI; j < N; ++j) {
                    result[j][i] = input[i][j];
                }
            }
        }
    }
    return result;
}

#endif //MATRIX_TRANSPOSE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
