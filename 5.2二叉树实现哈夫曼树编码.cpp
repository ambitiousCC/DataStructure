#include <iostream>
#include <cstring>
#include <iomanip>
/**
 * 哈夫曼树构造
 */

using namespace std;

//哈夫曼树
typedef struct {
    int weight; //结点权值
    int parent, lchild, rchild; //结点双亲、左孩子、右孩子下标
}HTNode,*HuffmanTree;
//哈夫曼编码表
typedef char **HuffmanCode;

//选择两个其双亲域为0且权值最小的结点并返回他们在哈夫曼树中的序号
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int min1 = 999;//设置较大阈值
    int min2 = 999;
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent==0 && min1>HT[i].weight)
        {
            min1 = HT[i].weight;//记录了最小权值
            s1 = i; //最小权值下标
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent==0 && i!=s1) //不能与s1重复
        {
            if(HT[i].weight<min2)
            {
                min2=HT[i].weight;
                s2 = i;
            }
        }
    }
}

//构造哈夫曼树
void CreateHuffmanTree(HuffmanTree &HT, int n)
{
    //初始化：
    if(n<=1) return ;
    int m=2*n-1;
    HT = new HTNode[m+1];
    for(int i=1;i<=m;i++)
    {
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    cout<<"输入这n个单元中叶子结点的权值："<<endl;
    for(int i=1;i<=n;i++)
    {
        cin>>HT[i].weight;
    }
    //创建：
    int s1,s2;
    for(int i=n+1;i<=m;i++)
    {
        Select(HT,i-1,s1,s2);
        //选择两个其双亲域为0且权值最小的结点并返回他们在哈夫曼树中的序号
        HT[s1].parent=i;
        HT[s2].parent=i;
        //新结点i，从森林中删除两结点，同时将s1和s2的双亲域由0改为i
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;//权值为左右孩子权值之和
    }
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    //叶子到根逆向求每个字符的哈夫曼编码，存储在HC
    HC = new char*[n+1];
    char *cd = new char[n];
    cd[n-1]='\0'; //编码结束符
    int start,c,f;
    int a[100];
    for(int i=1;i<=n;i++)
    {
        a[i] = 0;
        start = n-1;
        c = i;
        f = HT[i].parent;
        while(f!=0)
        {
            start--;
            if(HT[f].lchild==c) cd[start]='0';
            else cd[start]='1';
            c=f;
            f=HT[f].parent;
            a[i]++;
        }
        HC[i]=new char[n-start];
        strcpy(HC[i],&cd[start]);
    }
    delete cd;//释放临时空间
    cout<<"权值 哈夫曼编码"<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<setw(5)<<setiosflags(ios::left)<<HT[i].weight;
        cout<<setw(5)<<setiosflags(ios::left)<<HC[i]<<endl;
    }
    int w = 0;
    for(int i=1;i<=n;i++)
        w += HT[i].weight * a[i];
    cout<<"带权路径="<<w;
}

void printHuffmanTree(HuffmanTree HT, int n)
{
    if(HT==NULL) cout<<"空树";
    cout<<"输出表格："<<endl;
    cout<<"结点编号 weight parent lchild rchild"<<endl;
    for(int i=1;i<n*2;i++)
    {
        cout<<setw(5)<<setiosflags(ios::left)<<i;
        cout<<setw(7)<<setiosflags(ios::left)<<HT[i].weight;
        cout<<setw(7)<<setiosflags(ios::left)<<HT[i].parent;
        cout<<setw(7)<<setiosflags(ios::left)<<HT[i].lchild;
        cout<<setw(7)<<setiosflags(ios::left)<<HT[i].rchild<<endl;
    }
}

int main()
{
    int n;
    cout<<"输入结点个数：";
    cin>>n;

    HuffmanTree HT;
    CreateHuffmanTree(HT,n);
    cout<<"创建完毕"<<endl;
    printHuffmanTree(HT, n);

    //根据哈夫曼树创建表
    HuffmanCode HC;
    cout<<"创建哈夫曼编码表："<<endl;
    CreateHuffmanCode(HT,HC,n);
    return 0;
}
