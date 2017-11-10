RED = True
BLACK = False


class Node:
    def __init__(self, key, val):
        self.key = key
        self.val = val

        self.left = None
        self.right = None

        self.size = 1

        self.color = BLACK

    @property
    def is_red(self):
        return self.color == RED


class RedBlackBST:
    def __init__(self, root):
        self.root = root

    @staticmethod
    def size(node):
        if node is None:
            return 0
        return node.size

    @staticmethod
    def __is_red(node):
        if node is None:
            return False
        return node.color == RED

    def __rotate_left(self, node):
        new_node = node.right
        node.right = new_node.left
        new_node.left = node
        new_node.color = node.color
        node.color = RED

        new_node.size = node.size
        node.size = self.size(node.left) + 1 + self.size(node.right)

        return new_node

    def __rotate_right(self, node):
        new_node = node.left
        node.left = new_node.right
        new_node.right = node
        new_node.color = node.color
        node.color = RED

        new_node.size = node.size
        node.size = self.size(node.left) + 1 + self.size(node.right)

        return new_node

    @staticmethod
    def __flip_colors(node):
        node.left.color = BLACK
        node.right.color = BLACK
        node.color = RED

    def put(self, key, val, node):
        if node is None:
            return Node(key, val)

        if key < node.key:
            node.left = self.put(key, val, node.left)
        elif key > node.key:
            node.right = self.put(key, val, node.right)
        else:
            node.val = val

        if self.__is_red(node.right) and not self.__is_red(node.left):
            node = self.__rotate_left(node)
        if self.__is_red(node.left) and self.__is_red(node.left.left):
            node = self.__rotate_right(node)
        if self.__is_red(node.left) and self.__is_red(node.right):
            self.__flip_colors(node)

        node.size = self.size(node.left) + 1 + self.size(node.right)

        return node

    def __move_red_left(self, node):
        self.__flip_colors(node)
        if self.__is_red(node.right.left):
            node.right = self.__rotate_right(node.right)
            node = self.__rotate_left(node)
        return node

    def __balance(self, node):
        if self.__is_red(node.right):
            node = self.__rotate_left(node)
        return node

    def __delete_min(self, node):
        if node.left is None:
            return None

        if not self.__is_red(node.left) and not self.__is_red(node.left.left):
            node = self.__move_red_left(node)

        node.left = self.__delete_min(node.left)
        return self.__balance(node)

    def delete_min(self):
        if not self.__is_red(self.root.left) and not self.__is_red(self.root.right):
            self.root.color = RED
        self.root = self.__delete_min(self.root)
        if self.root:
            self.root.color = BLACK

    def __delete(self, key, node):
        if key < node.key:
            if not self.__is_red(node.left) and not self.__is_red(node.left.left):
                node = self.__move_red_left(node)
            node.left = self.__delete(key, node.left)
        else:
            if self.__is_red(node.left):
                node = self.__rotate_right(node)
            if key == node.key and node.right is None:
                return None
            if not self.__is_red(node.right) and not self.__is_red(node.right.left):
                node = self.__move_red_left(node)
            if key == node.key:
                node.val = self.get(min(node.right).key, node.right)  # TODO: implement this
                node.key = min(node.right).key
                node.right = self.__delete_min(node.right)
            else:
                node.right = self.__delete(key, node.right)

        return self.__balance(node)

    def delete(self, key):
        if not self.__is_red(self.root.left) and not self.__is_red(self.root.right):
            self.root.color = RED
        self.root = self.__delete(key, self.root)
        if self.root:
            self.root.color = BLACK
