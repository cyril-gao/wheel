/*
You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs.

If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.

Operations allowed:

Fill any of the jugs completely with water.
Empty any of the jugs.
Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.

Example 1: (From the famous "Die Hard" example)
Input: x = 3, y = 5, z = 4
Output: True

Example 2:
Input: x = 2, y = 6, z = 5
Output: False
*/

function toString(x: number, y: number): string {
    return `${x},${y}`;
}

function isVisited(xy: number[], visited: Set<string>): boolean {
    return visited.has(toString(xy[0], xy[1]));
}

function getNeighbours(
    x: number, y: number,
    maxX: number, maxY: number
): number[][] {
    let retval: number[][] = [];

    let xy: number[];
    retval.push([0, y]);
    retval.push([maxX, y]);

    if (y !== maxY) {
        let diffY = maxY - y;
        if (x >= diffY) {
            xy = [x - diffY, maxY];
        } else {
            xy = [0, x + y];
        }
        retval.push(xy);
    }

    retval.push([x, 0]);
    retval.push([x, maxY]);
    if (x !== maxX) {
        let diffX = maxX - x;
        if (y >= diffX) {
            xy = [maxX, y - diffX];
        } else {
            xy = [x + y, 0];
        }
        retval.push(xy);
    }

    return retval;
}

function dfs(
    x: number, y: number,
    maxX: number, maxY: number, z: number,
    visited: Set<string>
): boolean {
    visited.add(toString(x, y));
    if ((x + y) === z || (x === z) || (y === z)) {
        return true;
    }
    for (let xy of getNeighbours(x, y, maxX, maxY)) {
        if (!isVisited(xy, visited)) {
            if (dfs(xy[0], xy[1], maxX, maxY, z, visited)) {
                return true;
            }
        }
    }
    return false;
}

function bfs(
    x: number, y: number,
    maxX: number, maxY: number, z: number
): boolean {
    let visited = new Set<string>();
    let queue = [[x, y]];
    while (queue.length != 0) {
        let front = queue.shift();
        visited.add(toString(front[0], front[1]));
        for (let xy of getNeighbours(front[0], front[1], maxX, maxY)) {
            if (!isVisited(xy, visited)) {
                if ((xy[0] + xy[1]) === z || (xy[0] === z) || (xy[1] === z)) {
                    return true;
                }
                queue.push([xy[0], xy[1]]);
            }
        }
    }
    return false;
}

export function canMeasureWater(x: number, y: number, z: number): boolean {
    let retval = ((x + y) === z || x === z || y === z);
    if (!retval) {
        retval = bfs(0, 0, x, y, z);
    }
    return retval;
};
