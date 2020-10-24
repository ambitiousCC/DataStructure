#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <iomanip>
#include <queue>
#include <algorithm>

#define MVNum 100
#define QElemType int
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define NO_PATH -1
#define MaxInt 32767
#define MAXQSIZE 100
using namespace std;
typedef int VertexType; //顶点类型
typedef int ArcType;    //边的类型
typedef enum{
    DG,//有向图
    DN,//有向网//
    UDG,//无向图
    UDN//无向网
}GraphKind;
//边结点
typedef struct ArcNode
{
    int adjvex;//边指向的顶点位置
    struct ArcNode * nextarc;//下一条边的指针
    int weight;//边的信息
}ArcNode;

//顶点信息
typedef struct VNode
{
    VertexType data;
    ArcNode * firstarc;//指向第一条依附该顶点的指针
}VNode,AdjList[MVNum];//邻接表类型

//邻接表
typedef struct
{
    AdjList vertices; //邻接表
    int vexnum,arcnum;//当前顶点数和边数
    int kind; //图的种类：0无向图/1有向图
}ALGraph;

//顶点节点，保存id和到源顶点的估算距离，优先队列需要的类型
struct Node
{
    int id;//源顶点id
    int w;//估算距离

    //因要实现最小堆，按升序排列，因而需要重载运算符，重定义优先级，以小为先
    friend bool operator < (struct Node a, struct Node b)
    {
        return a.w > b.w;
    }
};

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

//队列操作
Status InitQueue(SqQueue &Q)
{
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front=Q.rear=0;
    return OK;
}
//入队
Status EnQueue(SqQueue &Q,QElemType e)
{
    if((Q.rear+1)%MAXQSIZE==Q.front)
        return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}
//出队
Status DeQueue(SqQueue &Q, QElemType &e)
{
    //删除队头并返回
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1) % MAXQSIZE;
    return OK;
}
//判断队列为空
bool QueueEmpty(SqQueue Q)
{
    return Q.front==Q.rear;
}

//基本操作
int LocateVex(ALGraph G, VertexType v)
{
    int i;
    for(i=0;i<G.vexnum && G.vertices[i].data!=v;i++)
        continue;
    return i;
}

//返回v的第一个邻接顶点
int FirstAdjVex(ALGraph G, int v)
{
	if (G.vertices[v].firstarc)
		return G.vertices[v].firstarc->adjvex;
	return -1;
}

//返回顶点v相对于邻接点w的下一个邻接点
int NextAdjVex(ALGraph G, int v, int w)
{
	ArcNode *p;
	p = G.vertices[v].firstarc;
	if (p){
		while (p){
			if (w == p->adjvex){
				if (NULL == p->nextarc)
					return -1;
				else
					return p->nextarc->adjvex;
			}
			p = p->nextarc;
		}
	}
	return -1;
}

//采用邻接表构造图G
Status CreateGraph(ALGraph &G)
{
	int weight;
	VertexType v1,v2;
	ArcNode *p1, *p2;
    cout<<"请输入总顶点数和总边数，空格隔开:";
	cin >> G.vexnum >> G.arcnum;
	//构造邻接表
	for (int i = 0; i < G.vexnum; i++)
    {
		cout << "请输入顶点vex[" << i << "]的值：";
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = nullptr;
	}
	cout<<endl;
	for (int j = 0; j<G.arcnum; j++)
	{
	    if(0==G.kind||1==G.kind)//是有向
            cout<<"输入<v1,v2>作为边（空格隔开）：";
        else
            cout<<"输入(v1,v2)作为边（空格隔开）：";
		cin >>v1>>v2;
		int index1 = LocateVex(G,v1);
		int index2 = LocateVex(G,v2);

        p1 = new ArcNode;
        p1->adjvex=index2;
        p1->nextarc=G.vertices[index1].firstarc;
        G.vertices[index1].firstarc = p1;

        if(2==G.kind||3==G.kind)//无向需要在两个顶点处同时插入
        {
            p2 = new ArcNode;
            p2->adjvex=index1;
            p2->nextarc=G.vertices[index2].firstarc;
            G.vertices[index2].firstarc=p2;
        }

        if(G.kind%2) //网
        {
			cout << "请输入该弧（边）的权值：";
			cin >> weight;
			p1->weight = weight;
            if(3==G.kind)//无向网
                p2->weight = weight;
        }
        else
        {
			p1->weight = 0;//置为空值
			if(2==G.kind)//无向图
                p2->weight = 0;
        }
	}

	return OK;
}

