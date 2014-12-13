// Model the input as a DAG. Compute the longest path in the DAG and print this to 
// stdout.
//
#include<iostream>
#include<queue>
#include<string>
#include<list>
#include<unordered_map>
#include<algorithm>

using namespace std;

#define MAXWLEN 875

class Graph {
	// vector<int> degree;
	vector<int> sortedG;		// Stores the sorted DAG order
	vector<int> inDeg;
	unordered_map<int,string> word; 
	unordered_map<int,list<int>> edges; 
	unordered_map<int,list<int>> rev_edges; 

	int nV;
	int nE;
	int mpathLen;

	void insertE (int x, int y);
	void compute_inDeg (vector<int> &inDeg);
	bool isE (int x, int y);
	void topsort ();

	public:
	Graph ();
	void readG ();
	int pathLen ();
};


Graph::Graph (){
	nV = 0;
	nE = 0;
	mpathLen = 0;
}

void Graph::readG () {
	string str;
	while (getline(cin, str) && !str.empty()){
		word[nV] = str;	
		for (int i = 1; i<MAXWLEN; i++)
			if ( isE(nV-i,nV) )
				insertE(nV-i,nV);
		nV++;
	}

	inDeg.reserve(nV);
	for (int i=0; i<nV; i++){

		if (rev_edges[i].empty())
			inDeg.push_back(0);
		else
			inDeg.push_back(rev_edges[i].size());
	}
}

void Graph::insertE (int x, int y) {
	edges[x].push_back(y);
	rev_edges[y].push_back(x);

	nE++;

	return;
}

bool Graph::isE (int x, int y){
	int minL, maxL;

	minL = min(word[x].size(), word[y].size());
	maxL = max(word[x].size(), word[y].size());

	if ((maxL - minL) > 1) return false;

	if ((maxL - minL) == 1){
		if (word[x].compare(0,minL,word[y],0,minL) == 0)
			return true;
		if (word[x].compare(1,minL,word[y],0,minL) == 0)
			return true;
		if (word[x].compare(0,minL,word[y],1,minL) == 0)
			return true;
		return false;
	} else {
		int numConflict=0;
		for (int i=0; i<minL; i++){
			if (!(word[x].compare(i,1,word[y],i,1) == 0))
				numConflict++;
		}
		
		if (numConflict>1)
			return false;
		else
			return true;
	}
}

void Graph::topsort (){
	sortedG.reserve(nV);
	vector<int> in (inDeg);
	queue<int> zeroin;
	int x, y;

	for (int i = 0; i<nV; i++)
		if (in[i] == 0) zeroin.push(i);

	while (!zeroin.empty()){
		x = zeroin.front();
		zeroin.pop();
		sortedG.push_back(x);
		for (auto ti = edges[x].begin(); ti != edges[x].end(); ti++){
			y = *ti;
			in[y] = in[y] - 1;
			if (in[y] == 0) zeroin.push(y);
		}
	}
	
	if (sortedG.size() != nV){ 
		cout<<"Not a DAG.\n";
		cout<<"nV = "<<nV<<" and sortedG has size "<<sortedG.size()<<endl;
	}
}

int Graph::pathLen (){
	// topsort();
	vector<int> len(nV, 1);
	int x,y;
	int maxLx = 1;

	for (int it = 0; it < nV; it++){
		x = it;

		if (rev_edges[x].empty()) continue;

		maxLx = 1;
		for (auto ti = rev_edges[x].begin(); ti != rev_edges[x].end(); ti++){
			y = *ti;
			if (len[y] >= maxLx) maxLx = len[y];
		}
		len[x] = maxLx + 1;

		if (len[x] > mpathLen) mpathLen = len[x];
	}
	return mpathLen;
}

int main(){
	Graph g;
	g.readG();
	cout<<g.pathLen()<<endl;
	return 0;
}

