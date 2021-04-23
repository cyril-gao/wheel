import { numSquares } from "./perfect.squares";

test(
    "check the result value of the call to the function numSquares",
    () => {
        let result = numSquares(12);
        expect(result).toEqual(3);

        result = numSquares(13);
        expect(result).toEqual(2);

        result = numSquares(69);
        expect(result).toEqual(3);

        result = numSquares(192);
        expect(result).toEqual(3);

        result = numSquares(1793);
        expect(result).toEqual(3);

        result = numSquares(7168);
        expect(result).toEqual(4);

        result = numSquares(Number.MAX_SAFE_INTEGER);
        expect(result).toEqual(4);
    }
);
