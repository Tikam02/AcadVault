#include<bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cout<<"Enter the number of items that are 0-1: ";
	cin>>n;
	int v[n+1],w[n+1];
	cout<<"Enter values and weights:"<<endl;
	for(int i=1; i<=n; i++) {
		cin>>v[i]>>w[i];
	}
	int m;
	cout<<"Enter the number of items that are fractional: ";
	cin>>m;
	vector<pair<double,pair<double,double> > > f;
	cout<<"Enter values and weights:"<<endl;
	for(int i=0; i<m; i++) {
		double value,weight;
		cin>>value>>weight;
		double fraction=value/weight;
		f.push_back(make_pair(fraction,make_pair(value,weight)));
	}
	sort(f.rbegin(),f.rend());
	int W;
	cout<<"Enter the maximum weight: ";
	cin>>W;
	int dp[n+1][W+1][2];
	double finalans=0;
	for(int i=0; i<=W; i++) {
		int p1=i;
		int p2=W-p1;
		memset(dp,0,sizeof dp);
		for(int j=1; j<=n; j++) {
			for(int k=0; k<=p1; k++) {
				if(w[j]>k) {
					dp[j][k][0]=dp[j-1][k][0];
					dp[j][k][1]=dp[j-1][k][1];
				}
				else {
					if(dp[j-1][k][0]>=dp[j-1][k-w[j]][0]+v[j]) {
						dp[j][k][0]=dp[j-1][k][0];
						dp[j][k][1]=dp[j-1][k][1];
					}
					else {
						dp[j][k][0]=dp[j-1][k-w[j]][0]+v[j];
						dp[j][k][1]=dp[j-1][k-w[j]][1]+w[j];
					}

				}
			}
		}
		double ans=dp[n][p1][0];
		int rem=p2+p1-dp[n][p1][1];
		int sum1=0;
		for(int j=0; j<m; j++) {
			if(sum1+f[j].second.second<=rem) {
				sum1+=f[j].second.second;
				ans+=f[j].second.first;
			}
			else {
				double temp=rem-sum1;
				ans+=(f[j].second.first)*(temp/f[j].second.second);
				break;
			}
		}
		finalans=max(ans,finalans);

	}
	cout<<"The Answer is : "<<finalans<<endl;
	return 0;
}
