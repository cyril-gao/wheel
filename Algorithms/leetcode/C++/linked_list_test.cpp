#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <vector>
#include <utility>
#include "check.h"

/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example 1:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
*/

template <typename T>
struct ListNode
{
    T data;
    ListNode * next;

    ListNode() : data{}, next(nullptr) {}
    explicit ListNode(T const& d, ListNode<T> * n = nullptr) : data(d), next(n) {}
};


template <typename T>
void deallocate(ListNode<T> * head)
{
    while (head != nullptr) {
        auto next = head->next;
        delete head;
        head = next;
    }
}

template <typename T>
ListNode<T> * add_two_numbers(ListNode<T>* l1, ListNode<T>* l2)
{
    if (l1 != nullptr && l2 != nullptr) {
        ListNode<T> * retval = nullptr;
        try {
            ListNode<T> * current = nullptr;
            T inc{0};
            auto add_new_item = [&](auto v) {
                inc = 0;
                if (v > 9) {
                    v -= 10;
                    inc = 1;
                }
                auto * p = new ListNode<T>(v);
                if (current != nullptr) {
                    current->next = p;
                } else {
                    retval = p;
                }
                current = p;
            };
            while (l1 != nullptr && l2 != nullptr) {
                T sum = l1->data + l2->data + inc;
                add_new_item(sum);
                l1 = l1->next;
                l2 = l2->next;
            }
            if (l2 != nullptr) {
                l1 = l2;
            }
            while (l1 != nullptr) {
                T sum = l1->data + inc;
                add_new_item(sum);
                l1 = l1->next;
            }
            if (inc != 0) {
                add_new_item(inc);
            }
        } catch (...) {
            deallocate(retval);
            retval = nullptr;
            throw;
        }
        return retval;
    } else {
        return l1 != nullptr ? l1 : l2;
    }
}

void add_two_numbers_test()
{
    {
        ListNode<int> n1{2}, n2{4}, n3{3}, n4{5}, n5{6}, n6{4};
        n1.next = &n2, n2.next = &n3;
        n4.next = &n5, n5.next = &n6;
        auto result = add_two_numbers(&n1, &n4);
        examine(
            result->data == 7 &&
            result->next->data == 0 &&
            result->next->next->data == 8 &&
            result->next->next->next == nullptr,
            "add_two_numbers is failed at the line: %d\n", __LINE__
        );
        deallocate(result);
    }
    {
        ListNode<int> n1{9}, n2{9}, n3{9}, n4{9}, n5{9}, n6{9}, n7{9}, n8{9};
        ListNode<int> n9{9}, n10{9}, n11{9};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8;
        n9.next = &n10, n10.next = &n11;
        auto result = add_two_numbers(&n1, &n9);
        examine(
            result->data == 8 &&
            result->next->data == 9 &&
            result->next->next->data == 9 &&
            result->next->next->next->data == 0 &&
            result->next->next->next->next->data == 0 &&
            result->next->next->next->next->next->data == 0 &&
            result->next->next->next->next->next->next->data == 0 &&
            result->next->next->next->next->next->next->next->data == 0 &&
            result->next->next->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "add_two_numbers is failed at the line: %d\n", __LINE__
        );
        deallocate(result);
    }
    {
        ListNode<int> n1{0}, n2{0};
        auto result = add_two_numbers(&n1, &n2);
        examine(
            result->data == 0 &&
            result->next == nullptr,
            "add_two_numbers is failed at the line: %d\n", __LINE__
        );
        deallocate(result);
    }
}


//////////////////////////////////////////////////////////////////////////////////////
/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Follow up: Could you do this in one pass?
*/

template <typename T>
std::pair<ListNode<T>*, ListNode<T>*> remove_from_end(ListNode<T> * head, size_t k)
{
    ListNode<T> * new_head = head, * item = nullptr;
    size_t i = 1;
    ListNode<T> * previous = nullptr, * current = head;
    for (; current != nullptr && i < k; current = current->next, ++i) {}
    if (current != nullptr) {
        previous = head;
        if (current->next != nullptr) {
            current = current->next;
            while (current->next != nullptr) {
                current = current->next;
                previous = previous->next;
            }
            item = previous->next;
            previous->next = item->next;
        } else {
            item = head;
            new_head = item->next;
        }
    }
    return std::make_pair(new_head, item);
}

void remove_from_end_test()
{
    {
        ListNode<int> n1{1};
        auto result = remove_from_end(&n1, 1);
        examine(result.first == nullptr && result.second == &n1, "remove_from_end is failed at the line: %d\n", __LINE__);
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5;
        auto result = remove_from_end(&n1, 5);
        examine(result.first == &n2 && result.second == &n1, "remove_from_end is failed at the line: %d\n", __LINE__);
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5;
        auto result = remove_from_end(&n1, 6);
        examine(result.first == &n1 && result.second == nullptr, "remove_from_end is failed at the line: %d\n", __LINE__);
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5;
        auto result = remove_from_end(&n1, 2);
        examine(result.first == &n1 && result.second == &n4, "remove_from_end is failed at the line: %d\n", __LINE__);
    }
}


