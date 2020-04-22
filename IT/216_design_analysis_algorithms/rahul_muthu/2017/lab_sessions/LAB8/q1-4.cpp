
/*----Part 4 - Number of Connected Components----*/

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
	queue<int> q;
	int cnt=0;
	for(int i=1; i<=nodes; i++) {
		if(!vis[i]) {
			q.push(i);
			vis[i]=1;
			cnt++;
		}
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
	}
	cout<<"The number of connected components in the graph are "<<cnt<<"."<<endl;
	return 0;
}
