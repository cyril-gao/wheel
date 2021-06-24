#ifndef AVL_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define AVL_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <assert.h>
#include <stdint.h>
#include <memory>
#include <utility>


template <typename T>
class AVLTree
{
    struct Node;

    union BalanceFactorAndParentPointer
    {
        intptr_t balance_factor;
        Node * parent;

        BalanceFactorAndParentPointer(): parent(nullptr) {}
        BalanceFactorAndParentPointer(Node * p, intptr_t factor = 0): parent(p)
        {
            assert(factor >= -1 && factor <= 1);
            intptr_t v = (factor + 1);
            balance_factor |= v;
        }

        const Node * get_parent() const
        {
            const intptr_t mask = 3;
            return reinterpret_cast<Node*>(balance_factor & (~mask));
        }

        void set_parent(Node* p)
        {
            this->parent = p;
        }
        void set_parent_and_reserve_balance_factor(Node* p)
        {
            const intptr_t mask = 3;
            intptr_t v = balance_factor & mask;
            parent = p;
            balance_factor |= v;
        }

        intptr_t get_balance_factor() const
        {
            return (balance_factor & 3U) - 1;
        }

        void set_balance_factor(intptr_t factor)
        {
            assert(factor >= -1 && factor <= 1);
            const intptr_t mask = 3;
            balance_factor &= (~mask);
            balance_factor |= (factor + 1);
        }
    };

    struct Node
    {
        T data;
        BalanceFactorAndParentPointer balance_factor_and_parent;
        Node * left_child;
        Node * right_child;

        Node(const T& d, Node * parent, intptr_t balance_factor, Node * lc = nullptr, Node * rc = nullptr):
            data(d), balance_factor_and_parent(parent, balance_factor), left_child(lc), right_child(rc)
        {
        }

        Node(const Node& other):
            data(other.data),
            balance_factor_and_parent(nullptr, other.get_balance_factor()),
            left_child(nullptr),
            right_child(nullptr)
        {
        }

        void exchange_content(Node* other)
        {
            using std::swap;
            swap(data, other->data);
        }

        const Node * get_parent() const
        {
            return balance_factor_and_parent.get_parent();
        }
        Node * get_parent()
        {
            return const_cast<Node*>(const_cast<const Node*>(this)->get_parent());
        }

        void set_parent(Node* parent)
        {
            balance_factor_and_parent.set_parent(parent);
        }

        void set_parent_and_reserve_balance_factor(Node* parent)
        {
            balance_factor_and_parent.set_parent_and_reserve_balance_factor(parent);
        }

        intptr_t get_balance_factor() const
        {
            return balance_factor_and_parent.get_balance_factor();
        }
        intptr_t get_balance_factor()
        {
            return const_cast<const Node*>(this)->get_balance_factor();
        }

        void set_balance_factor(intptr_t factor)
        {
            balance_factor_and_parent.set_balance_factor(factor);
        }
    };

    enum ExpectedPosition { CURRENT, ROOT, LEFT_CHILD, RIGHT_CHILD };

    static auto find(Node* root, const T& key)
    {
        Node* parent_or_self = nullptr;
        ExpectedPosition position = ROOT;
        for (Node* i = root; i != nullptr;) {
            parent_or_self = i;
            if (i->data == key) {
                position = CURRENT;
                break;
            } else if (i->data < key) {
                position = RIGHT_CHILD;
                i = i->right_child;
            } else {
                position = LEFT_CHILD;
                i = i->left_child;
            }
        }
        return std::make_pair(parent_or_self, position);
    }

    static void free(Node* node)
    {
        if (node != nullptr) {
            free(node->left_child);
            free(node->right_child);
            delete node;
        }
    }

    static Node* copy(Node* node)
    {
        Node * retval = nullptr;
        if (node != nullptr) {
            try {
                retval = new Node(*node);
                retval->left_child = copy(node->left_child);
                if (retval->left_child != nullptr) {
                    retval->left_child->set_parent_and_reserve_balance_factor(retval);
                }
                retval->right_child = copy(node->right_child);
                if (retval->right_child != nullptr) {
                    retval->right_child->set_parent_and_reserve_balance_factor(retval);
                }
            } catch (...) {
                free(retval);
                throw;
            }
        }
        return retval;
    }

