class RedBlackTree:
    class Position:
        ROOT = 0
        LEFT_CHILD = 1
        RIGHT_CHILD = 2
        FOUND_IT = 3

    class Color:
        BLACK = 0
        RED = 1

    class Node:
        def __init__(self, key, value, color, parent=None, left_child=None, right_child=None):
            self.key = key
            if value is not None:
                self.value = value
            self.color = color
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
            return "Node(%s, %s, ...)" % (self.key, "Black" if self.color == RedBlackTree.Color.BLACK else "Red")

    def _get_internal(self, node):
        class Internal:
            def __init__(self):
                self.height = 0
                self.valid = True
        internal = Internal()
        if node is not None:
            internal.valid = False
            inc = -1
            if node.color == RedBlackTree.Color.RED:
                left_child_color = self._get_color(node.left_child)
                right_child_color = self._get_color(node.right_child)
                if left_child_color == right_child_color and left_child_color == RedBlackTree.Color.BLACK:
                    inc = 0
            else:
                inc = 1
            if inc >= 0:
                li = self._get_internal(node.left_child)
                ri = self._get_internal(node.right_child)
                if li.valid and ri.valid and li.height == ri.height:
                    if (
                        (node.left_child is None or (node.left_child.key < node.key and node.left_child.parent is node)) and
                        (node.right_child is None or (node.right_child.key > node.key and node.right_child.parent is node))
                    ):
                        internal.height = li.height + inc
                        internal.valid = True
        return internal

    def valid(self):
        internal = self._get_internal(self._root)
        return internal.valid and self._get_color(self._root) == RedBlackTree.Color.BLACK

    def _find(self, key, node):
        parent_or_itself = None
        indicator = RedBlackTree.Position.ROOT
        while node is not None:
            parent_or_itself = node
            if key < node.key:
                indicator = RedBlackTree.Position.LEFT_CHILD
                node = node.left_child
            elif key > node.key:
                indicator = RedBlackTree.Position.RIGHT_CHILD
                node = node.right_child
            else:
                indicator = RedBlackTree.Position.FOUND_IT
                break
        return [parent_or_itself, indicator]

    def __init__(self):
        self._root = None
        self._len = 0

    def _get_color(self, node):
        color = RedBlackTree.Color.BLACK
        if node is not None:
            color = node.color
        return color

    def _get_sibling(self, node, parent):
        if parent.left_child is node:
            return parent.right_child
        else:
            assert parent.right_child is node
            return parent.left_child

    def _get_position(self, node, parent):
        if parent.left_child is node:
            return RedBlackTree.Position.LEFT_CHILD
        else:
            assert parent.right_child is node
            return RedBlackTree.Position.RIGHT_CHILD

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
        assert parent is not None
        sibling = self._get_sibling(node, parent)
        if sibling.color == RedBlackTree.Color.RED:
            #position = self._get_position(node, parent)
            left_nephew = sibling.left_child
            right_nephew = sibling.right_child
            self._replace_father_son_relationship(parent, sibling)
            parent.color = RedBlackTree.Color.RED
            sibling.color = RedBlackTree.Color.BLACK
            if position == RedBlackTree.Position.LEFT_CHILD:
                parent.right_child = left_nephew
                left_nephew.parent = parent
                sibling.left_child = parent
                parent.parent = sibling
                sibling = left_nephew
            else:
                assert position == RedBlackTree.Position.RIGHT_CHILD
                parent.left_child = right_nephew
                right_nephew.parent = parent
                sibling.right_child = parent
                parent.parent = sibling
                sibling = right_nephew
        assert sibling.color == RedBlackTree.Color.BLACK
        left_nephew = sibling.left_child
        right_nephew = sibling.right_child
        left_nephew_color = self._get_color(left_nephew)
        right_nephew_color = self._get_color(right_nephew)
        parent_color = parent.color
        if left_nephew_color == right_nephew_color and left_nephew_color == RedBlackTree.Color.BLACK:
            sibling.color = RedBlackTree.Color.RED
            if parent_color == RedBlackTree.Color.BLACK:
                grandparent = parent.parent
                if grandparent is not None:
                    self._reblance_after_deleting(self._get_position(parent, grandparent), parent, grandparent)
            else:
                parent.color = RedBlackTree.Color.BLACK
        else:
            position = self._get_position(node, parent)
            if (
                (position == RedBlackTree.Position.LEFT_CHILD and left_nephew_color == RedBlackTree.Color.RED) or
                (position == RedBlackTree.Position.RIGHT_CHILD and right_nephew_color == RedBlackTree.Color.RED)
            ):
                if position == RedBlackTree.Position.LEFT_CHILD:
                    left_child_of_nephew = left_nephew.left_child
                    right_child_of_nephew = left_nephew.right_child
                    self._replace_father_son_relationship(parent, left_nephew)
                    left_nephew.left_child = parent
                    parent.parent = left_nephew
                    left_nephew.right_child = sibling
                    sibling.parent = left_nephew
                    parent.right_child = left_child_of_nephew
                    if left_child_of_nephew is not None:
                        left_child_of_nephew.parent = parent
                    sibling.left_child = right_child_of_nephew
                    if right_child_of_nephew is not None:
                        right_child_of_nephew.parent = sibling
                    left_nephew.color = parent_color
                else:
                    left_child_of_nephew = right_nephew.left_child
                    right_child_of_nephew = right_nephew.right_child
                    self._replace_father_son_relationship(parent, right_nephew)
                    right_nephew.left_child = sibling
                    sibling.parent = right_nephew
                    right_nephew.right_child = parent
                    parent.parent = right_nephew
                    sibling.right_child = left_child_of_nephew
                    if left_child_of_nephew is not None:
                        left_child_of_nephew.parent = sibling
                    parent.left_child = right_child_of_nephew
                    if right_child_of_nephew is not None:
                        right_child_of_nephew.parent = parent
                    right_nephew.color = parent_color
                parent.color = RedBlackTree.Color.BLACK
                sibling.color = RedBlackTree.Color.BLACK
            else:
                self._replace_father_son_relationship(parent, sibling)
                if position == RedBlackTree.Position.LEFT_CHILD:
                    sibling.left_child = parent
                    parent.parent = sibling
                    parent.right_child = left_nephew
                    if left_nephew is not None:
                        left_nephew.parent = parent
                    right_nephew.color = RedBlackTree.Color.BLACK
                else:
                    sibling.right_child = parent
                    parent.parent = sibling
                    parent.left_child = right_nephew
                    if right_nephew is not None:
                        right_nephew.parent = parent
                    left_nephew.color = RedBlackTree.Color.BLACK
                parent.color = RedBlackTree.Color.BLACK
                sibling.color = parent_color

    def _delete(self, node):
        left_child = node.left_child
        right_child = node.right_child
        assert left_child is None or right_child is None
        if right_child is not None:
            assert right_child.color == RedBlackTree.Color.RED and right_child.left_child is None and right_child.right_child is None
            assert node.color == RedBlackTree.Color.BLACK
            self._replace_father_son_relationship(node, right_child)
            right_child.color = RedBlackTree.Color.BLACK
            del node
        elif left_child is not None:
            assert left_child.color == RedBlackTree.Color.RED and left_child.left_child is None and left_child.right_child is None
            assert node.color == RedBlackTree.Color.BLACK
            self._replace_father_son_relationship(node, left_child)
            left_child.color = RedBlackTree.Color.BLACK
            del node
        else:
            parent = node.parent
            if parent is not None:
                position = self._get_position(node, parent)
                color = node.color
                self._replace_father_son_relationship(node, None)
                del node
                if color == RedBlackTree.Color.BLACK:
                    self._reblance_after_deleting(position, None, parent)
            else:
                assert self._len == 0
                self._root = None
                del node

    def _reblance_after_inserting(self, node):
        parent = node.parent
        while parent is not None and parent.color == RedBlackTree.Color.RED:
            grandparent = parent.parent
            if grandparent is not None:
                uncle = self._get_sibling(parent, grandparent)
                if self._get_color(uncle) == RedBlackTree.Color.RED:
                    uncle.color = parent.color = RedBlackTree.Color.BLACK
                    grandparent.color = RedBlackTree.Color.RED
                    node = grandparent
                    parent = node.parent
                else:
                    sibling = self._get_sibling(node, parent)
                    position = self._get_position(node, parent)
                    parent_position = self._get_position(parent, grandparent)
                    if position == parent_position:
                        self._replace_father_son_relationship(grandparent, parent)
                        if position == RedBlackTree.Position.LEFT_CHILD:
                            grandparent.left_child = sibling
                            parent.right_child = grandparent
                        else:
                            grandparent.right_child = sibling
                            parent.left_child = grandparent
                        if sibling is not None:
                            sibling.parent = grandparent
                        grandparent.parent = parent
                        parent.color = RedBlackTree.Color.BLACK
                        grandparent.color = RedBlackTree.Color.RED
                    else:
                        left_child = node.left_child
                        right_child = node.right_child
                        self._replace_father_son_relationship(grandparent, node)
                        if position == RedBlackTree.Position.LEFT_CHILD:
                            grandparent.right_child = left_child
                            parent.left_child = right_child
                            node.left_child = grandparent
                            node.right_child = parent
                            if left_child is not None:
                                left_child.parent = grandparent
                            if right_child is not None:
                                right_child.parent = parent
                        else:
                            grandparent.left_child = right_child
                            parent.right_child = left_child
                            node.left_child = parent
                            node.right_child = grandparent
                            if left_child is not None:
                                left_child.parent = parent
                            if right_child is not None:
                                right_child.parent = grandparent
                        grandparent.parent = node
                        parent.parent = node
                        grandparent.color = RedBlackTree.Color.RED
                        parent.color = RedBlackTree.Color.RED
                        node.color = RedBlackTree.Color.BLACK
                    break
            else:
                assert self._root is parent
                break
        if self._root.color == RedBlackTree.Color.RED:
            self._root.color = RedBlackTree.Color.BLACK
        self._root.parent = None

    def insert(self, key, value=None):
        new_node_added = False
        parent_or_itself, indicator = self._find(key, self._root)
        if indicator == RedBlackTree.Position.FOUND_IT:
            parent_or_itself.key = key
            if value is not None:
                parent_or_itself.value = value
            else:
                del parent_or_itself.value
        else:
            new_node = None
            if indicator == RedBlackTree.Position.LEFT_CHILD:
                parent_or_itself.left_child = RedBlackTree.Node(
                    key, value, RedBlackTree.Color.RED, parent_or_itself
                )
                new_node = parent_or_itself.left_child
            elif indicator == RedBlackTree.Position.RIGHT_CHILD:
                parent_or_itself.right_child = RedBlackTree.Node(
                    key, value, RedBlackTree.Color.RED, parent_or_itself
                )
                new_node = parent_or_itself.right_child
            elif indicator == RedBlackTree.Position.ROOT:
                self._root = RedBlackTree.Node(
                    key, value, RedBlackTree.Color.BLACK
                )
            else:
                assert False, "Serious bug happened in the function insert"
            self._len += 1
            if new_node != None:
                self._reblance_after_inserting(new_node)
            new_node_added = True
        return new_node_added

    put = insert

    def __len__(self): return self._len

    def __contains__(self, key):
        _, indicator = self._find(key, self._root)
        return indicator == RedBlackTree.Position.FOUND_IT

    def __delitem__(self, key):
        item_deleted = False
        node, indicator = self._find(key, self._root)
        if indicator == RedBlackTree.Position.FOUND_IT:
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

    def min(self):
        retval = None
        node = self._root
        if node is not None:
            while node.left_child is not None:
                node = node.left_child
            retval = node.key
        return retval

    def max(self):
        retval = None
        node = self._root
        if node is not None:
            while node.right_child is not None:
                node = node.right_child
            retval = node.key
        return retval

if __name__ == "__main__":
    import random
    input = [_ for _ in range(1024)]
    rdata = None
    v = None
    try:
        for _ in range(4):
            tree = RedBlackTree()
            for v in input:
                tree.put(v)
                assert v in tree
                assert tree.valid()
            rdata = input[:]
            random.shuffle(rdata)
            for v in rdata:
                del tree[v]
                assert v not in tree
                assert tree.valid()
            input = rdata
    except AttributeError:
        print(input)
        print(rdata)
        print(v)