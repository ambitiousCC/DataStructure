#include <iostream>
#include <queue>
/**
 *  以二叉链表作为二叉树的存储结构，编写一下算法：
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

//创建二叉链表
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

//先序
void PreOrderTraverse(BiTree T)
{
    if(T)
    {
        cout<<T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
//中序
void InOrderTraverse(BiTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        cout<<T->data;
        InOrderTraverse(T->rchild);
    }
}
//后序
void PostOrderTraverse(BiTree T)
{
    if(T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data;
    }
}

//结点个数
int NodeCount(BiTree T)
{
    if(T==NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

//统计二叉树的叶结点个数
int LeefCount(BiTree T)
{
    if(!T)
        return 0;
    else if(!(T->lchild)&&!(T->rchild))
        return 1;
    else
        return LeefCount(T->lchild) + LeefCount(T->rchild);
}

//判别两棵树是否相等
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
    //结点个数不等
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

//复制
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
//交换二叉树每个结点的左孩子和右孩子
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

//层次遍历
void printLevelOrder(BiTree T) {
    if (T==NULL)  return;
    // 创建一个空队列
    queue<BiTNode *> q;
    q.push(T);

    while (q.empty() == false) {
        // 遍历当前节点
        BiTNode *node = q.front();
        cout<<node->data;
        q.pop();

        // 左子节点入队
        if (node->lchild != NULL)
            q.push(node->lchild);

        // 右子节点入队
        if (node->rchild != NULL)
            q.push(node->rchild);
    }
}

//用按层次顺序遍历二叉树的方法，统计数中度为1的结点数目
int OneDegreeCount(BiTree T) {
    if (T==NULL)  return 0;
    // 创建一个空队列
    queue<BiTNode *> q;
    q.push(T);
    int sum = 0;

    while (q.empty() == false) {
        // 遍历当前节点
        BiTNode *node = q.front();
        q.pop();

        // 左子节点入队
        if (node->lchild != NULL)
            q.push(node->lchild);

        // 右子节点入队
        if (node->rchild != NULL)
            q.push(node->rchild);

        if((node->rchild!=NULL&&node->lchild==NULL)||
            (node->lchild!=NULL&&node->rchild==NULL))
            sum++;
    }
    return sum;
}

//计算深度/高度
int getTreeHeight(BiTree T)
{
    if(T==NULL) return 0;
    int lheight = getTreeHeight(T->lchild);
    int rheight = getTreeHeight(T->rchild);
    return max(lheight,rheight) +1;
}

void Info(BiTree T1, BiTree T2)
{
    cout<<"叶结点数"<<endl;
    cout<<"T1:"<<LeefCount(T1)<<endl;
    cout<<"T2:"<<LeefCount(T2)<<endl;
    cout<<"结点数"<<endl;
    cout<<"T1:"<<NodeCount(T1)<<endl;
    cout<<"T2:"<<NodeCount(T2)<<endl;
    cout<<"树的高度"<<endl;
    cout<<"T1:"<<getTreeHeight(T1)<<endl;
    cout<<"T2:"<<getTreeHeight(T2)<<endl;
    cout<<"先序遍历"<<endl;
    PreOrderTraverse(T1);
    cout<<endl;
    PreOrderTraverse(T2);
    cout<<endl;
    cout<<"中序遍历"<<endl;
    InOrderTraverse(T1);
    cout<<endl;
    InOrderTraverse(T2);
    cout<<endl;
    cout<<"后序遍历"<<endl;
    PostOrderTraverse(T1);
    cout<<endl;
    PostOrderTraverse(T2);
    cout<<endl;
    cout<<"层次遍历"<<endl;
    printLevelOrder(T1);
    cout<<endl;
    printLevelOrder(T2);
    cout<<endl;
    cout<<"是否相等:"<<isBiTreesEqual(T1,T2)<<endl;
	cout<<"层次遍历寻找度数为1的结点总数="<<OneDegreeCount(T1)<<endl;
}

int main() {
    BiTree T1,T2,NewT;

    cout<<"请键入二叉树字符创建T1："<<endl;
    CreateBiTree(T1);

    //CreateBiTree(T2);
    //Info(T1,T2);

    cout<<"交换T1中每个结点的左孩子和右孩子:"<<endl;
    ChangeLR(T1,NewT);
    Info(T1,NewT);
    return 0;
}
