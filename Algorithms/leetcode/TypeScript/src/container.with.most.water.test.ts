import { maxArea } from "./container.with.most.water";

test(
    "check the result value of the call to the function maxArea",
    () => {
        let height = [1, 8, 6, 2, 5, 4, 8, 3, 7];
        let result = maxArea(height);
        expect(result).toEqual(49);

        height = [1, 1];
        result = maxArea(height);
        expect(result).toEqual(1);

        height = [4, 3, 2, 1, 4];
        result = maxArea(height);
        expect(result).toEqual(16);

        height = [1, 2, 1];
        result = maxArea(height);
        expect(result).toEqual(2);
    }
);