/*
Given a linked list, swap every two adjacent nodes and return its head.

Example 1:
Input: head = [1,2,3,4]
Output: [2,1,4,3]

Example 2:
Input: head = []
Output: []

Example 3:
Input: head = [1]
Output: [1]
*/
template <typename T>
ListNode<T> * swap_pairs(ListNode<T> * head)
{
    ListNode<T> * retval = head;
    ListNode<T> * previous = nullptr;
    while (head != nullptr && head->next != nullptr) {
        auto first = head;
        auto second = first->next;
        auto third = second->next;
        if (previous != nullptr) {
            previous->next = second;
        } else {
            retval = second;
        }
        second->next = first;
        previous = first;
        head = third;
    }
    if (previous != nullptr) {
        previous->next = head;
    }
    return retval;
}

void swap_pairs_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5;
        auto result = swap_pairs(&n1);
        examine(
            result->data == 2 &&
            result->next->data == 1 &&
            result->next->next->data == 4 &&
            result->next->next->next->data == 3 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next == nullptr,
            "swap_pairs is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> * nil = nullptr;
        auto result = swap_pairs(nil);
        examine(result == nullptr, "swap_pairs is failed at the line: %d\n", __LINE__);
    }
    {
        ListNode<int> n1{1};
        auto result = swap_pairs(&n1);
        examine(result->data == 1 && result->next == nullptr, "swap_pairs is failed at the line: %d\n", __LINE__);
    }
}

/*
Given the head of a linked list, rotate the list to the right by k places.
*/
template <typename T>
size_t size(ListNode<T> const* head)
{
    size_t retval = 0;
    while (head != nullptr) {
        ++retval;
        head = head->next;
    }
    return retval;
}

template <typename T>
ListNode<T> * rotate_right(ListNode<T> * head, size_t k)
{
    if (head != nullptr && head->next != nullptr) {
        size_t n = size(head);
        k %= n;
        ListNode<T> * retval = head;
        if (k > 0) {
            ListNode<T> * previous = head;
            ListNode<T> * tail = head;
            for (size_t i = 0; i < k; ++i, tail = tail->next) {}
            while (tail->next != nullptr) {
                previous = previous->next;
                tail = tail->next;
            }
            retval = previous->next;
            previous->next = nullptr;
            tail->next = head;
        }
        return retval;
    } else {
        return head;
    }
}

void rotate_right_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        for (size_t i = 0; i < 20; i += 5) {
            n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = nullptr;
            auto result = rotate_right(&n1, i);
            examine(
                result->data == 1 &&
                result->next->data == 2 &&
                result->next->next->data == 3 &&
                result->next->next->next->data == 4 &&
                result->next->next->next->next->data == 5 &&
                result->next->next->next->next->next == nullptr,
                "rotate_right is failed at the line: %d\n", __LINE__
            );
        }
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        for (size_t i = 1; i < 20; i += 5) {
            n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = nullptr;
            auto result = rotate_right(&n1, i);
            examine(
                result->data == 5 &&
                result->next->data == 1 &&
                result->next->next->data == 2 &&
                result->next->next->next->data == 3 &&
                result->next->next->next->next->data == 4 &&
                result->next->next->next->next->next == nullptr,
                "rotate_right is failed at the line: %d\n", __LINE__
            );
        }
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        for (size_t i = 2; i < 20; i += 5) {
            n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = nullptr;
            auto result = rotate_right(&n1, i);
            examine(
                result->data == 4 &&
                result->next->data == 5 &&
                result->next->next->data == 1 &&
                result->next->next->next->data == 2 &&
                result->next->next->next->next->data == 3 &&
                result->next->next->next->next->next == nullptr,
                "rotate_right is failed at the line: %d\n", __LINE__
            );
        }
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        for (size_t i = 3; i < 20; i += 5) {
            n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = nullptr;
            auto result = rotate_right(&n1, i);
            examine(
                result->data == 3 &&
                result->next->data == 4 &&
                result->next->next->data == 5 &&
                result->next->next->next->data == 1 &&
                result->next->next->next->next->data == 2 &&
                result->next->next->next->next->next == nullptr,
                "rotate_right is failed at the line: %d\n", __LINE__
            );
        }
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        for (size_t i = 4; i < 20; i += 5) {
            n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = nullptr;
            auto result = rotate_right(&n1, i);
            examine(
                result->data == 2 &&
                result->next->data == 3 &&
                result->next->next->data == 4 &&
                result->next->next->next->data == 5 &&
                result->next->next->next->next->data == 1 &&
                result->next->next->next->next->next == nullptr,
                "rotate_right is failed at the line: %d\n", __LINE__
            );
        }
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3};
        n1.next = &n2, n2.next = &n3;
        auto result = rotate_right(&n1, 4);
        examine(
            result->data == 3 &&
            result->next->data == 1 &&
            result->next->next->data == 2 &&
            result->next->next->next == nullptr,
            "rotate_right is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> * nil = nullptr;
        for (int i = 0; i < 10; ++i) {
            auto result = rotate_right(nil, i);
            examine(result == nullptr, "rotate_right is failed at the line: %d\n", __LINE__);
        }
    }
    {
        ListNode<int> n1{1};
        for (int i = 0; i < 10; ++i) {
            auto result = rotate_right(&n1, i);
            examine(result == &n1 && result->next == nullptr, "rotate_right is failed at the line: %d\n", __LINE__);
        }
    }
}


