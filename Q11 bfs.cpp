#include<stdio.h>
int max=100;

struct Vertex{
	char name;
	char visited;  // possible values B:not visited, W:processing, G: done
	
};

struct Edge{
	Vertex start;
	Vertex end;
};

struct Graph{
	int nv;
	Vertex vertices[100];
};


void main(){
	Graph g;
	int i;
	scanf("%d\n%d", &g.nv, &g.ne);
	printf("\nEnter vertices:");
	for(i=0; i<nv; i++){
		scanf("%d", &g.vertices[i]);
	}
	printf("\nEnter edges:");
	for(i=0; i<ne; i++){
		scanf("%d", &g.edges[i]);
	}
	Vertex v[] = adjacent('A', g);
	for(i=0; i<nv && adjacent!= NULL; i++){
		printf("\n%d",adjacent[i]);
	}
}