//增加一个新顶点v, InsertVex(G,v)
void InsertVex(ALGraph &G,VertexType v)
{
    G.vexnum++;
    G.vertices[G.vexnum-1].data = v; //顶点值
    G.vertices[G.vexnum-1].firstarc=NULL; //初始化表头结点指针
}
//删除顶点v以及相关的边，DeleteVex(G,v)
bool DeleteVex(ALGraph &G,VertexType v)
{
    //1. 删除以v为出度的边
    ArcNode *p,*q;
    int location = LocateVex(G,v);
    if(location<0)
        return false;
    p=G.vertices[location].firstarc;
    while(p)
    {
        q=p;
        p=p->nextarc;
        q=NULL;
        G.arcnum--;
    }
    G.vexnum--;//顶点数减少
    //2. 顶点v后面的顶点前移
    for(int i=location;i<G.vexnum;i++)
        G.vertices[i]=G.vertices[i+1];
    //3. 删除以v为入度的边并且修改表结点的顶点位置
    for(int i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            if(p->adjvex==v)//边结点信息
            {
                if(p==G.vertices[i].firstarc)//删除的是第一个结点
                {
                    G.vertices[i].firstarc=p->nextarc;
                    p=NULL;
                    p=G.vertices[i].firstarc;
                }
                else
                {
                    q->nextarc=p->nextarc;
                    p=NULL;
                    p=q->nextarc;
                }
            }
            else
            {
                if(p->adjvex>location)
                    p->adjvex--;//如果指向大于那个，就只需要修改表姐点的顶点位置
                q=p;
                p=p->nextarc;
            }
        }
    }
}
//增加一条边<v,w>, InsertArc(G,v,w)
bool InsertArc(ALGraph &G,VertexType v,VertexType w)
{
    //增加的顶点位置
    ArcNode *p;
    int index1 = LocateVex(G,v);
    int index2 = LocateVex(G,w);
    if(index1<0||index2<0)
        return false;
    G.arcnum++;
    p->adjvex=index2;
    p->nextarc=G.vertices[index1].firstarc;//表头
    G.vertices[index1].firstarc=p;
    //如果是无向图：就需要对称的一条弧

    return true;
}
//删除一条边<v,w>, DeleteArc(G,v,w)
bool DeleteArc(ALGraph &G,VertexType v,VertexType w)
{
    ArcNode *p,*q;
    int index1 = LocateVex(G,v);
    int index2 = LocateVex(G,w);
    if(index1<0||index2<0||index1==index2)//不重复
        return false;
    p=G.vertices[index1].firstarc;
    while(p&&p->adjvex!=index2)
    {
        q=p;
        p=p->nextarc;
    }
    if(p&&p->adjvex==index2)
    {
        if(p==G.vertices[index1].firstarc)//p是第一条弧
            G.vertices[index1].firstarc=p->nextarc;//指向下一条
        else
            q->nextarc=p->nextarc;//否则使用中间变量q指向下一条
        p=NULL;//释放节点
        G.arcnum--;
    }
    //无向操作：
    return true;
}

//打印邻接表
void PrintALGraph(ALGraph G)
{
	ArcNode *p;
	for (int i = 0; i < G.vexnum; i++){
		cout << G.vertices[i].data;
		if (G.vertices[i].firstarc){
			p = G.vertices[i].firstarc;
			while (p){
				if (2 == G.kind || 3 == G.kind)
					cout << "-" << G.vertices[p->adjvex].data;
				else
					cout << "→" << G.vertices[p->adjvex].data;
				p = p->nextarc;
			}
		}
		cout << endl;
	}
}

//深度优先遍历
void DFS(ALGraph G, int v)
{
	visited[v] = true;
	cout<<G.vertices[v].data<<" ";

    ArcNode *p = G.vertices[v].firstarc;
    while(p)
    {
        if(!visited[p->adjvex])
            DFS(G,p->adjvex);
        p=p->nextarc;
    }
}

void DFSTraverse(ALGraph G)
{
	int i;
	cout << "深度优先结果：" <<endl;
	for (i = 0; i < G.vexnum; i++)
		visited[i] = false;
	for (i = 0; i < G.vexnum; i++){
		if (!visited[i])
			DFS(G, i);
	}
	cout<<endl;
}

