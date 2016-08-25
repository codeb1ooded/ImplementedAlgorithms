#include<iostream>
using namespace std;
long int** numMultiplications;
int* size;
int** braces;
int n;

void inputSizes(){
	cout<<"Enter number of matrices: ";		cin>>n;
	size = new int[n+1];
	numMultiplications = new long int*[n];
	braces = new int*[n];
	cout<<"Enter sizes: \n";
	for(int i=0; i<=n; i++){
		if(i != n)
		numMultiplications[i] = new long int[n];
		braces[i] = new int[n];
		cin>>size[i];
	}
}

void matrixChainMultiplication(){
	for(int i=0; i<n; i++){
		numMultiplications[i][i]=0;
	}
	for(int i=1; i<n; i++){
		for(int j=0; i+j<n; j++){
			int min = INT_MAX;
			int s = -1;
			for(int k=j; k<i+j; k++){
				long int c = numMultiplications[j][k] + numMultiplications[k+1][i+j] + size[j]*size[k+1]*size[i+j+1];
				if(c < min){
					min = c;
					s = k;
				}
			}
			braces[j][j+i] = s;
			numMultiplications[j][j+i] = min;
		}
	}
}

void printBraces(int i, int j){
	if(i == j){
		cout<<"A"<<i+1;
	}
	if(braces[i][j] == -1 || i>=j)		return;
	cout<<" ( ";
	printBraces(i, braces[i][j]);
	cout<<" ) ";
	cout<<" ( ";
	printBraces(braces[i][j]+1, j);
	cout<<" ) ";
}

int main(){
	// 4 13 5 89 3 34
	inputSizes();
	matrixChainMultiplication();
	cout<<"\n"<<numMultiplications[0][n-1];
	cout<<"\n";
	printBraces(0, n-1);
	return 0;
}
