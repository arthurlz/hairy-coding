// Algorithm_analysis.cpp : 定义控制台应用程序的入口点。
//
//时空权衡

#include "stdafx.h"

int * DistributionCounting(int* A, int n, int leftNum, int rightNum);
map<char, int> ShiftTable(string pattern);
int HorspoolMatching(string text, string pattern);

void goodSuff(string pattern, int *suf);

int _tmain(int argc, _TCHAR* argv[])
{		
	//cout << "匹配的地点为： " << HorspoolMatching("ayumihamasaki", "hamasaki") << endl;

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
	for (int j = 1; j <= rightNum - leftNum; j++)			//分布计数排序,连续的[l,u]区间整数的排序
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
根据模式P[0..m-1]以及一个可能出现的字符字母表，
填写出Table[0..SIZE-1] 
对于每一个字符c,    t(c) = 1.模式的长度m(如果c不包含在模式的前m-1个字符中
						   2.模式前m-1个字符中最右边的c到模式最后一个字符的距离
*/

map<char,int> ShiftTable(string pattern)
{
	//只用26个小(大)写字母作为“自然语言的字符集”
	map<char, int> Table;
	int len = pattern.length();
	for (int i = 0; i < 26; i++)
		Table['a' + i] = len;
	for (int i = 0; i < 26; i++)
		Table['A' + i] = len;
		//Table[')'] = Table['（'] = Table['*'] = Table['&'] = Table['^'] = Table['%'] = Table['$']
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
}//cout << "匹配的地点为： " << HorspoolMatching("ayumihamasaki", "hamasaki") << endl;




//Boyer-Moore算法
/*
第一步：对于给定的模式和在模式及文本中用到的字母表，按照给出的描述构造坏符号移动表。
第二步：按照给出的描述，利用模式来构造好后缀移动表
第三步：将模式与文本的开始处对齐
第四步：重复下面的过程，直到发现了一个匹配子串或者模式到达了文本的最后一个字符以外；
从模式的最后一个字符开始，比较模式和文本中的相应字符，直到要么所有m个字符都匹配（然后停止），
要么在k>=0对字符成功匹配以后，遇到了一对不匹配的字符。在后一种情况下，如果c是文本中的不匹配字符，
我们从坏字符移动表的第c列中取出单元格t1(c)的值。如果k>0，还要从好后缀移动表中取出相应的d2的值。
然后将模式沿着文本向后移动d个字符的距离，d是按照以下公式计算出来的：
								 d1        , k == 0
							d =
								max{d1,d2} , k > 0
							其中， d1 = max{t1(c)-k,1}
*/

//void goodSuff(string pattern, int *suf)
//{
//	int len = pattern.length();
//	int i = len - 1;
//	int n;
//	for (int k = 1; k < len / 2; k++)
//	{
//		n = 0;//n为后缀的动态位
//		int m = 0;//前面的动态位
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