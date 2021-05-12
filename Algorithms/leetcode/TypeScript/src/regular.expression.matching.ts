class Graph
{
    private adjancentList: Map<string, number[]>[];
    constructor(public readonly V: number) {
        this.adjancentList = new Array<Map<string, number[]>>(V);
        for (let i = 0; i < V; ++i) {
            this.adjancentList[i] = new Map<string, number[]>();
        }
    }

    addAdge(from: number, to: number, by: string): void {
        let adj = this.adjancentList[from];
        if (adj.has(by)) {
            adj.get(by).push(to);
        } else {
            adj.set(by, [to]);
        }
    }

    adj(v: number): Map<string, number[]> {
        return this.adjancentList[v];
    }
}

function getFirstStates(graph: Graph): number[] {
    let retval = [0];
    let neighbours = graph.adj(0).get('');
    if (neighbours) {
        retval.push(...neighbours);
    }
    return retval;
}

function dfs(graph: Graph, vertex: number, visited: boolean[]): void {
    visited[vertex] = true;
    let neighbours = graph.adj(vertex).get('');
    if (neighbours) {
        for (let v of neighbours) {
            if (!visited[v]) {
                dfs(graph, v, visited);
            }
        }
    }
}

function getConnectedStates(graph: Graph, vertex: number): number[] {
    let visited = new Array<boolean>(graph.V);
    visited.fill(false);
    dfs(graph, vertex, visited);
    let retval = [];
    for (let i = 0; i < visited.length; ++i) {
        if (visited[i]) {
            retval.push(i);
        }
    }
    return retval;
}

function visit(c: string, graph: Graph, vertices: number[]): number[]
{
    let retval = new Set<number>();
    let visited = new Array<boolean>(graph.V);
    visited.fill(false);
    for (let v of vertices) {
        if (!visited[v]) {
            visited[v] = true;
            let adj = graph.adj(v);
            let neighbours = adj.get(c);
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            neighbours = adj.get('.');
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            retval.forEach(
                u => getConnectedStates(graph, u).forEach(w => retval.add(w))
            );
        }
    }
    return [...retval];
}

/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*' where: 
-  '.' Matches any single character.​​​​
-  '*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).
*/

export function isMatch(s: string, p: string): boolean {
    if (p.length > 0) {
        let graph = new Graph(p.length + 1);
        for (let i = 0; i < p.length;) {
            let c = p[i];
            let j = i + 1;
            if (c != '*') {
                graph.addAdge(i, j, c);
            } else {
                graph.addAdge(i, i - 1, '');
                let next = j;
                for (j = i; p[j] === '*';) {
                    --j;
                    graph.addAdge(j, next, '');
                    --j;
                }
                j = next;
            }
            i = j;
        }
        let state = getFirstStates(graph);
        for (let i = 0; i < s.length; ++i) {
            state = visit(s[i], graph, state);
        }
        return state.some(v => v === p.length);
    } else {
        return s.length == 0;
    }
}

/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
- '?' Matches any single character.
- '*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
*/

function wildcardVisit(c: string, graph: Graph, vertices: number[]): number[] {
    let retval = new Set<number>();
    let visited = new Array<boolean>(graph.V);
    visited.fill(false);
    for (let v of vertices) {
        if (!visited[v]) {
            visited[v] = true;
            let adj = graph.adj(v);
            let neighbours = adj.get(c);
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            neighbours = adj.get('?');
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            neighbours = adj.get('ANY');
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            retval.forEach(
                u => getConnectedStates(graph, u).forEach(w => retval.add(w))
            );
        }
    }
    return [...retval];
}

function simplify(pattern: string): string {
    let result = [];
    for (let i = 0; i < pattern.length;) {
        let char = pattern[i];
        if (char !== '*') {
            result.push(char);
            ++i;
        } else {
            let j = i + 1;
            while (j < pattern.length && pattern[j] === '*') {
                ++j;
            }
            result.push('*');
            i = j;
        }
    }
    return result.join('');
}

/**************************************************************************
 * This implementation has performance issue, cannot handle such a case:
 *  txt = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
 *  pattern = "*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*";
 *  isWildcardMatch(txt, pattern);

export function isWildcardMatch(s: string, p: string): boolean {
    if (p.length > 0) {
        p = simplify(p);
        let graph = new Graph(p.length + 1);
        for (let i = 0; i < p.length;) {
            let char = p[i];
            let next = i + 1;
            if (char !== '*') {
                graph.addAdge(i, next, char);
            } else {
                graph.addAdge(i, next, '');
                graph.addAdge(i, i, 'ANY');
            }
            i = next;
        }
        let state = getFirstStates(graph);
        for (let i = 0; i < s.length; ++i) {
            state = wildcardVisit(s[i], graph, state);
        }
        return state.some(v => v === p.length);
    } else {
        return s.length === 0;
    }
}
*/

function divide(pattern: string): string[] {
    let retval = [];
    for (let i = 0; i < pattern.length;) {
        if (pattern[i] === '*') {
            retval.push('*');
            ++i;
        }
        let j = i;
        while (j < pattern.length && pattern[j] !== '*') {
            ++j;
        }
        if (j > i) {
            retval.push(pattern.substring(i, j));
        }
        i = j;
    }
    return retval;
}

function getCandidates(matchInfo: boolean[][], index: number): number[] {
    let retval = [];
    if (index < matchInfo.length) {
        let row = matchInfo[index];
        if (row) {
            for (let i = 0; i < row.length; ++i) {
                if (row[i]) {
                    retval.push(index + i);
                }
            }
        }
    }
    return retval;
}