/*
Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list. Return the linked list sorted as well.
*/

template <typename T>
std::pair<ListNode<T>*, ListNode<T>*> separate_duplicates(ListNode<T> * head)
{
    ListNode<T> * dup = nullptr, * uni = head;
    if (head != nullptr && head->next != nullptr) {
        uni = nullptr;
        ListNode<T> * dup_previous = nullptr;
        ListNode<T> * uni_previous = nullptr;
        while (head != nullptr) {
            size_t count = 1;
            ListNode<T> * next = head;
            for (
                auto third = next->next;
                third != nullptr && third->data == head->data;
                ++count, next = third, third = third->next
            ) {
            }
            if (count > 1) {
                if (dup_previous != nullptr) {
                    dup_previous->next = head;
                } else {
                    dup = head;
                }
                dup_previous = next;
                head = next->next;
            } else {
                if (uni_previous != nullptr) {
                    uni_previous->next = head;
                } else {
                    uni = head;
                }
                uni_previous = head;
                head = head->next;
            }
        }
        if (uni_previous != nullptr) {
            uni_previous->next = nullptr;
        }
        if (dup_previous != nullptr) {
            dup_previous->next = nullptr;
        }
    }
    return std::make_pair(dup, uni);
}

void separate_duplicates_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n2_2{2}, n3{3}, n4{4}, n4_2{4}, n4_3{4}, n5{5};
        n1.next = &n2, n2.next = &n2_2, n2_2.next = &n3, n3.next = &n4, n4.next = &n4_2, n4_2.next = &n4_3, n4_3.next = &n5;
        auto result = separate_duplicates(&n1);
        examine(
            result.first->data == 2 &&
            result.first->next->data == 2 &&
            result.first->next->next->data == 4 &&
            result.first->next->next->next->data == 4 &&
            result.first->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next == nullptr &&
            result.second->data == 1 &&
            result.second->next->data == 3 &&
            result.second->next->next->data == 5 &&
            result.second->next->next->next == nullptr,
            "separate_duplicates is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n2_2{2}, n3{3}, n4{4}, n4_2{4}, n4_3{4}, n5{5}, n5_2{5};
        n1.next = &n2, n2.next = &n2_2, n2_2.next = &n3, n3.next = &n4, n4.next = &n4_2, n4_2.next = &n4_3, n4_3.next = &n5, n5.next = &n5_2;
        auto result = separate_duplicates(&n1);
        examine(
            result.first->data == 2 &&
            result.first->next->data == 2 &&
            result.first->next->next->data == 4 &&
            result.first->next->next->next->data == 4 &&
            result.first->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->data == 5 &&
            result.first->next->next->next->next->next->next->data == 5 &&
            result.first->next->next->next->next->next->next->next == nullptr &&
            result.second->data == 1 &&
            result.second->next->data == 3 &&
            result.second->next->next == nullptr,
            "separate_duplicates is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n1_2{1}, n2{2}, n2_2{2}, n3{3}, n4{4}, n4_2{4}, n4_3{4}, n5{5};
        n1.next = &n1_2, n1_2.next = &n2, n2.next = &n2_2, n2_2.next = &n3, n3.next = &n4, n4.next = &n4_2, n4_2.next = &n4_3, n4_3.next = &n5;
        auto result = separate_duplicates(&n1);
        examine(
            result.first->data == 1 &&
            result.first->next->data == 1 &&
            result.first->next->next->data == 2 &&
            result.first->next->next->next->data == 2 &&
            result.first->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->next == nullptr &&
            result.second->data == 3 &&
            result.second->next->data == 5 &&
            result.second->next->next == nullptr,
            "separate_duplicates is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n1_2{1}, n2{2}, n2_2{2}, n3{3}, n4{4}, n4_2{4}, n4_3{4}, n5{5}, n5_2{5};
        n1.next = &n1_2, n1_2.next = &n2, n2.next = &n2_2, n2_2.next = &n3, n3.next = &n4, n4.next = &n4_2, n4_2.next = &n4_3, n4_3.next = &n5, n5.next = &n5_2;
        auto result = separate_duplicates(&n1);
        examine(
            result.first->data == 1 &&
            result.first->next->data == 1 &&
            result.first->next->next->data == 2 &&
            result.first->next->next->next->data == 2 &&
            result.first->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->next->data == 5 &&
            result.first->next->next->next->next->next->next->next->next->data == 5 &&
            result.first->next->next->next->next->next->next->next->next->next == nullptr &&
            result.second->data == 3 &&
            result.second->next == nullptr,
            "separate_duplicates is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n1_2{1}, n2{2}, n2_2{2}, n3{3}, n3_2{3}, n4{4}, n4_2{4}, n4_3{4}, n5{5}, n5_2{5};
        n1.next = &n1_2, n1_2.next = &n2, n2.next = &n2_2, n2_2.next = &n3, n3.next = &n3_2, n3_2.next = &n4, n4.next = &n4_2, n4_2.next = &n4_3, n4_3.next = &n5, n5.next = &n5_2;
        auto result = separate_duplicates(&n1);
        examine(
            result.first->data == 1 &&
            result.first->next->data == 1 &&
            result.first->next->next->data == 2 &&
            result.first->next->next->next->data == 2 &&
            result.first->next->next->next->next->data == 3 &&
            result.first->next->next->next->next->next->data == 3 &&
            result.first->next->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->next->next->data == 4 &&
            result.first->next->next->next->next->next->next->next->next->next->data == 5 &&
            result.first->next->next->next->next->next->next->next->next->next->next->data == 5 &&
            result.first->next->next->next->next->next->next->next->next->next->next->next == nullptr &&
            result.second == nullptr,
            "separate_duplicates is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5;
        auto result = separate_duplicates(&n1);
        examine(
            result.first == nullptr &&
            result.second->data == 1 &&
            result.second->next->data == 2 &&
            result.second->next->next->data == 3 &&
            result.second->next->next->next->data == 4 &&
            result.second->next->next->next->next->data == 5 &&
            result.second->next->next->next->next->next == nullptr,
            "separate_duplicates is failed at the line: %d\n", __LINE__
        );
    }
}


/*
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.
*/

template <typename T>
ListNode<T>* partition(ListNode<T> * head, T const& v)
{
    if (head != nullptr && head->next != nullptr) {
        ListNode<T>* less_head = nullptr;
        ListNode<T>* less_previous = nullptr;
        ListNode<T>* ge_head = nullptr;
        ListNode<T>* ge_previous = nullptr;
        while (head != nullptr) {
            if (head->data < v) {
                if (less_previous != nullptr) {
                    less_previous->next = head;
                } else {
                    less_head = head;
                }
                less_previous = head;
            } else {
                if (ge_previous != nullptr) {
                    ge_previous->next = head;
                } else {
                    ge_head = head;
                }
                ge_previous = head;
            }
            head = head->next;
        }
        if (ge_previous != nullptr) {
            ge_previous->next = nullptr;
        }
        if (less_previous != nullptr) {
            less_previous->next = ge_head;
        }
        return less_head != nullptr ? less_head : ge_head;
    } else {
        return head;
    }
}

void partition_test()
{
    {
        ListNode<int> n1{1}, n4{4}, n3{3}, n2{2}, n5{5}, n2_2{2};
        n1.next = &n4, n4.next = &n3, n3.next = &n2, n2.next = &n5, n5.next = &n2_2;
        auto result = partition(&n1, 3);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 2 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next == nullptr,
            "partition is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n4{4}, n1{1}, n3{3}, n2{2}, n5{5}, n2_2{2};
        n4.next = &n1, n1.next = &n3, n3.next = &n2, n2.next = &n5, n5.next = &n2_2;
        auto result = partition(&n4, 4);
        examine(
            result->data == 1 &&
            result->next->data == 3 &&
            result->next->next->data == 2 &&
            result->next->next->next->data == 2 &&
            result->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next == nullptr,
            "partition is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n4{4}, n1{1}, n3{3}, n2{2}, n5{5}, n2_2{2};
        n4.next = &n1, n1.next = &n3, n3.next = &n2, n2.next = &n5, n5.next = &n2_2;
        auto result = partition(&n4, 5);
        examine(
            result->data == 4 &&
            result->next->data == 1 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 2 &&
            result->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next == nullptr,
            "partition is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n4{4}, n1{1}, n3{3}, n2{2}, n5{5}, n2_2{2};
        n4.next = &n1, n1.next = &n3, n3.next = &n2, n2.next = &n5, n5.next = &n2_2;
        auto result = partition(&n4, 13);
        examine(
            result->data == 4 &&
            result->next->data == 1 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 2 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next == nullptr,
            "partition is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n4{4}, n1{1}, n3{3}, n2{2}, n5{5}, n2_2{2};
        n4.next = &n1, n1.next = &n3, n3.next = &n2, n2.next = &n5, n5.next = &n2_2;
        auto result = partition(&n4, 0);
        examine(
            result->data == 4 &&
            result->next->data == 1 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 2 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next == nullptr,
            "partition is failed at the line: %d\n", __LINE__
        );
    }
}


/*
Given the head of a singly linked list and two integers left and right
where left <= right, reverse the nodes of the list from position left to
position right, and return the reversed list.
*/

template <typename T>
ListNode<T> * reverse_between(ListNode<T> * head, size_t from, size_t to)
{
    assert(from <= to);
    ListNode<T> * retval = head;
    if (head != nullptr && head->next != nullptr) {
        ListNode<T> * previous = nullptr;
        ListNode<T> * current = head;
        for (size_t i = 1; i < from && current != nullptr; ++i, previous = current, current = current->next) {}
        if (current != nullptr) {
            ListNode<T> * tail = current;
            ListNode<T> * next = current->next;
            for (size_t i = from + 1; i <= to && next != nullptr;) {
                auto j = next->next;
                if (previous != nullptr) {
                    ListNode<T> * third = previous->next;
                    next->next = third;
                    previous->next = next;
                } else {
                    next->next = retval;
                    retval = next;
                }
                ++i;
                next = j;
            }
            tail->next = next;
        }
    }
    return retval;
}

void reverse_between_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 1, 5);
        examine(
            result->data == 5 &&
            result->next->data == 4 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 2 &&
            result->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 2, 7);
        examine(
            result->data == 1 &&
            result->next->data == 7 &&
            result->next->next->data == 6 &&
            result->next->next->next->data == 5 &&
            result->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 1, 7);
        examine(
            result->data == 7 &&
            result->next->data == 6 &&
            result->next->next->data == 5 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 3, 3);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 6, 7);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 1, 1);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7;
        auto result = reverse_between(&n1, 3, 8);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 7 &&
            result->next->next->next->data == 6 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->next == nullptr,
            "reverse_between is failed at the line: %d\n", __LINE__
        );
    }
}


