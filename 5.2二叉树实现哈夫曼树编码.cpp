#include <iostream>
#include <cstring>
#include <iomanip>
/**
 * ������������
 */

using namespace std;

//��������
typedef struct {
    int weight; //���Ȩֵ
    int parent, lchild, rchild; //���˫�ס����ӡ��Һ����±�
}HTNode,*HuffmanTree;
//�����������
typedef char **HuffmanCode;

//ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ�㲢���������ڹ��������е����
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int min1 = 999;//���ýϴ���ֵ
    int min2 = 999;
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent==0 && min1>HT[i].weight)
        {
            min1 = HT[i].weight;//��¼����СȨֵ
            s1 = i; //��СȨֵ�±�
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent==0 && i!=s1) //������s1�ظ�
        {
            if(HT[i].weight<min2)
            {
                min2=HT[i].weight;
                s2 = i;
            }
        }
    }
}

//�����������
void CreateHuffmanTree(HuffmanTree &HT, int n)
{
    //��ʼ����
    if(n<=1) return ;
    int m=2*n-1;
    HT = new HTNode[m+1];
    for(int i=1;i<=m;i++)
    {
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    cout<<"������n����Ԫ��Ҷ�ӽ���Ȩֵ��"<<endl;
    for(int i=1;i<=n;i++)
    {
        cin>>HT[i].weight;
    }
    //������
    int s1,s2;
    for(int i=n+1;i<=m;i++)
    {
        Select(HT,i-1,s1,s2);
        //ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ�㲢���������ڹ��������е����
        HT[s1].parent=i;
        HT[s2].parent=i;
        //�½��i����ɭ����ɾ������㣬ͬʱ��s1��s2��˫������0��Ϊi
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;//ȨֵΪ���Һ���Ȩֵ֮��
    }
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    //Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢��HC
    HC = new char*[n+1];
    char *cd = new char[n];
    cd[n-1]='\0'; //���������
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
    delete cd;//�ͷ���ʱ�ռ�
    cout<<"Ȩֵ ����������"<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<setw(5)<<setiosflags(ios::left)<<HT[i].weight;
        cout<<setw(5)<<setiosflags(ios::left)<<HC[i]<<endl;
    }
    int w = 0;
    for(int i=1;i<=n;i++)
        w += HT[i].weight * a[i];
    cout<<"��Ȩ·��="<<w;
}

void printHuffmanTree(HuffmanTree HT, int n)
{
    if(HT==NULL) cout<<"����";
    cout<<"������"<<endl;
    cout<<"����� weight parent lchild rchild"<<endl;
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
    cout<<"�����������";
    cin>>n;

    HuffmanTree HT;
    CreateHuffmanTree(HT,n);
    cout<<"�������"<<endl;
    printHuffmanTree(HT, n);

    //���ݹ�������������
    HuffmanCode HC;
    cout<<"���������������"<<endl;
    CreateHuffmanCode(HT,HC,n);
    return 0;
}
