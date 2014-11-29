typedef struct Node
{
   int  adjvex;  //顶点位置
   struct Node  *next; 
}Node;      /*表结点定义*/

 

typedef struct VNode
{
   int vex;
   int indegree;     //入度 
   Node *firstadj;
}vertex;   /*邻接表中头顶点定义*/

 
typedef struct 
{
  vertex data[100];
  int m; // 顶点个数 
}adjlist;


void dfs(adjlist g, int v0)                        /*DFS算法核心*/
{
  int    k;
  Node   *p;

  printf("%3d",v0);
 
  visited[v0] = 1;

  p = g.data[v0].firstadj;

  while(p)
  {
    k = p->adjvex;
    if(visited[k] == 0)
      dfs(g,k);
    p = p->next;
  }
}

 

void dfstraver(adjlist g, int v0)              /*DFS初始化*/ 
{

  int i ;
  for(i = 0 ; i < g.m; i++)
      visited[i] = 0;
  dfs(g,v0);    
}