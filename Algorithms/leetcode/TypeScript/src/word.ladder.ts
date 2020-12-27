function getLetterSet(...words: string[]): Set<number> {
    let set = new Set<number>();
    for (let word of words) {
        for (let c of word) {
            set.add(c.charCodeAt(0));
        }
    }
    return set;
}

function getWordSet(...words: string[]): Set<string> {
    let set = new Set<string>();
    for (let word of words) {
        set.add(word);
    }
    return set;
}

function getNeighbours(word: string, letters: Set<number>, wordSet: Set<String>): string[] {
    let retval: string[] = [];
    for (let i = 0; i < word.length; ++i) {
        let left = word.substring(0, i);
        let right = word.substring(i+1);
        let original = word[i].charCodeAt(0);
        for (let c of letters) {
            if (c != original) {
                let newWord = left + String.fromCharCode(c) + right;
                if (wordSet.has(newWord)) {
                    retval.push(newWord);
                }
            }
        }
    }
    return retval;
}

export function ladderLength(beginWord: string, endWord: string, wordList: string[]): number {
    let retval = 0;
    let letters = getLetterSet(beginWord, endWord, ...wordList);
    let words = getWordSet(...wordList);
    if (words.has(endWord)) {
        let visited = new Set<string>();
        let queue : [string, number][] = [[beginWord, 1]];
        while (queue.length > 0) {
            let front = queue.shift();
            visited.add(front[0]);
            let distance = front[1];
            let neighbours = getNeighbours(front[0], letters, words);
            for (let n of neighbours) {
                if (n === endWord) {
                    retval = distance + 1;
                    queue = [];
                    break;
                }
                if (!visited.has(n)) {
                    queue.push([n, distance + 1]);
                }
            }
        }
    }
    return retval;
};
