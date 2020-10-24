#include <iostream>

using namespace std;


void Merge(int arr[], int L, int M, int R) {
    int LEFT_SIZE = M - L;
    int RIGHT_SIZE = R - M + 1;
    int left[LEFT_SIZE];
    int right[RIGHT_SIZE];
    int i,j,k;

    //1. left arr
    for(i=L;i<M;i++) {
        left[i-L] = arr[i];
    }

    //2. right arrMerge
    for(i=M;i<=R;i++) {
        right[i-M] = arr[i];
    }

    //3. merge
    i = 0;
    j = 0;
    k = L; //这里出大问题！！！！因为后面的分治k的起始值并不是0卧槽
    while(i < LEFT_SIZE && j < RIGHT_SIZE) {
        if(left[i]<right[j]) {
            arr[k] = left[i];
            i++;
            k++;
        } else {
            arr[k] = right[j];
            j++;
            k++;
        }
    }
    while(i < LEFT_SIZE) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while(j < RIGHT_SIZE) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int L, int R) {
    if(L==R) {
        return;
    } else {
        int M = (L + R) / 2 ;
        MergeSort(arr,L,M);
        MergeSort(arr,M+1,R);
        Merge(arr,L,M+1,R);
    }
}

void Print(int arr[], int n) {
    for(int i=0;i<n;i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


int main() {
    int L = 0;
    int R = 7;
    int arr2[] = {6,8,10,9,4,5,2,7};
    Print(arr2,8);
    MergeSort(arr2,L,R);
    for(int i=0;i<=R;i++)
        cout<<arr2[i]<<" ";
    cout<<endl;

    return 0;
}
