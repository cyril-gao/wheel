import { isMatch, isWildcardMatch } from './regular.expression.matching';

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

test(
    "check the result value of the call to the function isWildcardMatch",
    () => {
        expect(isWildcardMatch("", "")).toBe(true);
        expect(isWildcardMatch("", "*******")).toBe(true);
        expect(isWildcardMatch("aa", "a*")).toBe(true);
        expect(isWildcardMatch("aa", "*")).toBe(true);
        expect(isWildcardMatch("aaa", "a*a")).toBe(true);
        expect(isWildcardMatch("ab", "*?")).toBe(true);
        expect(isWildcardMatch("ab", "*??*")).toBe(true);
        expect(isWildcardMatch("adceb", "*a*b")).toBe(true);
        expect(isWildcardMatch("mississippi", "mis*is*ip*?")).toBe(true);

        let txt = "aabbbbbaabaaaaabbbabababbbababaabbbababbbbaababbabaaababaaabbbbaabbbbabbbbbbbaabbaabbaaaabbbaababaababaaabbbbbbabbbbbbbbaaaaabbaabbaabaaabbbaabababababaabaabbababbaaaaababaaaaaabaabaabbabaaababbbabbaaba";
        let pattern = "a*aa*bb*ba*bbab***ba***baa**a*bbabb***a***ab**abbbb**aaaa**bba*bb**a*****a*b****aa**b**b*****aaaa*a**";
        expect(isWildcardMatch(txt, pattern)).toBe(true);
        txt = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        pattern = "*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*";
        expect(isWildcardMatch(txt, pattern)).toBe(true);
        txt = "mississippi";
        pattern = "m??*ss*?i*";
        expect(isWildcardMatch(txt, pattern)).toBe(true);

        expect(isWildcardMatch("", "a*")).toBe(false);
        expect(isWildcardMatch("", "a*.*c*a*")).toBe(false);
        expect(isWildcardMatch("", "?*")).toBe(false);
        expect(isWildcardMatch("aaa", "ab*ac*a")).toBe(false);
        expect(isWildcardMatch("a", "ab*a")).toBe(false);
        expect(isWildcardMatch("ab", "a")).toBe(false);
        expect(isWildcardMatch("ab", "?*c")).toBe(false);
        expect(isWildcardMatch("acdcb", "a*c?b")).toBe(false);
        expect(isWildcardMatch("mississippi", "mis*is*ip*ii")).toBe(false);
        expect(isWildcardMatch("mississippi", "mis*iis*ip*i")).toBe(false);
        txt = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        pattern = "*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*";
        expect(isWildcardMatch(txt, pattern)).toBe(false);
        txt = "mississippi";
        pattern = "m??*ss*?i*pi";
        expect(isWildcardMatch(txt, pattern)).toBe(false);
        txt = "aaaaaabbaabaaaaabababbabbaababbaabaababaaaaabaaaabaaaabababbbabbbbaabbababbbbababbaaababbbabbbaaaaaaabbaabbbbababbabbaaabababaaaabaaabaaabbbbbabaaabbbaabbbbbbbaabaaababaaaababbbbbaabaaabbabaabbaabbaaaaba";
        pattern = "*bbb**a*******abb*b**a**bbbbaab*b*aaba*a*b**a*abb*aa****b*bb**abbbb*b**bbbabaa*b**ba**a**ba**b*a*a**aaa";
        expect(isWildcardMatch(txt, pattern)).toBe(false);
    }
);
