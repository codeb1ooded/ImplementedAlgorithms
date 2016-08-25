#include<iostream>
using namespace std;

struct knapsack{
	float cap;
	float value;
	float valuePerCap;
};

knapsack* mergeSort(knapsack* array1,int size1, knapsack* array2, int size2){
	int size=size1+size2;
	knapsack* array=new knapsack[size];
	int i=0,j=0,k=0;
	while(i<size1 && j<size2){
		if(array1[i].valuePerCap > array2[j].valuePerCap){
			array[k]=array1[i];
			i++;
		}
		else{
			array[k]=array2[j];
			j++;
		}
		k++;
	}
	while(k<size){
		if(i==size1){
			array[k]=array2[j];
			j++;
		}
		else{
			array[k]=array1[i];
			i++;
		}
		k++;
	}
	return array;
}

knapsack* mSort(knapsack* knap, int beg, int end){
	if(beg==end){
		knapsack* out = new knapsack[1];
		out[0].value = knap[beg].value;
		out[0].cap = knap[beg].cap;
		out[0].valuePerCap = knap[beg].valuePerCap;
		return out;
	}
	knapsack* array1=mSort(knap,beg,(beg+end)/2);
	knapsack* array2=mSort(knap,(beg+end)/2+1,end);
	int s1= (beg+end)/2 - beg +1;
	int s2= end - (beg+end)/2;
	knapsack* output=mergeSort(array1, s1, array2, s2);
	return output;
}
	
int main(){
	int n, tCap;
	cout<<"Enter number of items: ";
	cin>>n;
	cout<<"Enter total capacity: ";
	cin>>tCap;
	struct knapsack* knap = new knapsack[n];
	for(int i=0; i<n; i++){
		cout<<"Enter capacity and value of item "<<i+1<<": ";
		cin>>knap[i].cap>>knap[i].value;
		knap[i].valuePerCap = knap[i].value/knap[i].cap;
	}
	knap = mSort(knap, 0, n-1);
	int i=0;
	float capCalc=0, value=0, tValue=0;
	while(i<n && tCap > capCalc){
		if(capCalc + knap[i].cap <= tCap){
			cout<<i+1<<".  1\t"<<knap[i].cap<<"\t"<<knap[i].value<<"\n";
			tValue += knap[i].value;
			capCalc += knap[i].cap;
		}
		else{
			float per = (tCap - capCalc) / knap[i].cap;
			cout<<i+1<<".  "<<per<<"\t"<<knap[i].cap<<"\t"<<knap[i].value<<"\n";
			float fCap = knap[i].cap * per, fValue = knap[i].value * per;
			capCalc += fCap;
			tValue += fValue;
		}
		i++;
	}
	cout<<"\nTotal Value= "<<tValue;
}
