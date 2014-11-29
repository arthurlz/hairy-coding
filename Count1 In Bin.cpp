// Count1 In Bin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int countOriginal(int num);
int countByAnd(int num);
int countByAndSubOne(int num);

int _tmain(int argc, _TCHAR* argv[])
{ 
	int num,count = 0;
	scanf_s("%d",&num);
	count = countByAndSubOne(num);
	printf("��������%d��%d��1\n",num,count);
	
	int ret = 0;
	for(int i = 1;i <= num;i++)
	{
		int j = i;
		while(j % 5 ==0)
			ret++,j /= 5;
	}
	printf("%d�Ľ׳�ĩβ��%d��0\n",num,ret);
	system("pause");
	return 0;
}

int countOriginal(int num)
{
	int count = 0;
	while (num)
	{
		if(num % 2 == 1)
			count++;
		num = num/2;
	}
    return count;
}

int countByAnd(int num)
{
	int count = 0;
	while(num)
	{
		count += num & 0x01;
		num>>=1;
	}
	return count;
}

int countByAndSubOne(int num)
{
	int count = 0;
	while (num)
	{
		num &= (num-1);
	    count++;
	}
	return count;
}