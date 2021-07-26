#ifndef MATRIX_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define MATRIX_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <assert.h>
#include <stdint.h>
#include <vector>

template <typename T>
using matrix = std::vector<std::vector<T>>;

template <typename T>
inline matrix<T> new_instance(size_t rows, size_t columns)
{
    return matrix<T>(rows, std::vector<T>(columns));
}

template <typename T>
inline size_t rows(matrix<T> const& m)
{
    assert(!m.empty());
    return m.size();
}

template <typename T>
inline size_t cols(matrix<T> const& m)
{
    assert(!m.empty() && !m[0].empty());
    return m[0].size();
}

#endif //MATRIX_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
