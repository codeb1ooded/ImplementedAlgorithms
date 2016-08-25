#include<iostream>
using namespace std;

struct MinMax{
	int min, max;
};

MinMax calcMinMax(int *array, int beg, int end){
	MinMax x;
	if(beg == end){
		x.max = array[beg];
		x.min = array[beg];
		return x;
	}
	x = calcMinMax(array, beg, (beg+end)/2);
	MinMax y = calcMinMax(array, ((beg+end)/2)+1, end);
	if(y.max > x.max)		x.max = y.max;
	if(y.min < x.min)		x.min = y.min;
	return x;
}

int main(){
	int size, i;
	cout<<"\nEnter size: ";
	cin>>size;
	int *array = new int[size];
	cout<<"\nEnter elements of array: ";
	for(i=0; i<size; i++)		cin>>array[i];
	MinMax r = calcMinMax(array, 0, size-1);
	cout<<"\nMax: "<<r.max<<" and Min: "<<r.min;
	return 0;
}
