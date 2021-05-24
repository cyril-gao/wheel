/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of
words beginWord -> s1 -> s2 -> ... -> sk such that:
    1. Every adjacent pair of words differs by a single letter.
    2. Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    3. sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation
sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be
returned as a list of the words [beginWord, s1, s2, ..., sk].


Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
*/

function getLetterSets(wordList: string[]): Set<number>[] {
    let n = wordList[0].length;
    let retval = new Array<Set<number>>(n);
    for (let i = 0; i < n; ++i) {
        let set = new Set<number>();
        for (let j = 0; j < wordList.length; ++j) {
            set.add(wordList[j].charCodeAt(i));
        }
        retval[i] = set;
    }
    return retval;
}

function getWordSet(wordList: string[]): Set<string> {
    let retval = new Set<string>();
    for (let w of wordList) {
        retval.add(w);
    }
    return retval;
}

enum Color {
    WHITE,
    GRAY,
    BLACK
}

class State {
    public parent: Set<string>;
    constructor(
        public self: string,
        parent: string | null = null,
        public distance: number = 0,
        public color: Color = Color.GRAY
    ) {
        this.parent = new Set<string>();
        if (parent) {
            this.parent.add(parent);
        }
    }
}

function getNeighbours(word: string, candidates: Set<string>, letterSets: Set<number>[]): string[] {
    let retval = [];
    for (let i = 0; i < word.length; ++i) {
        let c = word.charCodeAt(i);
        let left = word.substring(0, i);
        let right = word.substring(i + 1);
        for (let j of letterSets[i]) {
            if (j != c) {
                let w = left + String.fromCharCode(j) + right;
                if (candidates.has(w)) {
                    retval.push(w);
                }
            }
        }
    }
    return retval;
}

function rebuildLadders(beginWord: string, endWord: string, states: Map<string, State>): string[][] {
    let retval = [];
    if (endWord !== beginWord) {
        for (let p of states.get(endWord).parent) {
            for (let l of rebuildLadders(beginWord, p, states)) {
                l.push(endWord);
                retval.push(l);
            }
        }
    } else {
        retval.push([beginWord]);
    }
    return retval;
}

export function findLadders(beginWord: string, endWord: string, wordList: string[]): string[][] {
    let retval = [];
    let candidates = getWordSet(wordList);
    if (candidates.has(endWord)) {
        let letterSets = getLetterSets(wordList);
        let states = new Map<string, State>();
        states.set(beginWord, new State(beginWord));
        let queue = [states.get(beginWord)];
        while (queue.length !== 0) {
            let currentState = queue.shift();
            let distance = currentState.distance + 1;
            for (let neighbour of getNeighbours(currentState.self, candidates, letterSets)) {
                if (!states.has(neighbour)) {
                    let nextState = new State(neighbour, currentState.self, distance);
                    states.set(neighbour, nextState);
                    queue.push(nextState);
                } else {
                    let previousState = states.get(neighbour);
                    if (previousState.distance === distance) {
                        previousState.parent.add(currentState.self);
                    }
                }
            }
            currentState.color = Color.BLACK;
        }
        if (states.has(endWord)) {
            retval = rebuildLadders(beginWord, endWord, states);
        }
    }
    return retval;
}


/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
    1. Every adjacent pair of words differs by a single letter.
    2. Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    3. sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.


Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
*/

export function ladderLength(beginWord: string, endWord: string, wordList: string[]): number {
    let retval = 0;
    let candidates = getWordSet(wordList);
    if (candidates.has(endWord)) {
        let letterSets = getLetterSets(wordList);
        let states = new Map<string, State>();
        states.set(beginWord, new State(beginWord));
        let queue = [states.get(beginWord)];
        while (queue.length !== 0) {
            let currentState = queue.shift();
            let distance = currentState.distance + 1;
            for (let neighbour of getNeighbours(currentState.self, candidates, letterSets)) {
                if (!states.has(neighbour)) {
                    let nextState = new State(neighbour, currentState.self, distance);
                    states.set(neighbour, nextState);
                    queue.push(nextState);
                }
            }
            currentState.color = Color.BLACK;
        }
        let lastState = states.get(endWord);
        if (lastState !== undefined && lastState.color === Color.BLACK) {
            retval = lastState.distance + 1;
        }
    }
    return retval;
}
