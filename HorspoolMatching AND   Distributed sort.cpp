// Algorithm_analysis.cpp : �������̨Ӧ�ó������ڵ㡣
//
//ʱ��Ȩ��

#include "stdafx.h"

int * DistributionCounting(int* A, int n, int leftNum, int rightNum);
map<char, int> ShiftTable(string pattern);
int HorspoolMatching(string text, string pattern);

void goodSuff(string pattern, int *suf);

int _tmain(int argc, _TCHAR* argv[])
{		
	//cout << "ƥ��ĵص�Ϊ�� " << HorspoolMatching("ayumihamasaki", "hamasaki") << endl;

	system("pause");
	return 0;
}

int * DistributionCounting(int* A, int n, int leftNum, int rightNum)
{
	int * D = new int[rightNum - leftNum + 1];
	for (int j = 0; j <= rightNum - leftNum; j++)            
		D[j] = 0;										     /*	int A[6] = { 13, 11, 12, 13, 12, 12 };
																DistributionCounting(A, 6, 11, 13);
																for (int i = 0; i < 6; i++)
																	cout << A[i] << endl;*/
	for (int i = 0; i < n; i++)
		D[A[i] - leftNum] += 1;
	for (int j = 1; j <= rightNum - leftNum; j++)			//�ֲ���������,������[l,u]��������������
		D[j] += D[j - 1];

	int * S = new int[n];
	for (int i = n - 1; i >= 0; i--)
	{
		int j = A[i] - leftNum;
		S[D[j] - 1] = A[i];
		D[j] = D[j] - 1;
	}

	for (int i = 0; i < n; i++)
		A[i] = S[i];

	delete [] D;
	delete [] S;
	return A;
}

//HorspoolMatching
/*
����ģʽP[0..m-1]�Լ�һ�����ܳ��ֵ��ַ���ĸ��
��д��Table[0..SIZE-1] 
����ÿһ���ַ�c,    t(c) = 1.ģʽ�ĳ���m(���c��������ģʽ��ǰm-1���ַ���
						   2.ģʽǰm-1���ַ������ұߵ�c��ģʽ���һ���ַ��ľ���
*/

map<char,int> ShiftTable(string pattern)
{
	//ֻ��26��С(��)д��ĸ��Ϊ����Ȼ���Ե��ַ�����
	map<char, int> Table;
	int len = pattern.length();
	for (int i = 0; i < 26; i++)
		Table['a' + i] = len;
	for (int i = 0; i < 26; i++)
		Table['A' + i] = len;
		//Table[')'] = Table['��'] = Table['*'] = Table['&'] = Table['^'] = Table['%'] = Table['$']
		//	= Table['#'] = Table['@'] = Table['!'] = Table['_'] = Table['/'] = Table['?'] = Table['.'] = len;


	for (int i = 0; i < len - 1; i++)
	{
		Table[pattern[i]] = len - i - 1;
	}

	return Table;
}

int HorspoolMatching(string text, string pattern)
{
	map<char, int> table = ShiftTable(pattern);

	int len = pattern.length();
	int i = len - 1;
	while (i < text.length())
	{
		int k = 0;
		while ( k < len && pattern[len-1-k] == text[i-k] )
		{
			k++;
		}
		if (k == len)
			return i - k + 1;
		else
			i += table[text[i]];
	}
	return -1;
}//cout << "ƥ��ĵص�Ϊ�� " << HorspoolMatching("ayumihamasaki", "hamasaki") << endl;




//Boyer-Moore�㷨
/*
��һ�������ڸ�����ģʽ����ģʽ���ı����õ�����ĸ�����ո������������컵�����ƶ���
�ڶ��������ո���������������ģʽ������ú�׺�ƶ���
����������ģʽ���ı��Ŀ�ʼ������
���Ĳ����ظ�����Ĺ��̣�ֱ��������һ��ƥ���Ӵ�����ģʽ�������ı������һ���ַ����⣻
��ģʽ�����һ���ַ���ʼ���Ƚ�ģʽ���ı��е���Ӧ�ַ���ֱ��Ҫô����m���ַ���ƥ�䣨Ȼ��ֹͣ����
Ҫô��k>=0���ַ��ɹ�ƥ���Ժ�������һ�Բ�ƥ����ַ����ں�һ������£����c���ı��еĲ�ƥ���ַ���
���Ǵӻ��ַ��ƶ���ĵ�c����ȡ����Ԫ��t1(c)��ֵ�����k>0����Ҫ�Ӻú�׺�ƶ�����ȡ����Ӧ��d2��ֵ��
Ȼ��ģʽ�����ı�����ƶ�d���ַ��ľ��룬d�ǰ������¹�ʽ��������ģ�
								 d1        , k == 0
							d =
								max{d1,d2} , k > 0
							���У� d1 = max{t1(c)-k,1}
*/

//void goodSuff(string pattern, int *suf)
//{
//	int len = pattern.length();
//	int i = len - 1;
//	int n;
//	for (int k = 1; k < len / 2; k++)
//	{
//		n = 0;//nΪ��׺�Ķ�̬λ
//		int m = 0;//ǰ��Ķ�̬λ
//		while (pattern[i - n] != pattern[i - m - k])
//			m++;
//		if (i - m - k < 0)
//		{
//			if (k == 1)
//				suf[k - 1] = 1;
//			else
//				suf[k - 1] = suf[k - 2];
//		}
//		else
//		{
//			while (1)
//			{
//				if (pattern[i - n] == pattern[i - m - k] && n < k && i - m - k > 0)
//				{
//					n++;
//					m++;
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			suf[k-1] = n - m - k;
//
//		}
//	}
//
//	for (int a = len / 2; a < len; a++)
//		suf[a] = suf[a - 1];
//}