#include<iostream>
using namespace std;
#include<string.h>
int max(int a,int b) {
	if(a>b)
		return a;
	else
		return b;
}

int lcs(int a[],int b[],int m,int n) {
	int l[m+1][n+1];
	int k;
	if(m>n)
		k=n;
	else
		k=m;
	int lc[k];
	k=0;
	for(int i=0;i<m+1;i++)
		l[0][i]=0;
	for(int i=0;i<n+1;i++)
		l[i][0]=0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) {
			if(a[i-1]==b[j-1]) {
				lc[k]=a[i-1];
				l[i][j]=l[i-1][j-1]+1;
				k++;
			}
			else
				l[i][j]=max(l[i-1][j],l[i][j-1]);
		}
	cout<<"The longest common subsequence is: ";
	for(int i=0;i<l[m][n];i++)
		cout<<lc[i];
	cout<<endl;
	return l[m][n];
}

int sort(int a[],int n) {
	int k,j;
	for(int i=1;i<n; i++) {
		k=a[i];
		j=i-1;
		while(j>=0 && a[j]>k) {
			a[j+1] = a[j];
			j=j-1;
		}
		a[j+1]=k;
	}
}

int main() {
	int a[100],b[100];
	int m,n;
	cout<<"Enter size of sequence 1: ";cin>>m;
	for(int i=0;i<m;i++)
		cin>>a[i];
	cout<<"Enter size of sequence 2: ";cin>>n;
	for(int j=0;j<n;j++)
	b[j]=a[j];

	sort(a,m);
	sort(b,n);
	cout<<"Longest common subsequence is of the size - "<<lcs(a,b,m,n)<<endl;
	return 0;

}
