/*
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.
getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
follow(followerId, followeeId): Follower follows a followee.
unfollow(followerId, followeeId): Follower unfollows a followee.

Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);
*/


class TweetMessage {
    constructor(public tweetId: number, public tick: number) {
    }
}

function itemSwap(data: TweetMessage[], i: number, j: number): void {
    if (i != j) {
        let tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}

function split(data: TweetMessage[], begin: number, end: number, K: number): number {
    if (K != 1) {
        let tm = data[begin];
        let ge = end;
        for (let i = end; i > begin;) {
            --i;
            if (data[i].tick >= tm.tick) {
                itemSwap(data, --ge, i);
            }
        }
        let L = end - ge;
        if (L == K) {
            return ge;
        } else {
            if (L < K) {
                return split(data, begin, ge, K - L);
            } else {
                if ((end - ge - 1) != K) {
                    return split(data, ge + 1, end, K);
                } else {
                    return ge + 1;
                }
            }
        }
    } else {
        let g = begin;
        for (let i = begin + 1; i < end; ++i) {
            if (data[i].tick > data[g].tick) {
                g = i;
            }
        }
        itemSwap(data, g, end - 1);
        return end - 1;
    }
}

function getTopK(data: TweetMessage[], K: number): TweetMessage[] {
    if (data.length > K) {
        let tmp = data[K];
        data[K] = data[0];
        data[0] = tmp;
        let s = split(data, 0, data.length, K);
        data = data.slice(s, data.length);
    }
    data.sort(
        (tm1, tm2) => {
            if (tm1.tick > tm2.tick) {
                return -1;
            } else if (tm1.tick < tm2.tick) {
                return 1;
            } else {
                return 0;
            }
        }
    );
    return data;
}

class UserProfile {
    tweetMessages: TweetMessage[];
    followees: Set<number>;

    constructor() {
        this.tweetMessages = [];
        this.followees = new Set<number>();
    }
}

export class Twitter {
    tick: number;
    allUsers: Map<number, UserProfile>;

    constructor() {
        this.tick = 0;
        this.allUsers = new Map<number, UserProfile>();
    }

    postTweet(userId: number, tweetId: number): void {
        let up = this.allUsers.get(userId);
        if (!up) {
            up = new UserProfile();
        }
        up.tweetMessages.unshift(new TweetMessage(tweetId, this.tick++));
        if (up.tweetMessages.length > 10) {
            up.tweetMessages.pop();
        }
        this.allUsers.set(userId, up);
    }

    getNewsFeed(userId: number): number[] {
        let retval = [];
        let up = this.allUsers.get(userId);
        if (up) {
            let buffer = [...up.tweetMessages];
            if (buffer.length > 10) {
                buffer = buffer.slice(0, 10);
            }
            for (let f of up.followees) {
                if (f != userId) {
                    let fup = this.allUsers.get(f);
                    if (fup) {
                        let b1 = buffer;
                        let b2 = fup.tweetMessages;
                        if (b2.length > 10) {
                            b2 = b2.slice(0, 10);
                        }
                        buffer = [];
                        let i: number;
                        let j: number;
                        for (i = 0, j = 0; i < b1.length && j < b2.length;) {
                            if (b1[i].tick >= b2[j].tick) {
                                buffer.push(b1[i]);
                                ++i;
                            } else {
                                buffer.push(b2[j]);
                                ++j;
                            }
                        }
                        if (i < b1.length) {
                            buffer.push(...b1.slice(i, b1.length));
                        } else if (j < b2.length) {
                            buffer.push(...b2.slice(j, b2.length));
                        }
                    }
                }
            }
            if (buffer.length > 10) {
                buffer = buffer.slice(0, 10);
            }
            retval = buffer.map(tm => tm.tweetId);
        }
        return retval;
    }

    follow(followerId: number, followeeId: number): void {
        let up = this.allUsers.get(followerId);
        if (!up) {
            up = new UserProfile();
        }
        up.followees.add(followeeId);
        this.allUsers.set(followerId, up);
    }

    unfollow(followerId: number, followeeId: number): void {
        let up = this.allUsers.get(followerId);
        if (!up) {
            up = new UserProfile();
        }
        up.followees.delete(followeeId);
        this.allUsers.set(followerId, up);
    }
}
