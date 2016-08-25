#include<iostream>
using namespace std;

void NQueen(int* answer, int x, int n){
	if(x == n){
		for(int i=0; i<n; i++){
			cout<<answer[i]<<" ";
		}
		cout<<"\n";
		return;
	}
	for(int i=1; i<=n; i++){
		bool check = true;
		for(int j=1; j<=x; j++){
			if(answer[j] != i){
				if(j+answer[j-1] == x+1+i && j-answer[j-1] == x+1+j){
					check = false;
				}
			}
		}
		if(check){
			int l;
			int* temp = new int[n];
			for(l=0; l<=x; l++){
				temp[l] = answer[l];
			}
			temp[l] = i;
			NQueen(temp, x+1, n);
		}
	}
}

int main(){
	int n;
	cout<<"Enter number of queens: ";
	cin>>n;
	int* answer = new int[n];
	NQueen(answer, 0, n);
	return 0;
}
