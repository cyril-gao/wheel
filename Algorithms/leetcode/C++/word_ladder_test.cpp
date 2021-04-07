#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "check.h"


namespace
{
    template <typename C>
    using String = std::basic_string<C>;

    template <typename C>
    std::unordered_set<C> generate_letter_set(
        const String<C>& first_word, const String<C>& last_word,
        std::vector<String<C>> const& word_list
    ) {
        std::unordered_set<C> retval;
        auto gather = [&retval](const String<C>& word) {
            std::for_each(
                word.begin(), word.end(),
                [&retval](auto c) { retval.insert(c); }
            );
        };
        gather(first_word);
        gather(last_word);
        for (const auto& w : word_list) {
            gather(w);
        }
        return retval;
    }

    template <typename C>
    struct State {
        size_t distance;
        std::vector<String<C>> parents;

        explicit State(size_t d) : distance(d) {}
        State(): State(SIZE_MAX) {}
        State(size_t d, const String<C>& parent) : State(d) {
            parents.push_back(parent);
        }
    };

    template <typename C>
    std::vector<String<C>> generate_neighbours(
        const String<C>& word,
        std::unordered_set<C> const& letter_set,
        std::unordered_set<String<C>> const& word_set
    ) {
        std::vector<String<C>> retval;
        std::basic_string<C> tmp(word);
        for (size_t i = 0, ie = word.length(); i != ie; ++i) {
            C old = tmp[i];
            for (auto c : letter_set) {
                if (c != old) {
                    tmp[i] = c;
                    if (word_set.find(tmp) != word_set.end()) {
                        retval.push_back(tmp);
                    }
                }
            }
            tmp[i] = old;
        }
        return retval;
    }

    template <typename C>
    std::vector<std::vector<std::basic_string<C>>> retrieve_paths(
        const String<C>& word,
        std::unordered_map<String<C>, State<C>> const& visited_words
    ) {
        std::vector<std::vector<std::basic_string<C>>> retval;
        const auto & parents = visited_words.at(word).parents;
        if (!parents.empty()) {
            for (const auto& p : parents) {
                auto paths = retrieve_paths(p, visited_words);
                for (auto & path : paths) {
                    path.push_back(word);
                    retval.push_back(std::move(path));
                }
            }
        } else {
            std::vector<std::basic_string<C>> path = { word };
            retval.emplace_back(std::move(path));
        }
        return retval;
    }

    template <typename C>
    void retrieve_paths(
        const String<C> & word, const String<C> & last_word,
        std::unordered_map<String<C>, State<C>> const& visited_words,
        std::vector<std::vector<std::basic_string<C>>> & result
    ) {
        auto paths = retrieve_paths<C>(word, visited_words);
        for (auto & path : paths) {
            path.push_back(last_word);
            result.emplace_back(std::move(path));
        }
    }
}


/*
Given two words (first_word and last_word), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
]
*/

template <typename C>
std::vector<std::vector<std::basic_string<C>>> find_ladders(
    const String<C>& first_word, const String<C>& last_word,
    std::vector<std::basic_string<C>> const& word_list
) {
    std::vector<std::vector<std::basic_string<C>>> retval;
    if (first_word != last_word) {
        auto letter_set = generate_letter_set(first_word, last_word, word_list);
        std::unordered_set<String<C>> word_set;
        std::for_each(
            word_list.begin(), word_list.end(),
            [&word_set](const auto& w) { word_set.insert(w); }
        );
        std::unordered_map<String<C>, State<C>> visited_words;
        visited_words[first_word] = State<C>(0);
        std::queue<String<C>> queue;
        queue.push(first_word);
        while (!queue.empty()) {
            auto w = std::move(queue.front());
            decltype(auto) state = visited_words[w];
            size_t new_distance = state.distance + 1;
            queue.pop();
            auto neighbours = generate_neighbours(w, letter_set, word_set);
            for (auto & n : neighbours) {
                if (n != last_word) {
                    auto ni = visited_words.find(n);
                    if (ni == visited_words.end()) {
                        visited_words[n] = State<C>(new_distance, w);
                        queue.push(std::move(n));
                    } else {
                        if (ni->second.distance == new_distance) {
                            ni->second.parents.push_back(w);
                        }
                    }
                } else {
                    auto li = visited_words.find(last_word);
                    if (li == visited_words.end()) {
                        visited_words[n] = State<C>(new_distance, w);
                        retrieve_paths(w, last_word, visited_words, retval);
                    } else {
                        if (li->second.distance == new_distance) {
                            retrieve_paths(w, last_word, visited_words, retval);
                        }
                    }
                }
            }
        }
    } else {
        std::vector<std::basic_string<C>> list = { std::basic_string<C>(first_word) };
        retval.emplace_back(std::move(list));
    }
    return retval;
}

int main()
{
    auto print_paths = [](
        std::vector<std::vector<std::string>> const& paths,
        FILE * pf = stdout
    ) {
        fprintf(pf, "%zu:\n[\n", paths.size());
        for (const auto & path : paths) {
            fprintf(pf, "\t[");
            for (size_t i = 0, ie = path.size(); i < ie; ++i) {
                if (i != 0) {
                    fprintf(pf, ",");
                }
                fprintf(pf, path[i].c_str());
            }
            fprintf(pf, "]\n");
        }
        fprintf(pf, "]\n");
    };
    {
        std::vector<std::string> word_list = { "hot", "dot", "dog", "lot", "log", "cog" };
        std::vector<std::vector<std::string>> expectation = {
            {"hit","hot","lot","log","cog"}, {"hit","hot","dot","dog","cog"}
        };
        auto result = find_ladders<char>("hit", "cog", word_list);
        if (result != expectation) { print_paths(result); }
        examine(result == expectation, "find_ladders is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<std::string> word_list = { "hot", "dot", "dog", "lot", "log" };
        std::vector<std::vector<std::string>> expectation = {};
        auto result = find_ladders<char>("hit", "cog", word_list);
        if (result != expectation) { print_paths(result); }
        examine(result == expectation, "find_ladders is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<std::string> word_list = { "a", "b", "c" };
        std::vector<std::vector<std::string>> expectation = { {"a", "b"} };
        auto result = find_ladders<char>("a", "b", word_list);
        if (result != expectation) { print_paths(result); }
        examine(result == expectation, "find_ladders is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<std::string> word_list = {
            "ted", "tex", "red", "tax", "tad", "den", "rex", "pee", "rad", "rax"
        };
        std::vector<std::vector<std::string>> expectation = {
            {"red","ted","tad","tax"},
            {"red","rad","tad","tax"},
            {"red","ted","tex","tax"},
            {"red","rex","tex","tax"},
            {"red","rad","rax","tax"},
            {"red","rex","rax","tax"}
        };
        auto result = find_ladders<char>("red", "tax", word_list);
        if (result != expectation) { print_paths(result); }
        examine(result == expectation, "find_ladders is failed at the line: %d\n", __LINE__);
    }
    return 0;
}
