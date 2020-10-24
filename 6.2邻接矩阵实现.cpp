#include <iostream>
#include <queue>
#include <cstdlib>
#include <iomanip>

#define QElemType int
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define NO_PATH -1
#define MaxInt 32767
#define MAXQSIZE 100
#define MVNum 100
#define QSize 30
using namespace std;
//存储结构：邻接矩阵和邻接表
//1. 邻接矩阵
typedef char VertexType;
typedef int ArcType;
typedef enum{
    DG,//有向图
    DN,//有向网//
    UDG,//无向图
    UDN//无向网
}GraphKind;
typedef struct
{
    VertexType vexs[MVNum]; //顶点表
    ArcType arcs[MVNum][MVNum]; //邻接矩阵
    int vexnum,arcnum; //图的顶点和边数
    GraphKind kind;
}AMGraph;

//定义队列
typedef struct
{
    QElemType *base;
    int front;
    int rear;
}SqQueue;
//遍历需要的访问数组
bool visited[MVNum] = {false};

void reVisited(bool * visited)
{
    for(int i=0;i<MVNum;i++)
        visited[i]=false;
}
/**********利用循环队列*******/
typedef struct
{
	int front;
	int rear;
	int count;
	int data[QSize];
}CirQueue;

void InitQueue(CirQueue *Q)
{
	Q->front=Q->rear=0;
	Q->count=0;
}
int QueueEmpty(CirQueue *Q)
{
	return Q->count=QSize;
}
int QueueFull(CirQueue *Q)
{
	return Q->count==QSize;
}
void EnQueue(CirQueue *Q,int x)
{
	if (QueueFull(Q))
		cout<<"OVERFLOW"<<endl;
	else
	{
		Q->count++;
		Q->data[Q->rear]=x;
		Q->rear=(Q->rear+1)%QSize;
	}
}
/**********************************/


//基本操作
int LocateVex(AMGraph G, VertexType v)
{
    int i;
    for(i=0;i<G.vexnum && G.vexs[i]!=v;i++)
        continue;
    return i;
}

void CreateGraph(AMGraph &G)
{
    if(G.kind<0||G.kind>3) cout<<"创建图出错，检查输入图类型是否正确"<<endl;
    cout<<"请输入总顶点数和总边数，空格隔开:";
    cin>>G.vexnum>>G.arcnum;
    int i,j;
    for(i=0;i<G.vexnum;i++)
    {
        cout<<"请输入顶点vex[" << i << "]的值："<<endl;
        cin>>G.vexs[i];
    }
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
        {
            if(G.kind%2)//网
                G.arcs[i][j]=MaxInt;
            else
                G.arcs[i][j]=0;
        }

    for(int k=0;k<G.arcnum;k++)
    {

	    if(0==G.kind||1==G.kind)//是有向
            cout<<"输入<v1,v2>作为边（空格隔开）：";
        else
            cout<<"输入(v1,v2)作为边（空格隔开）：";
        VertexType v1,v2;
        cin>>v1>>v2;
        int index1 = LocateVex(G,v1);
        int index2 = LocateVex(G,v2);
        int w;
        if(G.kind%2)
        {
            cout<<"请输入边的权值:";
            cin>>w;
        }
        if(G.kind==DG)
        {
            G.arcs[index1][index2] = 1;
        }
        else if(G.kind==DN)
        {
            G.arcs[index1][index2]=w;
        }
        else if(G.kind=UDG)
        {
            G.arcs[index1][index2] = 1;
            G.arcs[index2][index1] = G.arcs[index1][index2];
        }
        else if(G.kind=UDN)
        {
            G.arcs[index1][index2] = w;
            G.arcs[index2][index1] = G.arcs[index1][index2];
        }
    }
    cout<<"创建完毕"<<endl;
}



//增加一个新顶点v, InsertVex(G,v)
void InsertVex(AMGraph &G,VertexType v)
{
    int i;
    G.vexnum++;
    G.vexs[G.vexnum-1]=v; //输入新顶点数据
    //初始化新增的行列
    //注意这里的可优化逻辑问题，会重复赋值
    for(i=0;i<G.vexnum;i++)
        G.arcs[G.vexnum-1][i]=0;
    for(i=0;i<G.vexnum-1;i++)
        G.arcs[i][G.vexnum-1]=0;
}
//删除顶点v以及相关的边，DeleteVex(G,v)
bool DeleteVex(AMGraph &G,VertexType v)
{
    //1. 找到顶点位置
    int location = LocateVex(G,v);
    if(location<0)
        return false;
    //3. 更改顶点数组内容及大小
    for(int i=location+1;i<G.vexnum;i++)
        G.vexs[i-1] = G.vexs[i];
    //4. 更改邻接矩阵
    int j,k;
    for(j=0;j<G.vexnum;j++)
        for(k=location+1;k<G.vexnum;k++)
            G.arcs[j][k-1] = G.arcs[j][k];
    for(j=0;j<G.vexnum;j++)
        for(k=location+1;k<G.vexnum;k++)
            G.arcs[k-1][j] = G.arcs[k][j];

    G.vexnum--;
    return true;
}
//增加一条边<v,w>, InsertArc(G,v,w)
bool InsertArc(AMGraph &G,VertexType v,VertexType w)
{
    //找到两个顶点的位置
    int vL = LocateVex(G,v);
    int wL = LocateVex(G,w);
    if(vL<0||wL<0)
        return false;
    //更改邻接矩阵
    G.arcs[vL][wL] = 1;
    G.arcs[wL][vL] = G.arcs[vL][wL];
    return true;
}
//删除一条边<v,w>, DeleteArc(G,v,w)
bool DeleteArc(AMGraph &G,VertexType v,VertexType w)
{
    //找到两个顶点的位置
    int vL = LocateVex(G,v);
    int wL = LocateVex(G,w);
    if(vL<0||wL<0)
        return false;
    //更改邻接矩阵
    G.arcs[vL][wL] = 0;
    G.arcs[wL][vL] = G.arcs[vL][wL];
    return true;
}

