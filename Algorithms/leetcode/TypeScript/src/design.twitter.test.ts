import { Twitter } from './design.twitter';

test(
    "check the result value of the call to the class Twitter",
    () => {
        let twitter = new Twitter();
        twitter.postTweet(1, 5);
        let result = twitter.getNewsFeed(1);
        expect(result).toEqual([5]);
        twitter.postTweet(2, 6);
        twitter.follow(1, 2);
        result = twitter.getNewsFeed(1);
        expect(result).toEqual([6, 5]);
        twitter.unfollow(1, 2);
        result = twitter.getNewsFeed(1);
        expect(result).toEqual([5]);
        twitter.postTweet(3, 7);
        twitter.follow(1, 3);
        result = twitter.getNewsFeed(1);
        expect(result).toEqual([7, 5]);
        twitter.postTweet(1, 8);
        result = twitter.getNewsFeed(1);
        expect(result).toEqual([8, 7, 5]);
        twitter.follow(1, 2);
        result = twitter.getNewsFeed(1);
        expect(result).toEqual([8, 7, 6, 5]);

        setTimeout(() => twitter.postTweet(1, 9), 50);
        setTimeout(() => twitter.postTweet(2, 10), 100);
        setTimeout(() => twitter.postTweet(3, 11), 150);
        setTimeout(
            () => {
                result = twitter.getNewsFeed(1);
                expect(result).toEqual([11, 10, 9, 8, 7, 6, 5]);
            },
            200
        );

        setTimeout(() => twitter.postTweet(1, 12), 250);
        setTimeout(() => twitter.postTweet(1, 13), 300);
        setTimeout(() => twitter.postTweet(2, 14), 350);
        setTimeout(() => twitter.postTweet(2, 15), 400);
        setTimeout(() => twitter.postTweet(2, 16), 450);
        setTimeout(() => twitter.postTweet(2, 17), 500);
        setTimeout(() => twitter.postTweet(3, 18), 550);
        setTimeout(
            () => {
                result = twitter.getNewsFeed(1);
                expect(result).toEqual([18, 17, 16, 15, 14, 13, 12, 11, 10, 9]);
            },
            600
        );
    }
);
