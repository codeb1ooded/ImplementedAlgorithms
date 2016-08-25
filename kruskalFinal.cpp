#include<iostream>
using namespace std;

int numEdges, numVertices, i;
int heapSize;
int** bfs;

class Vertex{
	public: int refNo;
};

class Edge{
	public:
	int cost;
	Vertex source;
	Vertex dest;
};

Edge* putEdgeInHeap(Edge edge, Edge* edges, int s){
	edges[s] = edge;
	int p = (s-1)/2, c=s;
	while( ( c != 0) &&(edges[c].cost < edges[p].cost) ){
		Edge temp = edges[c];
		edges[c] = edges[p];
		edges[p] = temp;
		c = p;
		p = (c-1)/2;
	}
	return edges;
}

Edge* createHeapFromEdges(Edge* edges){
	Edge* result = new Edge[numEdges];
	for(i=0; i<numEdges; i++){
		result = putEdgeInHeap(edges[i], result, i);
	}
	return result;
}

Edge extractMin(Edge* heap){
//	if(heapSize == 0)	return NULL;
	Edge minEdge= heap[0];
	heap[0] = heap[heapSize];
	
	heapSize--;
	int j =0;
	int left=1, right=2;
	while(left<heapSize){
		Edge toReplace = heap[j];
		int check=0;
		int x;
		if(heap[left].cost < heap[j].cost){
			toReplace = heap[left];
			x = left;
			check =-1;
		}
		if(right<heapSize && heap[right].cost < toReplace.cost) {
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
	// 4 5 0 1 1 1 2 2 2 3 3 3 0 1 0 2 5
	return minEdge;
}

int checkCycle(int src, int dest){
	int* vertex = new int[numVertices];
	for(int j=0; j<numVertices; j++)		vertex[j] = 0;
	bfs[src][dest] = 1;
	for(int j=0; j<numVertices; j++){
		for(int k=0; k<numVertices; k++){
			if(bfs[j][k] == 1){
				if(vertex[j] == 1){
					bfs[src][dest] = 0;
					return 0;
				}
				else			vertex[j] = 1;
			}
		}
	}
	bfs[src][dest] = 0;
	return 1;
}

int main(){
	cout<<"Enter number of vertices: ";
	cin>>numVertices;
	Vertex* vertices = new Vertex[numVertices];
	for(i=0; i<numVertices; i++){
		vertices[i].refNo = i;
	}				
	
	cout<<"Enter number of edges: ";
	cin>>numEdges;
	Edge* edges = new Edge[numEdges];
	cout<<"Enter all edges data as correspond to: ";
	for(i=0; i<numEdges; i++){
		cout<<"\n"<<i<<"th Edge: \n";
		cout<<"Enter Source Vertex ref no.: ";	cin>>edges[i].source.refNo;
		cout<<"Enter Destination Vertex ref no.: ";	cin>>edges[i].dest.refNo;
		cout<<"Enter cost: "; cin>>edges[i].cost;
	}
	
	Edge* heap = createHeapFromEdges(edges);
	heapSize = numVertices;
	Edge* T = new Edge[numVertices-1];
	int m=0;
	bfs = new int*[numVertices];
	for(int j=0; j<numVertices; j++){
		bfs[j] = new int[numVertices];
		for(int k=0; k<numVertices; k++){
			bfs[j][k] = 0;
		}
	}
	while(m<numVertices && heapSize > 0){
		Edge minEdge = extractMin(heap);
		int c = checkCycle(minEdge.source.refNo, minEdge.dest.refNo);
		if(c!=0){
			bfs[minEdge.source.refNo][minEdge.dest.refNo] = 1;
			T[m++] = minEdge;
		}
	}
	
	if(m<numVertices){
		cout<<"\n\nMST not possible!!!";
	}
	else{
		cout<<"\n\nEdges of MST:";
		cout<<"\nSource\tDest\tCost";
		for(int j=0; j<numVertices-1; j++){
			cout<<"\n  "<<T[j].source.refNo<<"  \t  "<<T[j].dest.refNo<<" \t "<<T[j].cost;
		}
	}
//	system("PAUSE");
	delete edges, vertices, T ,heap;
	return 0;
}
