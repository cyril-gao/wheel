#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "check.h"


int main()
{
    try {
        for (int i = -100; i < 100; ++i) {
            BigInteger bi(i);
            for (int j = -100; j < 100; ++j) {
                BigInteger bj(j);
                examine(bi + bj == i + j, "add is failed\n");
                examine(bi - bj == i - j, "sub is failed\n");
                examine(bi * bj == i * j, "mul is failed\n");
                if (j != 0) {
                    examine(bi / bj == i / j, "div is failed\n");
                    examine(bi % bj == i % j, "mod is failed\n");
                }
                BigInteger bj2 = -bj;
                examine(-bj2 == bj, "negative is failed\n");
            }
        }

        for (int i = -100; i < 100; ++i) {
            BigInteger bi(i);
            for (int j = -100; j < 100; ++j) {
                BigInteger bj(j);
    
                {
                    BigInteger bi1(bi);
                    int i1 = i;
                    bi1 += bj, i1 += j;
                    examine(bi1 == i1, "add is failed\n");
                }
                {
                    BigInteger bi1(bi);
                    int i1 = i;
                    bi1 -= bj, i1 -= j;
                    examine(bi1 == i1, "sub is failed\n");
                }
                {
                    BigInteger bi1(bi);
                    int i1 = i;
                    bi1 *= bj, i1 *= j;
                    examine(bi1 == i1, "mul is failed\n");
                }
                if (j != 0) {
                    BigInteger bi1(bi);
                    int i1 = i;
                    bi1 /= bj, i1 /= j;
                    examine(bi1 == i1, "div is failed\n");
                }
            }
        }

        for (int64_t i = -100; i < 100; ++i) {
            BigInteger bi(i);
            for (size_t j = 0; j < 10; ++j) {
                examine((bi << j) == (i << j), "left shift is failed for %lld >> %d\n", i, j);
                {
                    auto bi1(bi);
                    auto i1(i);
                    bi1 <<= j;
                    i1 <<= j;
                    examine(bi1 == i1, "left shift is failed for %lld >> %d\n", i, j);
                }
            }
        }
        for (int64_t i = 0; i < 256; ++i) {
            BigInteger bi(i);
            for (size_t j = 0; j < 10; ++j) {
                {
                    auto r1 = bi >> j;
                    auto r2 = i >> j;
                    examine(r1 == r2, "right shift is failed for %lld >> %d (%s <-> %lld)\n", i, j, static_cast<std::string>(r1).c_str(), r2);
                }
                {
                    auto bi1(bi);
                    auto i1(i);
                    bi1 >>= j;
                    i1 >>= j;
                    examine(bi1 == i1, "right shift is failed for %lld >>= %d\n", i, j);
                }
            }
        }

        {
            uint64_t a = 73486UL, b = 45743UL, m = 548657UL;
            BigInteger ba(a), bb(b), bm(m);
            examine((a + b) % m == mod_add(ba, bb, bm), "mod_add is failed\n");
        }
        {
            auto make_x_be_mod_inverse = [](const BigInteger& a, const BigInteger& b, std::array<BigInteger, 3>& euclid_result) {
                while (euclid_result[1].is_negative()) {
                    euclid_result[1] += b;
                    euclid_result[2] -= a;
                }
                if (euclid_result[1] >= b) {
                    euclid_result[1] = euclid_result[1] % b;
                }
            };
            BigInteger a("34635273562734523754236542837913"), b("97354325452334239584563476534655321967");
            auto result = euclid(a, b);
            examine(result[0] == a * result[1] + b * result[2], "euclid is failed\n");
            make_x_be_mod_inverse(a, b, result);
            examine(result[0] == a * result[1] + b * result[2], "euclid is failed\n");
            auto inverse = mod_inverse(a, b);
            examine(result[1] == inverse, "euclid is failed\n");
        }
        {
            size_t bits = 2048;
            auto p = BigInteger::generate_prime(bits);
            auto q = BigInteger::generate_prime(bits);
            auto N = p * q;
            auto M = (p - 1) * (q - 1);
            auto e = BigInteger(65537);
            auto d = mod_inverse(e, M);
            printf("private key: %s\n", to_string(d).c_str());
        }
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
