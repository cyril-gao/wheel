#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

#include "check.h"

/*
iven two strings s and t, return the minimum window in s which will contain all the characters in t. If there is no such window in s that covers all characters in t, return the empty string "".

Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Example 2:

Input: s = "a", t = "a"
Output: "a"
*/

namespace
{
    template <typename C>
    using String = std::basic_string<C>;

    template <typename C>
    std::pair<size_t, size_t> min_max(std::unordered_map<C, size_t> const& cache)
    {
        size_t _min, _max;
        auto i = cache.begin();
        _min = i->second;
        ++i;
        _max = i->second;
        ++i;
        if (_min > _max) {
            std::swap(_min, _max);
        }
        for (auto e = cache.end(); i != e; ++i) {
            if (i->second < _min) {
                _min = i->second;
            }
            if (i->second > _max) {
                _max = i->second;
            }
        }
        return std::make_pair(_min, _max);
    }

    template <typename TABLE, typename K>
    inline bool contains(TABLE const& hash_table, K k)
    {
        return hash_table.find(k) != hash_table.end();
    }

    template <typename C>
    String<C> _min_window_without_dup_in_pattern(const String<C>& input, const std::unordered_set<C>& pattern)
    {
        size_t min_size = SIZE_MAX;
        String<C> retval;
        size_t m = input.length();
        size_t n = pattern.size();
        assert(m >= n && n > 1);
        std::unordered_map<C, size_t> cache;
        auto updating_retval = [&]() {
            auto pair = min_max<C>(cache);
            size_t diff = pair.second - pair.first;
            if (diff < min_size) {
                min_size = diff;
                retval.assign(&input[pair.first], &input[pair.second + 1]);
            }
        };

        size_t count = n;
        for (size_t i = 0; i < m; ++i) {
            C c = input[i];
            if (contains(pattern, c)) {
                auto j = cache.find(c);
                if (j == cache.end()) {
                    cache[c] = i;
                    --count;
                    if (count == 0) {
                        updating_retval();
                    }
                }
                else {
                    j->second = i;
                    if (count == 0) {
                        updating_retval();
                    }
                }
            }
        }
        return retval;
    }

    template <typename T>
    class CyclicBuffer
    {
        size_t m_max_size;
        size_t m_next;
        std::vector<T> m_buffer;
    public:
        CyclicBuffer(size_t max_size) : m_max_size(max_size), m_next(0)
        {
            m_buffer.reserve(max_size);
        }
        CyclicBuffer() : CyclicBuffer(1) {}
        bool insert(const T& t)
        {
            bool retval = m_buffer.size() < m_max_size;
            if (retval) {
                m_buffer.push_back(t);
            } else {
                m_buffer[m_next++] = t;
                if (m_next == m_max_size) {
                    m_next = 0;
                }
            }
            return retval;
        }
        std::pair<T, T> min_max() const
        {
            if (m_max_size > 1) {
                size_t min = m_next;
                size_t max;
                if (min > 0) {
                    max = min - 1;
                } else {
                    max = m_max_size - 1;
                }
                return std::make_pair(m_buffer[min], m_buffer[max]);
            } else {
                return std::make_pair(m_buffer[0], m_buffer[0]);
            }
        }
    };

    template <typename C>
    std::pair<size_t, size_t> min_max(std::unordered_map<C, CyclicBuffer<size_t>> const& cache)
    {
        auto i = cache.begin();
        auto [_min, _max] = i->second.min_max();
        ++i;
        for (auto e = cache.end(); i != e; ++i) {
            auto [_min2, _max2] = i->second.min_max();
            if (_min > _min2) {
                _min = _min2;
            }
            if (_max < _max2) {
                _max = _max2;
            }
        }
        return std::make_pair(_min, _max);
    }

