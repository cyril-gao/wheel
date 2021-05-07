#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iterator>
#include <set>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "check.h"

/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Constraints:
    1 <= candidates.length <= 30
    1 <= candidates[i] <= 200
    All elements of candidates are distinct.
    1 <= target <= 500
*/
namespace
{
    template <typename T>
    void next_element(
        std::vector<T> const& input, size_t index, T target,
        std::vector<T>& selected,
        std::vector<std::vector<T>>& result
    ) {
        if (target != 0) {
            for (size_t i = index, n = input.size(); i < n && input[i] <= target; ++i) {
                selected.push_back(input[i]);
                next_element(input, i, target - input[i], selected, result);
                selected.pop_back();
            }
        } else {
            result.push_back(selected);
        }
    }
}

template <typename T>
std::vector<std::vector<T>> combination_sum(std::vector<T> const& candidates, T target)
{
    std::set<T> no_dup{candidates.cbegin(), candidates.cend()};
    std::vector<T> input{no_dup.cbegin(), no_dup.cend()};
    std::vector<T> selected;
    std::vector<std::vector<T>> retval;
    next_element(input, 0, target, selected, retval);
    return retval;
}

void combination_sum_test()
{
    {
        std::vector<int> candidates = {2, 3, 5};
        int target = 8;
        auto result = combination_sum(candidates, target);
        examine(result.size() == 3, "combination_sum is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> candidates = {2, 3, 5};
        int target = 1;
        auto result = combination_sum(candidates, target);
        examine(result.empty(), "combination_sum is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> candidates = {2};
        int target = 2;
        auto result = combination_sum(candidates, target);
        examine(result.size() == 1, "combination_sum is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> candidates = {1, 1};
        int target = 2;
        auto result = combination_sum(candidates, target);
        examine(result.size() == 1, "combination_sum is failed at the line: %d\n", __LINE__);
    }
}

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
*/
namespace
{
    std::unordered_map<char, std::vector<char>> mapping_table = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };

    std::vector<char> empty;

    std::vector<char> const& get_mapping(char c)
    {
        auto i = mapping_table.find(c);
        if (i != mapping_table.end()) {
            return i->second;
        }
        return empty;
    }

    void next_element(
        std::string const& digits,
        size_t index,
        std::vector<char>& selected,
        std::vector<std::string>& result
    ) {
        if (index < digits.length()) {
            decltype(auto) mapping = get_mapping(digits[index]);
            if (!mapping.empty()) {
                for (char c : mapping) {
                    selected.push_back(c);
                    next_element(digits, index + 1, selected, result);
                    selected.pop_back();
                }
            } else {
                next_element(digits, index + 1, selected, result);
            }
        } else {
            selected.push_back('\0');
            result.emplace_back(&selected[0]);
            selected.pop_back();
        }
    }
}

std::vector<std::string> letter_combinations(std::string const& digits)
{
    std::vector<std::string> retval;
    if (!digits.empty()) {
        std::vector<char> selected;
        next_element(digits, 0, selected, retval);
    }
    return retval;
}

void letter_combinations_test()
{
    {
        auto result = letter_combinations("23");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 9, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("279");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 48, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("");
        examine(result.empty(), "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("2");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 3, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("7");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 4, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
}


/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.
*/
namespace only_once
{
    template <typename T>
    struct Hash
    {
        std::size_t operator()(std::vector<T> const& vt) const noexcept
        {
            std::hash<T> hasher;
            const size_t mask = 37;
            size_t retval = 0;
            for (auto t : vt) {
                retval = retval * mask + hasher(t);
            }
            return retval;
        }
    };

    template <typename T>
    void next_element(
        std::vector<T> const& input, size_t index,
        T target,
        std::vector<T>& selected,
        std::unordered_set<std::vector<T>, Hash<T>>& result
    ) {
        if (target != 0) {
            for (size_t i = index, n = input.size(); i < n && input[i] <= target; ++i) {
                selected.push_back(input[i]);
                next_element(input, i + 1, target - input[i], selected, result);
                selected.pop_back();
            }
        } else {
            result.insert(selected);
        }
    }

    template <typename T>
    std::vector<std::vector<T>> combination_sum(std::vector<T> const& candidates, T target)
    {
        std::vector<std::vector<T>> retval;
        if (!candidates.empty()) {
            auto input{candidates};
            std::sort(input.begin(), input.end());
            std::unordered_set<std::vector<T>, Hash<T>> result;
            std::vector<T> selected;
            next_element(input, 0, target, selected, result);
            retval.assign(result.begin(), result.end());
        }
        return retval;
    }

    void combination_sum_test()
    {
        {
            std::vector<int> candidates = {2, 5, 2, 1, 2};
            int target = 5;
            auto result = combination_sum(candidates, target);
            examine(result.size() == 2, "combination_sum(each candidate is used only once) is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
            int target = 8;
            auto result = combination_sum(candidates, target);
            examine(result.size() == 4, "combination_sum(each candidate is used only once) is failed at the line: %d\n", __LINE__);
        }
    }
}


/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
    1. Each of the digits 1-9 must occur exactly once in each row.
    2. Each of the digits 1-9 must occur exactly once in each column.
    3. Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

The '.' character indicates empty cells.
*/
namespace
{
    bool is_used(char c)
    {
        return (c >= '1' && c <= '9');
    }

    void clear_cell(char& c)
    {
        c = '.';
    }

    bool contains(std::unordered_set<char> const& set, char item)
    {
        return (set.find(item) != set.end());
    }

    const std::unordered_set<char> sudoku_digits = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    std::unordered_set<char> get_row_candidates(std::vector<std::vector<char>> const& board, int row)
    {
        auto retval{sudoku_digits};
        for (char c : board[row]) {
            if (is_used(c)) {
                if (contains(retval, c)) {
                    retval.erase(c);
                } else {
                    throw std::invalid_argument("The board argument is invalid");
                }
            }
        }
        return retval;
    }

    std::unordered_set<char> get_col_candidates(std::vector<std::vector<char>> const& board, int col)
    {
        auto retval{sudoku_digits};
        for (int i = 0; i < 9; ++i) {
            char c = board[i][col];
            if (is_used(c)) {
                if (contains(retval, c)) {
                    retval.erase(c);
                } else {
                    throw std::invalid_argument("The board argument is invalid");
                }
            }
        }
        return retval;
    }

    std::unordered_set<char> get_grid_candidates(std::vector<std::vector<char>> const& board, int row, int col)
    {
        auto retval{sudoku_digits};
        int grid_row_start = (row / 3) * 3;
        int grid_col_start = (col / 3) * 3;
        for (int i = 0, row = grid_row_start; i < 3; ++i, ++row) {
            for (int j = 0, col = grid_col_start; j < 3; ++j, ++col) {
                char c = board[row][col];
                if (is_used(c)) {
                    if (contains(retval, c)) {
                        retval.erase(c);
                    } else {
                        throw std::invalid_argument("The board argument is invalid");
                    }
                }
            }
        }
        return retval;
    }

    std::vector<char> get_candidates(std::vector<std::vector<char>> const& board, int row, int col)
    {
        assert(row >= 0 && row < 9 && col >= 0 && col < 9);
        auto c1 = get_row_candidates(board, row);
        auto c2 = get_col_candidates(board, col);
        auto c3 = get_grid_candidates(board, row, col);

        std::vector<char> retval;
        retval.reserve(9);
        for (char c : sudoku_digits) {
            if (contains(c1, c) && contains(c2, c) && contains(c3, c)) {
                retval.push_back(c);
            }
        }
        return retval;
    }
}

bool next_element(std::vector<std::vector<char>>& board, int row, int col)
{
    bool retval = true;
    if (row < 9) {
        int new_row = row;
        int new_col = col + 1;
        if (new_col >= 9) {
            new_col -= 9;
            ++new_row;
        }
        retval = false;
        if (is_used(board[row][col])) {
            retval = next_element(board, new_row, new_col);
        } else {
            auto candidates = get_candidates(board, row, col);
            if (!candidates.empty()) {
                for (char c : candidates) {
                    board[row][col] = c;
                    if (next_element(board, new_row, new_col)) {
                        retval = true;
                        break;
                    }
                    clear_cell(board[row][col]);
                }
            }
        }
    }
    return retval;
}

void solve_sudoku(std::vector<std::vector<char>>& board)
{
    next_element(board, 0, 0);
}

void sudoku_test()
{
    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    std::vector<std::vector<char>> expectation = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };
    solve_sudoku(board);
    examine(board == expectation, "solve_sudoku is failed\n");
}


int main()
{
    combination_sum_test();
    letter_combinations_test();
    only_once::combination_sum_test();
    sudoku_test();
    printf("OK\n");
    return 0;
}
