
/*----Part 2 - Classification of Edges----*/

/*     Name: Mohamed Shadab
       ID: 201601211           */

#include<bits/stdc++.h>

using namespace std;

vector<int> adj[1005];
int vis[1005]={0};
int level[1005]={0};

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
	level[source]=0;
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		for(int i=0; i<adj[x].size(); i++) {
			if(!vis[adj[x][i]]) {
				level[adj[x][i]]=level[x]+1;
				vis[adj[x][i]]=1;
				q.push(adj[x][i]);
			}
		}
	}
	int f[1005]={0};
	int f1[1005]={0};
	vector<int> hori,verti;
	for(int i=0; i<e.size(); i++) {
		int x=e[i].first;
		int y=e[i].second;
		if(level[x]==level[y]) {
			f1[i]=1;
			hori.push_back(i);
		}
		else if(level[x]==level[y]+1) {
			f[x]++;
			if(f[x]>1) {
				f1[i]=1;
				verti.push_back(i);
			}
		}
		else if(level[y]==level[x]+1) {
			f[y]++;
			if(f[y]>1) {
				f1[i]=1;
				verti.push_back(i);
			}
		}
	}
	cout<<"Tree edges:"<<endl;
	for(int i=0; i<e.size(); i++) {
		if(f1[i]) continue;
		cout<<e[i].first<<" "<<e[i].second<<endl;
	}
	cout<<"Horizontal cross edges:"<<endl;
	for(int i=0; i<hori.size(); i++) {
		cout<<e[hori[i]].first<<" "<<e[hori[i]].second<<endl;
	}
	cout<<"Vertical cross edges:"<<endl;
	for(int i=0; i<verti.size(); i++) {
		cout<<e[verti[i]].first<<" "<<e[verti[i]].second<<endl;
	}
	return 0;
}
