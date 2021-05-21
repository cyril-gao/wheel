import { wordBreak } from "./word.break.ii";

test(
    "check the result value of the call to the function wordBreak",
    () => {
        let s = "catsanddog";
        let wordDict = ["cat", "cats", "and", "sand", "dog"];
        let result = wordBreak(s, wordDict);
        expect(result.length).toEqual(2);

        s = "pineapplepenapple";
        wordDict = ["apple", "pen", "applepen", "pine", "pineapple"];
        result = wordBreak(s, wordDict);
        expect(result.length).toEqual(3);

        s = "catsandog";
        wordDict = ["cats", "dog", "sand", "and", "cat"];
        result = wordBreak(s, wordDict);
        expect(result.length).toEqual(0);
    }
);
