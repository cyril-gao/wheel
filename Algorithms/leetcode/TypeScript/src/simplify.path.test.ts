import { simplifyPath } from "./simplify.path";

test(
    "check the result value of the call to the function simplifyPath",
    () => {
        expect(simplifyPath("/home/")).toEqual("/home");
        expect(simplifyPath("/../")).toEqual("/");
        expect(simplifyPath("/home//foo/")).toEqual("/home/foo");
        expect(simplifyPath("/a/./b/../../c/")).toEqual("/c");
    }
);
