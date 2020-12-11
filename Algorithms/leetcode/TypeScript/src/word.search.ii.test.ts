import { findWords } from "./word.search.ii";

test(
    "check the result value of the call to the function findWords",
    () => {
        let board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]];
        let words = ["oath","pea","eat","rain"];
        let result = findWords(board, words);
        expect(result).toEqual(['oath', 'eat']);

        board = [["a","b"],["c","d"]];
        words = ["abcb"];
        result = findWords(board, words);
        expect(result).toEqual([]);

        board = [["a","a"]];
        words = ["a"];
        result = findWords(board, words);
        expect(result).toEqual(["a"]);
    }
);
