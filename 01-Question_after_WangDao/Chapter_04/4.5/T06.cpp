#include <iostream>
using namespace std;

typedef int ElemType;  // 把char强制转换成int。这样我可以使用上面写的测试用例，不然我还得重新写

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTNode *construct(ElemType *preOrder, ElemType *midOrder, int len) {
    if (preOrder == NULL || midOrder == NULL || len <= 0)
        return NULL;
    //先根遍历（前序遍历）的第一个值就是根节点的键值
    ElemType rootKey = preOrder[0];
    BiTree T = new BiTNode;
    T->data = rootKey;
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
    if (leftLen > 0) //构建左子树
        T->lchild = construct(preOrder + 1, midOrder, leftLen);
    if (len - leftLen - 1 > 0) //构建右子树
        T->rchild = construct(preOrder + leftLen + 1, rootMidOrder + 1, len - leftLen - 1);
    return T;
}

void visit(BiTree T) {
    std::cout << T->data << " ";
}

void PostOrder(BiTree T) {
    if (T == NULL)
        return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    visit(T);
}

void InOrder(BiTree T) {
    if (T == NULL)
        return;
    InOrder(T->lchild);
    visit(T);
    InOrder(T->rchild);
}

void PreOrder(BiTree T) {
    if (T == NULL)
        return;
    visit(T);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

bool getNodeByValue(BiTree T, ElemType value, BiTNode *&result) {
    if (T == NULL)
        return false;
    if (T->data == value) {
        result = T;
        return true;
    }
    if (getNodeByValue(T->lchild, value, result) == true)
        return true;
    else
        return getNodeByValue(T->rchild, value, result);
}

ElemType pre = -99999;  // 负无穷大
bool isBST(BiTree T) {  //基于中序遍历
    if (T == NULL)
        return true;
    int left = isBST(T->lchild);
    if (left == 0 || pre >= T->data)
        return false;
    pre = T->data;
    return isBST(T->rchild);
}

bool isBSTEntry(BiTree T) {
    pre = -99999;
    return isBST(T);
}

void test(ElemType *preOrder, ElemType *inOrder, int length) {
    BiTree T = construct(preOrder, inOrder, length);

    PreOrder(T);
    cout << endl;

    InOrder(T);
    cout << endl;

    PostOrder(T);
    cout << endl;

    cout << endl;
    // 在此处写要测试的函数...
    if (isBSTEntry(T))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    cout <<"--------------------------" << endl;
}

int main() {
    // BST树
    ElemType preOrder1[] = {54, 20, 40, 28, 66, 79};
    ElemType inOrder1[] = {20, 28, 40, 54, 66, 79};
    int length1 = sizeof(preOrder1) / sizeof(preOrder1[0]);

    // 非BST树
    ElemType preOrder2[] = {'B', 'E', 'F', 'C', 'G', 'D', 'H'};
    ElemType inOrder2[] = {'F', 'E', 'B', 'G', 'C', 'H', 'D'};
    int length2 = sizeof(preOrder2) / sizeof(preOrder2[0]);

    test(preOrder1, inOrder1, length1);

    test(preOrder2, inOrder2, length2);

    return 0;
}

// 运行结果：
// 54 20 40 28 66 79
// 20 28 40 54 66 79
// 28 40 20 79 66 54

// true
// --------------------------
// 66 69 70 67 71 68 72
// 70 69 66 71 67 72 68
// 70 69 71 72 68 67 66

// false
// --------------------------
