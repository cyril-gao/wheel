import { findLadders, ladderLength } from "./word.ladder";

test(
    "check the result value of the call to the function findLadders",
    () => {
        let beginWord = "hit";
        let endWord = "cog";
        let wordList = ["hot","dot","dog","lot","log","cog"];
        let result = findLadders(beginWord, endWord, wordList);
        expect(result.length).toEqual(2);

        beginWord = "red";
        endWord = "tax";
        wordList = ["ted", "tex", "red", "tax", "tad", "den", "rex", "pee", "rad", "rax"];
        result = findLadders(beginWord, endWord, wordList);
        expect(result.length).toEqual(6);

        beginWord = "hit";
        endWord = "pig";
        wordList = ["hot","dot","dog","lot","log, pig"];
        result = findLadders(beginWord, endWord, wordList);
        expect(result.length).toEqual(0);
    }
);

test(
    "check the result value of the call to the function ladderLength",
    () => {
        let wordList = ["hot", "dot", "dog", "lot", "log", "cog"];
        let result = ladderLength("hit", "cog", wordList);
        expect(result).toEqual(5);

        wordList = ["hot","dot","dog","lot","log"];
        result = ladderLength("hit", "cog", wordList);
        expect(result).toEqual(0);
    }
);
