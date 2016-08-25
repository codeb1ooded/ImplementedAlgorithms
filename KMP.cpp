#include<iostream>
#include<cstring>
using namespace std;

void computeLPSArray(char *pat, int M, int *lps){
    int len = 0;  
    int i;
    lps[0] = 0; 
    i = 1;
    while (i < M){
       if (pat[i] == pat[len]){
         len++;
         lps[i] = len;
         i++;
       }
       else {
         if (len != 0)
           len = lps[len-1];
         else{
           lps[i] = 0;
           i++;
         }
       }
    }
}

void KMPSearch(char *pat, char *txt){
    int M = strlen(pat);
    int N = strlen(txt);
    int *lps = new int[M];
    int j  = 0; 
    computeLPSArray(pat, M, lps);
    int i = 0;
    while (i < N){
      if (pat[j] == txt[i]){
        j++;
        i++;
      }
      if (j == M){
        cout<<"Found pattern at index " <<i-j<<"\n";
        j = lps[j-1];
      }
      else if (i < N && pat[j] != txt[i]){
        if (j != 0)
         j = lps[j-1];
        else
         i = i+1;
      }
    }
    delete [] lps; 
}

int main()
{
   char *txt = "abcabdeaba";
   char *pat = "a";
   KMPSearch(pat, txt);
   return 0;
}

