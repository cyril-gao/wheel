#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <limits>
#include <random>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>
#include "check.h"
#include "binary_tree.h"
#include "binary_search_tree.h"

void binary_tree_test()
{
    struct TreeNode
    {
        int val;
        TreeNode * left;
        TreeNode * right;

        explicit TreeNode(int v = 0, TreeNode* l = nullptr, TreeNode* r = nullptr) :
            val(v), left(l), right(r)
        {
        }

        const TreeNode* left_child() const noexcept
        {
            return left;
        }
        const TreeNode* right_child() const noexcept
        {
            return right;
        }
        int data() const noexcept
        {
            return val;
        }
        TreeNode* left_child() noexcept
        {
            return left;
        }
        TreeNode* right_child() noexcept
        {
            return right;
        }
    };

    std::vector<TreeNode> nodes(9);
    int i = 0;
    std::for_each(std::begin(nodes), std::end(nodes), [&i](TreeNode& n) { n.val = i++; });

    nodes[7].right = &nodes[8];
    nodes[6].left = &nodes[5], nodes[6].right = &nodes[7];
    nodes[2].right = &nodes[3];
    nodes[1].left = &nodes[0], nodes[1].right = &nodes[2];
    nodes[4].left = &nodes[1], nodes[4].right = &nodes[6];

    using namespace details;

    examine(leftmost(&nodes[4]) == &nodes[0], "leftmost is wrong\n");
    examine(rightmost(&nodes[4]) == &nodes[8], "rightmost is wrong\n");
    examine(height(&nodes[4]) == 4, "height is wrong\n");
    examine(count(&nodes[4]) == 9, "count is wrong\n");

    {
        TreeNode n4(4, nodes[4].left, nodes[4].right);
        examine(equals(&nodes[4], &n4), "equals is wrong\n");
        n4.right = &nodes[8];
        examine(!equals(&nodes[4], &n4), "equals is wrong\n");
    }

    {
        std::vector<int> sequence;
        preorder_visit_recursively(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {4, 1, 0, 2, 3, 6, 5, 7, 8};
        examine(sequence == result, "preorder_visit_recursively is wrong\n");
    }
    {
        std::vector<int> sequence;
        preorder_visit(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {4, 1, 0, 2, 3, 6, 5, 7, 8};
        examine(sequence == result, "preorder_visit is wrong\n");
    }
    {
        std::vector<int> sequence;
        inorder_visit_recursively(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        examine(sequence == result, "inorder_visit_recursively is wrong\n");
    }
    {
        std::vector<int> sequence;
        inorder_visit(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        examine(sequence == result, "inorder_visit is wrong\n");
    }
    {
        std::vector<int> sequence;
        postorder_visit_recursively(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {0, 3, 2, 1, 5, 8, 7, 6, 4};
        examine(sequence == result, "postorder_visit_recursively is wrong\n");
    }
    {
        std::vector<int> sequence;
        v1::postorder_visit(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {0, 3, 2, 1, 5, 8, 7, 6, 4};
        examine(sequence == result, "v1::postorder_visit is wrong\n");
    }
    {
        std::vector<int> sequence;
        v2::postorder_visit(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {0, 3, 2, 1, 5, 8, 7, 6, 4};
        examine(sequence == result, "v2::postorder_visit is wrong\n");
    }
    {
        std::vector<int> sequence;
        level_order_visit(&nodes[4], [&sequence](TreeNode* node) { sequence.push_back(node->val); });
        std::vector<int> result = {4, 1, 6, 0, 2, 5, 7, 3, 8};
        examine(sequence == result, "level_order_visit is wrong\n");
    }

    struct BinarySearchTree
    {
        TreeNode* root;

        void clear()
        {
            level_order_visit(root, [](TreeNode* node) { delete node; });
        }

        BinarySearchTree(size_t n) : root(nullptr)
        {
            if (n > 0) {
                std::default_random_engine eng((std::random_device())());
                std::uniform_int_distribution<int> idis(
                    std::numeric_limits<int>::min(),
                    std::numeric_limits<int>::max()
                );
                try {
                    root = new TreeNode(idis(eng));
                    for (size_t i = 1; i < n; ++i) {
                        while (true) {
                            int v = idis(eng);
                            auto retval = find(root, v);
                            if (retval.second != ExpectedPosition::CURRENT) {
								assert(retval.second != ExpectedPosition::ROOT);
                                if (retval.second == ExpectedPosition::RIGHT_CHILD) {
                                    retval.first->right = new TreeNode(v);
                                } else {
                                    retval.first->left = new TreeNode(v);
                                }
                                break;
                            }
                        }
                    }
                } catch (...) {
                    clear();
                    throw;
                }
            }
        }
        ~BinarySearchTree()
        {
            clear();
        }
    };

    for (int retry = 0; retry < 5; ++retry) {
        BinarySearchTree bst(1003001);
        {
            std::vector<int> s1, s2;
            auto begin = std::chrono::system_clock::now();
            preorder_visit_recursively(bst.root, [&s1](TreeNode* node) { s1.push_back(node->val); });
            auto end = std::chrono::system_clock::now();
            auto diff1 = std::chrono::duration<double>(end - begin).count();

            begin = std::chrono::system_clock::now();
            preorder_visit(bst.root, [&s2](TreeNode* node) { s2.push_back(node->val); });
            end = std::chrono::system_clock::now();
            auto diff2 = std::chrono::duration<double>(end - begin).count();

            examine(s1 == s2, "preorder_visit_recursively is different from preorder_visit");
            printf("preorder_visit_recursively: %f, preorder_visit: %f\n", diff1, diff2);
        }
        {
            std::vector<int> s1, s2;
            auto begin = std::chrono::system_clock::now();
            inorder_visit_recursively(bst.root, [&s1](TreeNode* node) { s1.push_back(node->val); });
            auto end = std::chrono::system_clock::now();
            auto diff1 = std::chrono::duration<double>(end - begin).count();

            begin = std::chrono::system_clock::now();
            inorder_visit(bst.root, [&s2](TreeNode* node) { s2.push_back(node->val); });
            end = std::chrono::system_clock::now();
            auto diff2 = std::chrono::duration<double>(end - begin).count();

            examine(s1 == s2, "inorder_visit_recursively is different from inorder_visit");
            printf("inorder_visit_recursively: %f, inorder_visit: %f\n", diff1, diff2);
        }
        {
            std::vector<int> s1, s2, s3;
            auto begin = std::chrono::system_clock::now();
            postorder_visit_recursively(bst.root, [&s1](TreeNode* node) { s1.push_back(node->val); });
            auto end = std::chrono::system_clock::now();
            auto diff1 = std::chrono::duration<double>(end - begin).count();

            begin = std::chrono::system_clock::now();
            v1::postorder_visit(bst.root, [&s2](TreeNode* node) { s2.push_back(node->val); });
            end = std::chrono::system_clock::now();
            auto diff2 = std::chrono::duration<double>(end - begin).count();

            examine(s1 == s2, "postorder_visit_recursively is different from v1::postorder_visit");

            begin = std::chrono::system_clock::now();
            v2::postorder_visit(bst.root, [&s3](TreeNode* node) { s3.push_back(node->val); });
            end = std::chrono::system_clock::now();
            auto diff3 = std::chrono::duration<double>(end - begin).count();
            examine(s1 == s3, "postorder_visit_recursively is different from v2::postorder_visit");

            printf("postorder_visit_recursively: %f, v1::postorder_visit: %f, v2::postorder_visit: %f\n", diff1, diff2, diff3);
        }
    }
}

int main()
{
    try {
        binary_tree_test();
        printf("OK\n");
        return 0;
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
}
