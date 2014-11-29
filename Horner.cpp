#include <iostream>
using namespace std;
int Horner(int *p, int x, int n) ;
int HornerRecursion(int *p, int *temp, int x, int n);

int LeftRightBinaryExponentiation(int a, int *bin, int n);
int RightLeftBinaryExponentiation(int a, int *bin, int n) ;

int main(int argc, char const *argv[])
{
	int a[3] = {1, 1, 2};
	//cout<<Horner(a,2,3);
	int *p = a;
	cout<<HornerRecursion(a,p,2,3)<<endl;

	int bin[] = {1,0,1,1};
	//cout<<LeftRightBinaryExponentiation(2,bin,4);
	cout<<RightLeftBinaryExponentiation(2,bin,4);
	return 0;
}

int Horner(int *p, int x, int n)    //x(2x+1)+1 = 2x*x + x + 1
{
	int coefficient = 0;
	coefficient = p[n-1];
	for(int t = n-2; t >= 0; t--)
	{
		coefficient = coefficient * x + p[t];
	}
	return coefficient;
}

int HornerRecursion(int *p, int *temp, int x, int n)
{
	if(temp - p == n - 1)
		return p[n-1];
	return x * HornerRecursion(p, temp+1, x, n) + *temp;
}


//2进制幂 求a的n次方

int LeftRightBinaryExponentiation(int a, int *bin, int n) // 13 = 1101 ←
{
	int p = a;
	for(int i = n-2; i >= 0; i--)
	{
		p *= p;
		if(bin[i] == 1)
			p *= a;
	}
	return p;
}


int RightLeftBinaryExponentiation(int a, int *bin, int n)  //13 = 1101 →
{
	int temp,product;
	if(bin[0] == 1)
		product = temp = a;
	else
		product = temp = 1;
	for(int i = 1; i < n; i++)
	{
		temp *= temp;
		if(bin[i] == 1)
			product *= temp;
	}
	return product;
}