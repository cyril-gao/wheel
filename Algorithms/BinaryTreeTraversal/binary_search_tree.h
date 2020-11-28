#ifndef BINARY_SEARCH_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define BINARY_SEARCH_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <utility>

namespace details
{
	enum class ExpectedPosition { CURRENT, ROOT, LEFT_CHIND, RIGHT_CHILD };

    template <typename BinarySearchTreeNode, typename T>
    auto find(BinarySearchTreeNode* root, const T& key)
    {
        BinarySearchTreeNode* parent_or_self = nullptr;
		ExpectedPosition position = ExpectedPosition::ROOT;
        for (BinarySearchTreeNode* i = root; i != nullptr;) {
            parent_or_self = i;
            if (i->data() == key) {
				position = ExpectedPosition::CURRENT;
                break;
            } else if (i->data() < key) {
				position = ExpectedPosition::RIGHT_CHILD;
                i = i->right_child();
            } else {
				position = ExpectedPosition::LEFT_CHIND;
                i = i->left_child();
            }
        }            
        return std::make_pair(parent_or_self, position);
    }
}

#endif //BINARY_SEARCH_TREE_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
