import { countAndSay } from "./count.and.say";

test(
    "check the result value of the call to the function countAndSay",
    () => {
        let result = countAndSay(1);
        expect(result).toEqual('1');

        result = countAndSay(4);
        expect(result).toEqual('1211');

        result = countAndSay(5);
        expect(result).toEqual('111221');
    }
);
