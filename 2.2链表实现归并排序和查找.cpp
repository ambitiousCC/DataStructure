/*
���ʵ�ֵ�����Ļ�������
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

int CreateListMain(LinkList &L,bool isEmpty) {
    if(isEmpty)
    {
        InitList(L);
        return 1;
    }
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
            n=0;
            break;
        }
        if(n==1||n==2||n==3)
            break;
        else
            continue;
    }
    return 1;
}

void Inverse(LinkList &L) {
    LNode *p = L -> next;
    L -> next = NULL;
    while(p) {
        LNode *q = p -> next;
        p -> next = L -> next;
        L -> next = p;
        p = q;
    }
}

//�����м���:��ָ�����ָ���ٶȿ���������ָ�뵽��ĩ���ʱ��ָ��ָ���м���
LNode* MidElem(LNode *head) {
    LNode *slow = head;
    LNode *fast = head -> next;
    while(fast!=NULL) {
        fast = fast -> next;
        if(fast == NULL)
            break;
        fast = fast -> next;
        slow = slow -> next;
    }
    return slow;
}

/**
 * �ϲ�������������
 * @param l1
 * @param l2
 * @return
 */
LinkList Merge(LinkList &l1, LinkList &l2) {
    LinkList l;
    LNode *p = l;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data < l2->data) {
            p->next = l1;
            l1 = l1->next;
        } else {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }

    if (l1 != NULL)
        p->next = l1;

    if (l2 != NULL)
        p->next = l2;

    return l->next;
}

/**
 * ����Ķ�·�鲢����
 * @param head
 * @return
 */
LinkList sortList(LinkList &L) {
    //���������ֻ��һ�����,ֱ�ӷ���head
    LNode *head = L;
    if(head == NULL || head->next==NULL){
        return head;
    }

    //1. ��list �з�Ϊ��������
    LNode *prev=NULL, *slow=head, *fast=head;

    while (fast !=NULL && fast->next !=NULL){
        prev = slow;
        slow = slow->next;//slowָ�����һ������
        fast = fast->next->next;//fastָ�������������
    }

    prev->next = NULL;//�������ж�

    //�ֱ�����ǰ����������
    LinkList l1 = sortList(head);
    LinkList l2 = sortList(slow);

    return Merge(l1, l2);
}
/*
// ��дԭmerge����
LNode* Merge(LNode *left, LNode *right) {
    LinkList fin;
    LNode *p = fin;

    if(left->data<right->data) {
        p = left;
        left = left -> next;
    } else {
        p = right;
        right = right -> next;
    }
    p -> next = NULL;
    while(left&&right) {
        if(left->data<right->data) {
            p -> next = left;
            left = left -> next;
        } else {
            p -> next = right;
            right = right -> next;
        }
        p = p -> next;
        p -> next = NULL;
    }
    if(left != NULL) p->next = left;
    if(right != NULL) p->next = right;
    cout<<"?"<<endl;
    return fin->next;
}
LNode* MergeList(LinkList &L) {
    if(L==NULL) return NULL;
    if(L->next==NULL) return L;
    LNode *head = L;
    //�����м��
    //LNode *Mid = MidElem(head);
    LNode *prev = NULL;
    LNode *slow = head;
    LNode *fast = head -> next;

    while(fast!=NULL) {
        prev = slow;
        fast = fast -> next;
        if(fast == NULL)
            break;
        fast = fast -> next;
        slow = slow -> next;
    }
    prev->next = NULL;

    //���Σ���������
    LNode *left = MergeList(head);
    LNode *right = MergeList(slow);
    LNode *fin = Merge(left,right);
    return fin;
}*/

//�̲ķ����������������ϲ�
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
    LNode *pa = La -> next;
    LNode *pb = Lb -> next;
    Lc = La;
    LNode *pc = Lc;
    int i = 1;
    while(pa&&pb) {
        if(pa->data<=pb->data) {
            pc -> next = pa;
            pc = pa;
            pa = pa -> next;
        } else {
            pc -> next = pb;
            pc = pb;
            pb = pb -> next;
        }
    }
    pc -> next = pa?pa:pb;
    delete Lb;
}


int main() {
    LinkList La,Lb,Lc;
    //LinkList L;
    //��������
    /*
    if(CreateListMain(L)) {
        cout<<"�����ɹ�������ԭʼ����"<<endl;
        PrintLinkList(L);
    } else {
        cout<<"ERROR"<<endl;
    }*/

    //��������
    cout<<"-����A����"<<endl;
    if(CreateListMain(La,false)) {
        cout<<"�����ɹ�������A����"<<endl;
        PrintLinkList(La);
    } else {
        cout<<"ERROR"<<endl;
    }
    cout<<"-����B����"<<endl;
    if(CreateListMain(Lb,false)) {
        cout<<"�����ɹ�������B����"<<endl;
        PrintLinkList(Lb);
    }
    CreateListMain(Lc,true);

    MergeList_L(La, Lb, Lc);
    cout<<"ִ�й鲢����"<<endl;
    PrintLinkList(Lc);
    //ʵ�ֹ鲢����
    /*
    LinkList fin = sortList(L);
    PrintLinkList(fin);
*/
    return 0;
}
