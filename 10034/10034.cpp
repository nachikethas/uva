#include<iostream>
#include<cstdlib>
#include<queue>
#include<string>
#include<vector>
#include<cmath>
#include<cfloat>


#define MAXV 200
#define MAXD 200
#define MAXDIST 999

typedef struct{
	int v;		
	float weight;
}edge;

struct node{
	float x,y;
	bool visited;
};

class Graph {
	edge edges[MAXV][MAXD];
	int degree[MAXV];
	int parent [MAXV];		// processV needs parent for coloring.
	bool intree[MAXV];
	float distance[MAXV];
	
	int nV;
	int nE;
	bool directed;
	bool bipartite;

	void insertE (int x, int y, float w);

	public:
	Graph ();
	void readG ();
	float prim();
};

using namespace std;

float norm (float x1, float y1, float x2, float y2){
	return sqrt(pow(x1-x2, 2.0) + pow(y1-y2, 2.0));
}

Graph::Graph (){
	nV = 0;
	nE = 0;
	directed = false;
	bipartite = true;

	for (int i=0; i<MAXV; i++){
		degree[i] = 0;
		for (int j=0; j<MAXD; j++){
			edges[i][j].v = -1;
			edges[i][j].weight = -1.0;
		}
		parent[i] = -1;
	}
}

void Graph::readG () {
	cin>>nV;

	float x, y, px, py;
	float wt;

	float V[MAXV][2];

	for (int i=1; i<MAXV; i++){
		intree[i] = false;
		distance[i] = MAXDIST;
	}

	cin>>V[0][0];
	cin>>V[0][1];
	for (int i=1; i<nV; i++){
		cin>>V[i][0];
		cin>>V[i][1];
		for (int j=0; j<i; j++){
			wt = norm (V[j][0], V[j][1], V[i][0], V[i][1]);
			insertE (j, i, wt);
		}
	}
	return;
}

// Assuming for now that we read only undirected graphs
void Graph::insertE (int x, int y, float w) {
	edges[x][degree[x]].v = y;
	edges[x][degree[x]].weight = w;
	degree[x]++;

	edges[y][degree[y]].v = x;
	edges[y][degree[y]].weight = w;
	degree[y]++;

	nE++;

	return;
}

float Graph::prim (){
	float wt, dist;

	int v = 0;
	distance[v] = 0.0;

	int w;

	float treeWeight = 0.0;
	int numEs = 0;
	while ((intree[v] == false)){
		intree[v] = true;
		treeWeight += distance[v];

		// Update the node weights
		for (int i=0; i<degree[v]; i++){
			w = edges[v][i].v;
			wt = edges[v][i].weight;	
			if ((distance[w] > wt) && (intree[w] == false)){
				distance[w] = wt;
				parent[w] = v;
			}
		}

		// Pick the node with the min weight
		dist = MAXDIST;
		int u = 0;
		for (int i=1; i<nV; i++){
			if ((dist > distance[i]) && (intree[i] == false)){
				dist = distance[i];
				u = i;
			}
		}
		// The selected edge is (u,parent[u])
		v = u;
	}
	return treeWeight;
}

void testcase(){
	Graph g;
	
	g.readG();
	g.prim();

}

int main (void){
	int numTests;
	cin>>numTests;
	string str;

	vector<Graph> g(numTests);
	
	float result;
	for (int i = 0; i<numTests; i++){
		g[i].readG();
		result = g[i].prim();
		printf("%.2lf\n", result);
		if (i < numTests-1)
			cout<<endl;
	}
	return 0;
}

