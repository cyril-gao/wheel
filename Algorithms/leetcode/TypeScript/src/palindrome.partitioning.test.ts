import { partition } from "./palindrome.partitioning";

test(
    "check the result value of the call to the function partition",
    () => {
        let resut = partition("aab");
        expect(resut.length).toEqual(2);

        resut = partition("a");
        expect(resut.length).toEqual(1);

        resut = partition("abbaabba");
        expect(resut.length).toEqual(16);
    }
);
