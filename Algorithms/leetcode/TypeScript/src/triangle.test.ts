import { minimumTotal } from "./triangle";

test(
    "check the result value of the call to the function minimumTotal",
    () => {
        let triangle = [[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]];
        let result = minimumTotal(triangle);
        expect(result).toEqual(11);

        triangle = [[-10]];
        result = minimumTotal(triangle);
        expect(result).toEqual(-10);
    }
);
