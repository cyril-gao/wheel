package com.example;

import java.util.*;

public class MatrixOperations {
    private void rotate(int[][] matrix, int row, int colRight, int rowBottom) {
        int diff = rowBottom - row;
        for (int col = row; col < colRight; ++col) {
            int tmp = matrix[row][col];
            int leftRow = row + (diff - (col - row)), leftCol = row;
            matrix[row][col] = matrix[leftRow][leftCol];
            int bottomRow = rowBottom, bottomCol = leftCol + (diff - (rowBottom - leftRow));
            matrix[leftRow][leftCol] = matrix[bottomRow][bottomCol];
            int rightRow = bottomRow - (diff - (colRight - bottomCol)), rightCol = colRight;
            matrix[bottomRow][bottomCol] = matrix[rightRow][rightCol];
            matrix[rightRow][rightCol] = tmp;
        }
    }

    public void rotate(int[][] matrix) {
        if (matrix != null && matrix.length > 1) {
            int loop = (matrix.length + 1) / 2;
            int row = 0, colRight = row + matrix.length - 1, rowBottom = colRight;
            for (int i = 0; i < loop; ++i) {
                rotate(matrix, row, colRight, rowBottom);
                ++row;
                --colRight;
                --rowBottom;
            }
        }
    }

    public List<Integer> spiralOrder(int[][] matrix) {
        int m = matrix.length, n = 0;
        if (m > 0) {
            n = matrix[0].length;
        }
        int total = m * n;
        List<Integer> retval = new ArrayList<>(total);
        if (total > 0) {
            int topRow = 0, topCol = n - 1;
            int bottomRow = m - 1;
            while (topRow <= topCol && topRow <= bottomRow) {
                for (int col = topRow; col <= topCol; ++col) {
                    retval.add(matrix[topRow][col]);
                }
                for (int row = topRow + 1; row <= bottomRow; ++row) {
                    retval.add(matrix[row][topCol]);
                }
                if (topRow < bottomRow) {
                    for (int col = topCol - 1; col >= topRow; --col) {
                        retval.add(matrix[bottomRow][col]);
                    }
                }
                if (topRow < topCol) {
                    for (int row = bottomRow - 1, col = topRow; row > topRow; --row) {
                        retval.add(matrix[row][col]);
                    }
                }
                ++topRow;
                --topCol;
                --bottomRow;
            }
        }
        return retval;
    }

    public int[][] generateMatrix(int n) {
        int[][] retval = new int[n][n];
        int rowTop = 0, rowBottom = n - 1;
        int colLeft = 0, colRight = rowBottom;
        int v = 1;
        for (int count = 0; count < n; count += 2) {
            for (int i = colLeft; i <= colRight; ++i) {
                retval[rowTop][i] = v++;
            }
            for (int i = rowTop + 1; i <= rowBottom; ++i) {
                retval[i][colRight] = v++;
            }
            for (int i = colRight - 1; i >= colLeft; --i) {
                retval[rowBottom][i] = v++;
            }
            for (int i = rowBottom - 1; i > rowTop; --i) {
                retval[i][colLeft] = v++;
            }
            ++rowTop;
            --rowBottom;
            ++colLeft;
            --colRight;
        }
        return retval;
    }

    private static int getValue(int[][] matrix, int m, int n, int i) {
        int row = i / n;
        int col = i % n;
        return matrix[row][col];
    }

    public boolean searchMatrix(int[][] matrix, int target) {
        boolean retval = false;
        int m = matrix.length;
        if (m > 0) {
            int n = matrix[0].length;
            if (n > 0) {
                int begin = 0;
                int end = m * n;
                int mid = end;
                while (begin < end) {
                    mid = (begin + end) / 2;
                    int middle = getValue(matrix, m, n, mid);
                    if (middle > target) {
                        end = mid;
                        mid = begin;
                    } else if (middle < target) {
                        begin = mid + 1;
                        mid = end;
                    } else {
                        break;
                    }
                }
                retval = (mid != end && getValue(matrix, m, n, mid) == target);
            }
        }
        return retval;
    }

