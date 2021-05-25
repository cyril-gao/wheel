import { largestRectangleArea } from "./largest.rectangle.in.histogram";

test(
    "check the result value of the call to the function largestRectangleArea",
    () => {
        let heights = [2, 1, 5, 6, 2, 3];
        let result = largestRectangleArea(heights);
        expect(result).toEqual(10);

        heights = [2, 4];
        result = largestRectangleArea(heights);
        expect(result).toEqual(4);

        heights = [2, 5];
        result = largestRectangleArea(heights);
        expect(result).toEqual(5);

        heights = [2, 5, 2];
        result = largestRectangleArea(heights);
        expect(result).toEqual(6);

        heights = [3, 5, 5, 2, 5, 5, 6, 6, 4, 4, 1, 1, 2, 5, 5, 6, 6, 4, 1, 3];
        result = largestRectangleArea(heights);
        expect(result).toEqual(24);
    }
);
