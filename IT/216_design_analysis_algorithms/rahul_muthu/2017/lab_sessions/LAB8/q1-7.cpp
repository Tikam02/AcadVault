
/*----Part 7 - Eccentricity, Diameter, Radius and Centre----*/

/*     Name: Mohamed Shadab
       ID: 201601211           */

#include <bits/stdc++.h>

using namespace std;

vector<int> adj[1005];
int vis[1005];
int ecc[1005];
int centre[1005];

void bfs(int r,int nodes) {
	memset(vis,0,sizeof vis);
	queue<int> q;
	q.push(r);
	vis[r]=1;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int i=0; i<adj[x].size(); i++) {
			if(vis[adj[x][i]]==0) {
				vis[adj[x][i]] = vis[x]+1;
				q.push(i);
			}
		}
	}
	sort(vis,vis+nodes);
	ecc[r] = vis[nodes-1];
	cout<<"Eccentricity of the vertex "<<r<<" is: "<<ecc[r]<<endl;
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
	for(int i=0; i<nodes; i++) {
		bfs(i,nodes);
	}
	for(int i=0; i<nodes; i++) {
		centre[i]=ecc[i];
	}
	sort(centre,centre+nodes);
	cout<<"Diameter of the graph is: "<<centre[nodes-1]<<endl;
	cout<<"Radius of the graph is: "<<centre[0]<<endl;
	cout<<"Centre of the graph is: ";
	for(int i=0; i<nodes; i++) {
		if(ecc[i]==centre[0]) {
			cout<<i<<" ";
		}
	}
	cout<<endl;
	return 0;

}
