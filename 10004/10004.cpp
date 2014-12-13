#include<iostream>
#include<queue>

#define MAXV 200
#define MAXD 200

class Graph {
	int edges[MAXV][MAXD];
	int degree[MAXV];
	int parent [MAXV];		// processV needs parent for coloring.
	int nV;
	int nE;
	bool directed;
	bool bipartite;

	int color[MAXV];
	void insertE (int x, int y);
	void processE (int x, int y);
	void processV (int x);

	public:
	Graph ();
	int readG ();
	void bfs (int start);
	bool isBipartite() {return bipartite;}
};

using namespace std;

Graph::Graph (){
	nV = 0;
	nE = 0;
	directed = false;
	bipartite = true;

	for (int i=0; i<MAXV; i++){
		degree[i] = 0;
		for (int j=0; j<MAXD; j++)
			edges[i][j] = -1;
		color[i] = -1;
		parent[i] = -1;
	}
}

// Assuming for now that we read only undirected graphs
int Graph::readG () {
	int m,x,y;

	cin >> nV;
	if (nV == 0) return -1;

	cin >> m;

	for (int i=0; i<m; i++){
		cin>>x>>y;
		insertE (x, y);
	}
	return 0;
}

void Graph::insertE (int x, int y) {
	edges[x][degree[x]] = y;
	degree[x]++;

	edges[y][degree[y]] = x;
	degree[y]++;

	nE++;

	return;
}

// Assumes the parent has been colored
void Graph::processV (int x){
	int px = parent[x]; 

	if (px == -1){
		color[x] = 0;
		return;
	}
	if (color[px] == 0)
		color[x] = 1;
	if (color[px] == 1)
		color[x] = 0;
}

// Assumes x has been colored to 0 or 1
void Graph::processE (int x, int y){
	if (color[x] == color[y])
		bipartite = false;
}

void Graph::bfs (int start) {
	queue<int> toVisit;
	bool procd [MAXV], discd [MAXV];
	int v;
	
	for (int i=0; i<MAXV; i++){
		procd[i] = false;
		discd[i] = false;
	}

	toVisit.push(start);
	discd[start] = true;
	
	while (!toVisit.empty()) {
		v = toVisit.front();
		toVisit.pop();
		
		processV(v);

		for (int i=0; i<degree[v]; i++) {	
			if (edges[v][i] == -1)
				continue;
			if (discd[edges[v][i]] == false) {
				toVisit.push(edges[v][i]);
				discd[edges[v][i]] = true;
				parent[edges[v][i]] = v;
			}

			if (procd[edges[v][i]] == false) 
				processE(v,edges[v][i]);
		}
	}
}

int testcase(){
	Graph g;
	int fin = 0;
	
	fin = g.readG();
	if (fin == -1)
		return fin;

	g.bfs(0);

	if (!g.isBipartite())
		cout<<"NOT BICOLORABLE.\n";
	else
		cout<<"BICOLORABLE.\n";
}

int main (void) {
	int ti = 0;
	while(1){
		ti = testcase();
		if (ti == -1)
			break;
	}
}
