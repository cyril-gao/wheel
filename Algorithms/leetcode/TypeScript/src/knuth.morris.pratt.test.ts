import { kmpSearch } from "./knuth.morris.pratt";

test(
    "check the result value of the call to the function kmpSearch",
    () => {
        let txt = "one two three";
        let result = kmpSearch(txt, "two");
        expect(result).toEqual(4);

        result = kmpSearch(txt, "");
        expect(result).toEqual(0);

        result = kmpSearch(txt, "nine");
        expect(result).toEqual(-1);

        result = kmpSearch(txt, "n");
        expect(result).toEqual(1);

        result = kmpSearch(txt, "ee");
        expect(result).toEqual(11);
    }
);
