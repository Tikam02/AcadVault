#include<bits/stdc++.h>

using namespace std;

int maxi=-1;

void findmax(int a[][2],int vis[],int n,int length,int element) {
	if(length>maxi) maxi=length;
	for(int i=0;i<n;i++){
		if(vis[i]==0){
			if(element==a[i][0]){
				vis[i]=1;
				findmax(a,vis,n,length+1,a[i][1]);
			}
			vis[i]=0;
		}
	}
}
int main(){
	int n,length;
	cout<<"Enter the no. of matrices : "<<endl;
	cin>>n;
	int a[n][2];
	int vis[n]={};
	cout<<"Enter the rows and cols one by one : "<<endl;
	for(int i=0;i<n;i++)
		cin>>a[i][0]>>a[i][1];
	for(int i=0;i<n;i++) {
		vis[i]=1;
		length=1;
		findmax(a,vis,n,length,a[i][1]);
		vis[i]=0;
	}
	cout<<"Maximum length of chain possible : "<<endl;
	cout<<maxi<<endl;
	return 0;
}
