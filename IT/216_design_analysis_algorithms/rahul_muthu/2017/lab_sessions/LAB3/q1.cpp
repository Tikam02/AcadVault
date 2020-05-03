#include<bits/stdc++.h>
using namespace std;
void printParenthesis(int i, int j, int n,
                      int *bracket, char &name)
{
    if (i == j)
    {
        cout << name++;
        return;
    }

    cout << "(";
    printParenthesis(i, *((bracket+i*n)+j), n,
                     bracket, name);
    printParenthesis(*((bracket+i*n)+j) + 1, j,
                     n, bracket, name);
    cout << ")";
}

void matrixChainOrder(int p[], int n)
{
    int m[n][n];

    int bracket[n][n];
    for (int i=1; i<n; i++)
        m[i][i] = 0;

    for (int L=2; L<n; L++)
    {
        for (int i=1; i<n-L+1; i++)
        {
            int j = i+L-1;
            m[i][j] = INT_MAX;
            for (int k=i; k<=j-1; k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    bracket[i][j] = k;
                }
            }
        }
    }

    char name = 'A';

    cout << "Optimal Parenthesization is : ";
    printParenthesis(1, n-1, n, (int *)bracket, name);
    cout << "Optimal Cost is : " << m[1][n-1];
}

int main()
{
  int n=0;
  cout<<"Enter the no. of Matrices"<<endl;
  cin>>n;
  int arr[n+1];
  cout<<"Enter the list of rows and cols with the legal chain order::"<<endl;
  for(int i=0;i<n+1;i++){
    cin>>arr[i];}
  matrixChainOrder(arr, n+1);
  return 0;
}
