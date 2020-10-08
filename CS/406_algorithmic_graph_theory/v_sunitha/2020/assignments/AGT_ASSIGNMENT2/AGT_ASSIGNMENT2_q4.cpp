#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

vector< vector< int > > matrix_multiplication(vector< vector< int > > &A, vector< vector< int > > &B)
{
    vector< vector< int> > C(A.size(), vector<int>(A.size(), 0));
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A.size(); j++)
            for (int k = 0; k < A.size(); k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

void printMatrix(vector< vector< int > > &A)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[0].size(); j++)
        {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{

    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;
    vector< vector <int> > A(n, vector<int>(n, 0));
    cout << "Enter the vertices (u, v): " << endl;
    for (int i = 0; i < m; i++)
    {
        int temp1, temp2;
        cin >> temp1 >> temp2;
        //cout<<Enter the weight<<endl; => If you want weighted
        A[temp1-1][temp2-1] = 1;
        A[temp2-1][temp1-1] = 1;
    }
    cout<<endl<<endl;
    cout<<"Adjacency Matrix: "<<endl;
    printMatrix(A);
    cout<<endl<<endl;
    vector< vector <int> > D(A);
    vector< vector <int> > distance_matrix(n, vector<int>(n, 0));

    for (int k = 1; k <= n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && D[i][j] != 0 && distance_matrix[i][j] == 0)
                {
                    distance_matrix[i][j] = k;
                    distance_matrix[j][i] = k; //for undirected graph
                }
            }
        }
        D = matrix_multiplication(D, A);
    }
    cout<<"Distance matrix: "<<endl;
    printMatrix(distance_matrix);
    return 0;
}

