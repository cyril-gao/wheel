import { maxProduct } from "./maximum.product.subarray";

test(
    "check the result value of the call to the function maxProduct",
    () => {
        let nums = [2, 3, -3, 4];
        let result = maxProduct(nums);
        expect(result).toBe(6);

        nums = [0];
        result = maxProduct(nums);
        expect(result).toBe(0);

        nums = [-2];
        result = maxProduct(nums);
        expect(result).toBe(-2);

        nums = [-2, 0, -1];
        result = maxProduct(nums);
        expect(result).toBe(0);

        nums = [-3, 0, 1, -2];
        result = maxProduct(nums);
        expect(result).toBe(1);

        nums = [-2, -8, -1];
        result = maxProduct(nums);
        expect(result).toBe(16);

        nums = [-2, 0, -6, 3, -3, -4, 3, -4, -5, 2, -2, 2, -3, -5, -1, -2, -7];
        result = maxProduct(nums);
        expect(result).toBe(3628800);
    }
);
