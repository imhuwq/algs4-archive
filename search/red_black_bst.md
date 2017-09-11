## 红黑树 (一)

### 红黑树是什么
红黑树是允许每个节点里包含最多两个 Node 的二叉树。

### 红黑树要解决什么问题
普通二叉树最大的问题在于，插入有序的序列会使二叉树会成为 N 的深度。  
红黑树允许每个节点上最多挂两个 Node， 每当第三个 Node 插入的时候， 把中间值的 Node 往上冒泡。  
如果在 root 上有三个 Node， 把中间的 Node 上冒做为新的 root。  
由此可见，红黑树的深度是通过 root 往上冒增加的， 从而保证了每条路径到 root 的深度一致为 lg N。  

### 红黑树的程序表达
红黑树是二叉树的一个变种， 数据结构和大部分行为与二叉树的几乎一样。 
最大的不同是它的 Node 多了一个颜色属性， 颜色为“红”或者“黑”。  
当一个 Node 的颜色为红色时， 可以认为该 Node 和其父 Node 属于同一个节点。  

```python

RED = 1
BLACK = 0

class Node:
    def __init__(self, key, value, color):
        self.key = key
        self.value = value
        if color not in [0, 1]:
            raise AttributeError("color must be 1 for 'RED' or 0 for 'BLACK'")
        self.color = color
        self.size = 1  # node 的子 node 数量，包括自己
        
        self.left = None
        self.right = None
        
    @property
    def is_red(self):
        return self.color == RED
```  
红黑树有这么几个特性：  

1. 根 Node 的颜色为黑色； 
 
2. 红 Node 只能悬在左侧；  

3. 新插入的 Node 的颜色默认为红色。 新插入的 Node 总是倾向于和已有的 Node 挤到同一个节点里；  

4. 每个 Node 只能与一个红 Node 连接（包括自己）。 因为红黑树允许每个节点有最多两个 Node。

红黑树的所有行为都是根据以上四点而来。  

#### 增加 Node
在最开始的情况下， 红黑树只有一个根 Node， 根据特性1， 其颜色为黑色；  
现在插入一个 Node， 根据特性3， 其颜色为红色： 
 - 当它比 Root 小时， 插入位置在 Root 左侧；
 - 当它比 Root 大时， 插入位置在 Root 右侧， 违反特性2， 这时需要把右侧的红 Node 旋转到左侧。
```python
def rotate_left(node):
    """把 node 右侧的 node 旋转到左侧 """
    new_node = node.right
    node.right = new_node.left
    new_node.left = node
    new_node.color = node.color
    node.color = 1  # RED
    new_node.size = node.size
    node.size = 1 + node.left.size + node.right.size

def rotate_right(node):
    """把 node 左侧的 node 旋转到右侧 """
    new_node = node.left
    node.left = new_node.right
    new_node.right = node
    new_node.color = node.color
    node.color = 1  # RED
    new_node.size = node.size
    node.size = 1 + node.left.size + node.right.size
```
再插入第三个 Node， 其颜色为红色。此时可能会出现三种情况：
 - 情况1， 第三个 Node 比 Root 大，和第二个 Node 并列， 这时违反特性4， 此时只需要把各 Node 的颜色翻转；
 - 情况2， 第三个 Node 比 Root 小，比第二个 Node 小， 这时还是违反特性4， 此时把 Root 右旋得到情况1， 再相应处理；
 - 情况3， 第三个 Node 比 Root 小，比第二个 Node 大， 仍然违反特性4， 此时把第二个 Node 左旋得到情况2， 再相应处理；
 
```python
def flip_color(node):
    """把 node 及其子 node 的颜色翻转"""
    node.left.color = 0  # BLACK
    node.right.color = 0  # BLACK
    node.color = 1  # RED
```
把一个 node 的颜色变成红色， 其实就是在把它往上挤。 `flip_color` 其实是在把挤在一个节点里的三个 Node 的中间那个往上冒泡。  
需要注意的是， Root 的颜色需要始终为黑色。  

以上几个例子覆盖了所有的新增 Node 时需要处理的情况。  
```python

RED = 1
BLACK = 0

class Node:
    def __init__(self, key, value, color):
        self.key = key
        self.value = value
        if color not in [0, 1]:
            raise AttributeError("color must be 1 for 'RED' or 0 for 'BLACK'")
        self.color = color
        self.size = 1  # node 的子 node 数量，包括自己
        
        self.left = None
        self.right = None
        
    @property
    def is_red(self):
        return self.color == RED

 
class RedBlackBST:
    def __init__(self, root_node=None):
        self._root = root_node
    
    @property
    def root(self):
        return self._root
    
    @root.setter
    def root(self, value):
        if value is None:
            return 
        assert isinstance(value, Node)
        self._root = value
        self._root.color = BLACK
    
    @staticmethod   
    def rotate_left(node):
        """把 node 右侧的 node 旋转到左侧 """
        new_node = node.right
        node.right = new_node.left
        new_node.left = node
        new_node.color = node.color
        node.color = RED
        new_node.size = node.size
        node.size = 1 + node.left.size + node.right.size
        return node

    @staticmethod   
    def rotate_right(node):
        """把 node 左侧的 node 旋转到右侧 """
        new_node = node.left
        node.left = new_node.right
        new_node.right = node
        new_node.color = node.color
        node.color = RED
        new_node.size = node.size
        node.size = 1 + node.left.size + node.right.size
        return node

    @staticmethod       
    def flip_color(node):
        """把 node 及其子 node 的颜色翻转"""
        node.left.color = BLACK
        node.right.color = BLACK
        node.color = RED
        return node
    
    @staticmethod
    def is_red(node):
        if node is None:
            return False
        return node.is_red
    
    def _put(self, key, value, node):
        if node is None:
            return Node(key, value, BLACK)
        
        if key < node.key:
            node.left = self._put(key, value, node.left)
        elif key > node.key:
            node.right = self._put(key, value, node.right)
        else:
            node.value = value
        
        if not node.left.is_red and node.right.is_red:
            node = RedBlackBST.rotate_left(node)
        if node.left.is_red and node.left.left.is_red:
            node = RedBlackBST.rotate_right(node)
        if node.left.is_red and node.right.is_red:
            node = RedBlackBST.flip_color(node)
        node.size = node.left.size + node.right.size + 1
        return node
        
    def put(self, key, value):
        self.root = self._put(key, value, self.root)
```