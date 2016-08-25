#include<iostream>
using namespace std;
int size;

int main(){
	int size;
	cout<<"Enter number of elements: ";
	cin>>size;
	int* array = new int[size];
	cout<<"Enter array: \n";
	for(int i=0; i<size; i++)
		cin>>array[i];
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-i-1;j++){
			if(array[j]>array[j+1]){
				int temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
	}
	cout<<"Sorted array: \n";
	for(int i=0; i<size; i++)
		cout<<array[i]<<"\t";
	delete array;
	return 0;
}
