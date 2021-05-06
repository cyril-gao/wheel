import { multiply } from './multiply.strings';

test(
    "check the result value of the call to the function multiply",
    () => {
        for (let i = 0; i < 10; ++i) {
            for (let j = 0; j < 10; ++j) {
                let result = multiply(i.toString(), j.toString());
                expect(result).toEqual((i * j).toString());
            }
        }

        for (let i = 10; i < 3493; i += 101) {
            for (let j = 10; j < 7533; j += 103) {
                let result = multiply(i.toString(), j.toString());
                expect(result).toEqual((i * j).toString());
            }
        }

        expect(multiply('0', '52')).toEqual('0');
    }
);
