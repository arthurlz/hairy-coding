
//题目：输入两个整数n和m，从数列1,2,3...n中随意取几个数，使其和等于m，要求列出所有的组合
#include <iostream>
#include <list>
using namespace std;

void find_factor(list<int> & list_sum, int sum,int n)
{
	//递归出口
	if(n<=0||sum<=0)
		return;
	//输出找到的数
	if(sum==n)
	{
		list_sum.reverse();
		for(list<int>::iterator iter=list_sum.begin();iter!=list_sum.end();iter++)
			cout<<*iter<<"+";
		cout<<n<<endl;
		list_sum.reverse();
	}
	list_sum.push_front(n);
	find_factor(list_sum,sum-n,n-1);//n放在里面
	list_sum.pop_front();
	find_factor(list_sum,sum,n-1);//n不放在里面
}

int main(void)
{
	list<int> list_sum;
	int sum,n;
	cin>>sum>>n;
	cout<<"All posiible orders: "<<endl;
	find_factor(list_sum,sum,n);
	return 0;
}