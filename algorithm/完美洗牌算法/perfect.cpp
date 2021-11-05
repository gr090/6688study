#include <iostream>
using namespace std;

class Solution {
public:
	// 完美洗牌算法
	void PerfectShuffle(int *a, int n){
		while (n >= 1){
			// 计算环的个数
			int k = 0;
			// 3^1
			int r = 3;
			// 2 * m  = 3^k - 1
			// m <= n  ->  2 * m <= 2 * n  -> 3^k - 1 <= 2 * n
			// 寻找最大的k使得3^k - 1 <= 2*n
			while (r - 1 <= 2 * n){
				r *= 3;
				++k;
			}//while
			int m = (r / 3 - 1) / 2;
			// 循环左移n-m位
			LeftRotate(a + m, n - m, n);
			// k个环 环起始位置start: 1,3...3^(k-1)
			for (int i = 0, start = 1; i < k; ++i, start *= 3) {
				// 走圈
				CycleLeader(a, start, m);
			}//for
			a += 2 * m;
			n -= m;
		}
	}
private:
	// 翻转 start 开始位置 end 结束位置
	void Reverse(int *a, int start, int end){
		while (start < end){
			swap(a[start], a[end]);
			++start;
			--end;
		}//while
	}
	// 循环右移m位 n数组长度 下标从1开始
	void LeftRotate(int *a, int m, int n){
		// 翻转前m位
		Reverse(a, 1, m);
		// 翻转剩余元素
		Reverse(a, m + 1, n);
		// 整体翻转
		Reverse(a, 1, n);
	}
	// 走圈算法
	void CycleLeader(int *a, int start, int n) {
		int pre = a[start];
		// 2 * i % (2 * n + 1)
		int mod = 2 * n + 1;
		// 实际位置
		int next = start * 2 % mod;
		// 按环移动位置
		while (next != start){
			swap(pre, a[next]);
			next = 2 * next % mod;
		}//while
		a[start] = pre;
	}
};


int main() {
	Solution solution;
	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	solution.PerfectShuffle(A, 6);
	for (int i = 1; i <= 12; ++i){
		cout << A[i] << " ";
	}//for
	cout << endl;
	system("pause");
}