    static bool equals(Node* n1, Node * n2)
    {
        bool retval = (n1 == n2);
        if (!retval) {
            if (n1 != nullptr && n2 != nullptr) {
                retval = (n1->data == n2->data && n1->get_balance_factor() == n2->get_balance_factor());
                if (retval) {
                    retval = (
                        equals(n1->left_child, n2->left_child) &&
                        equals(n1->right_child, n2->right_child)
                    );
                }
            }
        }
        return retval;
    }

    static Node* get_sibling(const Node* node, const Node* parent)
    {
        assert(parent != nullptr);
        const Node* retval = nullptr;
        if (parent->left_child == node) {
            retval = parent->right_child;
        } else {
            assert(parent->right_child == node);
            retval = parent->left_child;
        }
        return const_cast<Node*>(retval);
    }

    static ExpectedPosition get_position(const Node* node, const Node* parent)
    {
        if (parent->left_child == node) {
            return LEFT_CHILD;
        } else {
            assert(parent->right_child == node);
            return RIGHT_CHILD;
        }
    }

    struct Internal
    {
        intptr_t height{0};
        bool     valid{true};
    };

    static Internal get_internal(const Node* const node)
    {
        Internal internal;
        if (node != nullptr) {
            internal.valid = false;
            auto balance_factor = node->get_balance_factor();
            if (
                balance_factor >= -1 && balance_factor <= 1 &&
                (node->left_child == nullptr || (node->left_child->data < node->data && node->left_child->get_parent() == node)) &&
                (node->right_child == nullptr || (node->right_child->data > node->data && node->right_child->get_parent() == node))
            ) {
                auto li = get_internal(node->left_child);
                auto ri = get_internal(node->right_child);
                if (li.valid && ri.valid) {
                    auto diff = li.height - ri.height;
                    if (balance_factor == diff) {
                        internal.height = (li.height < ri.height ? ri.height : li.height) + 1;
                        internal.valid = true;
                    }
                }
            }
        }
        return internal;
    }

    void replace_father_son_relationship(Node* to_be_replaced, Node* the_new_one)
    {
        auto parent = to_be_replaced->get_parent();
        if (parent != nullptr) {
            assert(parent != the_new_one);
            if (parent->left_child == to_be_replaced) {
                parent->left_child = the_new_one;
            } else {
                assert(parent->right_child == to_be_replaced);
                parent->right_child = the_new_one;
            }
            if (the_new_one != nullptr) {
                the_new_one->set_parent(parent);
            }
        } else {
            assert(m_root == to_be_replaced);
            m_root = the_new_one;
            m_root->set_parent_and_reserve_balance_factor(nullptr);
        }
    }

