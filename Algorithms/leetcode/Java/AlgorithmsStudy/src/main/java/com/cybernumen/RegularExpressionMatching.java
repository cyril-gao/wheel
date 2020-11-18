package com.cybernumen;

public class RegularExpressionMatching {
    /*
    public boolean isMatch(String s, String p) {
        StringBuilder sb = new StringBuilder();
        sb.append('(');
        sb.append(p);
        sb.append(')');
        NFA nfa = new NFA(sb.toString());
        return nfa.recognizes(s);
    }
    */

    public boolean isMatch(String s, String p) {
        boolean retval = s == p;
        if (!retval) {
            if (s != null && p != null) {
                int sl = s.length();
                int pl = p.length();
                int si = 0, pi = 0;
                retval = true;
                while (pi < pl && retval) {
                    char pc = p.charAt(pi);
                    char sc = si < sl ? s.charAt(si) : '\0';
                    int nextPi = pi + 1;
                    if (nextPi == pl || p.charAt(nextPi) != '*') {
                        if (pc == '.') {
                            if (si < sl) {
                                ++si;
                                pi = nextPi;
                            } else {
                                retval = false;
                            }
                        } else if (pc == sc) {
                            ++si;
                            pi = nextPi;
                        } else {
                            retval = false;
                        }
                    } else {
                        if (pc == '.' || pc == sc) {
                            retval = false;
                            String subp = p.substring(nextPi + 1);
                            int nextSubI = sl;
                            if (pc != '.') {
                                for (nextSubI = si; nextSubI < sl && s.charAt(nextSubI) == pc; ++nextSubI) {}
                            }
                            if (!subp.isEmpty()) {
                                //for (int i = si; i <= nextSubI; ++i) {
                                for (int i = nextSubI; i >= si; --i) {
                                    if (isMatch(s.substring(i), subp)) {
                                        si = sl;
                                        pi = pl;
                                        retval = true;
                                        break;
                                    }
                                }
                            } else {
                                retval = nextSubI >= sl;
                                if (retval) {
                                    si = sl;
                                    pi = pl;
                                }
                            }
                        } else {
                            pi = nextPi + 1;
                        }
                    }
                }
                if (retval) {
                    retval = (si >= sl);
                }
            }
        }
        return retval;
    }

    public boolean isValid(String s) {
        boolean retval = s != null;
        if (retval) {
            char[] input = s.toCharArray();
            retval = false;
            if ((input.length % 2) == 0) {
                char[] buffer = new char[input.length/2 + 1];
                int bi = 0;
                retval = true;
                for (int i = 0; i < input.length; ++i) {
                    char c = input[i];
                    if (c == '(' || c == '[' || c == '{') {
                        buffer[bi++] = c;
                        if (bi > buffer.length) {
                            retval = false;
                            break;
                        }
                    } else {
                        retval = false;
                        if (bi > 0) {
                            --bi;
                            if (c == ')') {
                                if (buffer[bi] == '(') {
                                    retval = true;
                                } else {
                                    break;
                                }
                            } else if (c == ']') {
                                if (buffer[bi] == '[') {
                                    retval = true;
                                } else {
                                    break;
                                }
                            } else if (c == '}') {
                                if (buffer[bi] == '{') {
                                    retval = true;
                                } else {
                                    break;
                                }
                            }
                        } else {
                            break;
                        }
                    }
                }
                if (retval) {
                    retval = (bi == 0);
                }
            }
        }
        return retval;
    }
}

/*
                        if (pc == '.') {
                            retval = false;
                            String subp = p.substring(nextPi + 1);
                            for (int i = si; i < sl; ++i) {
                                if (isMatch(s.substring(i), subp)) {
                                    si = sl;
                                    pi = pl;
                                    retval = true;
                                    break;
                                }
                            }
                        } else if (pc == sc) {
                            int nextSubI;
                            for (nextSubI = si; nextSubI < sl && s.charAt(nextSubI) == pc; ++nextSubI) {}
                            retval = false;
                            String subp = p.substring(nextPi + 1);
                            for (int i = si; i < nextSubI; ++i) {
                                if (isMatch(s.substring(i), subp)) {
                                    si = sl;
                                    pi = pl;
                                    retval = true;
                                    break;
                                }
                            }
                        } else {

                        }
*/