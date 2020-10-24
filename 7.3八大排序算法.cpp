# include <iostream>
# include <cstdlib>

#define ElementType int
using namespace std;

/*
    �����㷨��
    1. *ð������
    2. ��������
    3. ϣ������
    4. ѡ������
    5. *��������
    6. ������
    7. *�鲢����
    8. ������
*/
void ERROR(string e) {
    cout<<"�ռ䲻��"<<endl;
}

//��ʼ������
void InitElement(ElementType A[], int N)
{
    for(int i=0;i<N;i++) {
        cout<<"�����"<<i+1<<"��Ԫ��:";
        cin>>A[i];
    }
}

//��������
void Swap(ElementType A[], int a, int b) {
	int temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}
//ð������
void Bubble_Sort(ElementType A[], int N) {
	for(int P=N-1;P>=0;P--) {
		int flag = 0;
		for(int i=0;i<P;i++)
			if(A[i]>A[i+1])
				Swap(A,i,i+1); //���û�б�ִ�У���������б���������
				flag = 1; //��ʶ�����˽���
		if(flag==0) break;
    }
}

//��������
void Insertion_Sort(ElementType A[], int N) {
    int i = 0;
	for(int P=1; P<N; P++) {
		int tmp = A[P]; //����һ����
		for(i=P; i>0 && A[i-1]>tmp; i--)
			A[i] = A[i-1];
		A[i] = tmp; //����
	}
}

//��������
/*ѡ��Ԫ��*/
ElementType Median3(ElementType A[], int Left, int Right) {
	int center = (Left + Right) /2;
	if(A[Left]>A[center])
		Swap(A,Left,center);
	if(A[Left]>A[Right])
		Swap(A,Left,Right);
	if(A[center]>A[Right])
		Swap(A,center,Right);
	//�õ��������С���ұ����
	Swap(A,center,Right-1);//���һ���Ѿ�����ˣ����ԣ��Ͱ���λ������������������һλ�������Ҫ�Ƚϵľ���A[left+1]~A[Right-2]
	return A[Right-1];
}
//�ݹ����
void Quicksort(ElementType A[], int Left, int Right) {
    int Cutoff = 4;
	if(Cutoff<=Right-Left) {
		int Pivot = Median3(A, Left, Right);
		int i = Left; int j = Right - 1;
		for(;;) {
			while(A[++i]<Pivot) {}
			while(A[--j]>Pivot) {}
			if(i<j)
				Swap(A,i,j);
			else break;
		}
		Swap(A,i,Right-1);//�Ѳ�ס����Ԫ����λ��
		Quicksort(A, Left, i-1);
		Quicksort(A, i+1, Right);
	} else {
		Insertion_Sort(A+Left, Right-Left+1);//С��ģ���ò�������
	}
}

//���ϱ�׼�ӿ�Ҫ�����ӿ�
void Quick_Sort(ElementType A[], int N) {
	Quicksort(A, 0, N-1);
}

//�����󶥶�
void PercDown(ElementType A[], int i, int N) {
	int temp = A[i];//ȡ����ǰԪ��
	for(int k=i*2+1; k<N; k=k*2+1) {
		if(k+1<N&&A[k]<A[k+1])
			k++;//���ӽ��С���ҽ�㣬kָ�����ӽ��
		if(A[k]>temp) {//�ӽ����ڸ��ڵ㣬ֱ�Ӹ�ֵ�����ڵ�
			A[i] = A[k];
			i = k;
		} else {
			break;
		}
	}
	A[i] = temp;
}
//�������㷨
void Heap_Sort(ElementType A[], int N) {
	for(int i=N/2; i>=0; i--)
		PercDown(A, i, N); //��������
	for(int i=N-1; i>0; i--) {
		Swap(A,0,i);
		PercDown(A, 0, i);
	}
}

//�鲢����
/* L:�����ʼλ�ã�R:�ұ���ʼλ�ã�RightEnd:�ұ��յ�λ��*/
void Merge(ElementType A[], ElementType tempA[], int L, int R, int RightEnd) {
	int LeftEnd = R - 1;
	int temp = L;
	int NumElements = RightEnd - L + 1;//Ԫ���ܸ���
	//�鲢����
	while(L<=LeftEnd&&R<=RightEnd) {
		if(A[L]<=A[R]) tempA[temp++] = A[L++];
		else tempA[temp++] = A[R++];
	}
	//�����ֱ��ƴ��
	while(L<=LeftEnd)
		tempA[temp++] = A[L++];
	while(R<=RightEnd)
		tempA[temp++] = A[R++];
	//L�Ѿ���ʹ�ù���
	for(int i=0;i<NumElements;i++,RightEnd--) {//RightEndδ��ʹ��
		A[RightEnd] = tempA[RightEnd];
	}
}

void MSort(ElementType A[], ElementType tempA[], int L, int RightEnd) {
	int center;
	if(L<RightEnd) {
		center = (L+RightEnd) /2;
		MSort(A,tempA,L,center);
		MSort(A,tempA,center+1,RightEnd);
		Merge(A,tempA,L,center+1,RightEnd);
	}
}

void Merge_sort(ElementType A[], int N) {
	ElementType *tempA;
	tempA = (ElementType *)malloc(N*sizeof(ElementType));//����ռ�
	if(tempA!=NULL) {
		MSort(A,tempA,0,N-1);
		free(tempA);
	} else {
		ERROR("�ռ䲻��");//������
	}
}


//��ӡ����
void printElement(ElementType A[], int N) {
    for(int i=0; i<N; i++) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

void CopyElem(ElementType A[], ElementType temp[], int N) {
    for(int i=0;i<N;i++) {
        temp[i] = A[i];
    }
}

int main()
{
    int N;
    cout<<"�������鳤��:";
    cin>>N;
    ElementType A[N];
    ElementType temp[N];

    InitElement(A, N);
    CopyElem(A,temp, N);

    //ð������
    cout<<"origin:";
    printElement(temp, N);
    cout<<"ð������"<<endl;
    Bubble_Sort(temp, N);
    printElement(temp, N);

    //��������
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"��������"<<endl;
    Quick_Sort(temp, N);
    printElement(temp, N);

    //��������
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"��������"<<endl;
    Insertion_Sort(temp,N);
    printElement(temp, N);

    //������
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"������"<<endl;
    Heap_Sort(temp,N);
    printElement(temp, N);

    //�鲢����
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"�鲢����"<<endl;
    Merge_sort(temp,N);

    printElement(temp, N);
    return 0;
}
