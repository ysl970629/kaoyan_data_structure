#define maxSize 100
typedef int ElemType;
typedef struct {
    ElemType *data;
    int length;
} SqList;

bool deleteList(SqList &L, ElemType s, ElemType t) {
    if (L.length == 0 || s >= t)
        return false;
    int k = 0;
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] >= s && L.data[i] <= t)
            k++;
        else
            L.data[i - k] = L.data[i];
    }
    L.length -= k;
    return true;
}
