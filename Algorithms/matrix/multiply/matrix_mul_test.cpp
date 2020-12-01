#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <chrono>
#include <vector>


void mul1(
    std::vector<std::vector<int>> const & m1,
    std::vector<std::vector<int>> const & m2,
    std::vector<std::vector<int>> & result
) {
    size_t m = m1.size();
    size_t n = m1[0].size();
    assert(n == m2.size());
    size_t k = m2[0].size();
    assert(result.empty());
    result.resize(m, std::vector<int>(k));

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < k; ++j) {
            int total = 0;
            for (size_t l = 0; l < n; ++l) {
                total += m1[i][l] * m2[l][j];
            }
            result[i][j] = total;
        }
    }
}

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> const & input)
{
    size_t m = input.size();
    size_t n = input[0].size();
    std::vector<std::vector<int>> result(n, std::vector<int>(m));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[j][i] = input[i][j];
        }
    }
    return result;
}

template <size_t BATCH_SIZE>
std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> const & input)
{
    const size_t M = input.size();
    const size_t N = input[0].size();
    std::vector<std::vector<int>> result(M, std::vector<int>(N));

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

void mul2(
    std::vector<std::vector<int>> const & m1,
    std::vector<std::vector<int>> const & m2,
    std::vector<std::vector<int>> & result
) {
    size_t m = m1.size();
    size_t n = m1[0].size();
    assert(n == m2.size());
    size_t k = m2[0].size();
    assert(result.empty());
    result.resize(m, std::vector<int>(k));

    auto transposed = transpose<512>(m2);
    //auto transposed = transpose(m2);
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < k; ++j) {
            int total = 0;
            for (size_t l = 0; l < n; ++l) {
                total += m1[i][l] * transposed[j][l];
            }
            result[i][j] = total;
        }
    }
}

template <size_t BATCH_SIZE>
void mul3(
    std::vector<std::vector<int>> const & m1,
    std::vector<std::vector<int>> const & m2,
    std::vector<std::vector<int>> & result
) {
    const size_t M = m1.size();
    const size_t N = m1[0].size();
    assert(N == m2.size());
    const size_t K = m2[0].size();
    assert(result.empty());
    result.resize(M, std::vector<int>(K));

#if 0
    std::vector<int> cache(BATCH_SIZE);
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
            int * cache = &result[r][ci];
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
            int * cache = &result[r][ci];
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
}

#if 0
// not better than method3
template <size_t BATCH_SIZE>
void mul4(
    std::vector<std::vector<int>> const & m1,
    std::vector<std::vector<int>> const & m2,
    std::vector<std::vector<int>> & result
) {
    const size_t M = m1.size();
    const size_t N = m1[0].size();
    assert(N == m2.size());
    const size_t K = m2[0].size();
    assert(result.empty());
    result.resize(M, std::vector<int>(K, 0));

    const size_t MB = M/BATCH_SIZE, MR = M%BATCH_SIZE, MI = MB*BATCH_SIZE;
    const size_t NB = N/BATCH_SIZE, NR = N%BATCH_SIZE, NI = NB*BATCH_SIZE;
    const size_t KB = K/BATCH_SIZE, KR = K%BATCH_SIZE, KI = KB*BATCH_SIZE;
    
    for (size_t r = 0; r < MB; ++r) {
        for (size_t c = 0; c < KB; ++c) {
            for (size_t b = 0; b < NB; ++b) {
                for (size_t i = 0, ri = r * BATCH_SIZE; i < BATCH_SIZE; ++i, ++ri) {
                    for (size_t j = 0, ci = c * BATCH_SIZE; j < BATCH_SIZE; ++j, ++ci) {
                        for (size_t k = 0, bi = b * BATCH_SIZE; k < BATCH_SIZE; ++k, ++bi) {
                            result[ri][ci] += m1[ri][bi] * m2[bi][ci];
                        }
                    }
                }
            }
        }
    }
}
#endif

void matrix_mul_test()
{
    std::chrono::steady_clock::time_point begin, end;
    const size_t sizes[] = {63, 127, 257, 511, 1027, 2049, 4139, 8117, 11113};
    for (const auto N : sizes) {
        std::vector<std::vector<int>> m1(N, std::vector<int>(N)), m2(m1);
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                m1[i][j] = rand() % 7;
            }
        }
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                m2[i][j] = rand() % 11;
            }
        }
        begin = std::chrono::steady_clock::now();
        std::vector<std::vector<int>> r2;
        mul2(m1, m2, r2);
        end = std::chrono::steady_clock::now();
        auto d2 = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
        printf("%zu elements -> execution time for method2: %f seconds\n", N, d2);

        begin = std::chrono::steady_clock::now();
        std::vector<std::vector<int>> r3;
        mul3<2048>(m1, m2, r3);
        end = std::chrono::steady_clock::now();
        auto d3 = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
        printf("%zu elements -> execution time for method3: %f seconds\n", N, d3);

        if (r2 != r3) {
            printf("the results from the method2 and the method3 are different\n");
        }
        printf("\n");
    }
}

int main()
{
    matrix_mul_test();
#if 0
    {
    #if ( defined( _DEBUG ) || defined( DEBUG ) || defined( DBG ) )
        const size_t N = 39;
    #else
        const size_t N = 11111;
    #endif
        std::vector<std::vector<int>> m1(N, std::vector<int>(N)), m2(m1);
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                m1[i][j] = rand() % 7;
            }
        }
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                m2[i][j] = rand() % 11;
            }
        }

        std::chrono::steady_clock::time_point begin, end;
        //begin = std::chrono::steady_clock::now();
        //std::vector<std::vector<int>> r1;
        //mul1(m1, m2, r1);
        //end = std::chrono::steady_clock::now();
        //auto d1 = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();

        begin = std::chrono::steady_clock::now();
        std::vector<std::vector<int>> r2;
        mul2(m1, m2, r2);
        end = std::chrono::steady_clock::now();
        auto d2 = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
        printf("execution time for method2: %f seconds\n", d2);

        begin = std::chrono::steady_clock::now();
        std::vector<std::vector<int>> r3;
        mul3<2048>(m1, m2, r3);
        end = std::chrono::steady_clock::now();
        auto d3 = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
        printf("execution time for method3: %f seconds\n", d3);

        // begin = std::chrono::steady_clock::now();
        // std::vector<std::vector<int>> r4;
        // mul4<32>(m1, m2, r4);
        // end = std::chrono::steady_clock::now();
        // auto d4 = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
        // printf("execution time for method4: %f seconds\n", d4);

        //printf("execution time for method2: %f seconds\nexecution time for method3: %f seconds\n", d2, d3);
        if (r2 != r3) {
            printf("the results from the method2 and the method3 are different\n");
        }
        // if (r2 != r4) {
            // printf("the results from the method2 and the method4 are different\n");
        // }
        // printf(
           // "execution time for method1: %f seconds\n"
           // "execution time for method2: %f seconds\n"
           // "execution time for method3: %f seconds\n",
           // d1, d2, d3
        // );
        // if (r1 != r2) {
           // printf("method2 is bad\n");
        // }
        // if (r1 != r3) {
           // printf("method3 is bad\n");
        // }
    }
#endif

    return 0;
}
