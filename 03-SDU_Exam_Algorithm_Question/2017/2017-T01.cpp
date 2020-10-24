#include <iostream>
#include <stack>
using namespace std;

typedef int ElemType;

void outPut(ElemType *A, int length) {
    for (int i = 0; i < length; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void swap(ElemType *A, int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void reverseOddAndEven(ElemType a[], int length) {
    stack<ElemType> s;
    int k = 0;
    for (int i = 0; i < length; i++) {
        // 如果是奇数，就留下
        // 如果是偶数，就暂存
        if (a[i] % 2 == 1)
            a[i - k] = a[i];
        else {
            s.push(a[i]);
            k++;
        }
    }
    for (int i = length - 1; i >= 0 && !s.empty(); i--) {
        a[i] = s.top();
        s.pop();
    }
}

void test(ElemType a[], int length) {
    reverseOddAndEven(a, length);
    outPut(a, length);
}

int main() {
    ElemType A[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int length = sizeof(A) / sizeof(int);
    test(A, length);
    return 0;
}

// 输出结果：
// 1 3 5 7 9 0 2 4 6 8