/*     Name: Mohamed Shadab
       ID: 201601211   */

#include <bits/stdc++.h>

using namespace std;

int main() {
	cout<<"Enter the length of the rod: ";
	int l;
	cin>>l;
	cout<<"Enter the price of each length: ";
	int a[l+1];
	for(int i=1; i<=l; i++) {
		cin>>a[i];
	}
	cout<<"Enter the amount in rupees you want to earn: ";
	int p;
	cin>>p;
	int dp[l+1][p+1];
	memset(dp,-1,sizeof dp);
	dp[0][0]=0;
	for(int i=1; i<=l; i++) {
		for(int j=1; j<=p; j++) {
			for(int k=1; k<=i; k++) {
				if(j-a[k]>=0 && dp[i-k][j-a[k]]>=0) dp[i][j]=k;
			}
		}
	}
	int i,j;
	for(i=1; i<=l; i++) {
		if(dp[i][p]>0) break;
	}
	if(i<=l) {
		cout<<"Yes, it is possible to earn exactly "<<p<<" rupees"<<endl;
		cout<<"It can be made by using the lengths:"<<" ";
		j=p;
		while(i!=0) {
			cout<<dp[i][j]<<" ";
			int temp=i;
			i-=dp[i][j];
			j-=a[dp[temp][j]];
		}
		cout<<endl;
	}
	else cout<<"No, it is not possible to earn exactly "<<p<<" rupees."<<endl;
	return 0;
}
