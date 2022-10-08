'''
This module implements AVL tree
'''


class AVLTree:
    class Node:
        def __init__(self, key, value, balance_factor, parent=None, left_child=None, right_child=None):
            assert balance_factor in {-1, 0, 1}
            self.key = key
            if value is not None:
                self.value = value
            self.balance_factor = balance_factor
            self.parent = parent
            self.left_child = left_child
            self.right_child = right_child

        def exchange_content(self, other):
            self.key, other.key = other.key, self.key
            v1 = self.__dict__.get("value", None)
            v2 = other.__dict__.get("value", None)
            if v1 is not None:
                other.value = v1
            else:
                if v2 is not None:
                    del other.value
            if v2 is not None:
                self.value = v2
            else:
                if v1 is not None:
                    del self.value

        def __repr__(self):
            return "Node(%s, %s, ...)" % (self.key, self.balance_factor)

    def _get_internal(self, node):
        class Internal:
            def __init__(self):
                self.height = 0
                self.valid = True
        internal = Internal()
        if node is not None:
            internal.valid = False
            if (
                (node.left_child is None or (node.left_child.key < node.key and node.left_child.parent is node)) and
                (node.right_child is None or (node.right_child.key > node.key and node.right_child.parent is node))
            ):
                li = self._get_internal(node.left_child)
                ri = self._get_internal(node.right_child)
                if li.valid and ri.valid:
                    diff = li.height - ri.height
                    if node.balance_factor == diff:
                        internal.height = (
                            li.height if li.height > ri.height else ri.height) + 1
                        internal.valid = True
        return internal

    def valid(self):
        internal = self._get_internal(self._root)
        return internal.valid

    class Position:
        ROOT = 0
        LEFT_CHILD = 1
        RIGHT_CHILD = 2
        FOUND_IT = 3

    def _find(self, key, node):
        parent_or_itself = None
        indicator = AVLTree.Position.ROOT
        while node is not None:
            parent_or_itself = node
            if key < node.key:
                indicator = AVLTree.Position.LEFT_CHILD
                node = node.left_child
            elif key > node.key:
                indicator = AVLTree.Position.RIGHT_CHILD
                node = node.right_child
            else:
                indicator = AVLTree.Position.FOUND_IT
                break
        return [parent_or_itself, indicator]

    def __init__(self):
        self._root = None
        self._len = 0

    def _get_sibling(self, node, parent):
        assert parent is not None
        if parent.left_child is node:
            return parent.right_child
        assert parent.right_child is node
        return parent.left_child

    def _get_position(self, node, parent):
        assert parent is not None
        if parent.left_child is node:
            return AVLTree.Position.LEFT_CHILD
        assert parent.right_child is node
        return AVLTree.Position.RIGHT_CHILD

    def _replace_father_son_relationship(self, to_be_replaced, the_new_one):
        parent = to_be_replaced.parent
        if parent is not None:
            if parent is not the_new_one:
                if parent.left_child is to_be_replaced:
                    parent.left_child = the_new_one
                else:
                    assert parent.right_child is to_be_replaced
                    parent.right_child = the_new_one
                if the_new_one is not None:
                    the_new_one.parent = parent
            else:
                assert False, "It is not supported to replace a child node with its parent node"
        else:
            assert self._root is to_be_replaced
            self._root = the_new_one
            self._root.parent = None

    def _reblance_after_deleting(self, position, node, parent):
        while parent is not None:
            parent_balance_factor = parent.balance_factor
            if parent_balance_factor == 0:
                if position == AVLTree.Position.LEFT_CHILD:
                    parent.balance_factor = -1
                else:
                    assert position == AVLTree.Position.RIGHT_CHILD
                    parent.balance_factor = 1
                break
            else:
                if (
                    (position == AVLTree.Position.LEFT_CHILD and parent_balance_factor == 1) or
                    (position == AVLTree.Position.RIGHT_CHILD and parent_balance_factor == -1)
                ):
                    parent.balance_factor = 0
                    node = parent
                else:
                    sibling = self._get_sibling(node, parent)
                    sibling_balance_factor = sibling.balance_factor
                    left_nephew = sibling.left_child
                    right_nephew = sibling.right_child
                    if sibling_balance_factor == 0:
                        self._replace_father_son_relationship(parent, sibling)
                        if position == AVLTree.Position.LEFT_CHILD:
                            parent.right_child = left_nephew
                            left_nephew.parent = parent
                            sibling.left_child = parent
                            parent.parent = sibling
                            parent.balance_factor = -1
                            sibling.balance_factor = 1
                        else:
                            assert position == AVLTree.Position.RIGHT_CHILD
                            parent.left_child = right_nephew
                            right_nephew.parent = parent
                            sibling.right_child = parent
                            parent.parent = sibling
                            parent.balance_factor = 1
                            sibling.balance_factor = -1
                        break
                    else:
                        if position == AVLTree.Position.LEFT_CHILD:
                            if sibling_balance_factor == 1:
                                left_nephew_balance_factor = left_nephew.balance_factor
                                left_grand_child = left_nephew.left_child
                                right_grand_child = left_nephew.right_child
                                self._replace_father_son_relationship(
                                    parent, left_nephew)
                                left_nephew.left_child = parent
                                parent.parent = left_nephew
                                left_nephew.right_child = sibling
                                sibling.parent = left_nephew
                                parent.right_child = left_grand_child
                                if left_grand_child is not None:
                                    left_grand_child.parent = parent
                                sibling.left_child = right_grand_child
                                if right_grand_child is not None:
                                    right_grand_child.parent = sibling
                                if left_nephew_balance_factor == 1:
                                    parent.balance_factor = 0
                                    sibling.balance_factor = -1
                                elif left_nephew_balance_factor == 0:
                                    parent.balance_factor = 0
                                    sibling.balance_factor = 0
                                else:
                                    assert left_nephew_balance_factor == -1
                                    parent.balance_factor = 1
                                    sibling.balance_factor = 0
                                left_nephew.balance_factor = 0
                                node = left_nephew
                            else:
                                assert sibling_balance_factor == -1
                                self._replace_father_son_relationship(
                                    parent, sibling)
                                parent.right_child = left_nephew
                                if left_nephew is not None:
                                    left_nephew.parent = parent
                                sibling.left_child = parent
                                parent.parent = sibling
                                parent.balance_factor = 0
                                sibling.balance_factor = 0
                                node = sibling
                        else:
                            if sibling_balance_factor == 1:
                                self._replace_father_son_relationship(
                                    parent, sibling)
                                parent.left_child = right_nephew
                                if right_nephew is not None:
                                    right_nephew.parent = parent
                                sibling.right_child = parent
                                parent.parent = sibling
                                parent.balance_factor = 0
                                sibling.balance_factor = 0
                                node = sibling
                            else:
                                assert sibling_balance_factor == -1
                                right_nephew_balance_factor = right_nephew.balance_factor
                                left_grand_child = right_nephew.left_child
                                right_grand_child = right_nephew.right_child
                                self._replace_father_son_relationship(
                                    parent, right_nephew)
                                right_nephew.left_child = sibling
                                sibling.parent = right_nephew
                                right_nephew.right_child = parent
                                parent.parent = right_nephew
                                sibling.right_child = left_grand_child
                                if left_grand_child is not None:
                                    left_grand_child.parent = sibling
                                parent.left_child = right_grand_child
                                if right_grand_child is not None:
                                    right_grand_child.parent = parent
                                if right_nephew_balance_factor == 1:
                                    parent.balance_factor = -1
                                    sibling.balance_factor = 0
                                elif right_nephew_balance_factor == 0:
                                    parent.balance_factor = 0
                                    sibling.balance_factor = 0
                                else:
                                    assert right_nephew_balance_factor == -1
                                    parent.balance_factor = 0
                                    sibling.balance_factor = 1
                                right_nephew.balance_factor = 0
                                node = right_nephew
                parent = node.parent
                if parent is not None:
                    position = self._get_position(node, parent)
        if parent is None:
            assert node is not None
            self._root = node
            self._root.parent = None

    def _delete(self, node):
        left_child = node.left_child
        right_child = node.right_child
        assert left_child is None or right_child is None
        if right_child is not None:
            assert node.balance_factor == -1
            assert right_child.balance_factor == 0 and right_child.left_child is None and right_child.right_child is None
            self._replace_father_son_relationship(node, right_child)
            del node
            parent = right_child.parent
            if parent is not None:
                self._reblance_after_deleting(self._get_position(right_child, parent), right_child, parent)
            else:
                assert self._root is right_child
        elif left_child is not None:
            assert node.balance_factor == 1
            assert left_child.balance_factor == 0 and left_child.left_child is None and left_child.right_child is None
            self._replace_father_son_relationship(node, left_child)
            del node
            parent = left_child.parent
            if parent is not None:
                self._reblance_after_deleting(self._get_position(left_child, parent), left_child, parent)
            else:
                assert self._root is left_child
        else:
            parent = node.parent
            if parent is not None:
                position = self._get_position(node, parent)
                self._replace_father_son_relationship(node, None)
                del node
                self._reblance_after_deleting(position, None, parent)
            else:
                assert self._len == 0
                self._root = None
                del node

    def _reblance_after_inserting(self, node):
        parent = node.parent
        while parent is not None:
            position = self._get_position(node, parent)
            parent_balance_factor = parent.balance_factor
            if parent_balance_factor != 0:
                if parent_balance_factor == 1:
                    if position == AVLTree.Position.LEFT_CHILD:
                        left_child = node.left_child
                        right_child = node.right_child
                        balance_factor = node.balance_factor
                        assert balance_factor != 0
                        if balance_factor == 1:
                            self._replace_father_son_relationship(parent, node)
                            parent.left_child = right_child
                            if right_child is not None:
                                right_child.parent = parent
                            node.right_child = parent
                            parent.parent = node
                            parent.balance_factor = 0
                            node.balance_factor = 0
                        else:
                            assert balance_factor == -1
                            right_child_balance_factor = right_child.balance_factor
                            left_grand_child = right_child.left_child
                            right_grand_child = right_child.right_child
                            self._replace_father_son_relationship(
                                parent, right_child)
                            right_child.left_child = node
                            node.parent = right_child
                            right_child.right_child = parent
                            parent.parent = right_child
                            node.right_child = left_grand_child
                            if left_grand_child is not None:
                                left_grand_child.parent = node
                            parent.left_child = right_grand_child
                            if right_grand_child is not None:
                                right_grand_child.parent = parent
                            if right_child_balance_factor == 1:
                                node.balance_factor = 0
                                parent.balance_factor = -1
                            elif right_child_balance_factor == 0:
                                node.balance_factor = 0
                                parent.balance_factor = 0
                            else:
                                assert right_child_balance_factor == -1
                                node.balance_factor = 1
                                parent.balance_factor = 0
                            right_child.balance_factor = 0
                    else:
                        parent.balance_factor = 0
                else:
                    assert parent_balance_factor == -1
                    if position == AVLTree.Position.LEFT_CHILD:
                        parent.balance_factor = 0
                    else:
                        left_child = node.left_child
                        right_child = node.right_child
                        balance_factor = node.balance_factor
                        assert balance_factor != 0
                        if balance_factor == 1:
                            left_child_balance_factor = left_child.balance_factor
                            left_grand_child = left_child.left_child
                            right_grand_child = left_child.right_child
                            self._replace_father_son_relationship(
                                parent, left_child)
                            left_child.left_child = parent
                            parent.parent = left_child
                            left_child.right_child = node
                            node.parent = left_child
                            parent.right_child = left_grand_child
                            if left_grand_child is not None:
                                left_grand_child.parent = parent
                            node.left_child = right_grand_child
                            if right_grand_child is not None:
                                right_grand_child.parent = node
                            if left_child_balance_factor == 1:
                                parent.balance_factor = 0
                                node.balance_factor = -1
                            elif left_child_balance_factor == 0:
                                parent.balance_factor = 0
                                node.balance_factor = 0
                            else:
                                assert left_child_balance_factor == -1
                                parent.balance_factor = 1
                                node.balance_factor = 0
                            left_child.balance_factor = 0
                        else:
                            assert balance_factor == -1
                            self._replace_father_son_relationship(parent, node)
                            parent.right_child = left_child
                            if left_child is not None:
                                left_child.parent = parent
                            node.left_child = parent
                            parent.parent = node
                            parent.balance_factor = 0
                            node.balance_factor = 0
                break
            else:
                if position == AVLTree.Position.LEFT_CHILD:
                    parent.balance_factor = 1
                else:
                    assert position == AVLTree.Position.RIGHT_CHILD
                    parent.balance_factor = -1
                node = parent
                parent = node.parent

    def insert(self, key, value=None):
        new_node_added = False
        parent_or_itself, indicator = self._find(key, self._root)
        if indicator == AVLTree.Position.FOUND_IT:
            parent_or_itself.key = key
            if value is not None:
                parent_or_itself.value = value
            else:
                del parent_or_itself.value
        else:
            new_node = None
            if indicator == AVLTree.Position.LEFT_CHILD:
                parent_or_itself.left_child = AVLTree.Node(
                    key, value, 0, parent_or_itself
                )
                new_node = parent_or_itself.left_child
            elif indicator == AVLTree.Position.RIGHT_CHILD:
                parent_or_itself.right_child = AVLTree.Node(
                    key, value, 0, parent_or_itself
                )
                new_node = parent_or_itself.right_child
            elif indicator == AVLTree.Position.ROOT:
                self._root = AVLTree.Node(key, value, 0)
            else:
                assert False, "Serious bug happened in the function insert"
            self._len += 1
            if new_node is not None:
                self._reblance_after_inserting(new_node)
            new_node_added = True
        return new_node_added

    put = insert

    def __len__(self): return self._len

    def __contains__(self, key):
        _, indicator = self._find(key, self._root)
        return indicator == AVLTree.Position.FOUND_IT

    def __delitem__(self, key):
        item_deleted = False
        node, indicator = self._find(key, self._root)
        if indicator == AVLTree.Position.FOUND_IT:
            self._len -= 1
            item_deleted = True
            right_child = node.right_child
            if right_child is not None:
                left_child = right_child.left_child
                if left_child is not None:
                    while left_child.left_child is not None:
                        left_child = left_child.left_child
                    left_child.exchange_content(node)
                    self._delete(left_child)
                else:
                    right_child.exchange_content(node)
                    self._delete(right_child)
            else:
                self._delete(node)
        return item_deleted


if __name__ == "__main__":
    import random
    input_data = list(range(1024))
    rdata = None
    v = None
    try:
        for _ in range(4):
            tree = AVLTree()
            for v in input_data:
                tree.put(v)
                assert v in tree
                assert tree.valid()
            rdata = input_data[:]
            random.shuffle(rdata)
            for v in rdata:
                del tree[v]
                assert v not in tree
                assert tree.valid()
            input_data = rdata
    except AssertionError:
        print(input)
        print(rdata)
        print(v)
