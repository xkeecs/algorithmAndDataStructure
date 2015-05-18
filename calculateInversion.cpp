//
//  main.cpp
//  stanfordAlgoAssign1
//  This program calculates the number of inversions in an array
//
//  Created by Kai Xiong on 3/26/15.
//  Copyright (c) 2015 ___UCB___. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

int merge(int *A, const int start, const int mid, const int end);

void mergeSort(int *A, const int start, const int end){

    int mid;
    if( start < end){
        mid = (start + end)/2;
        mergeSort(A, start, mid);
        mergeSort(A, mid+1, end);
        merge(A, start, mid, end);
    }
}

int merge(int *A, const int start, const int mid, const int end){
    int * b = new int[end+1-start];
    int h,i,j,k;
    h = start;
    i=0;
    j=mid+1;
    int invCounter = 0;
    
    while( (h <= mid) && (j<=end)){
        if(A[h]<=A[j])
        {
            b[i]=A[h];
            h++;
        }
        else{
            b[i]=A[j];
            invCounter += mid - h;
            j++;
        }
        i++;
    }
    
    if(h > mid){
        for(k=j;k<=end;k++){
            b[i]=A[k];
            i++;
        }
    }
    else{
        for(k=h;k<=mid;k++){
            b[i]=A[k];
            i++;
            invCounter += mid - k;
        }
    }
    
    for(k=0; k<=end-start;k++){
        A[k+start]=b[k];
    }
    delete[] b;
    return invCounter;
}

int countSplitInv(int* A, const int start, const int end){
    int mid = (start + end)/2;
	int *B = new int[5];
	for (int i = 0; i < 5; i++){
		B[i] = A[i];
	}
    mergeSort(B, start, mid);
    mergeSort(B, mid+1, end);
    return merge(B, start, mid, end);
    
}

int count(int* A, const int start, const int end){
    if (start == end) return 0;
    
    int x = count(A, start, (end-start)/2);
    int y = count(A, (end-start)/2+1, end);
    int z = countSplitInv(A, start, end);
    return x+y+z;
}

int main(int argc, const char * argv[])
{
    ifstream myfile;
    int nrows = 5;
    int * myarray = new int[nrows];
	myfile.open("data.txt");
    if(myfile.fail()){
        cerr << "file open fail" << endl;
    }
    
    for(int i = 0; i < nrows ; ++i){
        if(!(myfile >> myarray[i])){
            cerr << "error reading file"<<endl;
            break;
            }
        if(!myfile){
            break;}
        }
	cout << "running" << endl;
    cout<<count(myarray, 0, nrows)<<endl;
	system("PAUSE");
    return 0;
}