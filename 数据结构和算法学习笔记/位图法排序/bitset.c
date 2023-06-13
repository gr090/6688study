#include <stdio.h>
#define MAX 10000000
#define SHIFT 5           
#define MASK 0x1F
#define DIGITS 32


int a[1 + MAX / DIGITS];

void set(int n)                                //���߼�λ��Ϊn�Ķ�����λ��Ϊ1 
{
	a[n >> SHIFT] |= (1 << (n&MASK));               //n>>SHIFT����5λ�൱�ڳ���32�����ֽ�λ�ã�n&MASK�൱�ڶ�32ȡ�༴��λλ�ã�
}

void clear(int n)
{
	a[n >> SHIFT] &= (~(1 << (n&MASK)));           //���߼�λ��Ϊn�Ķ�����λ��Ϊ0
}

int test(int n)
{
	return a[n >> SHIFT] & (1 << (n&MASK));        //�����߼�λ��Ϊn�Ķ�����λ�Ƿ�Ϊ1 
}

int main(int argc, char *argv[])
{
	int i, n;
	for (i = 1; i <= MAX; i++)
	{
		clear(i);
	}

	while (scanf("%d", &n) != EOF)
	{
		set(n);
	}
	for (i = 1; i <= MAX; i++)
	{
		if (test(i))
			printf("%d ", i);
	}
	system("pause");

	return 0;
}