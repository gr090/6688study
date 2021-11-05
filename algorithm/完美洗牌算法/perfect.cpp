#include <iostream>
using namespace std;

class Solution {
public:
	// ����ϴ���㷨
	void PerfectShuffle(int *a, int n){
		while (n >= 1){
			// ���㻷�ĸ���
			int k = 0;
			// 3^1
			int r = 3;
			// 2 * m  = 3^k - 1
			// m <= n  ->  2 * m <= 2 * n  -> 3^k - 1 <= 2 * n
			// Ѱ������kʹ��3^k - 1 <= 2*n
			while (r - 1 <= 2 * n){
				r *= 3;
				++k;
			}//while
			int m = (r / 3 - 1) / 2;
			// ѭ������n-mλ
			LeftRotate(a + m, n - m, n);
			// k���� ����ʼλ��start: 1,3...3^(k-1)
			for (int i = 0, start = 1; i < k; ++i, start *= 3) {
				// ��Ȧ
				CycleLeader(a, start, m);
			}//for
			a += 2 * m;
			n -= m;
		}
	}
private:
	// ��ת start ��ʼλ�� end ����λ��
	void Reverse(int *a, int start, int end){
		while (start < end){
			swap(a[start], a[end]);
			++start;
			--end;
		}//while
	}
	// ѭ������mλ n���鳤�� �±��1��ʼ
	void LeftRotate(int *a, int m, int n){
		// ��תǰmλ
		Reverse(a, 1, m);
		// ��תʣ��Ԫ��
		Reverse(a, m + 1, n);
		// ���巭ת
		Reverse(a, 1, n);
	}
	// ��Ȧ�㷨
	void CycleLeader(int *a, int start, int n) {
		int pre = a[start];
		// 2 * i % (2 * n + 1)
		int mod = 2 * n + 1;
		// ʵ��λ��
		int next = start * 2 % mod;
		// �����ƶ�λ��
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