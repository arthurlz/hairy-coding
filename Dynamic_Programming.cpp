// Dynamic_Programming.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int Binomial(int n, int k, vector<vector<int>>& arr);//二项式系数
int calcBinomial();

void Warshall(vector<vector<int>>& R);//图的传递闭包

//最短路径All
void Floyd(vector<vector<int>>& W, vector<vector<int>>& P);
void ShowShortestPath(vector<vector<int>> & P, int i, int j);
void initDAG(vector<vector<int>>& W, vector<vector<int>>& P);
void createEdge(vector<vector<int>>& W, int i, int j, int weight);
void showShortestWeights(vector<vector<int>> & W);
void showShortestPathMatrix(vector<vector<int>> & P);
void ShowAllShortestPath(vector<vector<int>>& P, vector<vector<int>>& W);
void ShortestPathGraphAll();

//最优二叉搜索树
void OptimalBST(double *p, vector<vector<double>>& C, vector<vector<int>>& R);
void OptimalTree(vector<vector<int>> & R, int i, int j);//preorder
void OptimalBST_ALL();


//矩阵连乘次数最少
void MatrixSuccessiveMultiplication(int *dim, vector<vector<int>>& MatEven);

int _tmain(int argc, _TCHAR* argv[])
{
	//cout << calcBinomial();

	ShortestPathGraphAll();

	//OptimalBST_ALL();
	
	//int dim[] = { 30, 35, 35, 15, 15, 5, 5, 10, 10, 20, 20, 25 };
	//vector<vector<int>> mat(6, vector<int>(6));

	//MatrixSuccessiveMultiplication(dim, mat);

	//for (auto& e: mat)
	//{
	//	for(auto &c: e)
	//	{
	//		cout << right << c << "\t";
	//	}
	//	cout << endl;
	//}


	system("pause");
	return 0;
}

/*
求C(n,k)
C(n,k) = C(n-1,k-1) + C(n-1,k)
*/

int Binomial(int n, int k, vector<vector<int>>& arr)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= min(i, k); j++)
		{
			if (j == 0 || j == i)
				arr[i][j] = 1;
			else
			{
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			}
		}
	}

	return arr[n][k];
}

int calcBinomial()
{
	int n, k;
	cout << "输入n:";
	cin >> n;
	cout << "输入k:";
	cin >> k;

	vector<vector<int>> arr(n + 1, vector<int>(k + 1));
	return Binomial(n, k, arr);
}


/*
求有向图的传递闭包
一个n个顶点的有向图的传递闭包为可以定义为一个n阶布尔矩阵T={tij},如果从第i个顶点到第j个顶点之间
存在一条有效的有向路径，矩阵第i行，第j列的元素为1，否则 tij为0
***如果一个元素rij在R(k-1)中是1，它在R(k)中仍然是1
***如果一个元素rij在R(k-1)中是0，当且仅当矩阵中第i行第k列的元素和第k行第j列的元素都是1，该元素在R(k)中才能变成1



initialization_________
vector<vector<int>> arr(4,vector<int>(4));
arr[0][1] = arr[1][3] = arr[3][0] = arr[3][2] = 1;

Warshall(arr);

*/
void Warshall(vector<vector<int>>& R)
{
	for (size_t k = 0; k < R.size(); k++)
	{
		for (size_t i = 0; i < R.size(); i++)
		{
			for (size_t j = 0; j < R.size(); j++)
				R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
		}
	}
}

void Floyd(vector<vector<int>>& W, vector<vector<int>>& P)
{
	for (size_t k = 0; k < W.size(); k++)
	{
		for (size_t i = 0; i < W.size(); i++)
		{
			for (size_t j = 0; j < W.size(); j++)
			{
				//W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
				if (W[i][j] > W[i][k] + W[k][j])
				{
					W[i][j] = W[i][k] + W[k][j];
					P[i][j] = k + 1;
				}
			}
		}

	}
}

void ShowShortestPath(vector<vector<int>>& P, int i, int j)
{
	int k = P[i][j];
	if (k != 0)
	{
		ShowShortestPath(P, i, k - 1);
		cout << k - 1 << "->";
		ShowShortestPath(P, k - 1, j);
	}
}

void initDAG(vector<vector<int>>& W, vector<vector<int>>& P)  //test data: 0  2 3, 1 0 2, 2 1 7, 2 3 1, 3 0 6,
{
	for (size_t i = 0; i < W.size(); i++)
	{
		for (size_t j = 0; j < W.size(); j++)
		{
			if (i == j)
			{
				W[i][j] = 0;
			}
			else
			{
				W[i][j] = 100;
			}
			P[i][j] = 0;
		}
	}
	string i, j, weight, str, mark;
	cin.sync();
	while (mark != "#")
	{

		cout << "输入第i个顶点到第j个顶点的权值：(空格隔开_#结束)";
		getline(cin, str);
		istrstream istr(str.c_str());
		istr >> i >> j >> weight >> mark;
		//cout << i << j << weight << endl;
		createEdge(W, stoi(i), stoi(j), stoi(weight));
	}


}

