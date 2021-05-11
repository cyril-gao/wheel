import { permute } from './permutations';

test(
    "check the result value of the call to the function permute",
    () => {
        expect(permute([1]).length).toEqual(1);
        expect(permute([1, 2]).length).toEqual(2);
        expect(permute([1, 2, 3]).length).toEqual(6);
        expect(permute([1, 2, 3, 4]).length).toEqual(24);
        expect(permute([1, 2, 3, 4, 5]).length).toEqual(120);
    }
);
