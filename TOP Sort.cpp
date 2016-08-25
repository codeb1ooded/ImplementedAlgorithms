#include<iostream>
using namespace std;

struct Vertex{
	int name;
	char* color;
	int startTime;
	int finishTime;
};

struct Node{
	Vertex v;
	struct Node* next = NULL;
};

struct Node* head = NULL;
char *BLACK = "Black", *GREY = "Grey", *WHITE = "White";
int numVertices, numEdges, count=0;
Vertex* vertices;
int** graph;

void inputGraph(){
	cout<<"Enter number of Vertices: ";		cin>>numVertices;
	cout<<"Enter number of Edges: ";		cin>>numEdges;
	vertices = new Vertex[numVertices];
	graph = new int*[numVertices];
	int i, j, k;
	for(i=0; i<numVertices; i++){
		vertices[i].name = i;
		vertices[i].color = BLACK;
		vertices[i].finishTime = 0;
		vertices[i].startTime = 0;
	}	
	for(i=0; i<numVertices; i++){
		graph[i] = new int[numVertices];
		for(j=0; j<numVertices; j++){
			graph[i][j] = INT_MAX;
		}
	}
	for(i=0; i<numEdges; i++){
		cout<<i+1<<". Enter start vertex: ";		cin>>j;
		cout<<"Enter end vertex: ";					cin>>k;
		graph[i][j] = 1;
	}
}

void DFS(Vertex s){
	if(s.color == WHITE){
		s.color = GREY;
		s.startTime = ++count;
		for(int i=0; i<numVertices; i++){	
			if(s.name != i && graph[s.name][i] != INT_MAX){
				DFS(vertices[i]);
			}
		}
		s.finishTime = ++count;
		s.color = BLACK;
		struct Node* node = new Node();
		node->v = s;
		node->next = head;
		head = node;
	}
}

int main(){
	inputGraph();
	// 9 9 0 9 0 1 6 7 1 9 1 2 3 2 2 5 3 4 4 5
	for(int i=0; i<numVertices; i++){
		DFS(vertices[i]);
	}
	for(int i=0; i<numVertices; i++){
		cout<<vertices[i].startTime<<"\t"<<vertices[i].finishTime<<"\n";
	}
	return 0;
}
