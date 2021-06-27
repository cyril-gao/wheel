import { range } from 'rxjs';
import { skip } from './skip';

test(
    "check the result value of the call to the operator skip",
    () => {
        for (let k = 0, count = 1000; k <= count; ++k) {
            let result: any[] = [];
            skip(k)(range(0, count)).subscribe(
                v => result.push(v)
            );
            let ok = true;
            if (result.length === (count - k)) {
                for (let i = k, j = 0; i < count; ++i, ++j) {
                    if (i !== result[j]) {
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