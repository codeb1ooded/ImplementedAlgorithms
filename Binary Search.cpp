#include<iostream>
using namespace std;

int binarySearch(int array[], int beg, int end, int x ){
	if(beg > end){
		return -1;
	}
	if(beg == end){
		if(array[beg] == x)			return beg;
		else						return -1;
	}
	int mid = (beg+end)/2;
	int i = binarySearch(array, beg, mid, x);
	if(i != -1)		return i;
	return binarySearch(array, mid + 1, end, x);
}

int main(){
	int size, x, i;
	cout<<"Enter size: ";		cin>>size;
	int array[100];
	cout<<"Enter array: ";
	for(i=0; i<size; i++)		cin>>array[i];
	cout<<"Enter element to be searched: ";			cin>>x;
	i = binarySearch(array, 0, size-1, x);
	if(i == -1)			cout<<"\nElement not found";
	else				cout<<"\nElement found at position: "<<i+1;
	return 0;
}
