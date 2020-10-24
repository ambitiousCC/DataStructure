#include<iostream>
#include<cstdlib>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;

typedef int Status;
typedef char SElemType;
typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStack;

//��ʼ��
Status InitStack(LinkStack &S) {
	S=NULL;
	return OK;
}

//��ջ
Status Push(LinkStack &S, SElemType e) {
    StackNode *p = new StackNode;
    p->data = e;
    p->next = S;
    S=p;
    return OK;
}

//��ջ
Status Pop(LinkStack &S, SElemType &e) {
    if(S==NULL) return ERROR;
    e=S->data;
    StackNode *p=S;
    S=S->next;
    delete p;
    return OK;
}

//ջ��Ԫ��
SElemType GetTop(LinkStack S) {
    if(S!=NULL) return S->data;
}

//�ж��Ƿ�Ϊ��
bool StackEmpty(LinkStack S) {
	if(S==NULL) return true;
	else return false;
}

//���ջ
bool ClearStack(LinkStack &S) {
    StackNode *p,*q;
    p=S->next;
    while(p) {
        q = p;
        p = p -> next;
        free(q);
    }
    return true;
}

//����
int LinkStackLen(StackNode *head) {
    if(head==NULL||head->next==NULL) return 0;
    StackNode *p = head->next;
    int len = 1;
    while(p!=NULL) {
        len++;
        p=p->next;
    }
    return len;
}

int main() {
    //��ʼ��
    LinkStack S;
    if(InitStack(S)==OK) cout<<"��ʼ���ɹ�"<<endl;
    else cout<<"��ʼ��ʧ��"<<endl;
    //��ջ
    int n;
    cout<<"������ջԪ�ظ���:";
    cin>>n;
    int i=1;
    while(n>0) {
        SElemType e;
        cout<<"��"<<i<<"��Ԫ��:";
        cin>>e;
        if(Push(S,e)==OK) cout<<e<<"��ջ�ɹ�"<<endl;
        else cout<<"��ջʧ��"<<endl;
        n--;
        i++;
    }
    cout<<"��ʱջ��:"<<LinkStackLen(S)<<endl;
    //��ջ
    SElemType getE1, getE2;
    if(Pop(S,getE1)==OK) cout<<getE1<<"��ջ�ɹ�"<<endl;
    cout<<"��ʱջ��:"<<LinkStackLen(S)<<endl;
    //ȡջ��Ԫ��
    cout<<"ջ��Ԫ��Ϊ"<<GetTop(S)<<endl;
    cout<<"��ʱջ��:"<<LinkStackLen(S)<<endl;
    return 0;
}
