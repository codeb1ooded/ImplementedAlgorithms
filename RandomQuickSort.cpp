#include<iostream>
#include<cstdlib>
using namespace std;
int size;

void printArray(int* input){
	for(int i=0;i<size;i++){
		cout<<input[i]<<"\t";
	}
	cout<<"\n";
}

int pivot(int* array,int begIndex,int endIndex){
	int temp = endIndex-begIndex+1;
	int pivotIndex = rand()%temp + begIndex;
	int p = array[pivotIndex];
	int index = begIndex;
	for(int i = begIndex; i <= endIndex; i++){
		if(p > array[i]){
			index++;
		}
	}
	array[pivotIndex] = array[index];
	array[index] = p;

	int i=begIndex,j=endIndex;
	while(i < j){
		while(array[i]<p && i<j){
			i++;
		}
		while(array[j]>=p && i<j){
			j--;
		}
		if(i<j){
			int t=array[i];
			array[i]=array[j];
			array[j]=t;
			i++;
			j--;
		}
	}
	return index;
}
	
int* takeInput(){
	cout<<"Enter Size : ";
	cin>>size;
	int* input=new int[size];
	for(int i=0;i<size;i++){ 
		cin>>input[i];
	}
	return input;
}

void qSort(int* array,int beginIndex,int endIndex){
	if(beginIndex<0 || beginIndex >= endIndex){
		return;
	}
	int n = pivot(array, beginIndex, endIndex);
	qSort(array, beginIndex, n-1);
	qSort(array, n+1, endIndex);
}

int main(){
	// 5 10 4 7 6 7
	int* array=takeInput();
	qSort(array,0,size-1);
	printArray(array);
	return 0;
}
