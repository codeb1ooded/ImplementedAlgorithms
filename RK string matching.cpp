#include<iostream>
#include<cstring>
using namespace std;

int d = 256;
void search(char* pat, char* txt, int q){
    int m = strlen(pat);
    int n = strlen(txt);
    int i, j, p = 0, t = 0, h = 1;
    for (i = 0; i < m-1; i++)
        h = (h*d)%q;
    for (i = 0; i < m; i++){
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
    for (i = 0; i <= n - m; i++){
		if ( p == t ){
    	    for (j = 0; j < m; j++)
        	    if (txt[i+j] != pat[j])
            		break;
	        if (j == m)
    	    	cout<<"Pattern found at index" <<i<<"\n";
	    }
    	    if ( i < n-m ){
        	    t = (d*(t - txt[i]*h) + txt[i+m])%q;
            	if (t < 0)
            	t = (t + q);
			}       	
	}
}

int main(){
    char txt[] = "Analysis and design of algorithm ";
    char pat[] = "design";
    int q = 101;
    search(pat, txt, q);
    return 0;
}


