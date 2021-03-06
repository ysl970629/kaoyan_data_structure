// 2020-10-28
#include <string.h>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef int ElemType;
typedef struct {
    int number;  // 顶点的编号，这一项用户不能自己定义，是固定的从1开始的数字
    ElemType data;  // 顶点信息。这一项是从用户输入的vertex数组中写入的，并不要求非要int型，也可以是A，B，C这种
} VertexType;  // 上面这两项，在遍历的时候不会打印。但是真实存在，用于对结点信息进行补充描述

typedef struct {
    VertexType *vertex;
    int **edge;
    int vexnum, arcnum;
} Matrix, *MatrixGraph;

void outputEdge(MatrixGraph G) {
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++)
            cout << *(*(G->edge + i) + j) << " ";  // 虽然是二维数组，但是按照一维的方式遍历，只是需要解引用两层
        cout << endl;
    }
}

// 初始化邻接矩阵
void initMatrixGraph(MatrixGraph &G, int vexnum) {
    G->vexnum = vexnum;
    G->arcnum = 0;
    G->vertex = new VertexType[G->vexnum];
    for (int i = 0; i < G->vexnum; i++) {
        G->vertex[i].number = i;
        // G->vertex[i].info = NULL;  // 可选，因为在下面的函数中，会再次赋值
    }
    G->edge = new int *[G->vexnum];
    for (int i = 0; i < G->vexnum; i++) {
        G->edge[i] = new int[G->vexnum];
        memset(G->edge[i], 0, sizeof(int) * (G->vexnum));
    }
}

// 通过一个一维顶点数组和一个二维边数组得到一个邻接矩阵图
MatrixGraph createMatrix(ElemType *vertex, int vexnum, int *edge) {
    MatrixGraph G = new Matrix;
    initMatrixGraph(G, vexnum);
    for (int i = 0; i < vexnum; i++)
        G->vertex[i].data = vertex[i];
    for (int i = 0; i < vexnum; i++) {
        for (int j = 0; j < vexnum; j++) {
            if (edge[i * vexnum + j] != 0) {
                G->edge[i][j] = edge[i * vexnum + j];  // 将一维数组edge的值按照二维数组的方式输入到G->edge
                G->arcnum++;
            }
        }
    }
    return G;
}

// 返回的是二维数组的下标值。如果需要返回顶点，需要 + 1
int FirstNeighbor(MatrixGraph G, int v) {
    int i, flag = -1;
    for (i = 0; i < G->vexnum; i++) {
        if (*(*(G->edge + v) + i) != 0) {
            flag = 1;
            break;
        }
    }
    return (flag == -1) ? flag : i;
}

// 返回的是二维数组的下标值。如果需要返回顶点，需要 + 1
int NextNeighbor(MatrixGraph G, int v, int w) {
    int i, flag = -1;
    for (i = w + 1; i < G->vexnum; i++) {
        if (*(*(G->edge + v) + i) != 0) {
            flag = 1;
            break;
        }
    }
    return (flag == -1) ? flag : i;
}

// 距离顶点v的最后一个顶点，就是BFS的最后一个顶点
int *visited;
stack<int> s;

void visit(int v) {
    s.push(v + 1);  // 这里由于要得到的是顶点的名称，而不是顶点的下标，因此要加1。比如，顶点名称为3的下标其实是2，实际操作都是以2操作的，真正遍历的时候要恢复为3
}

void BFS(MatrixGraph G, int v0) {
    queue<int> q;
    visit(v0);
    visited[v0] = 1;
    q.push(v0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                visit(w);
                visited[w] = 1;
                q.push(w);
            }
        }
    }
}

// 清空栈
// https://blog.csdn.net/ShellDawn/article/details/80014842
void stackClean() {
    stack<int>().swap(s);
}

int getTheFarestVertex(MatrixGraph G, int v0) {
    stackClean();
    visited = new int[G->vexnum];
    memset(visited, 0, sizeof(int) * G->vexnum);
    BFS(G, v0);
    return s.top();
}

void test(ElemType *vertex, int vexnum, int *edge, int V0) {
    int v0 = V0 - 1;  // 根据顶点名称获取顶点的下标
    MatrixGraph G = createMatrix(vertex, vexnum, edge);
    cout << getTheFarestVertex(G, v0) << endl;
}

int main() {
    ElemType vertex[] = {1, 2, 3, 4, 5, 6, 7};
    int vexnum = sizeof(vertex) / sizeof(ElemType);
    int edge[] = {
        0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0,
        0, 0, 1, 0, 0, 1, 1,
        0, 0, 0, 1, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0};

    test(vertex, vexnum, edge, 1);
    test(vertex, vexnum, edge, 2);
    test(vertex, vexnum, edge, 3);
    test(vertex, vexnum, edge, 4);
    test(vertex, vexnum, edge, 5);
    test(vertex, vexnum, edge, 6);
    test(vertex, vexnum, edge, 7);

    return 0;
}

// 输出结果：
// 7
// 5
// 7
// 5
// 6
// 7
// 7
