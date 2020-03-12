## AVL树

### 1 二叉查找树的一些特点

1、若它的左子树不为空，则左子树上所有的节点值都小于它的根节点值。

2、若它的右子树不为空，则右子树上所有的节点值均大于它的根节点值。

3、它的左右子树也分别可以充当为二叉查找树。

例如：

![图1](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/1.jpg?raw=true)

这种数据结构可以让我们快速找到想要查找的值。

例如，我现在想要查找数值为14的节点。由于二叉查找树的特性，我们可以很快着找到它，其过程如下：

1、和根节点9比较

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/2.jpg?raw=true)

2、由于 14 > 9，所以14只可能存在于9的右子树中，因此查看右孩子13

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/3.jpg?raw=true)

3、由于 14 > 13，所以继续查看13的右孩子15

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/4.jpg?raw=true)

4、由于 14 < 15，所以14只可能存在于15的左孩子中，因此查找15的左孩子14

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/5.jpg?raw=true)

5、这时候发现14正是自己查找的值，于是查找结束。

这种查找二叉树的查找正是**二分查找**的思想，可以很快着找到目的节点，查找所需的最大次数等同于二叉查找树的高度。

在插入的时候也是一样，通过一层一层的比较，最后找到适合自己的位置。

当然，查找二叉树存在一些缺陷：

初始的二叉查找树只有三个节点：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/6.jpg?raw=true)

然后我们按照顺序陆续插入节点 4，3，2，1，0。插入之后的结构如下：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/7.jpg?raw=true)

所有的节点都倾向于一边了，这种形态的二叉树查找树在查找的性能上，就大打折扣了，几乎变成了线性链表。

所以我们因此引入了AVL平衡树。这种树就可以帮助我们解决二叉查找树刚才的那种所有节点都倾向一边的缺点的。具有如下特性：

1. 具有二叉查找树的全部特性。
2. 每个节点的左子树和右子树的高度差至多等于1。

例如：图一就是一颗AVL树了，而图二则不是(节点右边标的是这个节点的高度)。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/8.jpg?raw=true)

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/9.jpg?raw=true)

对于图二，因为节点9的左孩子高度为2，而右孩子高度为0。他们之间的差值超过1了。这种树就可以保证不会出现大量节点偏向于一边的情况了。

可以对于图1，如果我们要插入一个节点3，按照查找二叉树的特性，我们只能把3作为节点4的左子树插进去，可是插进去之后，又会破坏了AVL树的特性，那我们那该怎么弄？

> 右旋

我们在进行节点插入的时候，可能会出现节点都倾向于左边的情况，例如：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/10.jpg?raw=true)

我们把这种倾向于左边的情况称之为 **左-左型**。这个时候，我们就可以对节点9进行**右旋操作**，使它恢复平衡。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/11.jpg?raw=true)

**即：顺时针旋转两个节点，使得父节点被自己的左孩子取代，而自己成为自己的右孩子**

再举个例子：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/12.jpg?raw=true)

节点4和9高度相差大于1。由于是**左孩子的高度较高**，此时是**左-左型**，进行右旋。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/13.jpg?raw=true)

**这里要注意，节点4的右孩子成为了节点6的左孩子了**

我找了个动图，尽量这个动图和上面例子的节点不一样。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/14.gif?raw=true)

> 左旋

左旋和右旋一样，就是用来解决当大部分节点都偏向右边的时候，通过左旋来还原。例如：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/15.jpg?raw=true)

我们把这种倾向于右边的情况称之为 **右-右型**。

我也找了一张动图。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/16.gif?raw=true)

### 2 一个实例，覆盖了所有情况

初始状态如下：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/17.jpg?raw=true)

然后我们主键插入如下数值：1,4,5,6,7,10,9,8

插入 1

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/18.jpg?raw=true)

左-左型，需要右旋调整。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/19.jpg?raw=true)

插入4

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/20.jpg?raw=true)

继续插入 5

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/21.jpg?raw=true)

右-右型，需要左旋转调整。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/22.jpg?raw=true)

继续插入6

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/23.jpg?raw=true)

右-右型，需要进行左旋

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/24.jpg?raw=true)

继续插入7

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/25.jpg?raw=true)

右-右型，需要进行左旋

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/26.jpg?raw=true)

继续插入10

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/27.jpg?raw=true)

继续插入9

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/28.jpg?raw=true)

