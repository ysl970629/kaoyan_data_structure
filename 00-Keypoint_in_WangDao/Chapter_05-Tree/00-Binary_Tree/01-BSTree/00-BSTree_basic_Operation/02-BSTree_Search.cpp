#include <iostream>
using namespace std;

typedef int ElemType;  // 把char强制转换成int。这样我可以使用上面写的测试用例，不然我还得重新写

typedef struct BSTNode {
    ElemType key;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

BSTNode *construct(ElemType *preOrder, ElemType *midOrder, int len) {
    if (preOrder == NULL || midOrder == NULL || len <= 0)
        return NULL;
    //先根遍历（前序遍历）的第一个值就是根节点的键值
    ElemType rootKey = preOrder[0];
    BSTree T = new BSTNode;
    T->key = rootKey;
    T->lchild = T->rchild = NULL;
    if (len == 1 && *preOrder == *midOrder)  //只有一个节点
        return T;
    //在中根遍历（中序遍历）中找到根节点的值
    ElemType *rootMidOrder = midOrder;
    int leftLen = 0;  //左子树节点数
    while (*rootMidOrder != rootKey && rootMidOrder <= (midOrder + len - 1)) {
        ++rootMidOrder;
        ++leftLen;
    }
    if (*rootMidOrder != rootKey)  //在中根序列未找到根节点,输入错误
        return NULL;
    if (leftLen > 0)  //构建左子树
        T->lchild = construct(preOrder + 1, midOrder, leftLen);
    if (len - leftLen - 1 > 0)  //构建右子树
        T->rchild = construct(preOrder + leftLen + 1, rootMidOrder + 1, len - leftLen - 1);
    return T;
}

void visit(BSTree T) {
    std::cout << T->key << " ";
}

void PostOrder(BSTree T) {
    if (T == NULL)
        return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    visit(T);
}

void InOrder(BSTree T) {
    if (T == NULL)
        return;
    InOrder(T->lchild);
    visit(T);
    InOrder(T->rchild);
}

void PreOrder(BSTree T) {
    if (T == NULL)
        return;
    visit(T);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

// 非递归
BSTNode *BSTreeSearch(BSTree T, int key) {
    while (T != NULL) {
        if (T->key == key)
            break;
        if (T->key < key)
            T = T->rchild;
        else
            T = T->lchild;
    }
    return T;
}

// 递归
BSTNode *BSTreeSearchRecurrence(BSTree T, int key) {
    if (T == NULL)
        return NULL;
    if (T->key == key)
        return T;
    return (T->key < key) ? BSTreeSearchRecurrence(T->rchild, key) : BSTreeSearchRecurrence(T->lchild, key);
}

void test(ElemType *preOrder, ElemType *inOrder, int length, ElemType k, int index) {
    BSTree T = construct(preOrder, inOrder, length);

    PreOrder(T);
    cout << endl;

    InOrder(T);
    cout << endl;

    PostOrder(T);
    cout << endl;

    cout << endl;
    // 在此处写要测试的函数...
    BSTNode *result = NULL;
    if (index == 0)
        result = BSTreeSearch(T, k);
    else if (index == 1)
        result = BSTreeSearchRecurrence(T, k);
    if (result == NULL)
        cout << "NULL" << endl;
    else
        cout << result->key << endl;

    cout << endl;
    cout << "--------------------------" << endl;
}

int main() {
    // BST树
    ElemType preOrder1[] = {54, 20, 40, 28, 66, 79};
    ElemType inOrder1[] = {20, 28, 40, 54, 66, 79};
    int length1 = sizeof(preOrder1) / sizeof(preOrder1[0]);

    // 非BST树
    // ElemType preOrder2[] = {'B', 'E', 'F', 'C', 'G', 'D', 'H'};
    // ElemType inOrder2[] = {'F', 'E', 'B', 'G', 'C', 'H', 'D'};
    // int length2 = sizeof(preOrder2) / sizeof(preOrder2[0]);

    ElemType k1 = 66;
    test(preOrder1, inOrder1, length1, k1, 0);
    test(preOrder1, inOrder1, length1, k1, 1);
    ElemType k2 = 19;
    test(preOrder1, inOrder1, length1, k2, 0);
    test(preOrder1, inOrder1, length1, k2, 1);

    // test(preOrder2, inOrder2, length2);

    return 0;
}

// 运行结果：
// 54 20 40 28 66 79
// 20 28 40 54 66 79
// 28 40 20 79 66 54

// 66

// --------------------------
// 54 20 40 28 66 79
// 20 28 40 54 66 79
// 28 40 20 79 66 54

// 66

// --------------------------
// 54 20 40 28 66 79
// 20 28 40 54 66 79
// 28 40 20 79 66 54

// NULL

// --------------------------
// 54 20 40 28 66 79
// 20 28 40 54 66 79
// 28 40 20 79 66 54

// NULL

// --------------------------
