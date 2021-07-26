#include <stdio.h>
#include <stdlib.h>

#include <chrono>

#include "matrix_multiply.h"

template <typename F>
matrix<int> run(F f, matrix<int> const& m1, matrix<int> const& m2, double& duration)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto result = f(m1, m2);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
    return result;
}

void matrix_mul_test(bool verifying)
{
    std::vector<size_t> sizes = {63, 127, 257, 511, 1027, 2049, 4139, 8117, 11113};
    if (verifying) {
        sizes.pop_back();
        sizes.pop_back();
        sizes.pop_back();
        sizes.pop_back();
    }
    for (const auto N : sizes) {
        matrix<int> m1 = new_instance<int>(N, N), m2 = new_instance<int>(N, N);
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

        double m2_duration = 0;
        auto r2 = run(mul2<int>, m1, m2, m2_duration);

        double m3_duration = 0;
        auto r3 = run(mul3<2048, int>, m1, m2, m3_duration);

        printf(
            "%5zu integers ->\tmethod2: %fs,\tmethod3: %fs\n",
            N, m2_duration, m3_duration
        );

        if (r2 != r3) {
            printf("the results from the method2 and the method3 are different\n");
        }
    }
}

int main(int argc, char* argv[])
{
    bool verifying = false;
    if (argc > 1 && strcmp(argv[1], "verify") == 0) {
        verifying = true;
    }
    matrix_mul_test(verifying);
    return 0;
}
