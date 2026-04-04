#define  _CRT_SECURE_NO_WARNINGS l
#include <stdio.h>
int main()
{
	int line = 4;
	int i = 0;
	for (i = 0; i < line;i++)
	{
		int kongge = 0;
		for (kongge = 0; kongge < line - i; kongge++)
		{
			printf(" ");
		}
		for (int star=0;star<i+1;star++)
		{
			printf("* ");
		}
		printf("\n");
	}
	for (i = line-1; i >=1; i--)
	{
		int kongge = 0;
		for (kongge = 0; kongge < line - i + 1; kongge++)
		{
			printf(" ");
		}
		for (int star = 0; star < i; star++)
		{
			printf("* ");
		}
		printf("\n");

	}

	return 0;
}
