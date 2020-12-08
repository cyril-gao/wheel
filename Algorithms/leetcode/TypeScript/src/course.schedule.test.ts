import { canFinish } from "./course.schedule";

test(
    "check the result value of the call to the function canFinish",
    () => {
        let prerequisites = [[1,0]];
        let result = canFinish(2, prerequisites);
        expect(result).toBe(true);

        prerequisites = [[1,0],[0,1]];
        result = canFinish(2, prerequisites);
        expect(result).toBe(false);
    }
);
