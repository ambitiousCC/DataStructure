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
typedef int VertexType; //��������
typedef int ArcType;    //�ߵ�����
typedef enum{
    DG,//����ͼ
    DN,//������//
    UDG,//����ͼ
    UDN//������
}GraphKind;
//�߽��
typedef struct ArcNode
{
    int adjvex;//��ָ��Ķ���λ��
    struct ArcNode * nextarc;//��һ���ߵ�ָ��
    int weight;//�ߵ���Ϣ
}ArcNode;

//������Ϣ
typedef struct VNode
{
    VertexType data;
    ArcNode * firstarc;//ָ���һ�������ö����ָ��
}VNode,AdjList[MVNum];//�ڽӱ�����

//�ڽӱ�
typedef struct
{
    AdjList vertices; //�ڽӱ�
    int vexnum,arcnum;//��ǰ�������ͱ���
    int kind; //ͼ�����ࣺ0����ͼ/1����ͼ
}ALGraph;

//����ڵ㣬����id�͵�Դ����Ĺ�����룬���ȶ�����Ҫ������
struct Node
{
    int id;//Դ����id
    int w;//�������

    //��Ҫʵ����С�ѣ����������У������Ҫ������������ض������ȼ�����СΪ��
    friend bool operator < (struct Node a, struct Node b)
    {
        return a.w > b.w;
    }
};

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

//���в���
Status InitQueue(SqQueue &Q)
{
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front=Q.rear=0;
    return OK;
}
//���
Status EnQueue(SqQueue &Q,QElemType e)
{
    if((Q.rear+1)%MAXQSIZE==Q.front)
        return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}
//����
Status DeQueue(SqQueue &Q, QElemType &e)
{
    //ɾ����ͷ������
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1) % MAXQSIZE;
    return OK;
}
//�ж϶���Ϊ��
bool QueueEmpty(SqQueue Q)
{
    return Q.front==Q.rear;
}

//��������
int LocateVex(ALGraph G, VertexType v)
{
    int i;
    for(i=0;i<G.vexnum && G.vertices[i].data!=v;i++)
        continue;
    return i;
}

//����v�ĵ�һ���ڽӶ���
int FirstAdjVex(ALGraph G, int v)
{
	if (G.vertices[v].firstarc)
		return G.vertices[v].firstarc->adjvex;
	return -1;
}

//���ض���v������ڽӵ�w����һ���ڽӵ�
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

//�����ڽӱ���ͼG
Status CreateGraph(ALGraph &G)
{
	int weight;
	VertexType v1,v2;
	ArcNode *p1, *p2;
    cout<<"�������ܶ��������ܱ������ո����:";
	cin >> G.vexnum >> G.arcnum;
	//�����ڽӱ�
	for (int i = 0; i < G.vexnum; i++)
    {
		cout << "�����붥��vex[" << i << "]��ֵ��";
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = nullptr;
	}
	cout<<endl;
	for (int j = 0; j<G.arcnum; j++)
	{
	    if(0==G.kind||1==G.kind)//������
            cout<<"����<v1,v2>��Ϊ�ߣ��ո��������";
        else
            cout<<"����(v1,v2)��Ϊ�ߣ��ո��������";
		cin >>v1>>v2;
		int index1 = LocateVex(G,v1);
		int index2 = LocateVex(G,v2);

        p1 = new ArcNode;
        p1->adjvex=index2;
        p1->nextarc=G.vertices[index1].firstarc;
        G.vertices[index1].firstarc = p1;

        if(2==G.kind||3==G.kind)//������Ҫ���������㴦ͬʱ����
        {
            p2 = new ArcNode;
            p2->adjvex=index1;
            p2->nextarc=G.vertices[index2].firstarc;
            G.vertices[index2].firstarc=p2;
        }

        if(G.kind%2) //��
        {
			cout << "������û����ߣ���Ȩֵ��";
			cin >> weight;
			p1->weight = weight;
            if(3==G.kind)//������
                p2->weight = weight;
        }
        else
        {
			p1->weight = 0;//��Ϊ��ֵ
			if(2==G.kind)//����ͼ
                p2->weight = 0;
        }
	}

	return OK;
}

