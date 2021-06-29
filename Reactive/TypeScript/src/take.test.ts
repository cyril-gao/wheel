import { range } from 'rxjs';
import { take } from './take';

test(
    "check the result value of the call to the operator take",
    () => {
        for (let k = 1, count = 1000; k <= count; ++k) {
            let result: any[] = [];
            take(k)(range(0, count)).subscribe(
                v => result.push(v)
            );
            let ok = true;
            if (result.length === k) {
                for (let i = 0; i < k; ++i) {
                    if (i !== result[i]) {
                        ok = false;
                        break;
                    }
                }
            } else {
                ok = false;
            }
            expect(ok).toBeTruthy();
        }
    }
);
