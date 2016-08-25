#include<iostream>
using namespace std;

int** inputMatrix(int n){
	int** array = new int*[n];
	for(int i=0; i<n; i++){
		array[i] = new int[n];
		for(int j=0; j<n; j++){
			cin>>array[i][j];
		}
	}
	return array;
}

void printMatrix(int** matrix, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<matrix[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

int** divideMatrix(int** matrix, int n, int rep){
	int** mat = new int*[n/2];
	if(rep == 1){
		for(int i=0; i<n/2; i++){
			mat[i] = new int[n/2];
			for(int j=0; j<n/2; j++){
				mat[i][j] = matrix[i][j];
			}
		}
	} else if(rep == 2){
		for(int i=0; i<n/2; i++){
			mat[i] = new int[n/2];
			for(int j=0; j<n/2; j++){
				mat[i][j] = matrix[i][j+n/2];
			}
		}
	} else if(rep == 3){
		for(int i=0; i<n/2; i++){
			mat[i] = new int[n/2];
			for(int j=0; j<n/2; j++){
				mat[i][j] = matrix[i+n/2][j];
			}
		}
	} else{
		for(int i=0; i<n/2; i++){
			mat[i] = new int[n/2];
			for(int j=0; j<n/2; j++){
				mat[i][j] = matrix[i+n/2][j+n/2];
			}
		}
	}
	return mat;
}

int** subtractMatrix(int** matrixA, int** matrixB, int n){
	int** matrix = new int*[n];
	for(int i=0; i<n; i++){
		matrix[i] = new int[n];
		for(int j=0; j<n; j++){
			matrix[i][j] = matrixA[i][j] - matrixB[i][j];
		}
	}
	return matrix;
}

int** addMatrix(int** matrixA, int** matrixB, int n){
	int** matrix = new int*[n];
	for(int i=0; i<n; i++){
		matrix[i] = new int[n];
		for(int j=0; j<n; j++){
			matrix[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}
	return matrix;
}

int** multiplyMatrices(int** matrixA, int** matrixB){
	int** matrix = new int*[1];
	matrix[0] = new int[1];
	matrix[0][0] = matrixA[0][0] * matrixB[0][0];
	return matrix;
}

int** combineMatrices(int** C11, int** C12, int** C21, int** C22, int n){
	int** matrix = new int*[n];
	for(int i=0; i<n/2; i++){
		matrix[i] = new int[n];
		for(int j=0; j<n/2; j++){
			matrix[i][j] = C11[i][j];
		}
	}
	for(int i=0; i<n/2; i++){
		for(int j=0; j<n/2; j++){
			matrix[i][j+n/2] = C12[i][j];
		}
	}
	for(int i=0; i<n/2; i++){
		matrix[i+n/2] = new int[n];
		for(int j=0; j<n/2; j++){
			matrix[i+n/2][j] = C21[i][j];
		}
	}
	for(int i=0; i<n/2; i++){
		for(int j=0; j<n/2; j++){
			matrix[i+n/2][j+n/2] = C22[i][j];
		}
	}
	return matrix;
}

int** strassenMatrixMultiplication(int** matrixA, int** matrixB, int n){
	int** matrix;
	
	int **A11 = divideMatrix(matrixA, n, 1);
	int **A12 = divideMatrix(matrixA, n, 2);
	int **A21 = divideMatrix(matrixA, n, 3);
	int **A22 = divideMatrix(matrixA, n, 4);
	int **B11 = divideMatrix(matrixB, n, 1);
	int **B12 = divideMatrix(matrixB, n, 2);
	int **B21 = divideMatrix(matrixB, n, 3);
	int **B22 = divideMatrix(matrixB, n, 4);
	int** S1 = subtractMatrix(B12, B22, n/2);	
	int** S2 = addMatrix(A11, A12, n/2);	
	int** S3 = addMatrix(A21, A22, n/2);
	int** S4 = subtractMatrix(B21, B11, n/2);
	int** S5 = addMatrix(A11, A22, n/2);
	int** S6 = addMatrix(B11, B22, n/2);
	int** S7 = subtractMatrix(A12, A22, n/2);
	int** S8 = addMatrix(B21, B22, n/2);
	int** S9 = subtractMatrix(A11, A21, n/2);
	int** S10 = addMatrix(B11, B12, n/2);
	if(n == 2){
		int** P1 = multiplyMatrices(A11, S1);
		int** P2 = multiplyMatrices(S2, B22);
		int** P3 = multiplyMatrices(S3, B11);
		int** P4 = multiplyMatrices(A22, S4);
		int** P5 = multiplyMatrices(S5, S6);
		int** P6 = multiplyMatrices(S7, S8);
		int** P7 = multiplyMatrices(S9, S10);
		int** C11 = addMatrix(P4, P5, n/2);
		C11 = addMatrix(C11, P6, n/2);
		C11	= subtractMatrix(C11, P2, n/2);
		int** C12 = addMatrix(P1, P2, n/2);
		int** C21 = addMatrix(P3, P4, n/2);
		int** C22 = addMatrix(P1, P5, n/2);
		C22 = subtractMatrix(C22, P3, n/2);
		C22 = subtractMatrix(C22, P7, n/2);
		
		matrix = combineMatrices(C11, C12, C21, C22, n);
	}
	else{
		int** P1 = strassenMatrixMultiplication(A11, S1, n/2);
		int** P2 = strassenMatrixMultiplication(S2, B22, n/2);
		int** P3 = strassenMatrixMultiplication(S3, B11, n/2);
		int** P4 = strassenMatrixMultiplication(A22, S4, n/2);
		int** P5 = strassenMatrixMultiplication(S5, S6, n/2);
		int** P6 = strassenMatrixMultiplication(S7, S8, n/2);
		int** P7 = strassenMatrixMultiplication(S9, S10, n/2);
		int** C11 = addMatrix(P4, P5, n/2);
		C11 = addMatrix(C11, P6, n/2);
		C11	= subtractMatrix(C11, P2, n/2);
		int** C12 = addMatrix(P1, P2, n/2);
		int** C21 = addMatrix(P3, P4, n/2);
		int** C22 = addMatrix(P1, P5, n/2);
		C22 = subtractMatrix(C22, P3, n/2);
		C22 = subtractMatrix(C22, P7, n/2);
		
		matrix = combineMatrices(C11, C12, C21, C22, n);
	}
}

int main(){
	int n;
	// 2 3 2 2 2 1 1 1 1
	// 4 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
	cout<<"Enter size of matrix: ";		cin>>n;
	int** matrixA = inputMatrix(n);
	int** matrixB = inputMatrix(n);
	int** matrixR = strassenMatrixMultiplication(matrixA, matrixB, n);
	cout<<"Matrix A: \n";
	printMatrix(matrixA, n);
	cout<<"\n\nMatrix B: \n";
	printMatrix(matrixB, n);
	cout<<"\n\n\nResultant Matrix: \n";
	printMatrix(matrixR, n);
	return 0;
}
