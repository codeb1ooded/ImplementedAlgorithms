#include<iostream>
using namespace std;
int size;
	
int* takeInput(){
	cout<<"Enter Size : ";
	cin>>size;
	int* input = new int[size];
	cout<<"Enter array: ";
	for(int i=0; i<size; i++)		cin>>input[i];
	return input;
}

int* mergeSort(int* array1, int size1, int* array2, int size2){
	int size = size1+size2;
	int* array = new int[size];
	int i=0, j=0, k=0;
	while(i<size1 && j<size2){
		if(array1[i] < array2[j]){
			array[k] = array1[i];
			i++;
		}
		else{
			array[k] = array2[j];
			j++;
		}
		k++;
	}
	while(k < size){
		if(i == size1){
			array[k] = array2[j];
			j++;
		}
		else{
			array[k] = array1[i];
			i++;
		}
		k++;
	}
	return array;
}

void printArray(int* input){
	for(int i=0; i<size; i++)
		cout<<input[i]<<"\t";
	cout<<"\n";
}

int* mSort(int* array, int beg, int end){
	if(beg == end){
		int* output = new int[1];
		output[0] = array[beg];
		return output;
	}
	int* array1 = mSort(array, beg, (beg+end)/2);
	int* array2 = mSort(array, (beg+end)/2+1, end);
	int s1 = (beg+end)/2 - beg +1;
	int s2 = end - (beg+end)/2;
	int* output = mergeSort(array1, s1, array2, s2);
	return output;
}

int main() {
	int* array = takeInput();
	int* output = mSort(array,0,size-1);
	printArray(output);
	return 0;
}


