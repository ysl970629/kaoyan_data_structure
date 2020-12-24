# 堆和二叉排序树的区别

> 王道课后题7.4 T01

关键在中序遍历：

**BST中序遍历，一定有序**
堆中序遍历，不一定有序

并且堆可以有重复元素，但是**BST不能有重复元素**。

可以参考BST的结点插入代码。当有重复结点插入时，会什么都不做直接返回。

![IMG_0291](../../../sources/00-Keypoint_in_WangDao/Chapter_05-Tree/00-Binary_Tree/IMG_0291.JPG)
