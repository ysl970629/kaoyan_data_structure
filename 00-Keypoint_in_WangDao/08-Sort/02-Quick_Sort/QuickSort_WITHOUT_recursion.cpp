#include <iostream>
#include <stack>
using namespace std;

// 划分算法
int partition(int A[], int low, int high) {
	// 假设每次都以第一个元素作为枢轴值，进行一趟划分：
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) high--;
		A[low] = A[high]; // 停下来做交换
		while (low < high && A[low] <= pivot) low++;
		A[high] = A[low]; // 停下来做交换
	}
	A[low] = pivot; // pivot的最终落点
	return low;
}

// 非递归快排
void quickSort(int A[], int low, int high) {
	// 手动利用栈来存储每次分块快排的起始点
	// 栈非空时循环获取中轴入栈
	stack<int> S;
	if (low < high) {
		int _part = partition(A, low, high);
		if (_part - 1 > low) {  // 确保左分区存在
			// 将左分区端点入栈
			S.push(low);
			S.push(_part - 1);
		}
		if (_part + 1 < high) {  // 确保右分区存在
			S.push(_part + 1);
			S.push(high);
		}
		while (!S.empty()) {
			// 得到某分区的左右边界
			int _high = S.top();
			S.pop();
			int _low = S.top();
			S.pop();

			_part = partition(A, _low, _high);
			if (_part - 1 > _low) {  // 确保左分区存在
				// 将左分区端点入栈
				S.push(_low);
				S.push(_part - 1);
			}
			if (_part + 1 < _high) {  //确保右分区存在
				S.push(_part + 1);
				S.push(_high);
			}
		}
	}
}

int main() {
	int A[5] = {44, 18, 55, 44, 21};
	int low = 0, high = 4;
	quickSort(A, low, high);
	//输出，检验结果
	for (int i = 0; i < 5; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}