/*
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.
*/
template <typename T>
ListNode<T> * reverse(ListNode<T> * head)
{
    ListNode<T> * retval = head;
    if (head != nullptr) {
        head = head->next;
        retval->next = nullptr;
        while (head != nullptr) {
            auto next = head->next;
            head->next = retval;
            retval = head;
            head = next;
        }
    }
    return retval;
}

template <typename T>
void reorder_list(ListNode<T> * head)
{
    if (head != nullptr && head->next != nullptr) {
        ListNode<T> * i = head;
        for (
            ListNode<T> * two_steps = i->next;
            two_steps != nullptr;
        ) {
            two_steps = two_steps->next;
            if (two_steps != nullptr) {
                i = i->next;
                two_steps = two_steps->next;
            }
        }
        auto another_head = i->next;
        i->next = nullptr;
        another_head = reverse(another_head);
        for (i = nullptr; another_head != nullptr; ) {
            auto n1 = head->next;
            auto n2 = another_head->next;
            if (i != nullptr) {
                i->next = head;
            }
            i = head;
            i->next = another_head;
            i = another_head;
            head = n1;
            another_head = n2;
        }
        i->next = head;
    }
}

void reorder_list_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5;
        auto head = &n1;
        reorder_list(head);
        examine(
            head->data == 1 &&
            head->next->data == 5 &&
            head->next->next->data == 2 &&
            head->next->next->next->data == 4 &&
            head->next->next->next->next->data == 3 &&
            head->next->next->next->next->next == nullptr,
            "reorder_list is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6;
        auto head = &n1;
        reorder_list(head);
        examine(
            head->data == 1 &&
            head->next->data == 6 &&
            head->next->next->data == 2 &&
            head->next->next->next->data == 5 &&
            head->next->next->next->next->data == 3 &&
            head->next->next->next->next->next->data == 4 &&
            head->next->next->next->next->next->next == nullptr,
            "reorder_list is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3};
        n1.next = &n2, n2.next = &n3;
        auto head = &n1;
        reorder_list(head);
        examine(
            head->data == 1 &&
            head->next->data == 3 &&
            head->next->next->data == 2 &&
            head->next->next->next == nullptr,
            "reorder_list is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2};
        n1.next = &n2;
        auto head = &n1;
        reorder_list(head);
        examine(
            head->data == 1 &&
            head->next->data == 2 &&
            head->next->next == nullptr,
            "reorder_list is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1};
        auto head = &n1;
        reorder_list(head);
        examine(
            head->data == 1 &&
            head->next == nullptr,
            "reorder_list is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4};
        n1.next = &n2, n2.next = &n3, n3.next = &n4;
        auto head = &n1;
        reorder_list(head);
        examine(
            head->data == 1 &&
            head->next->data == 4 &&
            head->next->next->data == 2 &&
            head->next->next->next->data == 3 &&
            head->next->next->next->next == nullptr,
            "reorder_list is failed at the line: %d\n", __LINE__
        );
    }
}


/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.
*/
template <typename T>
ListNode<T> * merge_two_lists(ListNode<T>* l1, ListNode<T> * l2)
{
    ListNode<T> * retval = nullptr;
    if (l1 != nullptr && l2 != nullptr) {
        ListNode<T> * i = nullptr;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->data <= l2->data) {
                if (i != nullptr) {
                    i->next = l1;
                } else {
                    retval = l1;
                }
                i = l1;
                l1 = l1->next;
            } else {
                if (i != nullptr) {
                    i->next = l2;
                } else {
                    retval = l2;
                }
                i = l2;
                l2 = l2->next;
            }
        }
        i->next = l1 != nullptr ? l1 : l2;
    } else {
        retval = l1 != nullptr ? l1 : l2;
    }
    return retval;
}

template <typename T>
ListNode<T> * merge_lists(std::vector<ListNode<T>*>& lists)
{
    ListNode<T> * retval = nullptr;
    size_t n = lists.size();
    if (n > 2) {
        auto comp = [](ListNode<T>* n1, ListNode<T>* n2) {
            return n1->data > n2->data;
        };
        std::vector<ListNode<T>*> cache;
        cache.reserve(n);
        for (auto n : lists) {
            if (n != nullptr) {
                cache.push_back(n);
            }
        }
        if (!cache.empty()) {
            ListNode<T> * i = nullptr;
            std::make_heap(cache.begin(), cache.end(), comp);
            for (n = cache.size(); n > 1; n = cache.size()) {
                std::pop_heap(cache.begin(), cache.end(), comp);
                ListNode<T> * j = cache.back();
                if (i != nullptr) {
                    i->next = j;
                } else {
                    retval = j;
                }
                i = j;
                j = j->next;
                if (j != nullptr) {
                    cache.back() = j;
                    std::push_heap(cache.begin(), cache.end(), comp);
                } else {
                    cache.pop_back();
                }
            }
            i->next = cache[0];
        }
    } else {
        if (n == 2) {
            retval = merge_two_lists(lists[0], lists[1]);
        } else if (n == 1) {
            retval = lists[0];
        }
    }
    return retval;
}

void merge_lists_test()
{
    {
        ListNode<int> n5{5};
        ListNode<int> n1{1}, n6{6};
        n1.next = &n6;
        std::vector<ListNode<int>*> lists{&n5, &n1};
        auto result = merge_lists(lists);
        examine(
            result->data == 1 &&
            result->next->data == 5 &&
            result->next->next->data == 6 &&
            result->next->next->next == nullptr,
            "merge_lists is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5}, n9{9};
        ListNode<int> n1{1}, n6{6};
        n5.next = &n9;
        n1.next = &n6;
        std::vector<ListNode<int>*> lists{&n5, &n1};
        auto result = merge_lists(lists);
        examine(
            result->data == 1 &&
            result->next->data == 5 &&
            result->next->next->data == 6 &&
            result->next->next->next->data == 9 &&
            result->next->next->next->next == nullptr,
            "merge_lists is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5}, n7{7}, n8{8};
        ListNode<int> n1{1}, n10{10};
        n5.next = &n7, n7.next = &n8;
        n1.next = &n10;
        std::vector<ListNode<int>*> lists{&n5, &n1};
        auto result = merge_lists(lists);
        examine(
            result->data == 1 &&
            result->next->data == 5 &&
            result->next->next->data == 7 &&
            result->next->next->next->data == 8 &&
            result->next->next->next->next->data == 10 &&
            result->next->next->next->next->next == nullptr,
            "merge_lists is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5};
        ListNode<int> n1{1}, n6{6};
        ListNode<int> n2{2}, n9{9};
        ListNode<int> n3{3}, n8{8};
        ListNode<int> n4{4}, n7{7};
        n1.next = &n6;
        n2.next = &n9;
        n3.next = &n8;
        n4.next = &n7;
        std::vector<ListNode<int>*> lists{&n5, &n1, &n2, &n3, &n4};
        auto result = merge_lists(lists);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "merge_lists is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5}, n6_2{6}, n10{10};
        ListNode<int> n1{1}, n6{6};
        ListNode<int> n2{2}, n9{9};
        ListNode<int> n3{3}, n8{8};
        ListNode<int> n4{4}, n7{7};
        n5.next = &n6_2, n6_2.next = &n10;
        n1.next = &n6;
        n2.next = &n9;
        n3.next = &n8;
        n4.next = &n7;
        std::vector<ListNode<int>*> lists{&n5, &n1, &n2, &n3, &n4};
        auto result = merge_lists(lists);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "merge_lists is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5}, n6_2{6}, n10{10};
        ListNode<int> n1{1}, n6{6};
        ListNode<int> n2{2}, n9{9};
        ListNode<int> n3{3}, n8{8};
        ListNode<int> n4{4}, n7{7};
        n5.next = &n6_2, n6_2.next = &n10;
        n1.next = &n6;
        n2.next = &n9;
        n3.next = &n8;
        n4.next = &n7;
        std::vector<ListNode<int>*> lists{&n5, &n1, &n2, &n3, &n4, nullptr};
        auto result = merge_lists(lists);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "merge_lists is failed at the line: %d\n", __LINE__
        );
    }
    {
        std::vector<ListNode<int>*> lists{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        auto result = merge_lists(lists);
        examine(result == nullptr, "merge_lists is failed at the line: %d\n", __LINE__);
    }
}


/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
*/
template <typename T>
ListNode<T> * reverse_in_group(ListNode<T>* head, size_t k)
{
    ListNode<T> * retval = head;
    if (head != nullptr && head->next != nullptr && k > 1) {
        retval = nullptr;
        ListNode<T> * tail = nullptr;
        for (ListNode<T> * i = head; i != nullptr;) {
            ListNode<T> * group_head = i;
            ListNode<T> * group_tail = i;
            ListNode<T> * j = i->next;
            group_tail->next = nullptr;
            size_t c = 1;
            while (c < k && j != nullptr) {
                auto next = j->next;
                j->next = group_head;
                group_head = j;
                ++c;
                j = next;
            }
            if (c < k) {
                group_head = reverse(group_head);
            }
            if (tail != nullptr) {
                tail->next = group_head;
            } else {
                retval = group_head;
            }
            tail = group_tail;
            i = j;
        }
    }
    return retval;
}

void reverse_in_group_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 2);
        examine(
            result->data == 2 &&
            result->next->data == 1 &&
            result->next->next->data == 4 &&
            result->next->next->next->data == 3 &&
            result->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 3);
        examine(
            result->data == 3 &&
            result->next->data == 2 &&
            result->next->next->data == 1 &&
            result->next->next->next->data == 6 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 4);
        examine(
            result->data == 4 &&
            result->next->data == 3 &&
            result->next->next->data == 2 &&
            result->next->next->next->data == 1 &&
            result->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 5);
        examine(
            result->data == 5 &&
            result->next->data == 4 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 2 &&
            result->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 6);
        examine(
            result->data == 6 &&
            result->next->data == 5 &&
            result->next->next->data == 4 &&
            result->next->next->next->data == 3 &&
            result->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 7);
        examine(
            result->data == 7 &&
            result->next->data == 6 &&
            result->next->next->data == 5 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 8);
        examine(
            result->data == 8 &&
            result->next->data == 7 &&
            result->next->next->data == 6 &&
            result->next->next->next->data == 5 &&
            result->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 9);
        examine(
            result->data == 9 &&
            result->next->data == 8 &&
            result->next->next->data == 7 &&
            result->next->next->next->data == 6 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 10);
        examine(
            result->data == 10 &&
            result->next->data == 9 &&
            result->next->next->data == 8 &&
            result->next->next->next->data == 7 &&
            result->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 11);
        examine(
            result->data == 11 &&
            result->next->data == 10 &&
            result->next->next->data == 9 &&
            result->next->next->next->data == 8 &&
            result->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 12);
        examine(
            result->data == 12 &&
            result->next->data == 11 &&
            result->next->next->data == 10 &&
            result->next->next->next->data == 9 &&
            result->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->next->next->next->data == 3 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 1 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10}, n11{11}, n12{12};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10, n10.next = &n11, n11.next = &n12;
        auto result = reverse_in_group(&n1, 13);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next->data == 11 &&
            result->next->next->next->next->next->next->next->next->next->next->next->data == 12 &&
            result->next->next->next->next->next->next->next->next->next->next->next->next == nullptr,
            "reverse_in_group is failed at the line: %d\n", __LINE__
        );
    }
}


