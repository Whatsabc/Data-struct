## AVL树

### 1 二叉查找树的一些特点

1、若它的左子树不为空，则左子树上所有的节点值都小于它的根节点值。

2、若它的右子树不为空，则右子树上所有的节点值均大于它的根节点值。

3、它的左右子树也分别可以充当为二叉查找树。

例如：

![avatar](https://github.com/whatsabc/data-structure-practice/blob/master/4%20tree%20and%20binary%20tree/AVL%20tree/img/1.jpg?raw=true)

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

对于图二，因为节点9的左孩子高度为2，而右孩子高度为0。他们之间的差值超过1了。

这种树就可以保证不会出现大量节点偏向于一边的情况了。

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

