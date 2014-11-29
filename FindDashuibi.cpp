// FindDashuibi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

string findDashuibi(vector<string>& str,size_t num);

int _tmain(int argc, _TCHAR* argv[])
{
	//vector<string> str(5);
	//str.insert(str.begin(),"ayumi");
	//str.insert(str.begin() + 1,"ayumi");
	//str.insert(str.begin() + 2,"ammi");
	//str.insert(str.begin() + 3,"ayumi");
	//str.insert(str.begin() + 4,"mikku");
	//str.shrink_to_fit();

	istream_iterator<string> ini_it(cin);
	istream_iterator<string> eof;
	vector<string> str(ini_it,eof);
	//ostream_iterator<string> out_iter(cout);
	/*copy(ini_it,eof,str.begin());*/
	auto s = findDashuibi(str,str.size());
	
	cout<<"Dashuibi is "<<s<<endl;
	system("pause");
	return 0;
}

string findDashuibi(vector<string>& str,size_t num)
{
	int nTimes = 0;
	string candicate;
	for(size_t i = 0;i < num;i++)
	{
		if(nTimes == 0)
		{
			candicate = str[i];
		    nTimes = 1;
		}
		else
		{
			if(candicate == str[i])
				nTimes++;
			else
			    nTimes--;
		}
	}
	return candicate;
}