//打印邻接矩阵
void PrintArc(AMGraph G)
{
    int i, j;
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
            cout<<G.arcs[i][j]<< " ";
        cout<<endl;
    }
}

//深度优先遍历
void DFS_AM(AMGraph G, int v)
{
    //从第v个顶点出发递归深度优先遍历图
    int judge;
    if(G.kind%2) //是网
        judge = MaxInt;
    else
        judge = 0;
    if(visited[v]==0)
        cout<<G.vexs[v]<<" ";
    visited[v]=true;
    for(int w=0;w<G.vexnum;w++)
        if((G.arcs[v][w]!=judge)&&(!visited[w]))
        {
            DFS_AM(G,w);
        }
}

/*
//v的第一个邻接点
int FirstAdjVex(AMGraph G, VertexType v)
{
    int i;
    int j = 0;
    int k;
    cout<<"v:"<<v<<endl;
    k = LocateVex(G,v);

    cout<<"打印顶点表"<<endl;
    for(int i=0;i<G.vexnum;i++)
        cout<<G.vexs[i]<<endl;

    cout<<"LocateVex(G,v):"<<k<<endl;

    if(G.kind%2) //是网
        j = MaxInt;

    for(i=0;i<G.vexnum;i++)
        cout<<G.arcs[k][i]<<" ";

    cout<<endl;
    for(i=0;i<G.vexnum;i++)
        if(G.arcs[k][i]!=j)
            return i;
    return -1;
}

//v相当于w的下一个邻接点，只要有值就代表存在邻接点
int NextAdjVex(AMGraph G, VertexType v, VertexType w)
{
    int i;
    int j = 0;
    int k1,k2;
    k1 = LocateVex(G,v);
    k2 = LocateVex(G,w);
    if(G.kind%2)
        j = MaxInt;
    for(i=k2+1;i<G.vexnum;i++)
    {
        if(G.arcs[k1][i]!=j)
            return i;
    }
    return -1;
}

//广度优先遍历
void BFS_AM(AMGraph G, int v)
{
    int visited[MVNum] = {0} ;
    cout<<"************"<<endl;
    for(int i=0;i<MVNum;i++)
        cout<<visited[i]<<" ";
    cout<<endl;
    cout<<"************"<<endl;
    cout<<v;
    cout<<"flag1"<<endl;
    visited[v]=1;
    //利用队列
    SqQueue Q;
    InitQueue(Q);

    EnQueue(Q,v);
    cout<<"flag2"<<endl;

    while(!QueueEmpty(Q))
    {
        cout<<"flag3"<<endl;
        //出队并且出队元素为u
        QElemType u;
        DeQueue(Q,u);
        cout<<"u:"<<u<<endl;
        int w=FirstAdjVex(G,u);
        cout<<w<<endl;
        for(;w>=0;w=NextAdjVex(G,u,w))
        {
            cout<<"flag4"<<endl;
            if(!visited[w])
            {
            cout<<"flag5"<<endl;
                cout<<w<<"->";
                visited[w]=true;
                EnQueue(Q,w);
            }
        }
    }
}
*/

int DeQueue(CirQueue *Q)
{
	int temp;
	if(QueueEmpty(Q))
	{
	    cout<<"UNDERFLOW"<<endl;
		return -1;
	}
	else
	{
		temp=Q->data[Q->front];
		Q->count--;
		Q->front=(Q->front+1)%QSize;
		return temp;
	}
}

void BFSM(AMGraph &G,int k)
{
	int i,j;
	CirQueue Q;
	InitQueue(&Q);
	cout<<G.vexs[k]<<" ";
	visited[k]=true;
	EnQueue(&Q,k);
	while (!QueueEmpty(&Q))
	{
		i=DeQueue(&Q);
		for (j=0;j<G.vexnum;j++)
			if(G.arcs[i][j]==1&&!visited[j])
			{
			    cout<<G.vexs[j]<<" ";
				visited[j]=true;
				EnQueue(&Q,j);
			}
	}
}

