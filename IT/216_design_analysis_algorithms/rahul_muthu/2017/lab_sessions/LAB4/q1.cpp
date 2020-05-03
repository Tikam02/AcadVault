/* Name-Mohamed Shadab
	 ID-201601211
	 Assignment-4 */

#include<bits/stdc++.h>

using namespace std;

int n;
int sum[1001];
int dp[1001][1001];

int solve(int i,int j,vector<pair<int,int> > &a,int sum[]) {
	if(j<i) return 0;
	if(i==j) return a[i].second;
	if(dp[i][j]!=-1) return dp[i][j];
	int mn = 1e9;
	for(int k=i; k<=j; k++) {
		int ans = solve(i,k-1,a,sum) + solve(k+1,j,a,sum);
		if(ans<mn) {
			mn = ans;
		}
	}
	if(i==0) return dp[i][j] = mn + sum[j];
	return dp[i][j] = mn + sum[j] - sum[i-1];
}


int main() {
	cout<<"Enter the no. of pairs : "<<endl;
	cin>>n;
	vector<pair<int,int> > a;
	memset(dp,-1,sizeof dp);
	std::cout << "Enter the pairs one by one : " << '\n';
	for(int i=0; i<n; i++) {
		int key,value;
		cin>>key>>value;
		a.push_back(make_pair(key,value));
	}
	int sum[n];
	sum[0]=a[0].second;
	for(int i=1; i<n; i++) {
		sum[i]=a[i].second+sum[i-1];
	}
	solve(0,n-1,a,sum);
	cout<<"Ans - "<<endl;
	cout<<dp[0][n-1]-sum[n-1]<<endl;
	return 0;
}