function nextStep(txt: string, txtIndex: number, patterns: string[], patternIndex: number, matchInfo: boolean[][][]): boolean {
    let retval = false;
    if (patternIndex < patterns.length) {
        let candidates = getCandidates(matchInfo[patternIndex], txtIndex);
        if (candidates.length > 0) {
            for (let nextTxtIndex of candidates) {
                if (nextStep(txt, nextTxtIndex, patterns, patternIndex + 1, matchInfo)) {
                    retval = true;
                    break;
                }
            }
        }
    } else {
        retval = txtIndex >= txt.length;
    }
    return retval;
}

function wildcardCompare(txt: string, begin: number, end: number, pattern: string): boolean {
    let retval = false;
    if ((end - begin) === pattern.length) {
        retval = true;
        for (let i1 = begin, i2 = 0; i2 < pattern.length; ++i1, ++i2) {
            let p = pattern[i2];
            if (p !== '?' && p!== txt[i1]) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

/**************************************************************************
 * This implementation has performance issue, cannot handle such a case:
 *  txt = "aaaabaabaabbbabaabaabbbbaabaaabaaabbabbbaaabbbbbbabababbaabbabbbbaababaaabbbababbbaabbbaabbaaabbbaabbbbbaaaabaaabaabbabbbaabababbaabbbabababbaabaaababbbbbabaababbbabbabaaaaaababbbbaabbbbaaababbbbaabbbbb";
 *  pattern = "**a*b*b**b*b****bb******b***babaab*ba*a*aaa***baa****b***bbbb*bbaa*a***a*a*****a*b*a*a**ba***aa*a**a*";

export function isWildcardMatch(txt: string, originalPattern: string): boolean {
    if (originalPattern.length > 0) {
        let patterns = divide(simplify(originalPattern));
        let matchInfo = new Array<boolean[][]>(patterns.length);
        for (let i = 0, last = patterns.length - 1; i < patterns.length; ++i) {
            let pattern = patterns[i];
            let info = new Array<boolean[]>(txt.length + 1);
            if (pattern.length === 1 && pattern[0] === '*') {
                for (let start = 0; start <= txt.length; ++start) {
                    let row = new Array<boolean>(txt.length + 1 - start);
                    row.fill(true);
                    info[start] = row;
                }
            } else {
                let matchExists = false;
                let lastMatchExists = false;
                for (let start = 0, end = start + pattern.length; end <= txt.length; ++start, ++end) {
                    let row = new Array<boolean>(txt.length + 1 - start);
                    row.fill(false);
                    if (wildcardCompare(txt, start, end, pattern)) {
                        matchExists = true;
                        row[pattern.length] = true;
                        if (i === last && end === txt.length) {
                            lastMatchExists = true;
                        }
                    }
                    info[start] = row;
                }
                if (!matchExists || (i === last && !lastMatchExists)) {
                    return false;
                }
            }
            matchInfo[i] = info;
        }
        return nextStep(txt, 0, patterns, 0, matchInfo);
    } else {
        return txt.length === 0;
    }
}

function _isMatch(txt: string, begin: number, end: number, toBeFound: string): boolean {
    let retval = (end - begin) === toBeFound.length && end <= txt.length;
    if (retval) {
        for (let i = 0; begin < txt.length && i < toBeFound.length; ++i, ++begin) {
            if (toBeFound[i] !== '?' && toBeFound[i] !== txt[begin]) {
                retval = false;
            }
        }
    }
    return retval;
}

function find(txt: string, begin: number, toBeFound: string): number {
    for (let end = begin + toBeFound.length; end <= txt.length; ++begin, ++end) {
        if (_isMatch(txt, begin, end, toBeFound)) {
            return begin;
        }
    }
    return -1;
}

export function isWildcardMatch(txt: string, pattern: string): boolean {
    if (pattern.length > 0) {
        if (pattern[0] !== '*') {
            let i = 0;
            while (i < pattern.length && pattern[i] !== '*') {
                ++i;
            }
            if (_isMatch(txt, 0, i, pattern.substring(0, i))) {
                return isWildcardMatch(txt.substring(i), pattern.substring(i));
            }
            return false;
        } else {
            let i = 1;
            while (i < pattern.length && pattern[i] === '*') {
                ++i;
            }
            if (i < pattern.length) {
                let j = i + 1;
                while (j < pattern.length && pattern[j] !== '*') {
                    ++j;
                }
                let ptxt = pattern.substring(i, j);
                for (let k = -1;;) {
                    k = find(txt, k + 1, ptxt);
                    if (k >= 0) {
                        if (isWildcardMatch(txt.substring(k + ptxt.length), pattern.substring(j))) {
                            return true;
                        }
                    } else {
                        break;
                    }
                }
                return false;
            } else {
                return true;
            }
        }
    } else {
        return txt.length === 0;
    }
}
*/

/* we do not need to backtrack to the previous *, this is the key of this algorithm */
export function isWildcardMatch(txt: string, pattern: string): boolean {
    let ti = 0;
    let pi = 0;
    let tStar = -1;
    let pStar = -1;
    while (ti < txt.length) {
        if (pi < pattern.length) {
            if (txt[ti] === pattern[pi] || pattern[pi] === '?') {
                ++ti;
                ++pi;
            } else {
                if (pattern[pi] === '*') {
                    tStar = ti;
                    pStar = pi++;
                } else {
                    if (tStar >= 0) {
                        ti = ++tStar;
                        pi = pStar + 1;
                    } else {
                        return false;
                    }
                }
            }
        } else {
            if (tStar >= 0) {
                ti = ++tStar;
                pi = pStar + 1;
            } else {
                return false;
            }
        }
    }
    while (pi < pattern.length && pattern[pi] === '*') {
        ++pi;
    }
    return pi === pattern.length;
}
