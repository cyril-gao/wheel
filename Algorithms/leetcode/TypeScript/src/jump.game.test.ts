import { minimumJump, canJump } from "./jump.game";

test(
    "check the result value of the call to the function minimumJump",
    () => {
        let nums = [2, 3, 1, 1, 4];
        expect(minimumJump(nums)).toEqual(2);

        nums = [2, 3, 0, 1, 4];
        expect(minimumJump(nums)).toEqual(2);

        expect(minimumJump([0])).toEqual(0);
    }
);

test(
    "check the result value of the call to the function canJump",
    () => {
        let nums = [2, 3, 1, 1, 4];
        expect(canJump(nums)).toBe(true);

        nums = [2, 3, 0, 1, 4];
        expect(canJump(nums)).toBe(true);

        expect(canJump([0])).toBe(true);

        nums = [3, 2, 1, 0, 4];
        expect(canJump(nums)).toBe(false);
    }
);