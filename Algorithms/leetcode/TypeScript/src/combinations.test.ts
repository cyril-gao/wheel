import { combine } from './combinations';

test(
    "check the result value of the call to the function combine",
    () => {
        let result = combine(4, 2);
        expect(result.length).toEqual(6);
        result = combine(6, 1);
        expect(result.length).toEqual(6);
        result = combine(6, 3);
        expect(result.length).toEqual(20);
    }
);