void createEdge(vector<vector<int>>& W, int i, int j, int weight)
{
	W[i][j] = weight;
}

void showShortestWeights(vector<vector<int>> & W)
{
	cout << "\n\n最短路径权值矩阵：" << endl;
	for (auto& c : W)
	{
		for (auto&e : c)
			cout << e << "\t";
		cout << endl;
	}
	cout << endl;
}

void showShortestPathMatrix(vector<vector<int>> & P)
{
	cout << "最短路径途径点矩阵：" << endl;
	for (auto& c : P)
	{
		for (auto&e : c)
			cout << e << "\t";
		cout << endl;
	}
	cout << endl;
}

void ShowAllShortestPath(vector<vector<int>>& P, vector<vector<int>>& W)
{
	for (size_t i = 0; i < P.size(); i++)
	{
		for (size_t j = 0; j < P.size(); j++)
		{
			if (P[i][j] != 0 && P[i][j] != j - 1)
			{
				cout << "最短路径: " << i << "->";
				ShowShortestPath(P, i, j);
				cout << j << "  长度为" << W[i][j] << endl;
			}
		}
	}
}

void ShortestPathGraphAll()
{
	cout << "输入图的定点个数: " << endl;
	size_t n;
	cin >> n;
	vector<vector<int>> w(n, vector<int>(n)), p(n, vector<int>(n));
	initDAG(w, p);
	Floyd(w, p);
	showShortestWeights(w);
	showShortestPathMatrix(p);
	ShowAllShortestPath(p, w);
}



//最优二叉查找树  难！！！难 。。希望以后看到这段代码的我，可以不忘记当时研究算法的那份激情^_^僕は最強だ、頑張れ！
//n个键的二叉查找树的总数量为第n个卡特兰数
//卡特兰数很重要，很多问题解都是卡特兰数给出的，有时间研究卡特兰数

void OptimalBST(double *p, vector<vector<double>>& C, vector<vector<int>>& R)
{
	for (size_t i = 0; i < C.size(); i++)
	{
		C[i][i] = p[i];
		R[i][i] = i + 1;
	}
	size_t n = C.size();
	for (size_t d = 1; d <= n - 1; d++)
	{
		for (size_t i = 0; i <= n - d - 1; i++)
		{
			size_t j = i + d;
			double min = 10000.0;

			int root = 0;

			for (size_t k = i; k <= j; k++)
			{
				double C1 = 0, C2 = 0;
				if (k > i)
				{
					C1 = C[i][k - 1];
				}
				if (k < j)
				{
					C2 = C[k + 1][j];
				}

				if (C1 + C2 < min)
				{
					min = C1 + C2;
					root = k;
				}
			}

			R[i][j] = root + 1;  //1开始

			double sum = 0;
			for (size_t s = i; s <= j; s++)
			{
				sum += p[s];
			}

			C[i][j] = sum + min;
		}
	}
}


void OptimalTree(vector<vector<int>> & R, int i, int j) //输出前序的树，已知中序的树（输入)
{
	if (i <= j)
	{
		int k = R[i][j] - 1;
		cout << k << " ";
		OptimalTree(R, i, k - 1);
		OptimalTree(R, k + 1, j);
	}
}

void OptimalBST_ALL()
{
	double p[4] = { 0.1, 0.2, 0.4, 0.3 };    //输入中序序列的二叉树（概率对应与点的中序遍历）
	vector<vector<double>> C(4, vector<double>(4)); //0-n
	vector<vector<int>> R(4, vector<int>(4));      //存的根从1开始（为了便于理解）
	OptimalBST(p, C, R);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			cout << C[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			cout << R[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	cout << "前序遍历为：";
	OptimalTree(R, 0, 3);
	cout << endl;
}

void MatrixSuccessiveMultiplication(int *dim, vector<vector<int>>& MatEven)
{
	for (size_t i = 0; i < MatEven.size(); i++)
	{
		MatEven[i][i] = 0;
	}

	size_t len = MatEven.size();
	for (size_t d = 1; d <= len - 1; d++)
	{
		for (size_t i = 0; i < len - d; i++)
		{
			size_t j = i + d;
			int min = 10000000;
			int temp;
			for (size_t k = i; k < j; k++)
			{
				temp = MatEven[i][k] + MatEven[k + 1][j] + dim[2 * i] * dim[2 * k + 1] * dim[2 * j + 1];
				if (temp < min)
				{
					min = temp;
				}
			}
			MatEven[i][j] = min;
		}
	}
}