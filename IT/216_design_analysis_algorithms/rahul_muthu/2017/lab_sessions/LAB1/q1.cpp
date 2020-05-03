#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

int lcs( char *x, char *y, int m, int n) {
	int l[m+1][n+1];
	int i,j;
	int k=0;
	int h;
	if (m<n){
		h=m;}
	else {
		h=n;}
	char final[h];


	for(i=0;i<=m;i++) {
		for(j=0;j<=n;j++) {
			if(i == 0 || j == 0)
			l[i][j] = 0;

			else if(x[i-1] == y[j-1] ){
			l[i][j] = l[i-1][j-1] + 1;
			final[k]=x[i-1];
			k++;
			final[k]='\0';}

			else
			l[i][j] = max(l[i-1][j], l[i][j-1]);


		}
	}

cout<<endl;
for (int r=0;r<h;r++){
cout<<final[r];}
cout<<endl;
int z = l[m][n];
return z;

}

int max(int a,int b) {
	if(a > b)
	return a;
	else
	return b;
}

int main() {
	char x[1000],y[1000];
	cout << "Enter two strings" << endl;
	cin >> x >> y;
	int l1 = strlen(x);
	int l2 = strlen(y);
	int b = lcs(x, y,l1,l2);
	cout << "Length of LCS is : " << b << endl;
return 0;
}
