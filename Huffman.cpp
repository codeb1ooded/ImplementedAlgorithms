#include<iostream>
#include<string>
using namespace std;
int size, heapSize;

struct huffman{
	char alph;
	float freq;
};

string* symbols;
string* codes;

huffman* putInHeap(huffman obj, huffman* heap, int s){
	heap[s] = obj;
	int p = (s-1)/2, c=s;
	while( ( c != 0) &&(heap[c].freq < heap[p].freq) ){
		huffman temp = heap[c];
		heap[c] = heap[p];
		heap[p] = temp;
		c = p;
		p = (c-1)/2;
	}
	heapSize++;
	return heap;
}

huffman* createHeapFromhuffmans(huffman* huffmans){
	huffman* result = new huffman[size];
	for(int i=0; i<size; i++){
		result = putInHeap(huffmans[i], result, i);
	}
	return result;
}

huffman extractMin(huffman* heap){
	huffman minhuffman= heap[0];
	heap[0] = heap[heapSize-1];
	
	heapSize--;
	int j =0;
	int left=1, right=2;
	while(left<heapSize){
		huffman toReplace = heap[j];
		int check=0;
		int x;
		if(heap[left].freq< heap[j].freq){
			toReplace = heap[left];
			x = left;
			check =-1;
		}
		if(right<heapSize && heap[right].freq < toReplace.freq) {
			toReplace = heap[left];
			x = right;
			check =-1;
		}
		if(check != 0){
			heap[x] = heap[j];
			heap[j] = toReplace;
			j= x;
			left = 2*j+1;
			right = 2*j+2;
		}
		else			break;
	}
	return minhuffman;
}

void allOne(int index){
	char one = symbols[index][0];
	if(one>=48 && one<=57){
		allOne(one-48);
	}
	else{
		codes[one-97] += '0';
	}
	char two = symbols[index][1];
	if(two>=48 && two<=57){
		allOne(two-48);
	}
	else{
		codes[two-97] += '0';
	}
}

void allTwo(int index){
	char one = symbols[index][0];
	if(one>=48 && one<=57){
		allOne(one-48);
	}
	else{
		codes[one-97] += '1';
	}
	char two = symbols[index][1];
	if(two>=48 && two<=57){
		allOne(two-48);
	}
	else{
		codes[two-97] += '1';
	}
}

void figureOut(){
	for(int i = size-2; i>=0; i--){
		char one1 = symbols[i][0];
		int one = (int)one1;
		if(one>=48 && one<=57){
			allOne(one-48);
		}
		else{
			codes[one-97] += '0';
		}
		char two = symbols[i][1];
		if(two>=48 && two<=57){
			allTwo(two-48);
		}
		else{
			codes[two-97] += '1';
		}
	}
}

int main(){
	cout<<"Enter number of elements: ";
	cin>>size;
	huffman* array = new huffman[size];
	char enter;
	cout<<"Enter characters and frequencies: ";
	for(int i=0; i<size; i++){
		cin>>array[i].alph>>array[i].freq;
	}
	// 5 a 10 b 20 c 30 d 32 e 13
	huffman* heap = createHeapFromhuffmans(array); 
	symbols = new string[size-1];
	codes = new string[size];
	int m= -1;
	while(heapSize>1){
		huffman obj1 = extractMin(heap);
		huffman obj2 = extractMin(heap);
		char sym1 = obj1.alph, sym2 = obj2.alph;
		++m;
		symbols[m] = symbols[m]+sym1;
		symbols[m] = symbols[m]+sym2;
		huffman r;
		r.alph = (char) (m+48);
		r.freq = obj1.freq + obj2.freq;
		heap = putInHeap(r, heap, heapSize);
	}
	figureOut();
	cout<<"Codes: \n";
	for(int i=0; i<size; i++){
		cout<<array[i].alph<<":\t"<<codes[i]<<"\n";
	}
	return 0;
}
