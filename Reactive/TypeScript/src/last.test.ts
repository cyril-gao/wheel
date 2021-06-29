import { range } from 'rxjs';
import { last } from './last';

test(
    "check the result value of the call to the operator last",
    () => {
        for (let k = 1, count = 1000; k <= count; ++k) {
            let result: any[] = [];
            last(k)(range(0, count)).subscribe(
                v => result.push(v)
            );
            let ok = true;
            if (result.length === k) {
                let value = count - k;
                for (let i = 0; i < k; ++i, ++value) {
                    if (result[i] !== value) {
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
