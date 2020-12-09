import { canFinish, findOrder } from "./course.schedule";

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

test(
    "check the result value of the call to the function findOrder",
    () => {
        let prerequisites = [[1,0]];
        let result = findOrder(2, prerequisites);
        expect(result).toEqual([0, 1]);

        prerequisites = [[1,0],[2,0],[3,1],[3,2]];
        result = findOrder(4, prerequisites);
        expect(result).toEqual([0,2,1,3]);

        prerequisites = [];
        result = findOrder(1, prerequisites);
        expect(result).toEqual([0]);
    }
);