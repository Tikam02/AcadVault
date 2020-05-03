
/*----Part 8 - Maximum Bipartite Matching----*/

/*     Name: Mohamed Shadab
       ID: 201601211           */

#include<bits/stdc++.h>

using namespace std;

vector<int> adj[1005];
int match[1005];
bool vis[1005];

bool bpm(int u) {
	for (int i=0; i<adj[u].size(); i++) {
		if (!vis[adj[u][i]]) {
			vis[adj[u][i]]=true;
			if (match[adj[u][i]]<0 || bpm(match[adj[u][i]])) {
				match[adj[u][i]]=u;
				return true;
			}
		}
	}
	return false;
}

int maximum(int nodes) {
	memset(match,-1,sizeof match);
	int mx=0;
	for (int u=0; u<nodes; u++) {
		memset(vis,0,sizeof vis);
		if (bpm(u)) {
			mx++;
		}
	}
	return mx;
}

int main() {
	int nodes,edges;
	cin>>nodes>>edges;
	for(int i=0; i<edges; i++) {
		int x,y;
		cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	cout<<maximum(nodes)<<endl;
	return 0;
}
