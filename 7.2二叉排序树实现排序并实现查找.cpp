#include <iostream>

#define KeyType int
#define InfoType int

using namespace std;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
}ElemType;

typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

//�ж��Ƿ�Ϊ���������
bool isBST(BSTNode *T)
{
    if(!T)
    {
        cout<<"Ϊ����"<<endl;
        return true;
    }
    BSTNode *l = T->lchild;
    BSTNode *r = T->rchild;
    while(l!=NULL)
    {
        if(T->data.key<=l->data.key) return false; //��������ҪС�ڸ��ڵ�
        l = l -> rchild;
    }
    while(r!=NULL)
    {
        if(T->data.key>=r->data.key) return false; //��������ҪС�ڸ��ڵ�
        l = l -> lchild;
    }
    return isBST(T->lchild)&&isBST(T->rchild);
}

int last = 0, flag = 1; //������������ǰ���ڵ�һ���Ⱥ�̽ڵ�С
bool Is_BSTree(BSTree T)
{
    if(T->lchild&&flag) Is_BSTree(T->lchild);
    if(T->data.key<last) flag = 0;
    last = T->data.key;
    if(T->rchild&&flag) Is_BSTree(T->rchild);
    return flag;
}

//����������:����ָ������
int search_times = 0;
BSTree SearchBST(BSTree T, KeyType key)
{
    search_times++;
    if((!T)||key==T->data.key) return T;
    else if(key<T->data.key) return SearchBST(T->lchild,key);
    else return SearchBST(T->rchild,key);
}

int InsertBST(BSTNode * &p,KeyType k,InfoType i)
{
     if(p==NULL)
     {
       p=(BSTNode*)malloc(sizeof(BSTNode));
       p->data.key=k;
       p->data.otherinfo=i;
       p->lchild=p->rchild=nullptr;
       return 1;
     }
     else if(k==p->data.key)
       return 0;
     else if(k<p->data.key)
       return InsertBST(p->lchild, k, i);
     else
       return InsertBST(p->rchild, k, i);
}

BSTNode *CreateBST(KeyType K[], int n)
{
    BSTNode *B = nullptr;
    InfoType info;
    int i = 0;
    while(i<n)
    {
        info = i;
        InsertBST(B,K[i],info);
        i++;
    }
    return B;
}
void printTraverse(BSTNode *T,int n)
{
    if(NULL!=T)
    {
        if(n==1) cout<<"rchild:";
        else if(n==2) cout<<"root:";
        else cout<<"lchild";
        cout<<T->data.key<<endl;
        printTraverse(T->lchild,0);
        printTraverse(T->rchild,1);
    } else {
        if(n) cout<<"rchild:";
        else if(n==2) cout<<"root:";
        else cout<<"lchild";
        cout<<"null"<<endl;
    }
}
int main()
{
    int N;
    cout<<"�������鳤��:";
    cin>>N;
    KeyType K[N];
    for(int i=0;i<N;i++)
    {
        cout<<"�����"<<i+1<<"��Ԫ��"<<endl;
        cin>>K[i];
    }
    BSTNode *B = CreateBST(K,N);
    if(Is_BSTree(B))
        cout<<"�����ɹ�"<<endl;
    else
        cout<<"ERROR"<<endl;

    cout<<"------���������------"<<endl;
    printTraverse(B,2);
    cout<<"----------------------"<<endl;

    KeyType key;
    cout<<"����������ҵ�key:";
    cin>>key;
    BSTree BST = SearchBST(B,key);
    if(BST==NULL) cout<<"û���ҵ�,����"<<search_times<<"��"<<endl;
    else
    {
        cout<<"�ҵ�,index="<<BST->data.otherinfo<<",key="<<BST->data.key<<"����"<<search_times<<"��"<<endl;
    }
    return 0;
}