出现了这种情况怎么办呢?对于这种  **右-左型** 的情况，单单一次左旋或右旋是不行的，下面我们先说说如何处理这种情况。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/29.jpg?raw=true)

这种称之为右-左型。处理的方法是**先对节点10进行右旋把它变成右-右型。**

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/30.jpg?raw=true)

然后在进行左旋。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/31.jpg?raw=true)

所以对于这种 **右-左型的，我们需要进行一次右旋再左旋**。

同理，也存在 **左-右型**的，例如：

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/32.jpg?raw=true)

对于左-右型的情况和刚才的 右-左型相反，我们需要对它进行一次左旋，再右旋。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/33.jpg?raw=true)

回到刚才那道题

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/34.jpg?raw=true)

对它进行右旋再左旋。

![img](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/35.jpg?raw=true)

到此，我们的插入就结束了。

### 3 总结

在插入的过程中，会出现一下四种情况破坏AVL树的特性，我们可以采取如下相应的旋转。

1、左-左型：做右旋。

2、右-右型：做左旋转。

3、左-右型：先做左旋，后做右旋。

4、右-左型：先做右旋，再做左旋。

### 4 代码实现

```java
//定义节点
class AvlNode {
	int data;
	AvlNode lchild;//左孩子
	AvlNode rchild;//右孩子
	int height;//记录节点的高度
}

//在这里定义各种操作
public class AVLTree{
	//计算节点的高度
	static int height(AvlNode T) {
		if (T == null) {
			return -1;
		}else{
			return T.height;
		}
	}

	//左左型，右旋操作
	static AvlNode R_Rotate(AvlNode K2) {
		AvlNode K1;
		
		//进行旋转
		K1 = K2.lchild;
		K2.lchild = K1.rchild;
		K1.rchild = K2;

		//重新计算节点的高度
		K2.height = Math.max(height(K2.lchild), height(K2.rchild)) + 1;
		K1.height = Math.max(height(K1.lchild), height(K1.rchild)) + 1;

		return K1;
	}

	//进行左旋
	static AvlNode L_Rotate(AvlNode K2) {
		AvlNode K1;

		K1 = K2.rchild;
		K2.rchild = K1.lchild;
		K1.lchild = K2;

		//重新计算高度
		K2.height = Math.max(height(K2.lchild), height(K2.rchild)) + 1;
		K1.height = Math.max(height(K1.lchild), height(K1.rchild)) + 1;

		return K1;
	}

	//左-右型，进行右旋，再左旋
	static AvlNode R_L_Rotate(AvlNode K3) {
		//先对其孩子进行左旋
		K3.lchild = R_Rotate(K3.lchild);
		//再进行右旋
		return L_Rotate(K3);
	}

	//右-左型，先进行左旋，再右旋
	static AvlNode L_R_Rotate(AvlNode K3) {
		//先对孩子进行左旋
		K3.rchild = L_Rotate(K3.rchild);
		//在右旋
		return R_Rotate(K3);
	}

	//插入数值操作
	static AvlNode insert(int data, AvlNode T) {
		if (T == null) {
			T = new AvlNode();
			T.data = data;
			T.lchild = T.rchild = null;
		} else if(data < T.data) {
			//向左孩子递归插入
			T.lchild = insert(data, T.lchild);
			//进行调整操作
			//如果左孩子的高度比右孩子大2
			if (height(T.lchild) - height(T.rchild) == 2) {
				//左-左型
				if (data < T.lchild.data) {
					T = R_Rotate(T);
				} else {
					//左-右型
					T = R_L_Rotate(T);
				}
			}
		} else if (data > T.data) {
			T.rchild = insert(data, T.rchild);
			//进行调整
			//右孩子比左孩子高度大2
			if(height(T.rchild) - height(T.lchild) == 2)
				//右-右型
			if (data > T.rchild.data) {
				T = L_Rotate(T);
			} else {
				T = L_R_Rotate(T);
			}
		}
		//否则，这个节点已经在书上存在了，我们什么也不做
       
		//重新计算T的高度
		T.height = Math.max(height(T.lchild), height(T.rchild)) + 1;
		return T;
	}
}
```

### AVL树效率

查找节点：时间复杂度为O(logN)

插入节点：因为需要先查找到节点，然后进行旋转平衡操作（基本为1），所以也为O(logN)

删除节点：再查找到节点之后，还需要检查从删除节点到根节点的平衡因子，所以时间复杂度为O(logN)