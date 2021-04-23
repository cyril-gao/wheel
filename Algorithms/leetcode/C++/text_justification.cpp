#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <string>
#include <vector>
#include <stdexcept>

#include "check.h"


/*
Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.
 

Example 1:
Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:
Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be", because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified becase it contains only one word.

Example 3:
Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
*/

std::vector<std::string> justify_fully(std::vector<std::string> const & words, size_t max_width)
{
    std::vector<std::string> retval;
    size_t n = words.size();
    if (n > 0) {
        for (size_t i = 0, j = 0; i < n;) {
            size_t number_of_words = 0;
            size_t number_of_letters = 0;
            for (j = i; j < n; ++j) {
                size_t wl = words[j].length();
                assert(wl <= max_width);
                size_t nol = wl + !(j==i) + number_of_letters;
                if (nol <= max_width) {
                    number_of_letters = nol;
                    ++number_of_words;
                } else {
                    break;
                }
            }
            std::vector<char> buf;
            buf.reserve(max_width + 1);
            if (j < n) {
                if (number_of_words > 1) {
                    size_t number_of_separators = number_of_words - 1;
                    size_t remainder = max_width - number_of_letters;
                    size_t spaces = 1 + remainder/number_of_separators;
                    remainder %= number_of_separators;
                    buf.insert(buf.end(), words[i].begin(), words[i].end());
                    for (size_t k = 0, l = i+1; k < number_of_separators; ++k, ++l) {
                        size_t inc = 0;
                        if (remainder > 0) {
                            --remainder;
                            inc = 1;
                        }
                        buf.insert(buf.end(), spaces + inc, ' ');
                        buf.insert(buf.end(), words[l].begin(), words[l].end());
                    }
                } else if (number_of_words == 1) {
                    buf.insert(buf.end(), words[i].begin(), words[i].end());
                    buf.insert(buf.end(), max_width - number_of_letters, ' ');
                } else {
                    throw std::invalid_argument("bad argument");
                }
            } else {
                // the last line
                number_of_letters = 0;
                for (size_t k = i; k < n; ++k) {
                    if (k != i) {
                        buf.push_back(' ');
                        ++number_of_letters;
                    }
                    number_of_letters += words[k].length();
                    buf.insert(buf.end(), words[k].begin(), words[k].end());
                }
                if (number_of_letters < max_width) {
                    buf.insert(buf.end(), max_width - number_of_letters, ' ');
                }
            }
            buf.push_back('\0');
            retval.emplace_back(&buf[0]);
            i = j;
        }
    }
    return retval;
}

int main()
{
    {
        std::vector<std::string> words = { "This", "is", "an", "example", "of", "text", "justification." };
        std::vector<std::string> expectation = {
            "This    is    an",
            "example  of text",
            "justification.  "
        };
        size_t max_width = 16;
        auto r = justify_fully(words, max_width);
        examine(r == expectation, "justify_fully is failed at the line %d\n", __LINE__);
    }
    {
        std::vector<std::string> words = { "What", "must", "be", "acknowledgment", "shall", "be" };
        std::vector<std::string> expectation = {
            "What   must   be",
            "acknowledgment  ",
            "shall be        "
        };
        size_t max_width = 16;
        auto r = justify_fully(words, max_width);
        examine(r == expectation, "justify_fully is failed at the line %d\n", __LINE__);
    }
    {
        std::vector<std::string> words = { "Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do" };
        std::vector<std::string> expectation = {
            "Science  is  what we",
            "understand      well",
            "enough to explain to",
            "a  computer.  Art is",
            "everything  else  we",
            "do                  "
        };
        size_t max_width = 20;
        auto r = justify_fully(words, max_width);
        examine(r == expectation, "justify_fully is failed at the line %d\n", __LINE__);
    }
    printf("OK\n");
    return 0;
}
