#include<iostream>
using namespace std;
int size;

void printArray(int* input){
	for(int i=0; i<size; i++){
		cout<<input[i]<<"\t";
	}
	cout<<"\n";
}

int main(){
	cout<<"Enter number of elements: ";
	cin>>size;	
	
	int* input = new int[size];
	cout<<"Enter array: \n";
	for(int i=0; i<size; i++)
		cin>>input[i];
	
	int flag=-1,temp=0;
	int loc=0;
	for(int r=1; r<size; r++){
		for(int i=1; i<size; i++){
			flag=-1;
			if(input[i-1] > input[i]){
				temp=input[i];
				loc=i;
				flag=0;
				break;
			}
		}
		if(flag==0){
			if(input[0] > temp){
				for(int k=loc; k>0; k--){
					input[k] = input[k-1];
				}
				input[0] = temp;
			}
			else{
				for(int j=0; j<size-1; j++){
					if(input[j] < temp  &&  input[j+1] >= temp){
						for(int k=loc; k>j; k--){
							input[k] = input[k-1];
						}
						input[j+1] = temp;
						break;
					}
				}
			}
		}
	}
	printArray(input);
	return 0;
}
