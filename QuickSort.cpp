#include<iostream>
using namespace std;
int size;

int pivot(int* array,int begIndex,int endIndex){
	int p = array[begIndex];
	int index = begIndex;
	for(int i = begIndex+1; i<=endIndex; i++){
		if(p >= array[i])			index++;
	}
	array[begIndex] = array[index];
	array[index] = p;
	int i = begIndex, j = endIndex;
	while(i < j){
		while(array[i]<=p && i<j)				i++;
		while(array[j]>p && i<j)				j--;
		if(i < j){
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
			i++;
			j--;
		}
	}
	return index;
}
	
int* takeInput(){
	cout<<"Enter Size : ";				cin>>size;
	int* input = new int[size];
	for(int i=0; i<size; i++)			cin>>input[i];
	return input;
}

void qSort(int* array, int beginIndex, int endIndex){
	if(beginIndex >= endIndex)			return;
	int n = pivot(array, beginIndex, endIndex);
	qSort(array, beginIndex, n-1);
	qSort(array, n+1, endIndex);
}

void printArray(int input[]){
	for(int i=0; i<size; i++){
	cout<<input[i]<<"\t";
	}
}

int main(){
	int* array = takeInput();
	qSort(array, 0, size-1);
	printArray(array);
	return 0;
}


