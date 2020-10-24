#include <iostream>
#include <queue>
/**
 *  �Զ���������Ϊ�������Ĵ洢�ṹ����дһ���㷨��
 */

#define MAXTSIZE 100

using namespace std;
typedef char TElemType;
typedef TElemType SqBiTree[MAXTSIZE];
SqBiTree bt;
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

//������������
void CreateBiTree(BiTree &T)
{
    char ch;
    cin>>ch;

    if(ch=='#')
        T=NULL;
    else
    {
        T=new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

//����
void PreOrderTraverse(BiTree T)
{
    if(T)
    {
        cout<<T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
//����
void InOrderTraverse(BiTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        cout<<T->data;
        InOrderTraverse(T->rchild);
    }
}
//����
void PostOrderTraverse(BiTree T)
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data;
    }
}

//������
int NodeCount(BiTree T)
{
    if(T==NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

//ͳ�ƶ�������Ҷ������
int LeefCount(BiTree T)
{
    if(!T)
        return 0;
    else if(!(T->lchild)&&!(T->rchild))
        return 1;
    else
        return LeefCount(T->lchild) + LeefCount(T->rchild);
}

//�б��������Ƿ����
bool __isBiTreesEqual(BiTree T1,BiTree T2)
{
    if(T1==NULL&&T2==NULL)
        return true;
    else if (T1->data!=T2->data)
        return false;
    else
        return __isBiTreesEqual(T1->lchild,T2->lchild)&&__isBiTreesEqual(T1->rchild,T2->rchild);
    return false;

}
bool isBiTreesEqual(BiTree T1,BiTree T2)
{
    bool t1=true,t2=true;
    if(!T1) t1=false;
    if(!T2) t2=false;
    //����������
    if(NodeCount(T1)!=NodeCount(T2)) return false;
    if(!t1&&!t2)
        return true;
    else if(t1&&t2)
    {
        return __isBiTreesEqual(T1,T2);
    }
    else
        return false;
}

//����
void Copy(BiTree T, BiTree &NewT)
{
    if(T==NULL)
    {
        NewT = NULL;
        return ;
    }
    else
    {
        NewT = new BiTNode;
        NewT->data = T->data;
        Copy(T->lchild,NewT->lchild);
        Copy(T->rchild,NewT->rchild);
    }
}
//����������ÿ���������Ӻ��Һ���
void ChangeLR(BiTree T, BiTree &NewT)
{
    if(T==NULL)
    {
        NewT = NULL;
        return ;
    }
    else
    {
        NewT = new BiTNode;
        NewT->data = T->data;
        ChangeLR(T->lchild,NewT->rchild);
        ChangeLR(T->rchild,NewT->lchild);
    }
}

//��α���
void printLevelOrder(BiTree T) {
    if (T==NULL)  return;
    // ����һ���ն���
    queue<BiTNode *> q;
    q.push(T);

    while (q.empty() == false) {
        // ������ǰ�ڵ�
        BiTNode *node = q.front();
        cout<<node->data;
        q.pop();

        // ���ӽڵ����
        if (node->lchild != NULL)
            q.push(node->lchild);

        // ���ӽڵ����
        if (node->rchild != NULL)
            q.push(node->rchild);
    }
}

//�ð����˳������������ķ�����ͳ�����ж�Ϊ1�Ľ����Ŀ
int OneDegreeCount(BiTree T) {
    if (T==NULL)  return 0;
    // ����һ���ն���
    queue<BiTNode *> q;
    q.push(T);
    int sum = 0;

    while (q.empty() == false) {
        // ������ǰ�ڵ�
        BiTNode *node = q.front();
        q.pop();

        // ���ӽڵ����
        if (node->lchild != NULL)
            q.push(node->lchild);

        // ���ӽڵ����
        if (node->rchild != NULL)
            q.push(node->rchild);

        if((node->rchild!=NULL&&node->lchild==NULL)||
            (node->lchild!=NULL&&node->rchild==NULL))
            sum++;
    }
    return sum;
}

//�������/�߶�
int getTreeHeight(BiTree T)
{
    if(T==NULL) return 0;
    int lheight = getTreeHeight(T->lchild);
    int rheight = getTreeHeight(T->rchild);
    return max(lheight,rheight) +1;
}

void Info(BiTree T1, BiTree T2)
{
    cout<<"Ҷ�����"<<endl;
    cout<<"T1:"<<LeefCount(T1)<<endl;
    cout<<"T2:"<<LeefCount(T2)<<endl;
    cout<<"�����"<<endl;
    cout<<"T1:"<<NodeCount(T1)<<endl;
    cout<<"T2:"<<NodeCount(T2)<<endl;
    cout<<"���ĸ߶�"<<endl;
    cout<<"T1:"<<getTreeHeight(T1)<<endl;
    cout<<"T2:"<<getTreeHeight(T2)<<endl;
    cout<<"�������"<<endl;
    PreOrderTraverse(T1);
    cout<<endl;
    PreOrderTraverse(T2);
    cout<<endl;
    cout<<"�������"<<endl;
    InOrderTraverse(T1);
    cout<<endl;
    InOrderTraverse(T2);
    cout<<endl;
    cout<<"�������"<<endl;
    PostOrderTraverse(T1);
    cout<<endl;
    PostOrderTraverse(T2);
    cout<<endl;
    cout<<"��α���"<<endl;
    printLevelOrder(T1);
    cout<<endl;
    printLevelOrder(T2);
    cout<<endl;
    cout<<"�Ƿ����:"<<isBiTreesEqual(T1,T2)<<endl;
	cout<<"��α���Ѱ�Ҷ���Ϊ1�Ľ������="<<OneDegreeCount(T1)<<endl;
}

int main() {
    BiTree T1,T2,NewT;

    cout<<"�����������ַ�����T1��"<<endl;
    CreateBiTree(T1);

    //CreateBiTree(T2);
    //Info(T1,T2);

    cout<<"����T1��ÿ���������Ӻ��Һ���:"<<endl;
    ChangeLR(T1,NewT);
    Info(T1,NewT);
    return 0;
}
