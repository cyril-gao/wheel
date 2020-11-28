#ifndef BINARY_TREE_H_02CB0E96_B97F_42DA_9E1C_6A44173BF032
#define BINARY_TREE_H_02CB0E96_B97F_42DA_9E1C_6A44173BF032

#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

namespace details
{
    template <typename BinaryTreeNode>
    auto leftmost(const BinaryTreeNode* root)
    {
        if (root != nullptr) {
            auto left = root->left_child();
            while (left != nullptr) {
                root = left;
                left = root->left_child();
            }
        }
        return root;
    }

    template <typename BinaryTreeNode>
    auto rightmost(const BinaryTreeNode* root)
    {
        if (root != nullptr) {
            auto right = root->right_child();
            while (right != nullptr) {
                root = right;
                right = root->right_child();
            }
        }
        return root;
    }

    template <typename BinaryTreeNode>
    size_t height(const BinaryTreeNode* root)
    {
        size_t h = 0;
        if (root != nullptr) {
            size_t lh = height(root->left_child());
            size_t rh = height(root->right_child());
            h = std::max(lh, rh) + 1;
        }
        return h;
    }

    template <typename BinaryTreeNode>
    size_t count(const BinaryTreeNode* root)
    {
        size_t n = 0;
        if (root != nullptr) {
            size_t ln = count(root->left_child());
            size_t rn = count(root->right_child());
            n = ln + rn + 1;
        }
        return n;
    }

    template <typename BinaryTreeNode>
    bool equals(const BinaryTreeNode* t1, const BinaryTreeNode* t2)
    {
        bool retval = (t1 == t2);
        if (!retval) {
            if (t1 != nullptr && t2 != nullptr) {
                retval = (t1->data() == t2->data());
                if (retval) {
                    retval = (
                        equals(t1->left_child(), t2->left_child()) &&
                        equals(t1->right_child(), t2->right_child())
                    );
                }
            }
        }
        return retval;
    }

    template <typename BinaryTreeNode, typename Visitor>
    void preorder_visit_recursively(BinaryTreeNode* root, Visitor visitor)
    {
        if (root != nullptr) {
            visitor(root);
            preorder_visit_recursively(root->left_child(), visitor);
            preorder_visit_recursively(root->right_child(), visitor);
        }
    }

    template <typename BinaryTreeNode, typename Visitor>
    void inorder_visit_recursively(BinaryTreeNode* root, Visitor visitor)
    {
        if (root != nullptr) {
            inorder_visit_recursively(root->left_child(), visitor);
            visitor(root);
            inorder_visit_recursively(root->right_child(), visitor);
        }
    }

    template <typename BinaryTreeNode, typename Visitor>
    void postorder_visit_recursively(BinaryTreeNode* root, Visitor visitor)
    {
        if (root != nullptr) {
            postorder_visit_recursively(root->left_child(), visitor);
            postorder_visit_recursively(root->right_child(), visitor);
            visitor(root);
        }
    }

    template <typename BinaryTreeNode, typename Visitor>
    void level_order_visit(BinaryTreeNode* root, Visitor visitor)
    {
        if (root != nullptr) {
            std::queue<BinaryTreeNode*> nodes;
            nodes.push(root);
            while (!nodes.empty()) {
                auto front = nodes.front();
                nodes.pop();
                if (front->left_child() != nullptr) {
                    nodes.push(front->left_child());
                }
                if (front->right_child() != nullptr) {
                    nodes.push(front->right_child());
                }
                visitor(front);
            }
        }
    }

    template <typename BinaryTreeNode, typename Visitor>
    void preorder_visit(BinaryTreeNode* root, Visitor visitor)
    {
        if (root != nullptr) {
            std::stack<BinaryTreeNode*> nodes;
            nodes.push(root);
            while (true) {
                //while (nodes.top() != nullptr) {
                for (auto top = nodes.top(); top != nullptr; top = nodes.top()) {
                    visitor(top);
                    nodes.push(top->left_child());
                }
                nodes.pop();
                if (!nodes.empty()) {
                    auto top = nodes.top();
                    assert(top != nullptr);
                    nodes.pop();
                    nodes.push(top->right_child());
                } else {
                    break;
                }
            }
        }
    }

    template <typename BinaryTreeNode, typename Visitor>
    void inorder_visit(BinaryTreeNode* root, Visitor visitor)
    {
        if (root != nullptr) {
            std::stack<BinaryTreeNode*> nodes;
            nodes.push(root);
            while (true) {
                //while (nodes.top() != nullptr) {
                for (auto top = nodes.top(); top != nullptr; top = nodes.top()) {
                    nodes.push(top->left_child());
                }
                nodes.pop();
                if (!nodes.empty()) {
                    auto top = nodes.top();
                    assert(top != nullptr);
                    visitor(top);
                    nodes.pop();
                    nodes.push(top->right_child());
                } else {
                    break;
                }
            }
        }
    }

    namespace v1
    {
        template <typename BinaryTreeNode, typename Visitor>
        void postorder_visit(BinaryTreeNode* root, Visitor visitor)
        {
            enum WhereToGo { go_to_right, go_to_parent };
            if (root != nullptr) {
                typedef std::pair<BinaryTreeNode*, WhereToGo> Record;
                std::stack<Record> nodes;
                nodes.push(Record{root, go_to_parent});
                while (!nodes.empty()) {
                    while (nodes.top().first != nullptr) {
                        nodes.push(Record{nodes.top().first->left_child(), go_to_right});
                    }
                    WhereToGo where_to_go = nodes.top().second;
                    nodes.pop();
                    while (!nodes.empty()) {
                        if (where_to_go == go_to_right) {
                            nodes.push(Record{nodes.top().first->right, go_to_parent});
                            break;
                        } else {
                            visitor(nodes.top().first);
                            where_to_go = nodes.top().second;
                            nodes.pop();
                        }
                    }
                }
            }
        }
    }

    namespace v2
    {
        template <typename BinaryTreeNode, typename Visitor>
        void postorder_visit(BinaryTreeNode* root, Visitor visitor)
        {
            if (root != nullptr) {
                std::stack<BinaryTreeNode*> nodes;
                nodes.push(root), nodes.push(root);
                while (!nodes.empty()) {
                    for (auto left = nodes.top()->left_child(); left != nullptr;) {
                        nodes.push(left), nodes.push(left);
                        left = left->left_child();
                    }
                    while (!nodes.empty()) {
                        auto top = nodes.top();
                        nodes.pop();
                        if (!nodes.empty() && nodes.top() == top) {
                            auto right = top->right_child();
                            if (right != nullptr) {
                                nodes.push(right), nodes.push(right);
                                break;
                            } else {
                                visitor(top);
                                nodes.pop();
                            }
                        } else {
                            visitor(top);
                        }
                    }
                }
            }
        }
    }
}

#endif //BINARY_TREE_H_02CB0E96_B97F_42DA_9E1C_6A44173BF032
