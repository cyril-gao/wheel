import { State, IntervalManager } from './segment.trees';

test(
    "check the result value of the call to the methods of the class IntervalManager",
    () => {
        let upperLimit = 60 * 24;
        for (let span = 1; span <= upperLimit; ++span) {
            let im = new IntervalManager(upperLimit);
            for (let begin = 0, end = begin + span; end <= upperLimit; begin = end, end += span) {
                im.occupy(begin, end);
                expect(im.getState(begin, end)).toEqual(State.COMPLETE);
                expect(im.getState(0, end)).toEqual(State.COMPLETE);
                expect(im.getState(end, upperLimit)).toEqual(State.EMPTY);
                if (end < upperLimit) {
                    expect(im.getState(begin, end + 1)).toEqual(State.PARTIAL);
                    expect(im.getState(0, end + 1)).toEqual(State.PARTIAL);
                }
            }
        }
    }
);
