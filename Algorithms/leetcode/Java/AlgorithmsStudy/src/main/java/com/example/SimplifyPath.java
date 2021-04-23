package com.example;

import java.util.Stack;

public class SimplifyPath {
    public String simplifyPath(String path) {
        String retval = "/";
        if (path != null && path.length() > 1) {
            Stack<String> stack = new Stack<>();
            String[] pieces = path.split("/");
            for (int i = 0; i < pieces.length; ++i) {
                String piece = pieces[i];
                if (piece.isEmpty() || piece.equals(".")) {
                    continue;
                } else if (piece.equals("..")) {
                    if (!stack.isEmpty()) {
                        stack.pop();
                    }
                } else {
                    stack.push(piece);
                }
            }

            if (!stack.isEmpty()) {
                StringBuilder sb = new StringBuilder();
                while (!stack.isEmpty()) {
                    sb.insert(0, stack.pop());
                    sb.insert(0, '/');
                }
                retval = sb.toString();
            }
        }
        return retval;
    }
}