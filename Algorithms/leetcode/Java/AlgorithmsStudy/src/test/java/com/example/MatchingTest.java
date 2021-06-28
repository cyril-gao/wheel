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

    private boolean isValidIpv4(String input) {
        String strPattern = "^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$";
        return java.util.regex.Pattern.compile(strPattern).matcher(input).find();
    }

    @Test
    public void testRegexForIPAddress() {
        assertTrue(isValidIpv4("2.0.2.53"));
        assertTrue(isValidIpv4("200.0.255.253"));
        assertTrue(isValidIpv4("10.2.2.3"));
        assertTrue(isValidIpv4("0.0.0.0"));
        assertFalse(isValidIpv4("300.10.10.10"));
        assertFalse(isValidIpv4("0.510.10.10"));
        assertFalse(isValidIpv4("0.10.510.10"));
        assertFalse(isValidIpv4("0.10.10.256"));
        assertFalse(isValidIpv4("2.0.2.53a"));
        assertFalse(isValidIpv4("a2.0.2.53"));
        assertFalse(isValidIpv4("2.c0.2.53"));
        assertFalse(isValidIpv4("200-0.255.253"));
        assertFalse(isValidIpv4("10_2.2.3"));
        assertFalse(isValidIpv4("0.0.00.0"));
    }

    private void testSearcher(SubstringSearcher searcher) {
        assertEquals(searcher.search("", ""), 0);
        assertEquals(searcher.search("DA", ""), 0);
        assertEquals(searcher.search("11121112311", "11123"), 4);
        assertEquals(searcher.search("ABAAAABAAAAAAAAA", "BAAAAAAAAA"), 6);
        assertEquals(searcher.search("BCBAABACAABABACAA", "ABABAC"), 9);
        assertEquals(searcher.search("AABRAACADABRAACAADABRA", "AACAA"), 12);
        assertEquals(searcher.search("AAAAAAAAAAAAAAAAAAAAAAAAB", "AAAAAAAB"), 17);
        assertEquals(searcher.search("ABABAAAAABABABABAABABAAAA", "ABABABAB"), 8);
        assertEquals(searcher.search("ABABAAAAABABABABAABABAAAA", "ABABABABB"), -1);
    }

    @Test
    public void testKMPSearcher() {
        testSearcher(new KMPSearcher());
    }

    @Test
    public void testRabinKarpSearcher() {
        testSearcher(new RabinKarpSearcher());
    }
}
