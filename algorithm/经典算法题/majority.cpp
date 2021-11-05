#include <stdio.h>  

//Ѱ��a[m...n]�ж���Ԫ�غ�ѡ��     
int candidate(int a[], int m, int n)
{
	int j = m, c = a[m], count = 1; //��������1 

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
		return candidate(a, j + 1, n); //��a[j+1...n]Ѱ�Ҷ���Ԫ�غ�ѡ�ߣ���ȴ����ǰ���������ȵ�ֵ�������ں����������Ѱ�Һ�ѡ�� 
}

//����ѡ���Ƿ�����Ƕ���Ԫ��
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