    void reblance_after_deleting(ExpectedPosition position, Node* node, Node* parent)
    {
        while (parent != nullptr) {
            auto parent_balance_factor = parent->get_balance_factor();
            if (parent_balance_factor == 0) {
                if (position == LEFT_CHILD) {
                    parent->set_balance_factor(-1);
                } else {
                    assert(position == RIGHT_CHILD);
                    parent->set_balance_factor(1);
                }
                break;
            } else {
                if (
                    (position == LEFT_CHILD && parent_balance_factor == 1) ||
                    (position == RIGHT_CHILD && parent_balance_factor == -1)
                ) {
                    parent->set_balance_factor(0);
                    node = parent;
                } else {
                    auto sibling = get_sibling(node, parent);
                    auto sibling_balance_factor = sibling->get_balance_factor();
                    auto left_nephew = sibling->left_child;
                    auto right_nephew = sibling->right_child;
                    if (sibling_balance_factor == 0) {
                        replace_father_son_relationship(parent, sibling);
                        if (position == LEFT_CHILD) {
                            parent->right_child = left_nephew;
                            left_nephew->set_parent_and_reserve_balance_factor(parent);
                            sibling->left_child = parent;
                            parent->set_parent(sibling);
                            parent->set_balance_factor(-1);
                            sibling->set_balance_factor(1);
                        } else {
                            assert(position == RIGHT_CHILD);
                            parent->left_child = right_nephew;
                            right_nephew->set_parent_and_reserve_balance_factor(parent);
                            sibling->right_child = parent;
                            parent->set_parent(sibling);
                            parent->set_balance_factor(1);
                            sibling->set_balance_factor(-1);
                        }
                        break;
                    } else {
                        if (position == LEFT_CHILD) {
                            if (sibling_balance_factor == 1) {
                                auto left_nephew_balance_factor = left_nephew->get_balance_factor();
                                auto left_grand_child = left_nephew->left_child;
                                auto right_grand_child = left_nephew->right_child;
                                replace_father_son_relationship(parent, left_nephew);
                                left_nephew->left_child = parent;
                                parent->set_parent(left_nephew);
                                left_nephew->right_child = sibling;
                                sibling->set_parent(left_nephew);
                                parent->right_child = left_grand_child;
                                if (left_grand_child != nullptr) {
                                    left_grand_child->set_parent_and_reserve_balance_factor(parent);
                                }
                                sibling->left_child = right_grand_child;
                                if (right_grand_child != nullptr) {
                                    right_grand_child->set_parent_and_reserve_balance_factor(sibling);
                                }
                                if (left_nephew_balance_factor == 1) {
                                    parent->set_balance_factor(0);
                                    sibling->set_balance_factor(-1);
                                } else if (left_nephew_balance_factor == 0) {
                                    parent->set_balance_factor(0);
                                    sibling->set_balance_factor(0);
                                } else {
                                    assert(left_nephew_balance_factor == -1);
                                    parent->set_balance_factor(1);
                                    sibling->set_balance_factor(0);
                                }
                                left_nephew->set_balance_factor(0);
                                node = left_nephew;
                            } else {
                                assert(sibling_balance_factor == -1);
                                replace_father_son_relationship(parent, sibling);
                                parent->right_child = left_nephew;
                                if (left_nephew != nullptr) {
                                    left_nephew->set_parent_and_reserve_balance_factor(parent);
                                }
                                sibling->left_child = parent;
                                parent->set_parent(sibling);
                                parent->set_balance_factor(0);
                                sibling->set_balance_factor(0);
                                node = sibling;
                            }
                        } else {
                            if (sibling_balance_factor == 1) {
                                replace_father_son_relationship(parent, sibling);
                                parent->left_child = right_nephew;
                                if (right_nephew != nullptr) {
                                    right_nephew->set_parent_and_reserve_balance_factor(parent);
                                }
                                sibling->right_child = parent;
                                parent->set_parent(sibling);
                                parent->set_balance_factor(0);
                                sibling->set_balance_factor(0);
                                node = sibling;
                            } else {
                                assert(sibling_balance_factor == -1);
                                auto right_nephew_balance_factor = right_nephew->get_balance_factor();
                                auto left_grand_child = right_nephew->left_child;
                                auto right_grand_child = right_nephew->right_child;
                                replace_father_son_relationship(parent, right_nephew);
                                right_nephew->left_child = sibling;
                                sibling->set_parent(right_nephew);
                                right_nephew->right_child = parent;
                                parent->set_parent(right_nephew);
                                sibling->right_child = left_grand_child;
                                if (left_grand_child != nullptr) {
                                    left_grand_child->set_parent_and_reserve_balance_factor(sibling);
                                }
                                parent->left_child = right_grand_child;
                                if (right_grand_child != nullptr) {
                                    right_grand_child->set_parent_and_reserve_balance_factor(parent);
                                }
                                if (right_nephew_balance_factor == 1) {
                                    parent->set_balance_factor(-1);
                                    sibling->set_balance_factor(0);
                                } else if (right_nephew_balance_factor == 0) {
                                    parent->set_balance_factor(0);
                                    sibling->set_balance_factor(0);
                                } else {
                                    assert(right_nephew_balance_factor == -1);
                                    parent->set_balance_factor(0);
                                    sibling->set_balance_factor(1);
                                }
                                right_nephew->set_balance_factor(0);
                                node = right_nephew;
                            }
                        }
                    }
                }
                parent = node->get_parent();
                if (parent != nullptr) {
                    position = get_position(node, parent);
                }
            }
        }
        if (parent == nullptr) {
            assert(node != nullptr);
            m_root = node;
            m_root->set_parent_and_reserve_balance_factor(nullptr);
        }
    }

