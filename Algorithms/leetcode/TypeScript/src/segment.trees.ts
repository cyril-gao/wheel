export enum State {
    EMPTY, PARTIAL, COMPLETE
}

function getBlockSize(n: number): number {
    let i = 1;
    for (; i < n; i <<= 1) {}
    return i;
}

export class IntervalManager
{
    private states: State[];
    private lengthOfMeta: number;

    //[0 .. upperLimit)
    constructor(private readonly upperLimit) {
        this.lengthOfMeta = getBlockSize(upperLimit);
        this.states = new Array<State>(this.lengthOfMeta + this.lengthOfMeta - 1);
        this.states.fill(State.EMPTY);
    }

    private isAligning(position: number, blockSize: number): boolean {
        return (Math.floor(position / blockSize) * blockSize) === position;
    }

    private setCompleteDown(blockSize: number, blockIndex: number): void {
        if (this.states[blockIndex] !== State.COMPLETE) {
            this.states[blockIndex] = State.COMPLETE;
            if (blockSize > 1) {
                let halfBlockSize = blockSize >> 1;
                let childBlockIndex = (blockIndex + 1) << 1;
                this.setCompleteDown(halfBlockSize, childBlockIndex);
                this.setCompleteDown(halfBlockSize, childBlockIndex - 1);
            }
        }
    }

    private setPartialDown(begin: number, end: number, blockSize: number, blockIndex: number): void {
        let diff = end - begin;
        let blockBegin = Math.floor(begin / blockSize) * blockSize;
        if (diff != blockSize || blockBegin !== begin) {
            this.states[blockIndex] = State.PARTIAL;
            let halfBlockSize = blockSize >> 1;
            let blockMid = blockBegin + halfBlockSize;
            let rightChildBlockIndex = (blockIndex + 1) * 2;
            if (end <= blockMid) {
                this.setPartialDown(begin, end, halfBlockSize, rightChildBlockIndex - 1);
            } else if (begin >= blockMid) {
                this.setPartialDown(begin, end, halfBlockSize, rightChildBlockIndex);
            } else {
                this.setPartialDown(begin, blockMid, halfBlockSize, rightChildBlockIndex - 1);
                this.setPartialDown(blockMid, end, halfBlockSize, rightChildBlockIndex);
            }
        } else {
            this.setCompleteDown(blockSize, blockIndex);
        }
    }

    private setStateUp(blockIndex: number): void {
        while (blockIndex !== 0) {
            if ((blockIndex & 1) === 0) {
                --blockIndex;
            }
            let left = blockIndex;
            let right = left + 1;
            let parent = (left - 1) >> 1;
            let oldState = this.states[parent];
            if (this.states[left] === State.COMPLETE && this.states[right] === State.COMPLETE) {
                this.states[parent] = State.COMPLETE;
            } else {
                this.states[parent] = State.PARTIAL;
                if (this.states[left] === State.EMPTY && this.states[right] === State.EMPTY) {
                    throw new Error("There is a bug in the program");
                }
            }
            if (oldState === this.states[parent]) {
                break;
            }
            blockIndex = parent;
        }
    }

    private getBlockIndex(position: number, blockSize: number): number {
        let blockIndex = Math.floor(position / blockSize);
        let i = Math.floor(Math.log2(this.lengthOfMeta) - Math.log2(blockSize));
        i = (1 << i) - 1; // the number of upper nodes
        return blockIndex + i;
    }

    private errorMessage(begin: number, end: number): string {
        return `begin ${begin} must be less than end ${end}, end ${end} must be less than or equal to ${this.upperLimit}`;
    }

    public occupy(begin: number, end: number): void {
        if (0 <= begin && begin < end && end <= this.upperLimit) {
            let diff = end - begin;
            let blockSize = getBlockSize(diff);
            let blockIndex = Math.floor(begin / blockSize);
            let blockBegin = blockIndex * blockSize;
            let blockEnd = blockBegin + blockSize;

            blockIndex = this.getBlockIndex(blockBegin, blockSize);
            if (end <= blockEnd) {
                this.setPartialDown(begin, end, blockSize, blockIndex);
                this.setStateUp(blockIndex);
            } else {
                this.setPartialDown(begin, blockEnd, blockSize, blockIndex);
                this.setStateUp(blockIndex);
                this.setPartialDown(blockEnd, end, blockSize, ++blockIndex);
                this.setStateUp(blockIndex);
            }
        } else {
            throw new Error(this.errorMessage(begin, end));
        }
    }

    private getBlockState(begin: number, end: number, blockSize: number, blockBegin: number, blockEnd: number): State {
        let blockIndex = this.getBlockIndex(blockBegin, blockSize);
        if (this.states[blockIndex] === State.PARTIAL) {
            let halfBlockSize = blockSize >> 1;
            let blockMid = blockBegin + halfBlockSize;
            blockBegin = Math.floor(begin / halfBlockSize) * halfBlockSize;
            if (end <= blockMid || begin >= blockMid) {
                return this.getBlockState(begin, end, halfBlockSize, blockBegin, blockBegin + halfBlockSize);
            } else {
                let leftState = this.getBlockState(begin, blockMid, halfBlockSize, blockBegin, blockMid);
                blockBegin = Math.floor(blockMid / halfBlockSize) * halfBlockSize;
                let rightState = this.getBlockState(blockMid, end, halfBlockSize, blockBegin, blockBegin + halfBlockSize);

                if (leftState === State.COMPLETE && rightState === State.COMPLETE) {
                    return State.COMPLETE;
                } else if (leftState === State.EMPTY && rightState === State.EMPTY) {
                    return State.EMPTY;
                } else {
                    return State.PARTIAL;
                }
            }
        } else {
            return this.states[blockIndex];
        }
    }

    public getState(begin: number, end: number): State {
        if (0 <= begin && begin <= end && end <= this.upperLimit) {
            let diff = end - begin;
            if (diff !== 0) {
                let blockSize = getBlockSize(diff);
                let blockBegin = Math.floor(begin / blockSize) * blockSize;
                let blockEnd = blockBegin + blockSize;
                if (end <= blockEnd) {
                    return this.getBlockState(begin, end, blockSize, blockBegin, blockEnd);
                } else {
                    let leftState = this.getBlockState(begin, blockEnd, blockSize, blockBegin, blockEnd);
                    let rightState = this.getBlockState(blockEnd, end, blockSize, blockEnd, blockEnd + blockSize);
                    if (leftState === State.COMPLETE && rightState === State.COMPLETE) {
                        return State.COMPLETE;
                    } else if (leftState === State.EMPTY && rightState === State.EMPTY) {
                        return State.EMPTY;
                    }
                    return State.PARTIAL;
                }
            } else {
                return State.EMPTY;
            }
        } else {
            throw new Error(this.errorMessage(begin, end));
        }
    }
}
