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
//�洢�ṹ���ڽӾ�����ڽӱ�
//1. �ڽӾ���
typedef char VertexType;
typedef int ArcType;
typedef enum{
    DG,//����ͼ
    DN,//������//
    UDG,//����ͼ
    UDN//������
}GraphKind;
typedef struct
{
    VertexType vexs[MVNum]; //�����
    ArcType arcs[MVNum][MVNum]; //�ڽӾ���
    int vexnum,arcnum; //ͼ�Ķ���ͱ���
    GraphKind kind;
}AMGraph;

//�������
typedef struct
{
    QElemType *base;
    int front;
    int rear;
}SqQueue;
//������Ҫ�ķ�������
bool visited[MVNum] = {false};

void reVisited(bool * visited)
{
    for(int i=0;i<MVNum;i++)
        visited[i]=false;
}
/**********����ѭ������*******/
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


//��������
int LocateVex(AMGraph G, VertexType v)
{
    int i;
    for(i=0;i<G.vexnum && G.vexs[i]!=v;i++)
        continue;
    return i;
}

void CreateGraph(AMGraph &G)
{
    if(G.kind<0||G.kind>3) cout<<"����ͼ�����������ͼ�����Ƿ���ȷ"<<endl;
    cout<<"�������ܶ��������ܱ������ո����:";
    cin>>G.vexnum>>G.arcnum;
    int i,j;
    for(i=0;i<G.vexnum;i++)
    {
        cout<<"�����붥��vex[" << i << "]��ֵ��"<<endl;
        cin>>G.vexs[i];
    }
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
        {
            if(G.kind%2)//��
                G.arcs[i][j]=MaxInt;
            else
                G.arcs[i][j]=0;
        }

    for(int k=0;k<G.arcnum;k++)
    {

	    if(0==G.kind||1==G.kind)//������
            cout<<"����<v1,v2>��Ϊ�ߣ��ո��������";
        else
            cout<<"����(v1,v2)��Ϊ�ߣ��ո��������";
        VertexType v1,v2;
        cin>>v1>>v2;
        int index1 = LocateVex(G,v1);
        int index2 = LocateVex(G,v2);
        int w;
        if(G.kind%2)
        {
            cout<<"������ߵ�Ȩֵ:";
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
    cout<<"�������"<<endl;
}



//����һ���¶���v, InsertVex(G,v)
void InsertVex(AMGraph &G,VertexType v)
{
    int i;
    G.vexnum++;
    G.vexs[G.vexnum-1]=v; //�����¶�������
    //��ʼ������������
    //ע������Ŀ��Ż��߼����⣬���ظ���ֵ
    for(i=0;i<G.vexnum;i++)
        G.arcs[G.vexnum-1][i]=0;
    for(i=0;i<G.vexnum-1;i++)
        G.arcs[i][G.vexnum-1]=0;
}
//ɾ������v�Լ���صıߣ�DeleteVex(G,v)
bool DeleteVex(AMGraph &G,VertexType v)
{
    //1. �ҵ�����λ��
    int location = LocateVex(G,v);
    if(location<0)
        return false;
    //3. ���Ķ����������ݼ���С
    for(int i=location+1;i<G.vexnum;i++)
        G.vexs[i-1] = G.vexs[i];
    //4. �����ڽӾ���
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
//����һ����<v,w>, InsertArc(G,v,w)
bool InsertArc(AMGraph &G,VertexType v,VertexType w)
{
    //�ҵ����������λ��
    int vL = LocateVex(G,v);
    int wL = LocateVex(G,w);
    if(vL<0||wL<0)
        return false;
    //�����ڽӾ���
    G.arcs[vL][wL] = 1;
    G.arcs[wL][vL] = G.arcs[vL][wL];
    return true;
}
//ɾ��һ����<v,w>, DeleteArc(G,v,w)
bool DeleteArc(AMGraph &G,VertexType v,VertexType w)
{
    //�ҵ����������λ��
    int vL = LocateVex(G,v);
    int wL = LocateVex(G,w);
    if(vL<0||wL<0)
        return false;
    //�����ڽӾ���
    G.arcs[vL][wL] = 0;
    G.arcs[wL][vL] = G.arcs[vL][wL];
    return true;
}

//��ӡ�ڽӾ���
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

//������ȱ���
void DFS_AM(AMGraph G, int v)
{
    //�ӵ�v����������ݹ�������ȱ���ͼ
    int judge;
    if(G.kind%2) //����
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
//v�ĵ�һ���ڽӵ�
int FirstAdjVex(AMGraph G, VertexType v)
{
    int i;
    int j = 0;
    int k;
    cout<<"v:"<<v<<endl;
    k = LocateVex(G,v);

    cout<<"��ӡ�����"<<endl;
    for(int i=0;i<G.vexnum;i++)
        cout<<G.vexs[i]<<endl;

    cout<<"LocateVex(G,v):"<<k<<endl;

    if(G.kind%2) //����
        j = MaxInt;

    for(i=0;i<G.vexnum;i++)
        cout<<G.arcs[k][i]<<" ";

    cout<<endl;
    for(i=0;i<G.vexnum;i++)
        if(G.arcs[k][i]!=j)
            return i;
    return -1;
}

//v�൱��w����һ���ڽӵ㣬ֻҪ��ֵ�ʹ�������ڽӵ�
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

//������ȱ���
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
    //���ö���
    SqQueue Q;
    InitQueue(Q);

    EnQueue(Q,v);
    cout<<"flag2"<<endl;

    while(!QueueEmpty(Q))
    {
        cout<<"flag3"<<endl;
        //���Ӳ��ҳ���Ԫ��Ϊu
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


//Dijkstra�㷨ʵ����������v0���㵽���ඥ������·��
void ShortestPath_DIJ(AMGraph G,int D[],int path[][MVNum],int v0)
{
    int n = G.vexnum;
    int v,w;
    bool S[MVNum];
    for(v =0;v<n;v++)
    {
        S[v] = false;
        D[v] = G.arcs[v0][v];//���V0��V�����·������ʼֵΪֱ�Ӿ���
        //��ʼ��path����
        for(w=0;w<n;w++)
            path[v][w]= -1;
        if(D[v]<MaxInt)//��ֱ��·��
        {
            path[v][0] = v0; //���·��������һ������
            path[v][1] = v;  //���·�������ڶ�������
        }
    }
    S[v0]=true;//V0����S
    D[v0]=0;//v0-v0��0

    //��ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S��
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
        S[v]=true;//��v����S
        for(w=0;w<n;w++)
        {//���´�v0����������V-S���ж�������·������
            if(!S[w]
               &&(D[v]+G.arcs[v][w])
               &&minN<MaxInt
               &&G.arcs[v][w]<MaxInt
               &&(minN+G.arcs[v][w]<D[w]))
            {
              //w������S����v0->v->w�ľ���<Ŀǰv0->w�ľ���
					D[w]=minN+G.arcs[v][w];//����D[w]
					for(int j=0; j<G.vexnum; j++)//�޸�p[w]��v0��w�����Ķ������v0��v���������ж����ټ��϶���w
					{
						path[w][j]=path[v][j];
						if(path[w][j]==-1)//��p[w][]��һ������-1�ĵط����϶���w
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
    cout<<"���·������:"<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            cout<<setw(4)<<path[i][j]<<" ";
        cout<<endl;
    }
}

void printShortestPathFromV(AMGraph G,int D[], int path[][MVNum], int n)
{
    cout<<G.vexs[n]<<"�����������·���Լ����ȣ�"<<endl;
    for(int i=0;i<G.vexnum;i++)
    {
        if(i!=0 && D[i]!=MaxInt)
        {
            cout<<G.vexs[n]<<"->"<<G.vexs[i]<<"="<<D[i]<<" ";
            cout<<"���·��:";
            for(int j=0;j<G.vexnum;j++)
            {
                if(path[i][j]>-1)
                    cout<<G.vexs[path[i][j]]<<" ";
            }
            cout<<endl;
        }
        else if(D[i]==MaxInt)
            cout<<G.vexs[n]<<"->"<<G.vexs[i]<<":"<<"��ͨ"<<endl;
    }
}

/*



//����������С������
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
        //�����������һ����
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
    cout<<"���봴����ͼ������(����ͼDG)0(������DN)1(����ͼUDG)2(������UDN)3��";
    cin>>kind;
    AMGraph G;
    if(kind==0) G.kind = DG;
    else if(kind==1) G.kind = DN;
    else if(kind==2) G.kind = UDG;
    else if(kind==3) G.kind = UDN;
    cout<<G.kind<<endl;
    CreateGraph(G);
    PrintArc(G);

    cout<<"������ȱ������:"<<endl;//12
    DFS_AM(G,0);
    cout<<endl;
    cout<<"������ȱ������:"<<endl;
    //BFS_AM(G,0);
    BFSTraverse(G);

    if(G.kind%2) //����
    {
        cout<<"���·���㷨"<<endl;//���� 23
        int D[MVNum];
        int path[MVNum][MVNum];
        ShortestPath_DIJ(G,D,path,0);
        printShortestPath(G,path);
        printShortestPathFromV(G,D,path,0);
    }

    return 0;
}
