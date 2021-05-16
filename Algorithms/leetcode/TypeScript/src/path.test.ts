import { uniquePaths, uniquePathsWithObstacles } from "./path";

test(
    "check the result value of the call to the function uniquePaths",
    () => {
        let result = uniquePaths(3, 7);
        expect(result).toEqual(28);

        result = uniquePaths(3, 2);
        expect(result).toEqual(3);

        result = uniquePaths(3, 3);
        expect(result).toEqual(6);
    }
);


test(
    "check the result value of the call to the function uniquePathsWithObstacles",
    () => {
        let obstacleGrid = [[0, 0, 0], [0, 1, 0], [0, 0, 0]];
        expect(uniquePathsWithObstacles(obstacleGrid)).toEqual(2);

        obstacleGrid = [[0, 1], [0, 0]];
        expect(uniquePathsWithObstacles(obstacleGrid)).toEqual(1);

        obstacleGrid = [[1, 1], [0, 0]];
        expect(uniquePathsWithObstacles(obstacleGrid)).toEqual(0);
    }
);
