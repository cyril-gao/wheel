package com.example;

public class Coordinate implements Comparable<Coordinate> {
    int row;
    int col;

    public Coordinate(int row, int col) {
        this.row = row;
        this.col = col;
    }

    public Coordinate() {
        this(0, 0);
    }

    @Override
    public int hashCode() {
        return 19 * row + 23 * col;
    }

    @Override
    public boolean equals(Object other) {
        boolean retval = (this == other);
        if (!retval) {
            Coordinate c = (Coordinate) other;
            retval = (row == c.row) && (col == c.col);
        }
        return retval;
    }

    @Override
    public String toString() {
        return String.format("[%d,%d]", row, col);
    }

    @Override
    public int compareTo(Coordinate c) {
        int r = row - c.row;
        if (r != 0) {
            return r;
        } else {
            return col - c.col;
        }
    }

    public static Coordinate random(int m, int n) {
        var r = new java.util.Random();
        int row = r.nextInt(m);
        int col = r.nextInt(n);
        return new Coordinate(row, col);
    }
}