    template <typename C>
    String<C> _min_window_with_dup_in_pattern(const String<C>& input, size_t pattern_size, const std::unordered_map<C, size_t>& pattern)
    {
        size_t min_size = SIZE_MAX;
        String<C> retval;
        size_t m = input.length();
        assert(m >= pattern_size && pattern_size > 1);
        std::unordered_map<C, CyclicBuffer<size_t>> cache;
        auto updating_retval = [&]() {
            auto pair = min_max<C>(cache);
            size_t diff = pair.second - pair.first;
            if (diff < min_size) {
                min_size = diff;
                retval.assign(&input[pair.first], &input[pair.second + 1]);
            }
        };

        size_t count = pattern_size;
        for (size_t i = 0; i < m; ++i) {
            C c = input[i];
            auto pi = pattern.find(c);
            if (pi != pattern.end()) {
                auto j = cache.find(c);
                if (j == cache.end()) {
                    cache[c] = CyclicBuffer<size_t>(pi->second);
                }
                if (cache[c].insert(i)) {
                    --count;
                }
                if (count == 0) {
                    updating_retval();
                }
            }
        }
        return retval;
    }
}

template <typename C>
String<C> minimum_window(const String<C>& s, const String<C>& t)
{
    String<C> retval;
    size_t m = s.length();
    if (m > 0) {
        std::unordered_map<C, size_t> cache;
        size_t n = t.length();
        if (n > 0 && m >= n) {
            if (n > 1) {
                std::unordered_set<C> pattern;
                std::unordered_map<C, size_t> advanced_pattern;
                for (auto c : t) {
                    pattern.insert(c);
                    ++advanced_pattern[c];
                }
                if (pattern.size() == n) {
                    retval = _min_window_without_dup_in_pattern(s, pattern);
                } else {
                    retval = _min_window_with_dup_in_pattern(s, n, advanced_pattern);
                }
            } else {
                if (s.find(t[0]) != std::string::npos) {
                    retval = t;
                }
            }
        }
    }
    return retval;
}


int main(int argc, char * argv[])
{
    {
        auto r = minimum_window<char>("ADOBECOBLAEBANC", "ABC");
        examine(r == "BANC", "minimum_window is failed at the line: %d\n", __LINE__);
    }
    
    {
        auto r = minimum_window<char>("a", "a");
        examine(r == "a", "minimum_window is failed at the line: %d\n", __LINE__);
    }

    {
        auto r = minimum_window<char>("ADOBECOBLAEBANCBA", "ABC");
        examine(r == "CBA", "minimum_window is failed at the line: %d\n", __LINE__);
    }

    {
        auto r = minimum_window<char>("ADOBECOBLAEBANCBA", "AABC");
        examine(r == "ANCBA", "minimum_window is failed at the line: %d\n", __LINE__);
    }

    auto generate_random_input = [](size_t m) {
        srand(static_cast<unsigned int>(time(nullptr)));
        std::string retval;
        retval.reserve(m);
        for (size_t i = 0; i < m; ++i) {
            char c = static_cast<char>((static_cast<unsigned>(rand()) % 26) + 'A');
            retval.push_back(c);
        }
        return retval;
    };
    {
        size_t m = 10345879;
        std::string input = generate_random_input(m);
        std::string pattern;
        pattern.reserve(26);
        for (auto i = 'A'; i <= 'Z'; ++i) {
            pattern.push_back(i);
        }
        auto r = minimum_window<char>(input, pattern);
        printf("%s\n", r.c_str());

        r = minimum_window<char>(input, "AAAAABBBBBCCCCCDD");
        printf("%s\n", r.c_str());
    }

    for (int i = 1; i < argc; ++i) {
        std::ifstream ifs(argv[i]);
        if (ifs.is_open()) {
            std::string input, pattern;
            std::getline(ifs, input);
            std::getline(ifs, pattern);
            auto r = minimum_window<char>(input, pattern);
            printf("%s\n", r.c_str());
        }
    }
    return 0;
}