    void remove(Node* node)
    {
        auto left_child = node->left_child;
        auto right_child = node->right_child;
        assert(left_child == nullptr || right_child == nullptr);
        if (right_child != nullptr) {
            assert(node->get_balance_factor() == -1);
            assert(right_child->get_balance_factor() == 0 && right_child->left_child == nullptr && right_child->right_child == nullptr);
            assert(right_child->get_balance_factor() == 0);
            replace_father_son_relationship(node, right_child);
            right_child->set_balance_factor(0);
            auto parent = right_child->get_parent();
            if (parent != nullptr) {
                reblance_after_deleting(get_position(right_child, parent), right_child, parent);
            } else {
                assert(m_root == right_child);
            }
        } else if (left_child != nullptr) {
            assert(node->get_balance_factor() == 1);
            assert(left_child->get_balance_factor() == 0 && left_child->left_child == nullptr && left_child->right_child == nullptr);
            assert(left_child->get_balance_factor() == 0);
            replace_father_son_relationship(node, left_child);
            left_child->set_balance_factor(0);
            auto parent = left_child->get_parent();
            if (parent != nullptr) {
                reblance_after_deleting(get_position(left_child, parent), left_child, parent);
            } else {
                assert(m_root == left_child);
            }
        } else {
            auto parent = node->get_parent();
            if (parent != nullptr) {
                auto position = get_position(node, parent);
                replace_father_son_relationship(node, nullptr);
                reblance_after_deleting(position, nullptr, parent);
            } else {
                assert(m_count == 1);
                m_root = nullptr;
            }
        }
        delete node;
        --m_count;
    }

    void reblance_after_inserting(Node* node)
    {
        auto parent = node->get_parent();
        while (parent != nullptr) {
            auto position = get_position(node, parent);
            auto parent_balance_factor = parent->get_balance_factor();
            if (parent_balance_factor != 0) {
                if (parent_balance_factor == 1) {
                    if (position == LEFT_CHILD) {
                        //auto left_child = node->left_child;
                        auto right_child = node->right_child;
                        auto balance_factor = node->get_balance_factor();
                        assert(balance_factor != 0);
                        if (balance_factor == 1) {
                            replace_father_son_relationship(parent, node);
                            parent->left_child = right_child;
                            if (right_child != nullptr) {
                                right_child->set_parent_and_reserve_balance_factor(parent);
                            }
                            node->right_child = parent;
                            parent->set_parent(node);
                            parent->set_balance_factor(0);
                            node->set_balance_factor(0);
                        } else {
                            assert(balance_factor == -1);
                            auto right_child_balance_factor = right_child->get_balance_factor();
                            auto left_grand_child = right_child->left_child;
                            auto right_grand_child = right_child->right_child;
                            replace_father_son_relationship(parent, right_child);
                            right_child->left_child = node;
                            node->set_parent(right_child);
                            right_child->right_child = parent;
                            parent->set_parent(right_child);
                            node->right_child = left_grand_child;
                            if (left_grand_child != nullptr) {
                                left_grand_child->set_parent_and_reserve_balance_factor(node);
                            }
                            parent->left_child = right_grand_child;
                            if (right_grand_child != nullptr) {
                                right_grand_child->set_parent_and_reserve_balance_factor(parent);
                            }
                            if (right_child_balance_factor == 1) {
                                node->set_balance_factor(0);
                                parent->set_balance_factor(-1);
                            } else if (right_child_balance_factor == 0) {
                                node->set_balance_factor(0);
                                parent->set_balance_factor(0);
                            } else {
                                assert(right_child_balance_factor == -1);
                                node->set_balance_factor(1);
                                parent->set_balance_factor(0);
                            }
                            right_child->set_balance_factor(0);
                        }
                    } else {
                        parent->set_balance_factor(0);
                    }
                } else {
                    assert(parent_balance_factor == -1);
                    if (position == LEFT_CHILD) {
                        parent->set_balance_factor(0);
                    } else {
                        auto left_child = node->left_child;
                        //auto right_child = node->right_child;
                        auto balance_factor = node->get_balance_factor();
                        assert(balance_factor != 0);
                        if (balance_factor == 1) {
                            auto left_child_balance_factor = left_child->get_balance_factor();
                            auto left_grand_child = left_child->left_child;
                            auto right_grand_child = left_child->right_child;
                            replace_father_son_relationship(parent, left_child);
                            left_child->left_child = parent;
                            parent->set_parent(left_child);
                            left_child->right_child = node;
                            node->set_parent(left_child);
                            parent->right_child = left_grand_child;
                            if (left_grand_child != nullptr) {
                                left_grand_child->set_parent_and_reserve_balance_factor(parent);
                            }
                            node->left_child = right_grand_child;
                            if (right_grand_child != nullptr) {
                                right_grand_child->set_parent_and_reserve_balance_factor(node);
                            }
                            if (left_child_balance_factor == 1) {
                                parent->set_balance_factor(0);
                                node->set_balance_factor(-1);
                            } else if (left_child_balance_factor == 0) {
                                parent->set_balance_factor(0);
                                node->set_balance_factor(0);
                            } else {
                                assert(left_child_balance_factor == -1);
                                parent->set_balance_factor(1);
                                node->set_balance_factor(0);
                            }
                            left_child->set_balance_factor(0);
                        } else {
                            assert(balance_factor == -1);
                            replace_father_son_relationship(parent, node);
                            parent->right_child = left_child;
                            if (left_child != nullptr) {
                                left_child->set_parent_and_reserve_balance_factor(parent);
                            }
                            node->left_child = parent;
                            parent->set_parent(node);
                            parent->set_balance_factor(0);
                            node->set_balance_factor(0);
                        }
                    }
                }
                break;
            } else {
                if (position == LEFT_CHILD) {
                    parent->set_balance_factor(1);
                } else {
                    assert(position == RIGHT_CHILD);
                    parent->set_balance_factor(-1);
                }
                node = parent;
                parent = node->get_parent();
            }
        }
    }

