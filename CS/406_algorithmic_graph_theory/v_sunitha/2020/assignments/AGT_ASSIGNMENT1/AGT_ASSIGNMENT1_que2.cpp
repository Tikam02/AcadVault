#include <iostream>
using namespace std;

void inc2adj(int **inc, int **adj, int n, int m)
{
    // Converts a given incidence matrix to adjacency matrix.
    // Uses the fact that sum of column in an incidence matrix is 2.

    int i, j;

    // Here both the inner and outer loop can be parallelizable but again due to the temp_vertex variable, there needs to be a
    // critical section. Hence, we parallelize the outer loop to avoid these issues. We use static scheduling here because all
    // the loops will have similar load so to increase efficiency, we use static scheduling.

    //#pragma omp parallel for private(j, dist) schedule(static)
    for (i = 1; i <= m; i++)
    {
        int temp_vertex = -1;
        for (j = 1; j <= n; j++)
        {
            if (inc[j][i] != 0)
            {
                if (temp_vertex == -1)
                {
                    temp_vertex = j;
                }
                else
                {
                    adj[temp_vertex][j] += 1;
                    adj[j][temp_vertex] += 1;
                    break;
                }
            }
        }
    }
}

void printMatrix(int **matrix, int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int n, m; //no of nodes and edges

    cout << "Enter the number of nodes and edges." << endl;
    cin >> n >> m;
    int i, j;
    int **incidence_matrix;
    incidence_matrix = new int *[n + 1];
    for (i = 0; i <= n; i++)
    {
        incidence_matrix[i] = new int[m + 1];
    }
    cout << "Enter the node and the edge connected to that node. (node, edge)" << endl;
    cout << "Enter -1 and -1 to exit." << endl;
    while (1)
    {
        int temp1, temp2;
        cin >> temp1 >> temp2;
        if (temp1 == -1)
        {
            break;
        }
        incidence_matrix[temp1][temp2] = 1;
    }
    cout << "Incidence Matrix:" << endl;
    printMatrix(incidence_matrix, n, m);
    cout << endl
         << endl;
    int **adjacency_matrix;
    adjacency_matrix = new int *[n + 1];
    for (i = 0; i <= n; i++)
    {
        adjacency_matrix[i] = new int[n + 1];
    }
    inc2adj(incidence_matrix, adjacency_matrix, n, m);
    cout << "Adjacency Matrix:" << endl;
    printMatrix(adjacency_matrix, n, n);

    return 0;
}
