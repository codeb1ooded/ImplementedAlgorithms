#include<iostream>
using namespace std;

int** edges;

int main(){
	int numVertices, numEdges;
	cout<<"Enter number of vertices: ";
	cin>>numVertices;
	cout<<"Enter number of edges: ";
	cin>>numEdges;
	edges = new int*[numVertices];
	for(int i=0; i<numVertices; i++){
		edges[i] = new int[numVertices];
		for(int j=0; j<numVertices; j++){
			edges[i][j] = 0;
		}
	}
	for(int i=0; i<numEdges; i++){
		int source, dest, cost;
		cout<<"\n"<<i<<"th Vertex\n";
		cout<<"Enter source vertex: ";
		cin>>source;
		cout<<"Enter destination vertex: ";
		cin>>dest;
		cout<<"Enter cost: ";
		cin>>cost;
		edges[source][dest] = cost;
		edges[dest][source] = cost;
	}
	// 4 5 0 2 2 2 3 4 0 3 2 3 1 3 1 0 1
	cout<<"\n";
//	for(int i=0; i<numVertices; i++){
//		for(int j=0; j<numVertices; j++){
//			cout<<edges[i][j]<<"\t";
//		}
//		cout<<"\n";
//	}
	int* s = new int[numVertices-1];
	int* d = new int[numVertices-1];
	int* cost = new int[numVertices-1];
	int* ver = new int[numVertices];	int t=0;
	ver[0] = 0;
	int i=0, j=numEdges;
	int x=-1, y;
	while(i<numVertices-1 && j>0){
		int lc=-1;
		for(int a=0; a<=t; a++){
			for(int b=0; b<numVertices; b++){
				int c = edges[ver[a]][b];
				if(c != 0){
					if(lc == -1){
						lc = c;
						x = ver[a];
						y = b;
					}
					else if(lc > c){
						lc = c;
						x = ver[a];
						y = b;
					}		
				}
			}
		}
		if(x == -1){
			break;
		}
		j--;
		edges[x][y] = 0;
		for(int a=0; a<t; a++){
			if(ver[a] == y)				break;
		}
		s[i] = x;
		d[i] = y;
		cost[i] = lc;
		i++;
		ver[++t] = y;
	}
	if(i != numVertices-1)		cout<<"\nNo MST possible";
	else{
		cout<<"\n\nEdges of MST:";
		cout<<"\nSource\tDest\tCost";
		for(int j=0; j<numVertices-1; j++){
			cout<<"\n  "<<s[j]<<"  \t  "<<d[j]<<" \t "<<cost[j];
		}
	}
	return 0;
}
