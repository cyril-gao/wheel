import { range } from 'rxjs';
import { find } from './find';

test(
    "check the result value of the call to the operator find",
    () => {
        for (let k = 0, count = 1000, last = 998; k < count; ++k) {
            let result = [];
            find(v => (v > k) && (v % 2 === 0))(range(0, count)).subscribe(
                v => result.push(v)
            );
            if (k < last) {
                expect(result.length).toEqual(1);
                expect(result[0]).toEqual((k + 2) & (~1));
            } else {
                expect(result.length).toEqual(0);
            }
        }
    }
);
