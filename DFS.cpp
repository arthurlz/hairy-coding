// AdjMGraph.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int (*edge)[VERTEXNUM] = (int (*)[VERTEXNUM])malloc(sizeof(int) * (VERTEXNUM * VERTEXNUM));
	int *vertexStatusArr = (int*)malloc(sizeof(int) * VERTEXNUM);

	for(int i = 0; i != VERTEXNUM; i++)
	{
		for(int j = 0; j != VERTEXNUM; j++)
			edge[i][j] = 0;
	}

	for(int i = 0; i != VERTEXNUM; i++)
		vertexStatusArr[i] = 0;

	createGraph(edge,0,3);
	createGraph(edge,0,4);
	createGraph(edge,3,1);
	createGraph(edge,3,2);
	createGraph(edge,4,1);


	printf("after init\n");
	displayGraph(edge);

	DFT(edge,vertexStatusArr);

	free(edge);
	printf("\n");
	system("pause");
	return 0;
}

void createGraph(int (*edge)[VERTEXNUM], int start, int end)
{
	edge[start][end] = 1;
}

void displayGraph(int (*edge)[VERTEXNUM])
{
	for(int i = 0; i < VERTEXNUM; i++)
	{
		for(int j = 0; j < VERTEXNUM; j++)
		{
			printf("%d ",edge[i][j]);
		}
		printf("\n");
	}
}

void DFT(int (*edge)[VERTEXNUM], int *vertexStatusArr)
{
	printf("开始DFS\n");
	for(int i = 0; i < VERTEXNUM; i++)
	{
		DFTcore(edge,i,vertexStatusArr);
	}
}

void DFTcore(int (*edge)[VERTEXNUM],int i, int *vertexStatusArr)
{
	if(vertexStatusArr[i] == 1)
		return;
	printf("%d ",i);
	vertexStatusArr[i] = 1;

	for(int j = 0; j != VERTEXNUM; j++)
	{
		if(edge[i][j] == 1)
			DFTcore(edge,j,vertexStatusArr);
	}
}