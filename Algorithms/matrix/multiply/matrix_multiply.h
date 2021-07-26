#ifndef MATRIX_MULTIPLY_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define MATRIX_MULTIPLY_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <string.h>
#include "matrix_transpose.h"

template <typename T>
matrix<T> mul1(matrix<T> const& m1, matrix<T> const& m2)
{
    size_t M = rows(m1);
    size_t N = cols(m1);
    assert(N == rows(m2));
    size_t K = cols(m2);

    auto result = new_instance<T>(M, K);
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < K; ++j) {
            T total = 0;
            for (size_t l = 0; l < N; ++l) {
                total += m1[i][l] * m2[l][j];
            }
            result[i][j] = total;
        }
    }
    return result;
}

template <typename T>
matrix<T> mul2(matrix<T> const& m1, matrix<T> const& m2)
{
    size_t M = rows(m1);
    size_t N = cols(m1);
    assert(N == rows(m2));
    size_t K = cols(m2);

    auto result = new_instance<T>(M, K);
    auto transposed = transpose<512, T>(m2);
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < K; ++j) {
            T total = 0;
            for (size_t l = 0; l < N; ++l) {
                total += m1[i][l] * transposed[j][l];
            }
            result[i][j] = total;
        }
    }
    return result;
}

template <size_t BATCH_SIZE, typename T>
matrix<T> mul3(matrix<T> const& m1, matrix<T> const& m2)
{
    size_t M = rows(m1);
    size_t N = cols(m1);
    assert(N == rows(m2));
    size_t K = cols(m2);

    auto result = new_instance<T>(M, K);

#if 0
    std::vector<T> cache(BATCH_SIZE);
    size_t bytes = sizeof(cache[0]) * cache.size();

    for (size_t r = 0; r < M; ++r) {
        for (size_t c = 0, ce = (K + BATCH_SIZE - 1) / BATCH_SIZE; c < ce; ++c) {
            size_t ci = c * BATCH_SIZE;
            memset(&cache[0], 0, bytes);
            for (size_t b = 0, be = (N + BATCH_SIZE - 1) / BATCH_SIZE; b < be; ++b) {
                size_t bi = b * BATCH_SIZE;
                for (size_t i = 0; i < BATCH_SIZE; ++i) {
                    size_t ii = bi + i;
                    if (ii < N) {
                        auto v = m1[r][ii];
                        for (size_t j = 0; j < BATCH_SIZE; ++j) {
                            size_t ji = ci + j;
                            if (ji < K) {
                                cache[j] += (v * m2[ii][ji]);
                            }
                            else {
                                bytes = j * sizeof(cache[0]);
                                break;
                            }
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            memcpy(&result[r][ci], &cache[0], bytes);
        }
    }
#else
    const size_t KB = K/BATCH_SIZE, KR = K%BATCH_SIZE, KI = KB*BATCH_SIZE;
    const size_t NB = N/BATCH_SIZE, NR = N%BATCH_SIZE, NI = NB*BATCH_SIZE;
    for (size_t r = 0; r < M; ++r) {
        for (size_t c = 0; c < KB; ++c) {
            size_t ci = c * BATCH_SIZE;
            T * cache = &result[r][ci];
            for (size_t b = 0; b < NB; ++b) {
                size_t bi = b * BATCH_SIZE;
                for (size_t i = 0; i < BATCH_SIZE; ++i) {
                    size_t ii = bi + i;
                    auto v = m1[r][ii];
                    for (size_t j = 0; j < BATCH_SIZE; ++j) {
                        size_t ji = ci + j;
                        cache[j] += (v * m2[ii][ji]);
                    }
                }
            }

            for (size_t i = 0; i < NR; ++i) {
                size_t ii = NI + i;
                auto v = m1[r][ii];
                for (size_t j = 0; j < BATCH_SIZE; ++j) {
                    size_t ji = ci + j;
                    cache[j] += (v * m2[ii][ji]);
                }
            }
        }
    }
    if (KR != 0) {
        for (size_t r = 0; r < M; ++r) {
            size_t ci = KI;
            T * cache = &result[r][ci];
            for (size_t b = 0; b < NB; ++b) {
                size_t bi = b * BATCH_SIZE;
                for (size_t i = 0; i < BATCH_SIZE; ++i) {
                    size_t ii = bi + i;
                    auto v = m1[r][ii];
                    for (size_t j = 0; j < KR; ++j) {
                        size_t ji = ci + j;
                        cache[j] += (v * m2[ii][ji]);
                    }
                }
            }

            for (size_t i = 0; i < NR; ++i) {
                size_t ii = NI + i;
                auto v = m1[r][ii];
                for (size_t j = 0; j < KR; ++j) {
                    size_t ji = ci + j;
                    cache[j] += (v * m2[ii][ji]);
                }
            }
        }
    }
#endif
    return result;
}

#endif //MATRIX_MULTIPLY_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
