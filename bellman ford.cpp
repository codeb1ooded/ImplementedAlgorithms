#include<iostream>
using namespace std;

struct Vertex{
	int name;
	int pred;
	int d;
};

struct Edge{
	Vertex startVertex;
	Vertex endVertex;
	int cost;
};

int numVertices, numEdges;
Edge* edges;
Vertex* vertices;

void inputGraph(){
	cout<<"Enter number of Vertices: ";		cin>>numVertices;
	cout<<"Enter number of Edges: ";		cin>>numEdges;
	edges = new Edge[numEdges];
	vertices = new Vertex[numVertices];
	int i, j;
	for(i=0; i<numVertices; i++){
		vertices[i].name = i;
		vertices[i].d = 10000;
		vertices[i].pred = -1;
	}			
	for(i=0; i<numEdges; i++){
		int name;
		cout<<i+1<<". Enter start vertex: ";		cin>>name;
		edges[i].startVertex = vertices[name];
		cout<<"Enter end vertex: ";					cin>>name;
		edges[i].endVertex = vertices[name];
		cout<<"Enter cost: ";						cin>>edges[i].cost;
	}
}

void initaliseGraph(int s){
	for(int i=0; i<numEdges; i++){
		if(edges[i].startVertex.name == s){
			edges[i].startVertex.d = 0;
		}
		if(edges[i].endVertex.name == s){
			edges[i].endVertex.d = 0;
		}
	}
	vertices[s].d = 0;
}

void relax(Vertex u, Vertex v, int w, int i){
	if(u.d + w < v.d){
		v.d = u.d + w;
		v.pred = u.name;
		vertices[v.name] = v;
	}
}

int BellmanFord(int s){
	initaliseGraph(s);
	int i, j, k;
	for(k=1; k<numVertices; k++){
		for(j=0; j<numEdges; j++){
			Vertex u = vertices[edges[j].startVertex.name], v = vertices[edges[j].endVertex.name];
			relax(u, v, edges[j].cost, j);
		}
	}
	for(j=0; j<numEdges; j++){
		Vertex u = vertices[edges[j].startVertex.name], v = vertices[edges[j].endVertex.name];
		if(u.d + edges[j].cost < v.d){
			return 0;
		}
	}
	return 1;
}

void printGraph(){
	for(int i=0; i<numVertices; i++){
		cout<<i+1<<". "<<vertices[i].d<<"\n";
	}
}

int main(){
	// 5 9 1 2 5 1 3 8 1 4 -4 2 1 -2 3 2 -3 4 2 7 4 0 2 0 1 6 0 3 7
	inputGraph();
	BellmanFord(0);
	cout<<"\n\nGraph: \n";
	printGraph();
	return 0;
}
