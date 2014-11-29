// BFS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//队列的前端和后端，最后一个入队列的元素为rear，第一个出队列的元素为front
st_qElement* front = NULL;
st_qElement* rear = NULL;

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

	BFS(edge,vertexStatusArr);

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

void putQueue(int vertex)
{
	st_qElement * sqe = (st_qElement*)malloc(sizeof(st_qElement));
	sqe->value = vertex;
	sqe->next = nullptr;
	sqe->pre = nullptr;
	if(front == NULL || rear == NULL)
	{
		front = rear = sqe;
	}
	else
	{
		rear->next = sqe;
		sqe->pre = rear;
		rear = sqe;
	}
		
}

int* getQueue()
{
	if(front == NULL || rear == NULL)
		return NULL;
	else
	{
		int *res = (int*)malloc(sizeof(int));
		*res = front->value;

		st_qElement *p = front;
		front = front->next;
		if(front == NULL)
			rear = front;
		else
		{
			front->pre = NULL;
		}
		free(p);
		return res;

	}
}

void putRelatedInQueue(int (*edge)[VERTEXNUM], int vertex)
{
	for(int i = 0; i < VERTEXNUM; i++)
	{
		if(edge[vertex][i] == 1)
			putQueue(i);
	}
}

void BFS(int (*edge)[VERTEXNUM],int* vertexStatusArr)
{
	printf("start BFS\n");
	for (int i = 0; i < VERTEXNUM; i++)
	{
		BFScore(edge,i,vertexStatusArr);
	}
}

void BFScore(int (*edge)[VERTEXNUM],int i,int* vertexStatusArr)
{
	putQueue(i);
	int *returnValue = NULL;
	while ((returnValue = getQueue()) != NULL)
	{
		if(vertexStatusArr[*returnValue] == 0)
		{
			printf("%d ",*returnValue);
			vertexStatusArr[*returnValue] = 1;
			putRelatedInQueue(edge,i);
		}
	}
	free(returnValue);
}