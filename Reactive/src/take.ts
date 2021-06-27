import { Observable } from 'rxjs';

export const take = (k: number = 1) => (source: Observable<any>) => new Observable<any>(
    subscriber => {
        let count = 0;
        source.subscribe({
            next: v => {
                if (count++ < k) {
                    subscriber.next(v);
                }
            },
            error: err => subscriber.error(err),
            complete: () => subscriber.complete()
        });
    }
);