void BFSTraverse(AMGraph &G)
{
    reVisited(visited);
	int i;
	for (i=0;i<G.vexnum;i++)
		visited[i]=false;
	for (i=0;i<G.vexnum;i++)
		if (!visited[i])
			BFSM(G,i);
    cout<<endl;
}


//Dijkstra算法实现有向网的v0顶点到其余顶点的最短路径
void ShortestPath_DIJ(AMGraph G,int D[],int path[][MVNum],int v0)
{
    int n = G.vexnum;
    int v,w;
    bool S[MVNum];
    for(v =0;v<n;v++)
    {
        S[v] = false;
        D[v] = G.arcs[v0][v];//存放V0到V的最短路径，初始值为直接距离
        //初始化path数组
        for(w=0;w<n;w++)
            path[v][w]= -1;
        if(D[v]<MaxInt)//有直接路径
        {
            path[v][0] = v0; //最短路径经过第一个顶点
            path[v][1] = v;  //最短路径经过第二个顶点
        }
    }
    S[v0]=true;//V0进入S
    D[v0]=0;//v0-v0是0

    //开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集
    for(int i=1;i<n;i++)
    {
        int minN = MaxInt;
        for(w=0;w<n;w++)
        {
            if(!S[w]&&D[w]<minN)
            {
                v=w;
                minN=D[w];
            }
        }
        S[v]=true;//将v加入S
        for(w=0;w<n;w++)
        {//更新从v0出发到集合V-S所有顶点的最短路径长度
            if(!S[w]
               &&(D[v]+G.arcs[v][w])
               &&minN<MaxInt
               &&G.arcs[v][w]<MaxInt
               &&(minN+G.arcs[v][w]<D[w]))
            {
              //w不属于S集且v0->v->w的距离<目前v0->w的距离
					D[w]=minN+G.arcs[v][w];//更新D[w]
					for(int j=0; j<G.vexnum; j++)//修改p[w]，v0到w经过的顶点包括v0到v经过的所有顶点再加上顶点w
					{
						path[w][j]=path[v][j];
						if(path[w][j]==-1)//在p[w][]第一个等于-1的地方加上顶点w
						{
							path[w][j]=w;
							break;
						}
					}
            }
        }
    }
}

void printShortestPath(AMGraph G, int path[][MVNum])
{
    cout<<"最短路径数组:"<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            cout<<setw(4)<<path[i][j]<<" ";
        cout<<endl;
    }
}

void printShortestPathFromV(AMGraph G,int D[], int path[][MVNum], int n)
{
    cout<<G.vexs[n]<<"到各顶点最短路径以及长度："<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        if(i!=0 && D[i]!=MaxInt)
        {
            cout<<G.vexs[n]<<"->"<<G.vexs[i]<<"="<<D[i]<<" ";
            cout<<"最短路径:";
            for(int j=0;j<G.vexnum;j++)
            {
                if(path[i][j]>-1)
                    cout<<G.vexs[path[i][j]]<<" ";
            }
            cout<<endl;
        }
        else if(D[i]==MaxInt)
            cout<<G.vexs[n]<<"->"<<G.vexs[i]<<":"<<"不通"<<endl;
    }
}

/*



//构造网的最小生成树
void MiniSpanTree_PRIM(AMGraph G, VertexType u)
{
    int k = LocateVex(G,u);
    for(int j = 0;j<G.vexnum;j++)
    {
        if(j!=k)
        closeEdge[j]={
            u,G.arcs[k][j]
        };
    }
    closeEdge[k].lowcost=0;
    for(int i=1;i<G.vexnum;i++)
    {
        k=Min(closeEdge);
        //输出生成树上一条边
        cout<<closeEdge[k].adjvex<<" "<<G.vexs[k]<<endl;
        closeEdge[k].lowcost=0;
        for(int j=0;j<G.vexnum;j++)
        {
            if(G.arcs[k][j]<closeEdge[j].lowcost)
            closeEdge[j]={G.vexs[k],G.arcs[k][j]};
        }
    }
}
*/

int main()
{
    int kind;
    cout<<"输入创建的图的类型(有向图DG)0(有向网DN)1(无向图UDG)2(无向网UDN)3：";
    cin>>kind;
    AMGraph G;
    if(kind==0) G.kind = DG;
    else if(kind==1) G.kind = DN;
    else if(kind==2) G.kind = UDG;
    else if(kind==3) G.kind = UDN;
    cout<<G.kind<<endl;
    CreateGraph(G);
    PrintArc(G);

    cout<<"深度优先遍历结果:"<<endl;//12
    DFS_AM(G,0);
    cout<<endl;
    cout<<"广度优先遍历结果:"<<endl;
    //BFS_AM(G,0);
    BFSTraverse(G);

    if(G.kind%2) //是网
    {
        cout<<"最短路径算法"<<endl;//举例 23
        int D[MVNum];
        int path[MVNum][MVNum];
        ShortestPath_DIJ(G,D,path,0);
        printShortestPath(G,path);
        printShortestPathFromV(G,D,path,0);
    }

    return 0;
}
