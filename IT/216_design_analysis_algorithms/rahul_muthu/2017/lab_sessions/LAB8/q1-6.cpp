
/*----Part 6 - Shortest Cycle by BFS----*/

/*     Name: Mohamed Shadab
       ID: 201601211           */

#include <bits/stdc++.h>

using namespace std;

int adj[1005][1005];
int k =0;
int dist[1005];
int vis[1005];
int parent[1005];

struct crossedge {
	int startvertex;
	int endvertex;
};

crossedge* ced;

void bfs(int r,int v) {
	queue<int> q;
	q.push(r);
	memset(vis,0,sizeof vis);
	memset(parent,0,sizeof parent);
	vis[r]=1;
	parent[r]=-1;
	while(!q.empty()) {
		int t=q.front();
		q.pop();
		for(int i=0; i<v; i++) {
			if(adj[t][i]==1 && vis[i]==0) {
				vis[i]=vis[t]+1;
				parent[i]=t;
				adj[t][i]=2;
				adj[i][t]=2;
				q.push(i);
			}
		}
	}
	for(int i=0; i<v; i++) {
		for(int j=0; j<v; j++) {
			if(adj[i][j]==1 && vis[i]==vis[j]) {
				adj[i][j]=3;
				adj[j][i]=3;
			}
		}
	}
	for(int i=0; i<v; i++) {
		for(int j=0; j<v; j++) {
			if(adj[i][j]==3) {
				ced[k].startvertex=i;
				ced[k].endvertex=j;
				k++;
			}
			else if(adj[i][j]==1) {
				ced[k].startvertex=i;
				ced[k].endvertex=j;
				k++;
			}
		}
	}
	for(int i=0; i<k; i++) {
		int a=ced[i].startvertex;
		int b=ced[i].endvertex;
		dist[i]+=vis[a]-vis[r];
		dist[i]+=vis[b]-vis[r];
		if(vis[a]>vis[b]) {
			dist[i]+=vis[a]-vis[b];
		}
		else if(vis[b]>vis[a]) {
			dist[i]+=vis[b]-vis[a];
		}
		else {
			dist[i]++;
		}
	}
	int min = 100000l;
	int a;
	int b;
	for(int i=0; i<k; i++) {
		if(dist[i]<min) {
			min=dist[i];
			a=ced[i].startvertex;
			b=ced[i].endvertex;
		}
	}
	string path1="";
	string path2="";
	int i=b;
	while(i!=-1) {
		ostringstream oss;
		oss<<i;
		path1+=oss.str();
		i=parent[i];
	}
	i=a;
	while(i!=r) {
		ostringstream oss;
		oss<<i;
		path2+=oss.str();
		i=parent[i];
	}
	reverse(path2.begin(),path2.end());
	path1+=path2;
	cout<<path1<<endl;
}

int main() {
	int v,e;
	cin>>v>>e;
	for(int i=0; i<v; i++) {
		for(int j=0; j<v; j++) {
			adj[i][j]=-1;
		}
	}
	ced=new crossedge[e];
	memset(dist,0,sizeof dist);
	for(int i=0; i<e; i++) {
		int x,y;
		cin>>x>>y;
		adj[x][y]=1;
		adj[y][x]=1;
	}
	int source;
	cin>>source;
	bfs(source,v);
	return 0;
}