    public void setZeroesByBruteForce(int[][] matrix) {
        int m = matrix.length;
        if (m > 0) {
            int n = matrix[0].length;
            if (n > 0) {
                List<int[]> records = new LinkedList<int[]>();
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (matrix[i][j] == 0) {
                            int[] item = { i, j };
                            records.add(item);
                        }
                    }
                }
                for (int[] r : records) {
                    int row = r[0];
                    int col = r[1];
                    for (int i = 0; i < n; ++i) {
                        matrix[row][i] = 0;
                    }
                    for (int i = 0; i < m; ++i) {
                        matrix[i][col] = 0;
                    }
                }
            }
        }
    }

    // https://leetcode.com/problems/set-matrix-zeroes/
    public void setZeroes(int[][] matrix) {
        int m = matrix.length;
        if (m > 0) {
            int n = matrix[0].length;
            if (n > 0) {
                int row = 0;
                int col = 0;
                while (row < m && col < n) {
                    if (matrix[row][col] == 0) {
                        break;
                    }
                    ++col;
                    if (col == n) {
                        col = 0;
                        ++row;
                    }
                }
                if (row < m && col < n) {
                    for (int i = row, j = col;;) {
                        ++j;
                        if (j == n) {
                            j = 0;
                            ++i;
                        }
                        if (i < m && j < n) {
                            if (matrix[i][j] == 0) {
                                matrix[i][col] = 0;
                                matrix[row][j] = 0;
                            }
                        } else {
                            break;
                        }
                    }
                    for (int j = 0; j < n; ++j) {
                        if (j != col) {
                            if (matrix[row][j] == 0) {
                                for (int i = 0; i < m; ++i) {
                                    matrix[i][j] = 0;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < m; ++i) {
                        if (i != row) {
                            if (matrix[i][col] == 0) {
                                for (int j = 0; j < n; ++j) {
                                    matrix[i][j] = 0;
                                }
                            }
                        }
                    }
                    for (int j = 0; j < n; ++j) {
                        matrix[row][j] = 0;
                    }
                    for (int i = 0; i < m; ++i) {
                        matrix[i][col] = 0;
                    }
                }
            }
        }
    }

    private static boolean searchInOrderedMatrix(int[][] matrix, int rowBegin, int rowEnd, int colBegin, int colEnd,
            int target) {
        boolean retval = false;
        int rowMid = rowEnd, colMid = colEnd;
        if (rowBegin < rowEnd && colBegin < colEnd) {
            rowMid = (rowBegin + rowEnd) / 2;
            colMid = (colBegin + colEnd) / 2;
            if (rowMid > rowBegin && colMid > colBegin) {
                int rowMid_1 = rowMid - 1;
                int colMid_1 = colMid - 1;
                int v = matrix[rowMid_1][colMid_1];
                if (v != target) {
                    List<int[]> rectangles = new ArrayList<>();
                    rectangles.add(new int[] { rowBegin, rowMid, colMid, colEnd });
                    rectangles.add(new int[] { rowMid, rowEnd, colBegin, colMid });
                    if (v < target) {
                        rectangles.add(new int[] { rowMid, rowEnd, colMid, colEnd });
                    } else {
                        rectangles.add(new int[] { rowBegin, rowMid, colBegin, colMid });
                    }
                    for (int[] r : rectangles) {
                        if (searchInOrderedMatrix(matrix, r[0], r[1], r[2], r[3], target)) {
                            retval = true;
                            break;
                        }
                    }
                } else {
                    retval = true;
                }
            } else {
                if (rowMid > rowBegin || colMid > colBegin) {
                    if (rowMid > rowBegin) {
                        assert ((colEnd - colBegin) == 1);
                        int diff = colEnd - colBegin;
                        if (diff <= 8) {
                            for (int i = rowBegin; i < rowEnd; ++i) {
                                if (matrix[i][colBegin] == target) {
                                    retval = true;
                                    break;
                                }
                            }
                        } else {
                            while (rowBegin < rowEnd) {
                                rowMid = (rowBegin + rowEnd) / 2;
                                int v = matrix[rowMid][colBegin];
                                if (v > target) {
                                    rowEnd = rowMid;
                                    rowMid = rowBegin;
                                } else if (v < target) {
                                    rowBegin = rowMid + 1;
                                    rowMid = rowEnd;
                                } else {
                                    retval = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (colMid > colBegin) {
                        assert ((rowEnd - rowBegin) == 1);
                        int diff = colEnd - colBegin;
                        if (diff <= 128) {
                            for (int j = colBegin; j != colEnd; ++j) {
                                if (matrix[rowBegin][j] == target) {
                                    retval = true;
                                    break;
                                }
                            }
                        } else {
                            while (colBegin < colEnd) {
                                colMid = (colBegin + colEnd) / 2;
                                int v = matrix[rowBegin][colMid];
                                if (v > target) {
                                    colEnd = colMid;
                                    colMid = colBegin;
                                } else if (v < target) {
                                    colBegin = colMid + 1;
                                    colMid = colEnd;
                                } else {
                                    retval = true;
                                    break;
                                }
                            }
                        }
                    }
                } else {
                    retval = (matrix[rowBegin][colBegin] == target);
                }

            }
        }
        return retval;
    }

    // 240. Search a 2D Matrix II
    public boolean searchInOrderedMatrix(int[][] matrix, int target) {
        boolean retval = false;
        int m = matrix != null ? matrix.length : 0;
        if (m > 0) {
            int n = matrix[0].length;
            retval = searchInOrderedMatrix(matrix, 0, m, 0, n, target);
        }
        return retval;
    }
}
