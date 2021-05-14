import { findSubstring } from "./substring.with.concatenation.of.all.words";

test(
    "check the result value of the call to the function findSubstring",
    () => {
        let s = "barfoothefoobarman";
        let words = ["foo", "bar"];
        let result = findSubstring(s, words);
        expect(result.length).toEqual(2);
        expect(result[0]).toEqual(0);
        expect(result[1]).toEqual(9);

        s = "wordgoodgoodgoodbestword";
        words = ["word", "good", "best", "word"];
        result = findSubstring(s, words);
        expect(result.length).toEqual(0);

        words = ["good", "good", "best", "word"];
        result = findSubstring(s, words);
        expect(result.length).toEqual(1);
        expect(result[0]).toEqual(8);

        s = "barfoofoobarthefoobarman";
        words = ["bar", "foo", "the"];
        result = findSubstring(s, words);
        expect(result.length).toEqual(3);
        expect(result[0]).toEqual(6);
        expect(result[1]).toEqual(9);
        expect(result[2]).toEqual(12);
    }
);
