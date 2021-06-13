#ifndef RED_BLACK_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define RED_BLACK_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <assert.h>
#include <stdint.h>
#include <memory>
#include <utility>


template <typename T>
class RedBlackTree
{
    struct Node;

    enum Color { BLACK = 0, RED = 1 };

    union ColorAndParentPointer
    {
        uintptr_t color;
        Node *    parent;

        ColorAndParentPointer(): parent(nullptr) {}
        ColorAndParentPointer(Node * p, Color c): parent(p)
        {
            if (c == RED) {
                set_color(c);
            }
        }

        const Node * get_parent() const
        {
            const uintptr_t v = 1;
            return reinterpret_cast<Node*>(color & (~v));
        }

        void set_parent(Node* p)
        {
            this->parent = p;
        }
        void set_parent_and_reserve_color(Node* p)
        {
            uintptr_t v = get_color();
            this->parent = p;
            this->color |= v;
        }

        Color get_color() const
        {
            return static_cast<Color>(color & 1U);
        }

        void set_color(Color c)
        {
            Color o = get_color();
            if (o != c) {
                color ^= static_cast<uintptr_t>(1U);
            }
        }
    };

    struct Node
    {
        T data;
        ColorAndParentPointer color_and_parent;
        Node * left_child;
        Node * right_child;

        Node(const T& d, Node * parent, Color c, Node * lc = nullptr, Node * rc = nullptr):
            data(d), color_and_parent(parent, c), left_child(lc), right_child(rc)
        {
        }

        Node(const Node& other):
            data(other.data),
            color_and_parent(nullptr, other.get_color()),
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
            return color_and_parent.get_parent();
        }
        Node * get_parent()
        {
            return const_cast<Node*>(const_cast<const Node*>(this)->get_parent());
        }

        void set_parent(Node* parent)
        {
            color_and_parent.set_parent(parent);
        }

        void set_parent_and_reserve_color(Node* parent)
        {
            color_and_parent.set_parent_and_reserve_color(parent);
        }

        Color get_color() const
        {
            return color_and_parent.get_color();
        }
        Color get_color()
        {
            return const_cast<const Node*>(this)->get_color();
        }

        void set_color(Color c)
        {
            color_and_parent.set_color(c);
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
        Node* retval = nullptr;
        if (node != nullptr) {
            try {
                retval = new Node(*node);
                retval->left_child = copy(node->left_child);
                if (retval->left_child != nullptr) {
                    retval->left_child->set_parent_and_reserve_color(retval);
                }
                retval->right_child = copy(node->right_child);
                if (retval->right_child != nullptr) {
                    retval->right_child->set_parent_and_reserve_color(retval);
                }
            } catch (...) {
                free(retval);
                throw;
            }
        }
        return retval;
    }

    static Color get_color(const Node* node)
    {
        Color color = BLACK;
        if (node != nullptr) {
            color = node->get_color();
        }
        return color;
    }

