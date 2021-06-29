import { Observable, range } from 'rxjs';

export const find = (predicate: (value: any) => boolean) => (source: Observable<any>) => new Observable<any>(
    subscriber => {
        let completed = false;
        source.subscribe({
            next: v => {
                if (!completed && predicate(v)) {
                    subscriber.next(v);
                    completed = true;
                }
            },
            error: err => subscriber.error(err),
            complete: () => {
                subscriber.complete();
                completed = true;
            }
        })
    }
);
