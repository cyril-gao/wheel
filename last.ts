import { Observable, range } from 'rxjs';

const last = (k: number = 1) => (source: Observable<any>) => new Observable<any>(
    subscriber => {
        let cache = new Array<any>(k);
        let count = 0;
        let current = 0;
        source.subscribe({
            next: v => {
                ++count;
                if (current === k) {
                    current = 0;
                }
                cache[current++] = v;
            },
            error: err => subscriber.error(err),
            complete: () => {
                if (count >= k) {
                    for (let i = 0; i < k; ++i) {
                        if (current === k) {
                            current = 0;
                        }
                        subscriber.next(cache[current++]);
                    }
                } else {
                    for (let i = 0; i < current; ++i) {
                        subscriber.next(cache[i]);
                    }
                }
                subscriber.complete();
            }
        })
    }
);

for (let k = 2, count = 10000; k <= count; ++k) {
    let result: any[] = [];
    last(k)(range(0, count)).subscribe(
        v => result.push(v)
    );
    let ok: boolean = true;
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
    if (!ok) {
        console.log(`k=${k}, result=${result}`);
    }
}
