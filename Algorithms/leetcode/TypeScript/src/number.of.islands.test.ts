import { numIslands } from "./number.of.islands";

test(
    "check the result value of the call to the function numIslands",
    () => {
        let grid =  [
            ["1","1","1","1","0"],
            ["1","1","0","1","0"],
            ["1","1","0","0","0"],
            ["0","0","0","0","0"]
        ];
        let result = numIslands(grid);
        expect(result).toEqual(1);

        grid = [
            ["1","1","0","0","0"],
            ["1","1","0","0","0"],
            ["0","0","1","0","0"],
            ["0","0","0","1","1"]
        ];
        result = numIslands(grid);
        expect(result).toEqual(3);

        grid = [
            ["1","0","1","0","1"]
        ];
        result = numIslands(grid);
        expect(result).toEqual(3);

        grid = [
            ["1"],
            ["0"],
            ["1"],
            ["0"],
            ["1"]
        ];
        result = numIslands(grid);
        expect(result).toEqual(3);

        grid = [["1"]];
        result = numIslands(grid);
        expect(result).toEqual(1);
    }
);
