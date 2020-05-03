
/*----Part 1 - BFS Algorithm----*/

/*     Name: Mohamed Shadab
       ID: 201601211           */

#include<bits/stdc++.h>

using namespace std;

vector<int> adj[1005];
int vis[1005]={0};

int main() {
	int nodes,edges;
	cin>>nodes>>edges;
	for(int i=0; i<edges; i++) {
		int x,y;
		cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int source;
	cin>>source;
	queue<int> q;
	q.push(source);
	vis[source]=1;
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		for(int i=0; i<adj[x].size(); i++) {
			if(!vis[adj[x][i]]) {
				vis[adj[x][i]]=1;
				q.push(adj[x][i]);
			}
		}
	}
	for(int i=1; i<=nodes; i++) {
		cout<<vis[i]<<" ";
	}
	cout<<endl;
	return 0;
}
