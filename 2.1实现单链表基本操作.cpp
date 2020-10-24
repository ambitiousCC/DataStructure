/*
���ʵ�ֵ�����Ļ���������
����������
���ҵ�����
���뵥����
ɾ��������
*/
#include <iostream>

#define ElemType int
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
using namespace std;

typedef int Status;
//����洢�ṹ
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList; //LinkListΪָ��ṹ��LNode��ָ������

//��ʼ��
Status InitList(LinkList &L) {
    //����һ���յĵ�����
    L = new LNode;    //�µĽ����Ϊͷ�ڵ㣬��ͷָ��Lָ��ͷ���
    L -> next = NULL; //ͷ����ָ�����ÿ�
    return OK;
}

//��������ֵ�ĵ��������ַ���������
Status CreateList_H(LinkList &L, int n) {
    //��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ�����
    LNode *p = NULL;
    L = new LNode;
    L -> next = NULL;
    for(int i=0;i<n;i++) {
        p = new LNode;
        cin>>p->data;
        p -> next = L -> next;
        L -> next = p;
    }
    return OK;
}

//��巨����ָ�룺˳��ֵ
Status CreateList_R(LinkList &L, int n) {
    LNode *r,*p = NULL;
    L = new LNode;
    L -> next = NULL;
    r = L;
    for(int i=0;i<n;i++) {
        p = new LNode;
        cin>>p->data;
        p -> next = NULL;
        r -> next = p;
        r = p;
    }
    return OK;
}

//ȡֵ
Status GetElem(LinkList L, int i, ElemType &e) {
    LNode *p = NULL;
    p = L -> next;
    int j = 1; //������
    while(p && j<i) {//ֱ��pΪ���򣬻���pָ���i��Ԫ��
        p = p -> next;
        ++j;
    }

    if(!p||j>i) return ERROR;
    e = p -> data;
    return OK;
}

//����ȡֵ����
LNode *LocateElem(LinkList L, ElemType e) {
    LNode *p = NULL;
    //�ڴ�ͷ���ĵ�����L�в���ֵΪe��Ԫ��
    p = L -> next;
    while(p && p -> data!=e) {
        p = p -> next;
    }
    return p; //���ص���ָΪe�Ľ��ĵ�ַp���������ʧ��pΪnull
}

//����
Status ListInsert(LinkList &L, int i, ElemType e) {
    LNode *p,*s = NULL;
    //��ͷ���ĵ�����L�е�i��λ�ò���ֵΪe���½��
    p = L;
    int j = 0;
    while(p && (j<i-1)) {
        p = p -> next;
        ++j;
    }
    if(!p||j>i-1) return ERROR;
    s = new LNode;
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    return OK;
}

//ɾ��
Status ListDelete(LinkList &L, int i) {
    LNode *p,*q = NULL;
    p = L;
    int j = 0;
    while((p->next)&&(j<i-1)) {
        p = p -> next;
        ++j;
    }
    if(!(p->next)||(j>i-1)) return ERROR;
    q = p -> next;
    p -> next = q -> next;
    delete q;
    return OK;
}

void PrintLinkList(LinkList &L) {
    LNode *p = NULL;
    p = L -> next;
    while(p) {
        if(p->next==NULL)
            cout<<p->data<<endl;
        else
            cout<<p->data<<"->";
        p = p -> next;
    }
}

void PrintCout() {
    cout<<"����1�����ձ�"<<endl;
    cout<<"����2���򴴽�"<<endl;
    cout<<"����3���򴴽�"<<endl;
}

int CreateListMain(LinkList &L) {
    int n;
    PrintCout();
    cin>>n;
    while(n)
    {
        int len = 0;
        switch(n)
        {
        case 1:
            InitList(L);
            break;
        case 2:
            cout<<"���봴��������:";
            cin>>len;
            CreateList_H(L,len);
            break;
        case 3:
            cout<<"���봴��������:";
            cin>>len;
            CreateList_R(L,len);
            break;
        default:
            cout<<"������������"<<endl;
            break;
        }
        if(n==1||n==2||n==3)
            break;
        else
            continue;
    }
    return 1;
}

void PrintCout_S() {
    cout<<"---------------------ִ�в��������·���ʾ����---------------"<<endl;
    cout<<"-********************����1ִ�в��Ҳ���*********************-"<<endl;
    cout<<"-********************����2ִ�в������*********************-"<<endl;
    cout<<"-********************����3ִ��ɾ������*********************-"<<endl;
    cout<<"-********************����0�˳�*****************************-"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
}

void DoMain(LinkList &L) {
    int n;
    PrintCout_S();
    cin>>n;
    while(n) {
        if(n==0)
            break;
        ElemType e;
        int i;
        switch(n)
        {
        case 1:
            cout<<"������Ҫ���ҵ�ֵ:";
            cin>>e;
            if(LocateElem(L, e)) cout<<"�ܲ�ѯ�õ�"<<endl;
            else cout<<"������û��"<<endl;
            break;
        case 2:
            cout<<"����Ҫ�����ֵ:";
            cin>>e;
            cout<<"����Ҫ����ĵ�n��λ��:";
            cin>>i;
            if(ListInsert(L,i,e))
                cout<<"����ɹ�"<<endl;
            else
                cout<<"����ʧ��"<<endl;
            break;
        case 3:
            cout<<"������Ҫɾ����_��Ԫ��:";
            cin>>i;
            if(ListDelete(L, i))
                cout<<"ɾ���ɹ�"<<endl;
            else
                cout<<"ɾ��ʧ��"<<endl;
            break;
        default:
            cout<<"������������"<<endl;
            break;
        }
        PrintLinkList(L);
        PrintCout_S();
        cin>>n;
    }
}


/*
����������
���ҵ�����
���뵥����
ɾ��������
*/

int main() {
    LinkList L;
    //��������
    if(CreateListMain(L)) {
        cout<<"�����ɹ�"<<endl;
        PrintLinkList(L);
    } else {
        cout<<"ERROR"<<endl;
    }
    //���ң����룬ɾ��
    DoMain(L);
    return 0;
}
