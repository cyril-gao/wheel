import { isMatch } from './regular.expression.matching';

test(
    "check the result value of the call to the function isMatch",
    () => {
        expect(isMatch("", "")).toBe(true);
        expect(isMatch("", "a*")).toBe(true);
        expect(isMatch("", "a*.*c*a*")).toBe(true);
        expect(isMatch("", ".*")).toBe(true);
        expect(isMatch("aa", "a*")).toBe(true);
        expect(isMatch("aaa", "a*a")).toBe(true);
        expect(isMatch("aaa", "ab*ac*a")).toBe(true);
        expect(isMatch("ab", ".*..")).toBe(true);
        expect(isMatch("ab", ".*..c*")).toBe(true);
        expect(isMatch("mississippi", "mis*is*ip*.")).toBe(true);

        expect(isMatch("a", "ab*a")).toBe(false);
        expect(isMatch("ab", "a")).toBe(false);
        expect(isMatch("ab", ".*c")).toBe(false);
        expect(isMatch("mississippi", "mis*is*ip*ii")).toBe(false);
        expect(isMatch("mississippi", "mis*iis*ip*i")).toBe(false);
    }
);