    static bool equals(Node* n1, Node * n2)
    {
        bool retval = (n1 == n2);
        if (!retval) {
            if (n1 != nullptr && n2 != nullptr) {
                retval = (n1->data == n2->data && n1->get_color() == n2->get_color());
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
        size_t height{0};
        bool   valid{true};
    };

    static Internal get_internal(const Node* const node)
    {
        Internal internal;
        if (node != nullptr) {
            internal.valid = false;
            int inc = -1;
            if (node->get_color() == RED) {
                auto left_child_color = get_color(node->left_child);
                auto right_child_color = get_color(node->right_child);
                if (left_child_color == right_child_color && left_child_color == BLACK) {
                    inc = 0;
                }
            } else {
                inc = 1;
            }
            if (inc >= 0) {
                auto li = get_internal(node->left_child);
                auto ri = get_internal(node->right_child);
                if (li.valid && ri.valid && li.height == ri.height) {
                    if (
                        (node->left_child == nullptr || (node->left_child->data < node->data && node->left_child->get_parent() == node)) &&
                        (node->right_child == nullptr || (node->right_child->data > node->data && node->right_child->get_parent() == node))
                    ) {
                        internal.height = li.height + static_cast<size_t>(inc);
                        internal.valid = true;
                    }
                }
            }
        }
        return internal;
    }

    void replace_father_son_relationship(Node* to_be_replaced, Node* the_new_one)
    {
        Node* parent = to_be_replaced->get_parent();
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
            m_root->set_parent(nullptr);
        }
    }

    void remove(Node* node)
    {
        assert(node != nullptr);
        Node* left_child = node->left_child;
        Node* right_child = node->right_child;
        assert(left_child == nullptr || right_child == nullptr);
        if (right_child != nullptr) {
            assert(right_child->get_color() == RED && right_child->left_child == nullptr);
            assert(node->get_color() == BLACK);
            replace_father_son_relationship(node, right_child);
            right_child->set_color(BLACK);
        } else if (left_child != nullptr) {
            assert(left_child->get_color() == RED && left_child->left_child == nullptr && left_child->right_child == nullptr);
            assert(node->get_color() == BLACK);
            replace_father_son_relationship(node, left_child);
            left_child->set_color(BLACK);
        } else {
            auto parent = node->get_parent();
            if (parent != nullptr) {
                auto position = get_position(node, parent);
                auto color = node->get_color();
                replace_father_son_relationship(node, nullptr);
                if (color == BLACK) {
                    reblance_after_deleting(position, nullptr, parent);
                }
            } else {
                assert(m_count == 1);
                m_root = nullptr;
            }
        }
        delete node;
        --m_count;
    }

    void reblance_after_deleting(ExpectedPosition position, Node * node, Node * parent)
    {
        assert(parent != nullptr);
        auto sibling = get_sibling(node, parent);
        if (sibling->get_color() == RED) {
            auto left_nephew = sibling->left_child;
            auto right_nephew = sibling->right_child;
            replace_father_son_relationship(parent, sibling);
            parent->set_color(RED);
            sibling->set_color(BLACK);
            if (position == LEFT_CHILD) {
                parent->right_child = left_nephew;
                left_nephew->set_parent_and_reserve_color(parent);
                sibling->left_child = parent;
                parent->set_parent_and_reserve_color(sibling);
                sibling = left_nephew;
            } else {
                assert(position == RIGHT_CHILD);
                parent->left_child = right_nephew;
                right_nephew->set_parent_and_reserve_color(parent);
                sibling->right_child = parent;
                parent->set_parent_and_reserve_color(sibling);
                sibling = right_nephew;
            }
        }
        assert(sibling->get_color() == BLACK);
        auto left_nephew = sibling->left_child;
        auto right_nephew = sibling->right_child;
        auto left_nephew_color = get_color(left_nephew);
        auto right_nephew_color = get_color(right_nephew);
        auto parent_color = parent->get_color();
        if (left_nephew_color == right_nephew_color && left_nephew_color == BLACK) {
            sibling->set_color(RED);
            if (parent_color == BLACK) {
                auto grandparent = parent->get_parent();
                if (grandparent != nullptr) {
                    reblance_after_deleting(get_position(parent, grandparent), parent, grandparent);
                }
            } else {
                parent->set_color(BLACK);
            }
        } else {
            position = get_position(node, parent);
            if (
                (position == LEFT_CHILD && left_nephew_color == RED) ||
                (position == RIGHT_CHILD && right_nephew_color == RED)
            ) {
                if (position == LEFT_CHILD) {
                    auto left_child_of_nephew = left_nephew->left_child;
                    auto right_child_of_nephew = left_nephew->right_child;
                    replace_father_son_relationship(parent, left_nephew);
                    left_nephew->left_child = parent;
                    parent->set_parent(left_nephew);
                    left_nephew->right_child = sibling;
                    sibling->set_parent(left_nephew);
                    parent->right_child = left_child_of_nephew;
                    if (left_child_of_nephew != nullptr) {
                        left_child_of_nephew->set_parent_and_reserve_color(parent);
                    }
                    sibling->left_child = right_child_of_nephew;
                    if (right_child_of_nephew != nullptr) {
                        right_child_of_nephew->set_parent_and_reserve_color(sibling);
                    }
                    left_nephew->set_color(parent_color);
                } else {
                    auto left_child_of_nephew = right_nephew->left_child;
                    auto right_child_of_nephew = right_nephew->right_child;
                    replace_father_son_relationship(parent, right_nephew);
                    right_nephew->left_child = sibling;
                    sibling->set_parent(right_nephew);
                    right_nephew->right_child = parent;
                    parent->set_parent(right_nephew);
                    sibling->right_child = left_child_of_nephew;
                    if (left_child_of_nephew != nullptr) {
                        left_child_of_nephew->set_parent_and_reserve_color(sibling);
                    }
                    parent->left_child = right_child_of_nephew;
                    if (right_child_of_nephew != nullptr) {
                        right_child_of_nephew->set_parent_and_reserve_color(parent);
                    }
                    right_nephew->set_color(parent_color);
                }
                parent->set_color(BLACK);
                sibling->set_color(BLACK);
            } else {
                replace_father_son_relationship(parent, sibling);
                if (position == LEFT_CHILD) {
                    sibling->left_child = parent;
                    parent->set_parent(sibling);
                    parent->right_child = left_nephew;
                    if (left_nephew != nullptr) {
                        left_nephew->set_parent_and_reserve_color(parent);
                    }
                    right_nephew->set_color(BLACK);
                } else {
                    sibling->right_child = parent;
                    parent->set_parent(sibling);
                    parent->left_child = right_nephew;
                    if (right_nephew != nullptr) {
                        right_nephew->set_parent_and_reserve_color(parent);
                    }
                    left_nephew->set_color(BLACK);
                }
                parent->set_color(BLACK);
                sibling->set_color(parent_color);
            }
        }
    }

    void reblance_after_inserting(Node * node)
    {
        auto parent = node->get_parent();
        while (parent != nullptr && parent->get_color() == RED) {
            auto grandparent = parent->get_parent();
            if (grandparent != nullptr) {
                auto uncle = get_sibling(parent, grandparent);
                if (get_color(uncle) == RED) {
                    uncle->set_color(BLACK);
                    parent->set_color(BLACK);
                    grandparent->set_color(RED);
                    node = grandparent;
                    parent = node->get_parent();
                } else {
                    auto sibling = get_sibling(node, parent);
                    auto position = get_position(node, parent);
                    auto parent_position = get_position(parent, grandparent);
                    if (position == parent_position) {
                        replace_father_son_relationship(grandparent, parent);
                        if (position == LEFT_CHILD) {
                            grandparent->left_child = sibling;
                            parent->right_child = grandparent;
                        } else {
                            grandparent->right_child = sibling;
                            parent->left_child = grandparent;
                        }
                        if (sibling != nullptr) {
                            sibling->set_parent_and_reserve_color(grandparent);
                        }
                        grandparent->set_parent(parent);
                        parent->set_color(BLACK);
                        grandparent->set_color(RED);
                    } else {
                        auto left_child = node->left_child;
                        auto right_child = node->right_child;
                        replace_father_son_relationship(grandparent, node);
                        if (position == LEFT_CHILD) {
                            grandparent->right_child = left_child;
                            parent->left_child = right_child;
                            node->left_child = grandparent;
                            node->right_child = parent;
                            if (left_child != nullptr) {
                                left_child->set_parent_and_reserve_color(grandparent);
                            }
                            if (right_child != nullptr) {
                                right_child->set_parent_and_reserve_color(parent);
                            }
                        } else {
                            grandparent->left_child = right_child;
                            parent->right_child = left_child;
                            node->left_child = parent;
                            node->right_child = grandparent;
                            if (left_child != nullptr) {
                                left_child->set_parent_and_reserve_color(parent);
                            }
                            if (right_child != nullptr) {
                                right_child->set_parent_and_reserve_color(grandparent);
                            }
                        }
                        grandparent->set_parent(node);
                        parent->set_parent(node);
                        grandparent->set_color(RED);
                        parent->set_color(RED);
                        node->set_color(BLACK);
                    }
                    break;
                }
            } else {
                assert(m_root == parent);
                break;
            }
        }
        m_root->set_parent(nullptr);
    }

    Node * m_root;
    size_t m_count;
public:
    RedBlackTree(): m_root(nullptr), m_count(0) {}
    ~RedBlackTree()
    {
        free(m_root);
    }
    RedBlackTree(const RedBlackTree<T>& other):
        m_root(copy(other.m_root)), m_count(other.m_count)
    {
    }
    RedBlackTree(RedBlackTree<T>&& other):
        m_root(other.m_root), m_count(other.m_count)
    {
        other.m_root = nullptr;
        other.m_count = 0;
    }
    void swap(RedBlackTree<T>& other)
    {
        if (this != &other) {
            std::swap(m_root, other.m_root);
            std::swap(m_count, other.m_count);
        }
    }
    RedBlackTree& operator=(RedBlackTree<T> const& other)
    {
        if (this != &other) {
            free(m_root);
            m_root = copy(other.m_root);
            m_count = other.m_count;
        }
        return *this;
    }
    RedBlackTree& operator=(RedBlackTree<T>&& other)
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
    bool operator==(const RedBlackTree<T>& other) const
    {
        return m_count == other.m_count && equals(m_root, other.m_root);
    }
    bool operator!=(const RedBlackTree<T>& other) const
    {
        return !operator==(other);
    }

    bool valid() const
    {
        auto internal = get_internal(m_root);
        return (internal.valid && get_color(m_root) == BLACK);
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
                m_root = new Node(t, nullptr, BLACK);
                break;
            case LEFT_CHILD:
                new_node = new Node(t, result.first, RED);
                result.first->left_child = new_node;
                break;
            case RIGHT_CHILD:
                new_node = new Node(t, result.first, RED);
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

#endif //RED_BLACK_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
