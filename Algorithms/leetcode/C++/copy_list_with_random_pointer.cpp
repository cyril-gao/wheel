#include <stdio.h>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "check.h"

struct Node
{
    int val;
    Node* next;
    Node* random;

    explicit Node(int _val) : val(_val), next(nullptr), random(nullptr)
    {
    }
    Node(): Node(0) {}
};

bool equals(Node * n1, Node * n2, std::unordered_map<Node*, std::unordered_map<Node*, bool>> & cache)
{
    if (n1 != n2) {
        if (n1 != nullptr && n2 != nullptr && n1->val == n2->val) {
            auto p1 = cache.find(n1);
            if (p1 != cache.end()) {
                auto p2 = p1->second.find(n2);
                if (p2 != p1->second.end()) {
                    return p2->second;
                }
            }
            if (p1 != cache.end()) {
                p1->second[n2] = true;
            } else {
                std::unordered_map<Node*, bool> r;
                r[n2] = true;
                cache[n1] = std::move(r);
            }
            if (equals(n1->next, n2->next, cache) && equals(n1->random, n2->random, cache)) {
                return true;
            }
        }
        return false;
    }
    return true;
}

bool equals(Node * n1, Node * n2)
{
    std::unordered_map<Node*, std::unordered_map<Node*, bool>> cache;
    return equals(n1, n2, cache);
}

void visit(Node * node, std::unordered_set<Node*> & cache)
{
    if (node != nullptr) {
        auto pos = cache.find(node);
        if (pos == cache.end()) {
            cache.insert(node);
            visit(node->next, cache);
            visit(node->random, cache);
        }
    }
}

void free(Node * node)
{
    if (node != nullptr) {
        std::unordered_set<Node*> cache;
        visit(node, cache);
        std::for_each(cache.begin(), cache.end(), [](auto n) { delete n; });
    }
}

Node* deep_copy(Node* node, std::unordered_map<Node*, Node*>& cache)
{
    if (node != nullptr) {
        auto pos = cache.find(node);
        if (pos != cache.end()) {
            return pos->second;
        }
        else {
            Node* n = new Node(node->val);
            try {
                cache[node] = n;
                n->next = deep_copy(node->next, cache);
                n->random = deep_copy(node->random, cache);
            }
            catch (...) {
                delete n;
                throw;
            }
            return n;
        }
    }
    return nullptr;
}

Node * deep_copy(Node * node)
{
    std::unordered_map<Node*, Node*> cache;
    return deep_copy(node, cache);
}


int main()
{
    {
        auto r = deep_copy(nullptr);
        examine(r == nullptr, "failed at the line %d\n", __LINE__);
    }
    {
        Node n1(1), n2(2);
        n1.next = &n2;
        n1.random = &n2;
        n2.next = nullptr;
        n2.random = &n2;

        auto r = deep_copy(&n1);
        examine(equals(r, &n1), "failed at the line %d\n", __LINE__);
        free(r);
    }
    {
        Node n3_1(3), n3_2(3), n3_3(3);
        n3_1.next = &n3_2;
        n3_1.random = nullptr;
        n3_2.next = &n3_3;
        n3_2.random = &n3_1;
        n3_3.next = nullptr;
        n3_3.random = nullptr;

        auto r = deep_copy(&n3_1);
        examine(equals(r, &n3_1), "failed at the line %d\n", __LINE__);
        free(r);
    }
    {
        Node n7(7), n13(13), n11(11), n10(10), n1(1);
        n7.next = &n13;
        n7.random = nullptr;
        n13.next = &n11;
        n13.random = &n7;
        n11.next = &n10;
        n11.random = &n1;
        n10.next = &n1;
        n10.random = &n11;
        n1.next = nullptr;
        n1.random = &n7;

        auto r = deep_copy(&n7);
        examine(equals(r, &n7), "failed at the line %d\n", __LINE__);
        free(r);
    }
    return 0;
}
