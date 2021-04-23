import { ladderLength } from "./word.ladder";

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
