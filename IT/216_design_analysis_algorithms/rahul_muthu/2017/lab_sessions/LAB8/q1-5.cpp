
/*----Part 5 - Bipartedness of Graph----*/

/*     Name: Mohamed Shadab
       ID: 201601211           */

#include<bits/stdc++.h>

using namespace std;

vector<int> adj[1005];
int vis[1005]={0};
int color[1005];
int main() {
	int nodes,edges;
	cin>>nodes>>edges;
	vector<pair<int,int> > e;
	for(int i=0; i<edges; i++) {
		int x,y;
		cin>>x>>y;
		e.push_back(make_pair(x,y));
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int source;
	cin>>source;
	queue<int> q;
	q.push(source);
	vis[source]=1;
	color[cource]=1;
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		for(int i=0; i<adj[x].size(); i++) {
			if(!vis[adj[x][i]]) {
				if(color[x]==1) color[adj[x][i]]=0;
				else color[adj[x][i]]=1;
				vis[adj[x][i]]=1;
				q.push(adj[x][i]);
			}
		}
	}
	for(int i=0; i<e.size(); i++) {
		int x=e[i].first;
		int y=e[i].second;
		if(color[x]==color[y]) {
			cout<<"Not bipartite"<<endl;
			return 0;
		}
	}
	cout<<"Bipartite"<<endl;
	return 0;
}