//����һ���¶���v, InsertVex(G,v)
void InsertVex(ALGraph &G,VertexType v)
{
    G.vexnum++;
    G.vertices[G.vexnum-1].data = v; //����ֵ
    G.vertices[G.vexnum-1].firstarc=NULL; //��ʼ����ͷ���ָ��
}
//ɾ������v�Լ���صıߣ�DeleteVex(G,v)
bool DeleteVex(ALGraph &G,VertexType v)
{
    //1. ɾ����vΪ���ȵı�
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
    G.vexnum--;//����������
    //2. ����v����Ķ���ǰ��
    for(int i=location;i<G.vexnum;i++)
        G.vertices[i]=G.vertices[i+1];
    //3. ɾ����vΪ��ȵı߲����޸ı���Ķ���λ��
    for(int i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            if(p->adjvex==v)//�߽����Ϣ
            {
                if(p==G.vertices[i].firstarc)//ɾ�����ǵ�һ�����
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
                    p->adjvex--;//���ָ������Ǹ�����ֻ��Ҫ�޸ı���Ķ���λ��
                q=p;
                p=p->nextarc;
            }
        }
    }
}
//����һ����<v,w>, InsertArc(G,v,w)
bool InsertArc(ALGraph &G,VertexType v,VertexType w)
{
    //���ӵĶ���λ��
    ArcNode *p;
    int index1 = LocateVex(G,v);
    int index2 = LocateVex(G,w);
    if(index1<0||index2<0)
        return false;
    G.arcnum++;
    p->adjvex=index2;
    p->nextarc=G.vertices[index1].firstarc;//��ͷ
    G.vertices[index1].firstarc=p;
    //���������ͼ������Ҫ�ԳƵ�һ����

    return true;
}
//ɾ��һ����<v,w>, DeleteArc(G,v,w)
bool DeleteArc(ALGraph &G,VertexType v,VertexType w)
{
    ArcNode *p,*q;
    int index1 = LocateVex(G,v);
    int index2 = LocateVex(G,w);
    if(index1<0||index2<0||index1==index2)//���ظ�
        return false;
    p=G.vertices[index1].firstarc;
    while(p&&p->adjvex!=index2)
    {
        q=p;
        p=p->nextarc;
    }
    if(p&&p->adjvex==index2)
    {
        if(p==G.vertices[index1].firstarc)//p�ǵ�һ����
            G.vertices[index1].firstarc=p->nextarc;//ָ����һ��
        else
            q->nextarc=p->nextarc;//����ʹ���м����qָ����һ��
        p=NULL;//�ͷŽڵ�
        G.arcnum--;
    }
    //���������
    return true;
}

//��ӡ�ڽӱ�
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
					cout << "��" << G.vertices[p->adjvex].data;
				p = p->nextarc;
			}
		}
		cout << endl;
	}
}

//������ȱ���
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
	cout << "������Ƚ����" <<endl;
	for (i = 0; i < G.vexnum; i++)
		visited[i] = false;
	for (i = 0; i < G.vexnum; i++){
		if (!visited[i])
			DFS(G, i);
	}
	cout<<endl;
}

