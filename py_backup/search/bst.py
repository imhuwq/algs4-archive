from py_backup.utils import is_sorted, numbers


class Node:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.size = 1
        self.left = None
        self.right = None


class BST:
    @staticmethod
    def size(node):
        if node is None:
            return 0
        return node.size

    @classmethod
    def get(cls, of_key, from_node):
        """ get value of key from node """

        if from_node is None:
            return None

        if of_key < from_node.key:
            return cls.get(of_key, from_node.left)
        elif of_key > from_node.key:
            return cls.get(of_key, from_node.right)
        else:
            return from_node.val

    @classmethod
    def put(cls, value, key, node):
        """ put value of key into node """

        if node is None:
            return Node(key, value)

        if key < node.key:
            node.left = cls.put(value, key, node.left)
        elif key > node.key:
            node.right = cls.put(value, key, node.right)
        else:
            node.val = value

        node.size = cls.size(node.left) + cls.size(node.right) + 1
        return node

    @classmethod
    def max(cls, node):
        if node.right is None:
            return node
        return cls.max(node.right)

    @classmethod
    def min(cls, node):
        if node.left is None:
            return node
        return cls.min(node.left)

    @classmethod
    def floor(cls, key, node):
        """ get the node of the largest key in the BST smaller than or equal to the key """
        if node is None:
            return None

        if key == node.key:
            return node
        if key < node.key:
            return cls.floor(key, node.left)

        possible_node = cls.floor(key, node.right)
        if possible_node is not None:
            return possible_node
        return node

    @classmethod
    def ceil(cls, key, node):
        """ get the node of the smallest key in the BST larger than or equal to the key """
        if node is None:
            return None

        if key == node.key:
            return node
        elif key > node.key:
            return cls.ceil(key, node.right)

        possible_node = cls.ceil(key, node.left)
        if possible_node is not None:
            return possible_node
        return node

    @classmethod
    def select(cls, rank, node):
        if node is None:
            return None

        size = cls.size(node)
        if size == rank:
            return node
        elif size > rank:
            return cls.select(rank, node.left)
        else:
            return cls.select(rank - size - 1, node.right)

    @classmethod
    def rank(cls, key, node):
        if node is None:
            return 0

        if key == node.key:
            return cls.size(node.left)
        elif key < node.key:
            return cls.rank(key, node.left)
        else:
            return cls.size(node.left) + 1 + cls.rank(key, node.right)

    @classmethod
    def delete_min(cls, node):
        if node is None:
            return None

        if node.left is None:
            return node.right
        node.left = cls.delete_min(node.left)
        node.size = cls.size(node.left) + 1 + cls.size(node.right)
        return node

    @classmethod
    def delete(cls, key, node):
        if node is None:
            return None

        if key < node.key:
            node.left = cls.delete(key, node.left)
        elif key > node.key:
            node.right = cls.delete(key, node.right)
        else:
            node_cache = node
            node = cls.min(node.right)
            node.left = node_cache.left
            node.right = cls.delete_min(node_cache.right)
        node.size = cls.size(node.left) + 1 + cls.size(node.right)
        return node

    @classmethod
    def range(cls, start, stop, node, result):
        if node is None:
            return

        if start < node.key:
            cls.range(start, stop, node.left, result)

        if start <= node.key <= stop:
            result.append(node.key)

        if stop > node.key:
            cls.range(start, stop, node.right, result)


if __name__ == "__main__":
    print(numbers)
    root = Node(numbers[0], numbers[0])
    for index, number in enumerate(numbers[1:]):
        BST.put(number, number, root)

    ordered = list()
    min_num = min(numbers)
    max_num = max(numbers)

    BST.range(min_num, max_num, root, ordered)
    print(ordered)
    print(is_sorted(numbers, ordered))
    print(BST.size(root))
