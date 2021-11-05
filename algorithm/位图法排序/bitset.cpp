#include <iostream>
#include <bitset> 

using namespace std;

int main(int argc, char *argv[])
{
	const int max = 1000000;

	int n, i;
	bitset<max + 1> bit;                     //初始默认所有二进制位为0 

	while (scanf("%d", &n) != EOF)
	{
		bit.set(n, 1);                   //将第n位置1               
	}
	for (i = 0; i < max + 1; i++)
	{
		if (bit[i] == 1)
			printf("%d ", i);
	}
	system("pause");
	return 0;
}