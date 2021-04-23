package com.example;

public class WildcardMatching {
    /*
     * private boolean impl1(String s, String p) { boolean retval = s == p; if
     * (!retval) { if (s != null && p != null) { int sl = s.length(); int pl =
     * p.length(); int si = 0, pi = 0; retval = true; while (pi < pl && retval) {
     * char pc = p.charAt(pi); char sc = si < sl ? s.charAt(si) : '\0'; if (pc !=
     * '*') { if (pc == '?') { if (si < sl) { ++si; ++pi; } else { retval = false; }
     * } else if (pc == sc) { ++si; ++pi; } else { retval = false; } } else { int i;
     * for (i = pi + 1; i < pl && p.charAt(i) == '*'; ++i) {} pi = i - 1; retval =
     * false; String subp = p.substring(pi+1); for (i = sl; i >= si; --i) { if
     * (isMatch(s.substring(i), subp)) { retval = true; pi = pl; si = sl; break; } }
     * } } if (retval) { retval = (si >= sl); } } } return retval; }
     */
    private boolean patternStartsWithStar(String s, int sStart, String p, int pStart, boolean[] failedImmediately) {
        int sl = s.length();
        int pl = p.length();

        // skip the redundant '*'
        while (pStart < pl && p.charAt(pStart) == '*') {
            ++pStart;
        }

        for (int retry = 0, pi = pStart, si = sStart; si < sl; ++retry, pi = pStart, si = sStart + retry) {
            if (pi < pl) {
                // compare '?' with the char in the txt
                while (pi < pl && p.charAt(pi) == '?') {
                    if (si < sl) {
                        ++si;
                        ++pi;
                    } else {
                        return false;
                    }
                }
                if (pi < pl) {
                    if (p.charAt(pi) == '*') {
                        if (patternStartsWithStar(s, si, p, pi, failedImmediately)) {
                            return true;
                        }
                        if (failedImmediately[0]) {
                            return false;
                        }
                    } else {
                        // it must be a normal char
                        int j = pi + 1;
                        while (j < pl) {
                            char pc = p.charAt(j);
                            if (pc != '*' && pc != '?') {
                                ++j;
                            } else {
                                break;
                            }
                        }
                        String subp = p.substring(pi, j);
                        int subpLen = subp.length();
                        int subpPosition = s.indexOf(subp, si);
                        int firstSubpPosition = subpPosition;
                        while (true) {
                            if (subpPosition < 0) {
                                subpPosition = s.indexOf(subp);
                                while (true) {
                                    if (subpPosition < 0 || subpPosition >= firstSubpPosition) {
                                        failedImmediately[0] = true;
                                        return false;
                                    }
                                    boolean[] f1 = new boolean[] { false }, f2 = new boolean[] { false };
                                    if (impl2(s.substring(0, subpPosition), 0, p.substring(0, pi), 0, f1) && impl2(
                                            s.substring(subpPosition + subpLen), 0, p.substring(pi + subpLen), 0, f2)) {
                                        return true;
                                    } else {
                                        if (f1[0] || f2[0]) {
                                            failedImmediately[0] = true;
                                            return false;
                                        }
                                        subpPosition = s.indexOf(subp, subpPosition + 1);
                                    }
                                }
                            }
                            if (impl2(s, subpPosition + subpLen, p, pi + subpLen, failedImmediately)) {
                                return true;
                            }
                            subpPosition = s.indexOf(subp, subpPosition + 1);
                        }
                    }
                } else {
                    if (si >= sl) {
                        return true;
                    }
                }
            } else {
                return true;
            }
        }
        return pStart >= pl;
    }

    private boolean impl2(String s, int sStart, String p, int pStart, boolean[] failedImmediately) {
        if (failedImmediately[0]) {
            return false;
        }

        // System.out.printf("txt: %s\npattern: %s\n\n", s.substring(sStart),
        // p.substring(pStart));
        int sl = s.length();
        int pl = p.length();
        int si = sStart, pi = pStart;
        boolean retval = true;
        while (pi < pl && retval) {
            char pc = p.charAt(pi);
            if (pc != '*') {
                if (si < sl && (pc == '?' || pc == s.charAt(si))) {
                    ++si;
                    ++pi;
                } else {
                    return false;
                }
            } else {
                retval = patternStartsWithStar(s, si, p, pi, failedImmediately);
                if (retval) {
                    si = sl;
                    pi = pl;
                }
            }
        }
        if (retval) {
            retval = (si >= sl);
        }
        return retval;
    }

    private boolean impl2(String s, String p) {
        boolean retval = s == p;
        if (!retval) {
            if (s != null && p != null) {
                boolean[] failedImmediately = new boolean[] { false };
                retval = impl2(s, 0, p, 0, failedImmediately);
            }
        }
        return retval;
    }

    /**
     * '?' Matches any single character. '*' Matches any sequence of characters
     * (including the empty sequence).
     */
    public boolean isMatch(String s, String p) {
        return impl2(s, p);
    }

    public boolean isMatch2(String s, String p) {
        int si = 0, sl = s.length();
        int pi = 0, pl = p.length();
        int sStar = -1;
        int pStar = -1;
        while (si < sl) {
            if (pi < pl && (p.charAt(pi) == s.charAt(si) || p.charAt(pi) == '?')) {
                ++pi;
                ++si;
            } else if (pi < pl && p.charAt(pi) == '*') {
                sStar = si;
                pStar = pi++;
            } else if (sStar >= 0) {
                si = ++sStar;
                pi = pStar + 1;
            } else {
                return false;
            }
        }
        while (pi < pl && p.charAt(pi) == '*') {
            ++pi;
        }
        return pi == pl;
    }
}