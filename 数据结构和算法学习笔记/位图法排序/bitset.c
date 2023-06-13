#include <stdio.h>
#define MAX 10000000
#define SHIFT 5           
#define MASK 0x1F
#define DIGITS 32


int a[1 + MAX / DIGITS];

void set(int n)                                //将逻辑位置为n的二进制位置为1 
{
	a[n >> SHIFT] |= (1 << (n&MASK));               //n>>SHIFT右移5位相当于除以32求算字节位置，n&MASK相当于对32取余即求位位置，
}

void clear(int n)
{
	a[n >> SHIFT] &= (~(1 << (n&MASK)));           //将逻辑位置为n的二进制位置为0
}

int test(int n)
{
	return a[n >> SHIFT] & (1 << (n&MASK));        //测试逻辑位置为n的二进制位是否为1 
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