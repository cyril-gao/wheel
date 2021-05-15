import { trap } from "./trapping.rain.water";

test(
    "check the result value of the call to the function trap",
    () => {
        let height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1];
        let result = trap(height);
        expect(result).toEqual(6);

        height = [4, 2, 0, 3, 2, 5];
        result = trap(height);
        expect(result).toEqual(9);

        height = [0, 1, 0, 3, 2, 3, 2, 3, 7, 4, 5, 0, 1, 2, 6, 3, 0, 1, 4, 0, 2, 0];
        result = trap(height);
        expect(result).toEqual(31);
    }
);
