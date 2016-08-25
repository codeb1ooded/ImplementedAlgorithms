#include<iostream.h>
#include<conio.h>
//using namespace std;

void NQueen(int* answer, int x, int n){
	if(x+1 == n){
		for(int i=0; i<n; i++){
			cout<<answer[i]<<" ";
		}
		cout<<"\n";
		return;
	}
	for(int i=1; i<n; i++){
		int check = 1;
		for(int j=0; j<x; j++){
			if(answer[j] == i || j+answer[j] == x+i || j-answer[j] == x+i){
				check = 0;
			}
		}
		if(check != 0){
			int l;
			int* temp = new int[n];
			for(l=0; l<x; l++){
				temp[l] = answer[l];
			}
			temp[l] = i;
			NQueen(temp, x+1, n);
		}
	}
}

int main(){
	clrscr();
	int n;
	cout<<"Enter number of queens: ";
	cin>>n;
	int* answer = new int[n];
	NQueen(answer, 0, n);
	getch();
	return 0;
}
