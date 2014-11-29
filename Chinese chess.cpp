#include <iostream>

using namespace std;

typedef unsigned char byte;

int main(int argc, char *argv[])
{
	byte b = 81;
	while(b--)
	{
		if(b/9%3 == b%9%3)
		   continue;
        cout<<"A="<<(b/9+1)<<"  B="<<(b%9+1)<<endl; 
	}
	return 0;
}
