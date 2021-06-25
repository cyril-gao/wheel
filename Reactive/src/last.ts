import { Observable } from 'rxjs';

export const last = (k: number = 1) => (source: Observable<any>) => new Observable<any>(
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
