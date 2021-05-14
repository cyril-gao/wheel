import { groupAnagrams } from "./group.anagrams";

test(
    "check the result value of the call to the function groupAnagrams",
    () => {
        let strs = ["eat", "tea", "tan", "ate", "nat", "bat"];
        let result = groupAnagrams(strs);
        expect(result.length).toEqual(3);

        result = groupAnagrams([""]);
        expect(result.length).toEqual(1);

        result = groupAnagrams(["a"]);
        expect(result.length).toEqual(1);
    }
);