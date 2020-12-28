import { maximumGap } from "./maximum.gap";

test(
    "check the result value of the call to the function maximumGap",
    () => {
        let nums = [3, 6, 9, 1];
        let result = maximumGap(nums);
        expect(result).toEqual(3);

        nums = [100, 3, 1];
        result = maximumGap(nums);
        expect(result).toEqual(97);

        nums = [1];
        result = maximumGap(nums);
        expect(result).toEqual(0);
    }
);
