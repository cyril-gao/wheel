import { canCompleteCircuit } from "./gas.station";

test(
    "check the result value of the call to the function canCompleteCircuit",
    () => {
        let gas = [1, 2, 3, 4, 5];
        let cost = [3, 4, 5, 1, 2];
        let result = canCompleteCircuit(gas, cost);
        expect(result).toBe(3);

        gas = [2, 3, 4];
        cost = [3, 4, 3];
        result = canCompleteCircuit(gas, cost);
        expect(result).toBe(-1);
    }
);