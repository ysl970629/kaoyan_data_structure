#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode, *LinkList;

void outPut(LinkList L) {
    LinkNode *p = L->next;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void rearInsert(LinkList &L, ElemType x) {
    LinkNode *s = new LinkNode;
    s->data = x;
    L->next = s;
    L = s;
}

LinkList rearInsertCreate(ElemType arr[], int length) {
    LinkList L = new LinkNode;
    LinkNode *p = L;
    for (int i = 0; i < length; i++)
        rearInsert(p, arr[i]);
    p->next = NULL;
    return L;
}

void reverseList(LinkList &L) {
    LinkNode *p = L->next;
    L->next = NULL;
    while (p != NULL) {
        LinkNode *temp = p->next;
        p->next = L->next;
        L->next = p;
        p = temp;
    }
}

void test(ElemType a[], int length) {
    LinkList L = rearInsertCreate(a, length);
    reverseList(L);
    outPut(L);
}

int main() {
    ElemType arr[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int length = sizeof(arr) / sizeof(int);

    test(arr, length);

    return 0;
}

// 输出结果：
// 9 7 5 3 1 8 6 4 2 0
