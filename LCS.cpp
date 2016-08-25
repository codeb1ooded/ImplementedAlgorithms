#include<iostream>
#include<cstring>
using namespace std;

int lcs(char* s, char* t) {
	int m = strlen(s);
	int n = strlen(t);
	int** answers = new int*[m + 1];
	answers[0] = new int[n+1];
	for (int j = 0; j < n + 1; j++) {
		answers[0][j] = 0;
	}
	for (int i = 1; i < m + 1; i++) {
		answers[i] = new int[n+1];
		answers[i][0] = 0;
		for (int j = 1; j < n + 1; j++) {
			if (s[m - i] == t[n - j]) {
				answers[i][j] = 1 + answers[i - 1][j - 1];
 			} else {
 				if(answers[i - 1][j] > answers[i][j-1]){
 					answers[i][j] = answers[i - 1][j];
				}else{
 					answers[i][j] = answers[i][j-1];
				}
			}
		}
	}
	return answers[m][n];
}

int main(){
	char* s = new char[100];
	char* t = new char[100];
	cout<<"Enter first string: ";
	cin>>s;
	cout<<"Enter second string: ";
	cin>>t;
	int m = strlen(s);
	int n = strlen(t);
	cout<< lcs(s, t);
	return 0;
}
