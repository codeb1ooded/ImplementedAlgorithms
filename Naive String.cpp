#include<iostream>
#include<cstring>
using namespace std;

int patternMatch(char* text, char* pattern){
	for(int i=0; i<=(strlen(text)-strlen(pattern)); i++){
		for(int j=0; j<strlen(pattern); j++){
			if(text[i+j] != pattern[j]){
				break;
			}
			if(j == strlen(pattern)-1){
				return i;
			}
		}
	}
	return -1;
}

int main(){
	char* s = new char[100];
	char* t = new char[100];
	cout<<"Enter text string: ";
	cin>>s;
	cout<<"Enter pattern string: ";
	cin>>t;
	int i = patternMatch(s, t);
	if(i != -1) cout<<"\nPattern present at index "<<i;
	else cout<<"\nPattern not present!!";
	return 0;
}