    Node * m_root;
    size_t m_count;
public:
    AVLTree(): m_root(nullptr), m_count(0) {}
    ~AVLTree()
    {
        free(m_root);
    }
    AVLTree(const AVLTree<T>& other):
        m_root(copy(other.m_root)), m_count(other.m_count)
    {
    }
    AVLTree(AVLTree<T>&& other):
        m_root(other.m_root), m_count(other.m_count)
    {
        other.m_root = nullptr;
        other.m_count = 0;
    }
    void swap(AVLTree<T>& other)
    {
        if (this != &other) {
            std::swap(m_root, other.m_root);
            std::swap(m_count, other.m_count);
        }
    }
    AVLTree& operator=(AVLTree<T> const& other)
    {
        if (this != &other) {
            free(m_root);
            m_root = copy(other.m_root);
            m_count = other.m_count;
        }
        return *this;
    }
    AVLTree& operator=(AVLTree<T>&& other)
    {
        if (this != &other) {
            free(m_root);
            m_root = other.m_root;
            m_count = other.m_count;
            other.m_root = nullptr;
            other.m_count = 0;
        }
        return *this;
    }
    bool operator==(const AVLTree<T>& other) const
    {
        return m_count == other.m_count && equals(m_root, other.m_root);
    }
    bool operator!=(const AVLTree<T>& other) const
    {
        return !operator==(other);
    }

    bool valid() const
    {
        return get_internal(m_root).valid;
    }

    void insert(const T& t)
    {
        auto result = find(m_root, t);
        if (result.second != CURRENT) {
            Node * new_node = nullptr;
            switch (result.second) {
            case ROOT:
                assert(m_root == nullptr);
                assert(m_count == 0);
                m_root = new Node(t, nullptr, 0);
                break;
            case LEFT_CHILD:
                new_node = new Node(t, result.first, 0);
                result.first->left_child = new_node;
                break;
            case RIGHT_CHILD:
                new_node = new Node(t, result.first, 0);
                result.first->right_child = new_node;
                break;
            default:
                assert(false);
                break;
            }
            ++m_count;
            if (new_node != nullptr) {
                reblance_after_inserting(new_node);
            }
        } else {
            result.first->data = t;
        }
    }

    bool erase(const T& t)
    {
        bool item_deleted = false;
        auto result = find(m_root, t);
        if (result.second == CURRENT) {
            Node* node = result.first;
            item_deleted = true;
            Node* right_child = node->right_child;
            if (right_child != nullptr) {
                Node* left_child = right_child->left_child;
                if (left_child != nullptr) {
                    while (left_child->left_child != nullptr) {
                        left_child = left_child->left_child;
                    }
                    left_child->exchange_content(node);
                    remove(left_child);
                } else {
                    right_child->exchange_content(node);
                    remove(right_child);
                }
            } else {
                remove(node);
            }
        }
        return item_deleted;
    }

    bool contains(const T& t)
    {
        auto result = find(m_root, t);
        return result.second == CURRENT;
    }
};

#endif //AVL_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
