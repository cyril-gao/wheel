import { canMeasureWater } from "./water.and.jug.problem";

test(
    "check the result value of the call to the function canMeasureWater",
    () => {
        let result = canMeasureWater(3, 5, 4);
        expect(result).toBeTruthy();

        result = canMeasureWater(2, 6, 5);
        expect(result).toBeFalsy();

        result = canMeasureWater(104579, 104593, 12444);
        expect(result).toBeTruthy();

        result = canMeasureWater(0, 0, 0);
        expect(result).toBeTruthy();
    }
);
