#include<iostream>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;

typedef int Status;
typedef char SElemType;
typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//��ʼ��
Status InitStack(SqStack &S) {
	S.base = new SElemType[MAXSIZE];

	if(!S.base) exit(OVERFLOW);

	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}
//��ջ
Status Push(SqStack &S, SElemType e) {
    if(S.top-S.base==S.stacksize) return ERROR;
    *S.top++=e;
    return OK;
}
//��ջ
Status Pop(SqStack &S, SElemType &e) {
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}
//���ջ
Status ClearStack(SqStack &S) {
	if(S.base) S.top = S.base;
	return OK;
}
//ȡջ��Ԫ��
Status GetTop(SqStack S,SElemType &e) {
	if(S.top==S.base) return ERROR;
	e = *(S.top-1);
	return OK;
}
//���ջ�ĳ���
int StackLen(SqStack &S) {
    return (S.top-S.base);
}
//����ջ
Status DestroyStack(SqStack &S){
    int len = S.stacksize;
    for(int i =0; i < len; i++){
        free(S.base);
        S.base++;
    }
    S.base = S.top = NULL;
    S.stacksize = 0;
    return OK;
}

int main() {
    //��ʼ��
    SqStack S;
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
    cout<<"��ʱջ��"<<StackLen(S)<<"��Ԫ��"<<endl;
    //��ջ
    SElemType getE1, getE2;
    if(Pop(S,getE1)==OK) cout<<getE1<<"��ջ�ɹ�"<<endl;
    else cout<<"��ջʧ��"<<endl;
    //ȡջ��Ԫ��
    if(GetTop(S,getE2)==OK) cout<<"ջ��Ԫ��Ϊ:"<<getE2<<endl;
    else cout<<"ʧ��"<<endl;
    cout<<"��ʱջ��"<<StackLen(S)<<"��Ԫ��"<<endl;
    //���
    int m;
    cout<<"����1���ջ�������"<<endl;
    cin>>m;
    if(m==1) {
        if(ClearStack(S)==OK) {
            cout<<"ջ�����"<<endl;
            cout<<"��ʱջ��"<<StackLen(S)<<"��Ԫ��"<<endl;
        } else cout<<"���ʧ��"<<endl;
    } else {
        cout<<"��������"<<endl;
        cout<<"��ʱջ��"<<StackLen(S)<<"��Ԫ��"<<endl;
    }
    cout<<"����ջ"<<endl;
    if(DestroyStack(S)==OK) {
        cout<<"���ٳɹ�"<<endl;
        cout<<"��ʱջ��"<<StackLen(S)<<"��Ԫ��"<<endl;
    } else {
        cout<<"����ʧ��"<<endl;
    }

    return 0;
}
