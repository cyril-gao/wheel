import { findWords, exist } from "./word.search.ii";

test(
    "check the result value of the call to the function findWords",
    () => {
        let board = [["o", "a", "a", "n"], ["e", "t", "a", "e"], ["i", "h", "k", "r"], ["i", "f", "l", "v"]];
        let words = ["oath", "pea", "eat", "rain"];
        let result = findWords(board, words);
        expect(result).toEqual(['oath', 'eat']);

        board = [["a", "b"], ["c", "d"]];
        words = ["abcb"];
        result = findWords(board, words);
        expect(result).toEqual([]);

        board = [["a", "a"]];
        words = ["a"];
        result = findWords(board, words);
        expect(result).toEqual(["a"]);
    }
);


test(
    "check the result value of the call to the function exist",
    () => {
        let board = [["o", "a", "a", "n"], ["e", "t", "a", "e"], ["i", "h", "k", "r"], ["i", "f", "l", "v"]];
        let words = ["oath", "eat"];
        for (let word of words) {
            expect(exist(board, word)).toBe(true);
        }

        board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]];
        words = ["ABCCE", "SEE", "ASFD", "ECSE"];
        for (let word of words) {
            expect(exist(board, word)).toBe(true);
        }

        words = ["ABAB", "ABCB", "ASFE"];
        for (let word of words) {
            expect(exist(board, word)).toBe(false);
        }

        board = [["A", "B", "C", "E"], ["S", "F", "E", "S"], ["A", "D", "E", "E"]];
        expect(exist(board, "ABCESEEEFS")).toBe(true);
    }
);
