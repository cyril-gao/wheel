package com.example;

import org.testng.annotations.*;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertTrue;

interface Matcher {
    boolean isMatch(String txt, String pattern);
}

class MatcherParameters {
    public String txt;
    public String pattern;
    public boolean matched;

    public MatcherParameters(String s, String p, boolean m) {
        this.txt = s;
        this.pattern = p;
        this.matched = m;
    }
}

public class MatchingTest {
    private void testWildcardMatching(Matcher method) {
        var data = new MatcherParameters[] { new MatcherParameters("c", "*?*", true),
                new MatcherParameters("hi", "*?", true), new MatcherParameters("", "", true),
                new MatcherParameters("", "a*", false), new MatcherParameters("", "a*.*c*a*", false),
                new MatcherParameters("", "?*", false), new MatcherParameters("ab", "a", false),
                new MatcherParameters("ab", "?*", true), new MatcherParameters("aa", "*", true),
                new MatcherParameters("aa", "a*", true), new MatcherParameters("aaa", "a*a", true),
                new MatcherParameters("a", "ab*a", false), new MatcherParameters("aaa", "ab*ac*a", false),
                new MatcherParameters("ab", "*??", true), new MatcherParameters("cb", "?a", false),
                new MatcherParameters("acdcb", "a*c?b", false),
                new MatcherParameters("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b", false),
                new MatcherParameters(
                        "bbaaaababaaabaabbbbbaaaaaaaababbbababbbbbababbaababaabbbbababbaaaababbbbbaaabbbbababababbbaababaabbaabbababababbbbaabbbbaabbbababaaaabbbbbbaabababbaababababbbabababaaaaababbbabbbabbbbbabbabaabbabbaaababba",
                        "bb*b*a**bb*bb*ab*a***bbb*ab********a*aaaaaaaaa**b*b*bbabb**aaaa*a***aaaaaa*a****ba*aa**bb*a*ab*****aa**",
                        false),
                new MatcherParameters(
                        "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
                        "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb",
                        false) };
        for (var mp : data) {
            var result = method.isMatch(mp.txt, mp.pattern);
            assertEquals(result, mp.matched);
        }
    }

    @Test
    public void testWildcardMatching() {
        var wm = new WildcardMatching();
        {
            testWildcardMatching(wm::isMatch);
            testWildcardMatching(wm::isMatch2);
        }
    }

    @Test
    public void testRegularExpressionMatching() {
        var rem = new RegularExpressionMatching();
        assertTrue(rem.isMatch("", ""));
        assertTrue(rem.isMatch("", "a*"));
        assertTrue(rem.isMatch("", "a*.*c*a*"));
        assertTrue(rem.isMatch("", ".*"));
        assertFalse(rem.isMatch("ab", "a"));
        assertFalse(rem.isMatch("ab", ".*c"));
        assertTrue(rem.isMatch("aa", "a*"));
        assertTrue(rem.isMatch("aaa", "a*a"));
        assertFalse(rem.isMatch("a", "ab*a"));
        assertTrue(rem.isMatch("aaa", "ab*ac*a"));
        assertTrue(rem.isMatch("ab", ".*.."));
        assertTrue(rem.isMatch("ab", ".*..c*"));
        assertTrue(rem.isMatch("mississippi", "mis*is*ip*."));

        assertTrue(rem.isValid("()"));
        assertTrue(rem.isValid("()[]{}"));
        assertTrue(rem.isValid("{[]}"));
        assertFalse(rem.isValid("["));
        assertFalse(rem.isValid("([{((})"));
        assertFalse(rem.isValid("(]"));
        assertFalse(rem.isValid("([)]"));

        var dp = new DynamicProgramming();
        assertTrue(dp.isMatch("", ""));
        assertTrue(dp.isMatch("", "a*"));
        assertTrue(dp.isMatch("", "a*.*c*a*"));
        assertTrue(dp.isMatch("", ".*"));
        assertFalse(dp.isMatch("ab", "a"));
        assertFalse(dp.isMatch("ab", ".*c"));
        assertTrue(dp.isMatch("aa", "a*"));
        assertTrue(dp.isMatch("aaa", "a*a"));
        assertFalse(dp.isMatch("a", "ab*a"));
        assertTrue(dp.isMatch("aaa", "ab*ac*a"));
        assertTrue(dp.isMatch("ab", ".*.."));
        assertTrue(dp.isMatch("ab", ".*..c*"));
        assertTrue(dp.isMatch("mississippi", "mis*is*ip*."));
    }

    @Test
    public void testKMPSearcher() {
        var kmp = new KMPSearcher();
        assertEquals(kmp.find("", ""), 0);
        assertEquals(kmp.find("DA", ""), 0);
        assertEquals(kmp.find("11121112311", "11123"), 4);
        assertEquals(kmp.find("ABAAAABAAAAAAAAA", "BAAAAAAAAA"), 6);
        assertEquals(kmp.find("BCBAABACAABABACAA", "ABABAC"), 9);
        assertEquals(kmp.find("AABRAACADABRAACAADABRA", "AACAA"), 12);
        assertEquals(kmp.find("AAAAAAAAAAAAAAAAAAAAAAAAB", "AAAAAAAB"), 17);
        assertEquals(kmp.find("ABABAAAAABABABABAABABAAAA", "ABABABAB"), 8);
        assertEquals(kmp.find("ABABAAAAABABABABAABABAAAA", "ABABABABB"), -1);
    }
}
