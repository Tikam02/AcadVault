#include<bits/stdc++.h>

using namespace std;

int level(long int f) {
	long int p=1;
	int ans=1;
	while((f/p)!=1) {
		p=pow(2,ans);
		ans++;
	}
	return ans;
}
void gencode(long int num,int len) {
	int i=len;
	int arr[len];
	while(i>0) {
		arr[i-1]=num%2;
		num/=2;
		i--;
	}
	for(i=0;i<len;i++) {
		cout << arr[i];
	}
	return;
}

int main() {
	long int L;
	int n,i;
	cout << "Enter no. of items(>1):-\n";
	cin >> n ;
	long int p[n];
	cout << "Enter value of all " << n << " items:-\n" ;
	for(i=0;i<n;i++) {
		cin >> p[i] ;
	}
	cout << "Enter maximum length:-\n";
	cin >> L ;
	sort(p,p+n);
	long int lt=2;
	int it=2,it2=2;
	int k=1;
	long int node=1;
	long int first=2;
	long int last=3;
	while(it<n) {
		if(lt+k+2>L)break;
		long int lim=pow(2,k);
		while(node<=lim) {
			if(lt+k+2<L&&it<n) {
				it++;
				it2++;
				lt+=k+2;
				node++;
				last=first*2+1;
				first++;
			}
			else if(lt+k+2==L&&it<n) {
				if(it+1==n) {
					it++;
					it2++;
					lt+=k+2;
					node++;
					last=first*2+1;
					first++;
				}
				else {
					lt+=k+2;
					it2++;
					last=first*2+1;
					first++;
					break;
				}
			}
			else {
				if(it==n)break;
				else {
					break;
				}
			}
		}
		if(node==lim+1)k++;
	}
	long long ans=0;
	for(i=n-1;i>=n-it;i--) {
		ans+=p[i];
	}
	cout << it << " " ;
	if(L>1)cout << ans ;
	else if(L==1)cout << p[n-1] ;
	else cout << 0 ;
	//    cout << "\n" << first << "\n" << last ;
	cout << "\n" ;
	int d;
	long int t;
	long int j=first;
	for(i=0;i<n;i++) {
		if(i<it2-1) {
			d=level(j);
			d--;
			t=j-pow(2,d);
			cout << p[n-1-i] << " " ;
			gencode(t,d);
			cout << " " << "Stolen" << "\n" ;
			j++;
		}
		else if(it2==n&&i==it2-1) {
			d=level(j);
			d--;
			t=j-pow(2,d);
			cout << p[n-1-i] << " " ;
			gencode(t,d);
			if(it2==it)cout << " " << "Stolen" << "\n" ;
			else cout << "\n" ;
		}
		else if(i==it2-1) {
			j=last*2;
			last=last*2+1;
			d=level(j);
			d--;
			t=j-pow(2,d);
			cout << p[n-1-i] << " " ;
			gencode(t,d);
			if(it2==it)cout << " " << "Stolen" << "\n" ;
			else cout << "\n" ;
		}
		else {
			j=last*2;
			last=last*2+1;
			d=level(j);
			d--;
			t=j-pow(2,d);
			cout << p[n-1-i] << " " ;
			gencode(t,d);
			cout << "\n" ;
		}
	}
}