/*
Given the head of a singly linked list, sort the list using insertion sort, and return the sorted list's head.
*/
template <typename T>
ListNode<T> * insertion_sort(ListNode<T> * head)
{
    ListNode<T> * retval = head;
    if (head != nullptr && head->next != nullptr) {
        auto i = head->next;
        retval->next = nullptr;
        while (i != nullptr) {
            auto next = i->next;
            ListNode<T> * previous = nullptr;
            ListNode<T> * j = retval;
            while (j != nullptr) {
                if (i->data < j->data) {
                    previous = j;
                    j = j->next;
                } else {
                    break;
                }
            }
            if (previous != nullptr) {
                auto k = previous->next;
                previous->next = i;
                i->next = k;
            } else {
                i->next = retval;
                retval = i;
            }
            i = next;
        }
        retval = reverse(retval);
    }
    return retval;
}

void insertion_sort_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9;
        auto result = insertion_sort(&n1);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n9{9}, n8{8}, n7{7}, n6{6}, n5{5}, n4{4}, n3{3}, n2{2}, n1{1};
        n9.next = &n8, n8.next = &n7, n7.next = &n6, n6.next = &n5, n5.next = &n4, n4.next = &n3, n3.next = &n2, n2.next = &n1;
        auto result = insertion_sort(&n9);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5}, n9{9}, n8{8}, n2{2}, n1{1}, n7{7}, n4{4}, n3{3}, n6{6};
        n5.next = &n9, n9.next = &n8, n8.next = &n2, n2.next = &n1, n1.next = &n7, n7.next = &n4, n4.next = &n3, n3.next = &n6;
        auto result = insertion_sort(&n5);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
}

