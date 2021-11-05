#include <stdio.h>  

//寻找a[m...n]中多数元素候选者     
int candidate(int a[], int m, int n)
{
	int j = m, c = a[m], count = 1; //计数器置1 

	while (j < n && count > 0)
	{
		++j;
		if (a[j] == c)
			++count;
		else
			--count;
	}

	if (j == n)
		return c;
	else
		return candidate(a, j + 1, n); //对a[j+1...n]寻找多数元素候选者，即却掉了前面两个不等的值，继续在后面的区间内寻找候选者 
}

//检查候选者是否真的是多数元素
int Majority(int a[], int n)
{
	int c = candidate(a, 1, 10);
	int count = 0;

	for (int i = 1; i <= n; ++i)
	if (a[i] == c)
		++count;

	if (count > n / 2)
		return c;
	else
		return -1;
}

int main()
{
	int a[11];

	for (int i = 1; i < 11; ++i)
		scanf("%d", a + i);

	printf("%d\n", Majority(a, 10));
	getchar();
	getchar();
	return 0;
}