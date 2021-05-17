import { uniquePaths, uniquePathsWithObstacles, minPathSum } from "./path";

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


test(
    "check the result value of the call to the function minPathSum",
    () => {
        let grid = [[1, 3, 1], [1, 5, 1], [4, 2, 1]];
        expect(minPathSum(grid)).toEqual(7);

        grid = [[1, 2, 3], [4, 5, 6]];
        expect(minPathSum(grid)).toEqual(12);
    }
);
