// Dynamic_Programming.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int Binomial(int n, int k, vector<vector<int>>& arr);//����ʽϵ��
int calcBinomial();

void Warshall(vector<vector<int>>& R);//ͼ�Ĵ��ݱհ�

//���·��All
void Floyd(vector<vector<int>>& W, vector<vector<int>>& P);
void ShowShortestPath(vector<vector<int>> & P, int i, int j);
void initDAG(vector<vector<int>>& W, vector<vector<int>>& P);
void createEdge(vector<vector<int>>& W, int i, int j, int weight);
void showShortestWeights(vector<vector<int>> & W);
void showShortestPathMatrix(vector<vector<int>> & P);
void ShowAllShortestPath(vector<vector<int>>& P, vector<vector<int>>& W);
void ShortestPathGraphAll();

//���Ŷ���������
void OptimalBST(double *p, vector<vector<double>>& C, vector<vector<int>>& R);
void OptimalTree(vector<vector<int>> & R, int i, int j);//preorder
void OptimalBST_ALL();


//�������˴�������
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
��C(n,k)
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
	cout << "����n:";
	cin >> n;
	cout << "����k:";
	cin >> k;

	vector<vector<int>> arr(n + 1, vector<int>(k + 1));
	return Binomial(n, k, arr);
}


/*
������ͼ�Ĵ��ݱհ�
һ��n�����������ͼ�Ĵ��ݱհ�Ϊ���Զ���Ϊһ��n�ײ�������T={tij},����ӵ�i�����㵽��j������֮��
����һ����Ч������·���������i�У���j�е�Ԫ��Ϊ1������ tijΪ0
***���һ��Ԫ��rij��R(k-1)����1������R(k)����Ȼ��1
***���һ��Ԫ��rij��R(k-1)����0�����ҽ��������е�i�е�k�е�Ԫ�غ͵�k�е�j�е�Ԫ�ض���1����Ԫ����R(k)�в��ܱ��1



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

		cout << "�����i�����㵽��j�������Ȩֵ��(�ո����_#����)";
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
	cout << "\n\n���·��Ȩֵ����" << endl;
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
	cout << "���·��;�������" << endl;
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
				cout << "���·��: " << i << "->";
				ShowShortestPath(P, i, j);
				cout << j << "  ����Ϊ" << W[i][j] << endl;
			}
		}
	}
}

void ShortestPathGraphAll()
{
	cout << "����ͼ�Ķ������: " << endl;
	size_t n;
	cin >> n;
	vector<vector<int>> w(n, vector<int>(n)), p(n, vector<int>(n));
	initDAG(w, p);
	Floyd(w, p);
	showShortestWeights(w);
	showShortestPathMatrix(p);
	ShowAllShortestPath(p, w);
}



//���Ŷ��������  �ѣ������� ����ϣ���Ժ󿴵���δ�����ң����Բ����ǵ�ʱ�о��㷨���Ƿݼ���^_^�W��������B���죡
//n�����Ķ����������������Ϊ��n����������
//������������Ҫ���ܶ�����ⶼ�ǿ������������ģ���ʱ���о���������

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

			R[i][j] = root + 1;  //1��ʼ

			double sum = 0;
			for (size_t s = i; s <= j; s++)
			{
				sum += p[s];
			}

			C[i][j] = sum + min;
		}
	}
}


void OptimalTree(vector<vector<int>> & R, int i, int j) //���ǰ���������֪�������������)
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
	double p[4] = { 0.1, 0.2, 0.4, 0.3 };    //�����������еĶ����������ʶ�Ӧ�������������
	vector<vector<double>> C(4, vector<double>(4)); //0-n
	vector<vector<int>> R(4, vector<int>(4));      //��ĸ���1��ʼ��Ϊ�˱�����⣩
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

	cout << "ǰ�����Ϊ��";
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