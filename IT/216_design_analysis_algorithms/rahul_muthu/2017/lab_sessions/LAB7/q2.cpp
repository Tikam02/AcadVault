#include<bits/stdc++.h>

using namespace std;

int n;
vector<pair<int,pair<int,int> > > edges;
vector<int> adj[1005];
int vis[1005];

void dfs(int x) {
	vis[x]=1;
	for(int i=0; i<adj[x].size(); i++) {
		if(!vis[adj[x][i]]) dfs(adj[x][i]);
	}
}

int connected() {
	memset(vis,0,sizeof vis);
	dfs(1);
	for(int i=1; i<=n; i++) {
		if(!vis[i]) return 0;  // if any node is unvisited, then the graph is disconnected
	}
	return 1;
}


void reverseDelete() {
	sort(edges.begin(),edges.end());
	int minimumCost=0;
	for(int i=edges.size()-1; i>=0; i--) {
		int x=edges[i].second.first;
		int y=edges[i].second.second;
		for(int j=0; j<adj[x].size(); j++) {
			if(adj[x][j]==y) {
				adj[x].erase(adj[x].begin()+j);       // removing node y from adjacency list of x
				break;
			}
		}
		for(int j=0; j<adj[y].size(); j++) {
			if(adj[y][j]==x) {
				adj[y].erase(adj[y].begin()+j);     // removing node x from adjacency list of y
				break;
			}
		}
		if(connected()==0) {             // if the graph is disconnected
			adj[x].push_back(y);        // adding back the node y
			adj[y].push_back(x);        // adding back the node x
			minimumCost+=edges[i].first;  // adding the edge weight to the minimum cost of MST
		}
	}
	cout<<minimumCost<<endl;
}

int main() {
	int m;
	cin>>n>>m;
	for(int i=0; i<m; i++) {
		int x,y,w;
		cin>>x>>y>>w;
		adj[x].push_back(y);  // adding y in the adjacency list of x
		adj[y].push_back(x);  // adding x in the adjacency list of y
		edges.push_back(make_pair(w,make_pair(x,y)));
	}
	reverseDelete();
	return 0;
}