/*
Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.

The first node is considered odd, and the second node is even, and so on.

Note that the relative order inside both the even and odd groups should remain as it was in the input.
*/

template <typename T>
ListNode<T> * odd_even_list(ListNode<T> * head)
{
    ListNode<T> * retval = head;
    if (head != nullptr && head->next != nullptr) {
        ListNode<T> * odd_head = nullptr;
        ListNode<T> * odd_next = nullptr;
        ListNode<T> * even_head = nullptr;
        ListNode<T> * even_next = nullptr;
        while (head != nullptr) {
            auto odd = head;
            auto even = odd->next;
            if (odd_next != nullptr) {
                odd_next->next = odd;
            } else {
                odd_head = odd;
            }
            odd_next = odd;
            if (even_next != nullptr) {
                even_next->next = even;
            } else {
                even_head = even;
            }
            even_next = even;
            head = nullptr;
            if (even != nullptr) {
                head = even->next;
            }
        }
        odd_next->next = even_head;
        retval = odd_head;
    }
    return retval;
}

void odd_even_list_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9;
        auto result = odd_even_list(&n1);
        examine(
            result->data == 1 &&
            result->next->data == 3 &&
            result->next->next->data == 5 &&
            result->next->next->next->data == 7 &&
            result->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9}, n10{10};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9, n9.next = &n10;
        auto result = odd_even_list(&n1);
        examine(
            result->data == 1 &&
            result->next->data == 3 &&
            result->next->next->data == 5 &&
            result->next->next->next->data == 7 &&
            result->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->data == 2 &&
            result->next->next->next->next->next->next->data == 4 &&
            result->next->next->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->next->data == 10 &&
            result->next->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
}