//广度优先遍历
void BFS(ALGraph G)
{
    VertexType v = 0;
    reVisited(visited);
    SqQueue Q;
    InitQueue(Q);
    int l = 0, r = 0;
    EnQueue(Q,v);//入队:默认从第一个
    cout<<G.vertices[v].data<<" ";
    ArcNode *tmp = new ArcNode;
    while(!QueueEmpty(Q)) //队列不为空
    {
        int u;
        DeQueue(Q,u);
        tmp = G.vertices[u].firstarc;
        while(tmp)
        {
            VertexType pos = tmp->adjvex;
            if(!visited[pos])
            {
                cout<<G.vertices[pos].data<<" ";
                visited[pos] = true;
                EnQueue(Q,pos);
            }
            tmp = tmp->nextarc;
        }
    }
    cout<<endl;
}
/*
//最短路径算法
void Dijkstra(ALGraph G,int D[],int path[][MVNum],int v0)
{
    cout<<"flag"<<endl;
    int i,j,mindist,k,t;
    ArcNode *p;
    for(i=0;i<G.vexnum;i++){    //初始化最短路径数组D,和标记此顶点是否已经找到最短路径的path[i][0],等于0表示没有找到,等于1表示找到.
        D[i]=MaxInt;
        path[i][0]=0;
    }
    p=G.vertices[v0].firstarc->nextarc;
    cout<<"flag2"<<endl;
    while(p){                                  //保存源点到和此源点相关的顶点的路径.
        D[p->adjvex]=p->weight;
        path[p->adjvex][1]=v0;
        path[p->adjvex][2]=p->adjvex;
        path[p->adjvex][3]=0;
         p=p->nextarc;
    }
    cout<<"flag3"<<endl;
    path[v0][0]=1;               //源点标记为为1，其最短路径为0.此顶点以后不会再用到
    for(i=2;i<=G.vexnum;i++){                //选择最最短的路径
    cout<<"flag4"<<endl;
         mindist=MaxInt;
        for(j=1;j<=G.vexnum;j++){
            if(!path[j][0] && D[j] < mindist){
                k=j;
                mindist=D[j];
            }
        }
        if(mindist == MaxInt){         //如果没有找到最短的路径，则说明从此源点不能到任何其他顶点，直接返回.
            return;
        }
        path[k][0]=1;                  //标记找到最小路径的顶点，此顶点以后不会再用到.
        p=G.vertices[k].firstarc->nextarc;
        while(p)
        {
        cout<<"flag7"<<endl;
        cout<<path[p->adjvex][0]<<" "<< D[p->adjvex] << D[k]+ p->weight<<endl;
            if(!path[p->adjvex][0]&& D[p->adjvex] > D[k]+ p->weight){     //更新D，使其从保持从源点到和此顶点相关的顶点的路径最短.
                //printf("p->ad:%d ",p->adjvex);
                D[p->adjvex]=D[k]+p->weight;
                t=1;
    cout<<"flag7.5"<<endl;
                while(path[k][t]!=0)      //记录最新的路径
                {
                    path[p->adjvex][t]=path[k][t];
                    t++;
                }
                path[p->adjvex][t]=p->adjvex;
                path[p->adjvex][t+1]=0;                       //path[i][t+1]之前的都是最短路径所要经过的顶点，从t+1这里停止,作为最后输出路径的判断条件
            }
            p=p->nextarc;
        }
    cout<<"flag8"<<endl;
    }
}*/

int path[MVNum];
Node dist[MaxInt];
priority_queue<Node>q;
void ShortestPath_DIJ(ALGraph G, int v0)
{
    //初始化

    for(int i = 0; i < G.vexnum; i++)
    {
        dist[i].id = i;
        dist[i].w = MaxInt;
        path[i] = -1;       //每个顶点都无父亲节点
        visited[i] = false;     //都未找到最短路
    }
    dist[v0].w = 0;
    q.push(dist[v0]);
    while(!q.empty())
    {
        Node cd = q.top();
        q.pop();
        int u = cd.id;

        if(visited[u])
            continue;
        visited[u] = true;
        ArcNode *p = G.vertices[u].firstarc;

        while(p)
        {
            int tempv = p->adjvex;//点
            int tempw = p->weight;//权值

            if(!visited[tempv] && dist[tempv].w > dist[u].w+tempw)
            {
                dist[tempv].w = dist[u].w+tempw;
                path[tempv] = u;
                q.push(dist[tempv]);
            }
            p = p->nextarc;
        }
    }
}

int main()
{
    int kind;
    cout<<"输入创建的图的类型(有向图DG)0(有向网DN)1(无向图UDG)2(无向网UDN)3：";
    cin>>kind;
    ALGraph G;

    if(kind==0) G.kind = DG;
    else if(kind==1) G.kind = DN;
    else if(kind==2) G.kind = UDG;
    else if(kind==3) G.kind = UDN;
    cout<<G.kind<<endl;

    CreateGraph(G);

    cout<<"深度优先遍历结果:"<<endl;//12
    DFSTraverse(G);
    cout<<endl;
    cout<<"广度优先遍历结果:"<<endl;
    //BFS_AM(G,0);
    BFS(G);

    if(G.kind%2) //是网
    {
        cout<<"最短路径算法"<<endl;//举例 23
        int D[MVNum];
        int path[MVNum][MVNum];
        //Dijkstra(G,D,path,0);
        ShortestPath_DIJ(G,0);

        //输入顶点下标，搞清楚下标对应顶点，即可打印

        for(int i=0;i<G.vexnum;i++)
        {
            if(dist[i].w != MaxInt)
                cout<<"v0->v"<<G.vertices[i].data<<":"<<dist[i].w<<endl;
            else
                cout<<"v0->v"<<G.vertices[i].data<<":"<<"不可达"<<endl;
        }
    }

    return 0;
}