//������ȱ���
void BFS(ALGraph G)
{
    VertexType v = 0;
    reVisited(visited);
    SqQueue Q;
    InitQueue(Q);
    int l = 0, r = 0;
    EnQueue(Q,v);//���:Ĭ�ϴӵ�һ��
    cout<<G.vertices[v].data<<" ";
    ArcNode *tmp = new ArcNode;
    while(!QueueEmpty(Q)) //���в�Ϊ��
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
//���·���㷨
void Dijkstra(ALGraph G,int D[],int path[][MVNum],int v0)
{
    cout<<"flag"<<endl;
    int i,j,mindist,k,t;
    ArcNode *p;
    for(i=0;i<G.vexnum;i++){    //��ʼ�����·������D,�ͱ�Ǵ˶����Ƿ��Ѿ��ҵ����·����path[i][0],����0��ʾû���ҵ�,����1��ʾ�ҵ�.
        D[i]=MaxInt;
        path[i][0]=0;
    }
    p=G.vertices[v0].firstarc->nextarc;
    cout<<"flag2"<<endl;
    while(p){                                  //����Դ�㵽�ʹ�Դ����صĶ����·��.
        D[p->adjvex]=p->weight;
        path[p->adjvex][1]=v0;
        path[p->adjvex][2]=p->adjvex;
        path[p->adjvex][3]=0;
         p=p->nextarc;
    }
    cout<<"flag3"<<endl;
    path[v0][0]=1;               //Դ����ΪΪ1�������·��Ϊ0.�˶����Ժ󲻻����õ�
    for(i=2;i<=G.vexnum;i++){                //ѡ������̵�·��
    cout<<"flag4"<<endl;
         mindist=MaxInt;
        for(j=1;j<=G.vexnum;j++){
            if(!path[j][0] && D[j] < mindist){
                k=j;
                mindist=D[j];
            }
        }
        if(mindist == MaxInt){         //���û���ҵ���̵�·������˵���Ӵ�Դ�㲻�ܵ��κ��������㣬ֱ�ӷ���.
            return;
        }
        path[k][0]=1;                  //����ҵ���С·���Ķ��㣬�˶����Ժ󲻻����õ�.
        p=G.vertices[k].firstarc->nextarc;
        while(p)
        {
        cout<<"flag7"<<endl;
        cout<<path[p->adjvex][0]<<" "<< D[p->adjvex] << D[k]+ p->weight<<endl;
            if(!path[p->adjvex][0]&& D[p->adjvex] > D[k]+ p->weight){     //����D��ʹ��ӱ��ִ�Դ�㵽�ʹ˶�����صĶ����·�����.
                //printf("p->ad:%d ",p->adjvex);
                D[p->adjvex]=D[k]+p->weight;
                t=1;
    cout<<"flag7.5"<<endl;
                while(path[k][t]!=0)      //��¼���µ�·��
                {
                    path[p->adjvex][t]=path[k][t];
                    t++;
                }
                path[p->adjvex][t]=p->adjvex;
                path[p->adjvex][t+1]=0;                       //path[i][t+1]֮ǰ�Ķ������·����Ҫ�����Ķ��㣬��t+1����ֹͣ,��Ϊ������·�����ж�����
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
    //��ʼ��

    for(int i = 0; i < G.vexnum; i++)
    {
        dist[i].id = i;
        dist[i].w = MaxInt;
        path[i] = -1;       //ÿ�����㶼�޸��׽ڵ�
        visited[i] = false;     //��δ�ҵ����·
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
            int tempv = p->adjvex;//��
            int tempw = p->weight;//Ȩֵ

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
    cout<<"���봴����ͼ������(����ͼDG)0(������DN)1(����ͼUDG)2(������UDN)3��";
    cin>>kind;
    ALGraph G;

    if(kind==0) G.kind = DG;
    else if(kind==1) G.kind = DN;
    else if(kind==2) G.kind = UDG;
    else if(kind==3) G.kind = UDN;
    cout<<G.kind<<endl;

    CreateGraph(G);

    cout<<"������ȱ������:"<<endl;//12
    DFSTraverse(G);
    cout<<endl;
    cout<<"������ȱ������:"<<endl;
    //BFS_AM(G,0);
    BFS(G);

    if(G.kind%2) //����
    {
        cout<<"���·���㷨"<<endl;//���� 23
        int D[MVNum];
        int path[MVNum][MVNum];
        //Dijkstra(G,D,path,0);
        ShortestPath_DIJ(G,0);

        //���붥���±꣬������±��Ӧ���㣬���ɴ�ӡ

        for(int i=0;i<G.vexnum;i++)
        {
            if(dist[i].w != MaxInt)
                cout<<"v0->v"<<G.vertices[i].data<<":"<<dist[i].w<<endl;
            else
                cout<<"v0->v"<<G.vertices[i].data<<":"<<"���ɴ�"<<endl;
        }
    }

    return 0;
}
