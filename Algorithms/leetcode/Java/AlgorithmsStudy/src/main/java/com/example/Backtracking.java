package com.example;

import java.util.*;

public class Backtracking {
    static class Positions {
        public int[] cols;

        public Positions(int n) {
            cols = new int[n];
            Arrays.fill(cols, -1);
        }

        public boolean isValid(int row, int col) {
            boolean retval = true;
            for (int i = 0; i < row; ++i) {
                if (cols[i] == col || (row - i) == Math.abs(col - cols[i])) {
                    retval = false;
                    break;
                }
            }
            return retval;
        }
    }

    private boolean selectNextPosition(int n, int row, Positions positions, List<List<Integer>> result) {
        boolean retval = false;
        if (row < n) {
            for (int col = 0; col < n; ++col) {
                if (positions.isValid(row, col)) {
                    positions.cols[row] = col;
                    if (selectNextPosition(n, row + 1, positions, result)) {
                        retval = true;
                    }
                    positions.cols[row] = -1;
                }
            }
        } else {
            List<Integer> solution = new ArrayList<Integer>(n);
            for (int i = 0; i < n; ++i) {
                solution.add(Integer.valueOf(positions.cols[i]));
            }
            result.add(solution);
            retval = true;
        }
        return retval;
    }

    public List<List<Integer>> queen(int n) {
        List<List<Integer>> retval = new LinkedList<>();
        if (n > 0) {
            Positions positions = new Positions(n);
            selectNextPosition(n, 0, positions, retval);
            // if (selectNextPosition(n, 0, positions, retval)) {
            // retval.stream().forEach(System.out::println);
            // }
        }
        return retval;
    }

    public List<List<String>> solveNQueens(int n) {
        List<List<Integer>> solutions = queen(n);
        List<List<String>> retval = new ArrayList<>(solutions.size());
        for (List<Integer> s : solutions) {
            List<String> board = new ArrayList<>(n);
            for (int p : s) {
                char[] line = new char[n];
                Arrays.fill(line, '.');
                line[p] = 'Q';
                board.add(new StringBuilder().append(line).toString());
            }
            retval.add(board);
        }
        return retval;
    }

    private boolean selectNext(int[] candidates, int from, int target, Deque<Integer> temporary,
            Set<List<Integer>> solutions) {
        boolean retval = false;
        if (target > 0) {
            if (candidates[from] <= target) {
                int left = target - candidates[from];
                temporary.addLast(candidates[from]);
                if (left > 0) {
                    for (int i = from; i < candidates.length && candidates[i] <= left; ++i) {
                        if (selectNext(candidates, i, left, temporary, solutions)) {
                            retval = true;
                        }
                    }
                } else {
                    List<Integer> solution = new ArrayList<>(temporary);
                    solutions.add(solution);
                    retval = true;
                }
                temporary.removeLast();
            }
        } else {
            List<Integer> solution = new ArrayList<>(temporary);
            solutions.add(solution);
            retval = true;
        }
        return retval;
    }

    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        Arrays.sort(candidates);
        Deque<Integer> temporary = new LinkedList<>();
        Set<List<Integer>> solutions = new HashSet<>();

        for (int i = 0; i < candidates.length && candidates[i] <= target; ++i) {
            selectNext(candidates, i, target, temporary, solutions);
        }

        return new ArrayList<List<Integer>>(solutions);
    }

    private boolean selectNext2(int[] candidates, int from, int target, Deque<Integer> temporary,
            Set<List<Integer>> solutions) {
        boolean retval = false;
        if (target > 0) {
            if (candidates[from] <= target) {
                int left = target - candidates[from];
                temporary.addLast(candidates[from]);
                if (left > 0) {
                    for (int i = from + 1; i < candidates.length && candidates[i] <= left; ++i) {
                        if (selectNext2(candidates, i, left, temporary, solutions)) {
                            retval = true;
                        }
                    }
                } else {
                    List<Integer> solution = new ArrayList<>(temporary);
                    solutions.add(solution);
                    retval = true;
                }
                temporary.removeLast();
            }
        } else {
            List<Integer> solution = new ArrayList<>(temporary);
            solutions.add(solution);
            retval = true;
        }
        return retval;
    }

    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        Deque<Integer> temporary = new LinkedList<>();
        Set<List<Integer>> solutions = new HashSet<>();

        for (int i = 0; i < candidates.length && candidates[i] <= target; ++i) {
            selectNext2(candidates, i, target, temporary, solutions);
        }

        return new ArrayList<List<Integer>>(solutions);
    }

    private boolean selectNext(int n, int k, int from, int index, int[] tmp, List<List<Integer>> solutions) {
        boolean retval = false;
        int nextIndex = index + 1;
        tmp[index] = from;
        if (nextIndex < k) {
            for (int i = from + 1; i <= (n - k + index + 2); ++i) {
                if (selectNext(n, k, i, index + 1, tmp, solutions)) {
                    retval = true;
                }
            }
        } else {
            List<Integer> solution = new ArrayList<>(tmp.length);
            for (int v : tmp) {
                solution.add(v);
            }
            solutions.add(solution);
        }
        tmp[index] = 0;
        return retval;
    }

    public List<List<Integer>> combine(int n, int k) {
        int[] tmp = new int[k];
        List<List<Integer>> solutions = new LinkedList<>();
        for (int i = 1; i <= (n - k + 1); ++i) {
            selectNext(n, k, i, 0, tmp, solutions);
        }
        return solutions;
    }

    /*
     * A message containing letters from A-Z can be encoded into numbers using the
     * following mapping:
     *      'A' -> "1"
     *      'B' -> "2"
     *      ...
     *      'Z' -> "26"
     * To decode an encoded message, all the digits must be grouped then mapped back into
     * letters using the reverse of the mapping above (there may be multiple ways).
     * For example, "11106" can be mapped into:
     *      "AAJF" with the grouping (1 1 10 6)
     *      "KJF" with the grouping (11 10 6)
     * Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F'
     * since "6" is different from "06".
     * 
     * Given a string s containing only digits, return the number of ways to decode
     * it.
     * 
     * The answer is guaranteed to fit in a 32-bit integer.
     */
    private void nextStep(
        String input,
        int start,
        int[] result
    ) {
        int n = input.length();
        if (start < n) {
            char c = input.charAt(start);
            if (c != '0') {
                for (int i = 0, j = start + 1; i < 2 && j <= n; ++i, ++j) {
                    if (
                        i == 0 ||
                        c == '1' ||
                        (c == '2' && input.charAt(i) <= '6')
                    ) {
                        nextStep(input, j, result);
                    }
                }
            }
        } else {
            ++result[0];
        }
    }

    // its performance is not good
    public int numDecodings(String s) {
        var result = new int[1];
        nextStep(s, 0, result);
        return result[0];
    }
}
