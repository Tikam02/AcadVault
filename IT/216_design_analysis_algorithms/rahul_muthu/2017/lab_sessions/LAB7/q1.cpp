/*
// Prim's Algorithm

#include<bits/stdc++.h>

using namespace std;

bool vis[1005];
vector<pair<int,int> > adj[1005];

long long prim(int x) {
	// mimimum priority queue (sorted according to the weight of edges added)
	priority_queue<pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> > > Q;
	int y;
	long long minimumCost = 0;
	pair<int,int> p;
	Q.push(make_pair(0, x));    // pushing a source with 0 value in the priority queue
	while(!Q.empty()) {
		p = Q.top();
		Q.pop();
		x = p.second;
		if(vis[x] == true) continue;    // if already visited
		minimumCost+=p.first;       // adding the weight to the minimum cost
		vis[x]=true;
		for(int i=0; i<adj[x].size(); i++) {
			y=adj[x][i].second;
			if(!vis[y]) {
				Q.push(adj[x][i]);   // if not visited, adding the node with its edge weight
			}
		}
	}
	return minimumCost;
}

int main() {
	int nodes, edges;
	long long  minimumCost;
	cin >> nodes >> edges;
	for(int i = 0;i < edges;++i) {
		int x,y,w;
		cin>>x>>y>>w;
		adj[x].push_back(make_pair(w, y));
		adj[y].push_back(make_pair(w, x));
	}

	minimumCost=prim(1);  // calling prim function considering 1 as the source (source can be any node)
	cout<<minimumCost<<endl;
	return 0;
}
*/

// Dijkstra's Algorithm

#include<bits/stdc++.h>

using namespace std;

vector<pair<int,int> > adj[1005];
int dist[1005];
int vis[1005];

int main() {
	int n,m;
	cin>>n>>m;
	for(int i=0; i<m; i++) {
		int x,y,w;
		cin>>x>>y>>w;
		adj[x].push_back(make_pair(y,w));
		adj[y].push_back(make_pair(x,w));
	}
	memset(vis,0,sizeof vis);
	for(int i=1; i<=n; i++) {
		dist[i]=1e9;      // initially setting all the distances to infinity
	}
	dist[1]=0;
	// minimum priority queue (sorted according to the edge weight added)
	priority_queue< pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
	q.push(make_pair(0,1));   // source is 1 and distance of source from source = 0
	while(!q.empty()) {
		int d=q.top().first;
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;  // if already visited
		vis[x]=1;
		for(int i=0; i<adj[x].size(); i++) {
			int w=adj[x][i].second;
			int y=adj[x][i].first;
			if(dist[x]+w<dist[y]) {   // if (distance of x + edge weight) is less than distance of y
				dist[y]=dist[x]+w;
				q.push(make_pair(dist[y],y));  // pushing dist[y] and y in the priority queue
			}
		}
	}
	for(int i=1; i<=n; i++) {
		cout<<i<<" "<<dist[i]<<endl;
	}
	return 0;
}
