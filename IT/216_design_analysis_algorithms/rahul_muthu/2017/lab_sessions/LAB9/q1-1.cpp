
/*----Part 1 - Block-Cut-Point Tree----*/

/*     Name: Mohamed Shadab
       ID:201601211           */

#include <bits/stdc++.h>

using namespace std;

bool vis[15];
int mn[15],t1[15],t2[15],pt[15],tim=0;
vector<int> adj[15],art;
vector<pair<int,int> > bd;

int dfs(int s) {
	vis[s]=true;
	t1[tim]=s;
	t2[s]=tim;
	tim++;
	int c=0;
	bool ok=false;
	int mnt=1e5;
	for(int i=0; i<adj[s].size(); i++) {
		if(!vis[adj[s][i]]) {
			pt[adj[s][i]]=s;
			mnt=min(mnt,dfs(adj[s][i]));
			c++;
			if(!ok && s!=0 && mn[adj[s][i]]>=t2[s]) {
				ok=true;
				art.push_back(s);
			}
			if(mn[adj[s][i]]>t2[s]) {
				int a=min(adj[s][i],s);
				int b=max(adj[s][i],s);
				bd.push_back(make_pair(a,b));
			}
		}
		else {
			if(adj[s][i]!=pt[s]) {
				mnt=min(mnt,t2[adj[s][i]]);
			}
		}

	}
	if(s==0 && c>1) art.push_back(s);
	mn[s]=mnt;
	return mnt;
}

int main() {
	int n,m;
	cin>>n>>m;
	for(int i=0; i<m; i++) {
		int x,y;
		cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	memset(vis,false,sizeof vis);
	memset(pt,-1,sizeof pt);
	dfs(0);
	sort(art.begin(),art.end());
	sort(bd.begin(),bd.end());
	cout<<art.size()<<endl;
	for(int i=0; i<art.size(); i++) {
		cout<<art[i]<<" ";
	}
	cout<<endl;
	return 0;
}
