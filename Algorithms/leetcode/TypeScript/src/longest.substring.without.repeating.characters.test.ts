import { lengthOfLongestSubstring } from "./longest.substring.without.repeating.characters";

test(
    "check the result value of the call to the function maximumGap",
    () => {
        let result = lengthOfLongestSubstring("abcabcbb");
        expect(result).toEqual(3);

        result = lengthOfLongestSubstring("bbbbb");
        expect(result).toEqual(1);

        result = lengthOfLongestSubstring("pwwkew");
        expect(result).toEqual(3);

        result = lengthOfLongestSubstring("bacabcdbe");
        expect(result).toEqual(4);

        result = lengthOfLongestSubstring("bacabcbdce");
        expect(result).toEqual(4);
    }
);
