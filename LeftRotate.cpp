#include <iostream>
#include <string.h>

using namespace std;

void Reversion(char* begin, char* end)
{
	if(begin == NULL || end == NULL)
		return;
	char temp;
	while(begin < end)
	{
		temp = *begin;
		*begin = *end;
		*end = temp;
		begin++;
		end--;
	}
}

void StringMove(char* begin,const int nCount)
{
	if(begin == NULL)
		return;

	int num = strlen(begin);
    if((nCount > num) || num == 0)
    	return;

    char* end1 = begin + nCount - 1;
    char* begin2 = begin + nCount;
    char* end2 = begin + num - 1;

    Reversion(begin,end1);
    Reversion(begin2,end2);
    Reversion(begin,end2);
}

int main(int argc, char const *argv[])
{
	char str[] = "abcdefg";
	StringMove(str,2);
	cout<<str<<endl;
	return 0;
}