/*
Given the head of a linked list, return the list after sorting it in ascending order.

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
*/
template <typename T>
std::pair<ListNode<T>*, ListNode<T>*> halve(ListNode<T>* head)
{
    assert(head != nullptr && head->next != nullptr);
    ListNode<T> * i = nullptr;
    for (ListNode<T> * one_step = head, * two_steps = one_step->next; two_steps != nullptr;) {
        i = one_step;
        one_step = one_step->next;
        two_steps = two_steps->next;
        if (two_steps != nullptr) {
            two_steps = two_steps->next;
        }
    }
    auto next = i->next;
    i->next = nullptr;
    return std::make_pair(head, next);
}

template <typename T>
ListNode<T> * sort_list(ListNode<T> * head)
{
    ListNode<T> * retval = head;
    if (head != nullptr && head->next != nullptr) {
        auto segments = halve(head);
        auto left = sort_list(segments.first);
        auto right = sort_list(segments.second);
        retval = merge_two_lists(left, right);
    }
    return retval;
}

void sort_list_test()
{
    {
        ListNode<int> n1{1}, n2{2}, n3{3}, n4{4}, n5{5}, n6{6}, n7{7}, n8{8}, n9{9};
        n1.next = &n2, n2.next = &n3, n3.next = &n4, n4.next = &n5, n5.next = &n6, n6.next = &n7, n7.next = &n8, n8.next = &n9;
        auto result = sort_list(&n1);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n9{9}, n8{8}, n7{7}, n6{6}, n5{5}, n4{4}, n3{3}, n2{2}, n1{1};
        n9.next = &n8, n8.next = &n7, n7.next = &n6, n6.next = &n5, n5.next = &n4, n4.next = &n3, n3.next = &n2, n2.next = &n1;
        auto result = sort_list(&n9);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
    {
        ListNode<int> n5{5}, n9{9}, n8{8}, n2{2}, n1{1}, n7{7}, n4{4}, n3{3}, n6{6};
        n5.next = &n9, n9.next = &n8, n8.next = &n2, n2.next = &n1, n1.next = &n7, n7.next = &n4, n4.next = &n3, n3.next = &n6;
        auto result = sort_list(&n5);
        examine(
            result->data == 1 &&
            result->next->data == 2 &&
            result->next->next->data == 3 &&
            result->next->next->next->data == 4 &&
            result->next->next->next->next->data == 5 &&
            result->next->next->next->next->next->data == 6 &&
            result->next->next->next->next->next->next->data == 7 &&
            result->next->next->next->next->next->next->next->data == 8 &&
            result->next->next->next->next->next->next->next->next->data == 9 &&
            result->next->next->next->next->next->next->next->next->next == nullptr,
            "insertion_sort is failed at the line: %d\n", __LINE__
        );
    }
}

int main()
{
    add_two_numbers_test();
    remove_from_end_test();
    swap_pairs_test();
    rotate_right_test();
    separate_duplicates_test();
    partition_test();
    reverse_between_test();
    reorder_list_test();
    merge_lists_test();
    reverse_in_group_test();
    insertion_sort_test();
    odd_even_list_test();
    sort_list_test();
    printf("OK\n");
    return 0;
}
