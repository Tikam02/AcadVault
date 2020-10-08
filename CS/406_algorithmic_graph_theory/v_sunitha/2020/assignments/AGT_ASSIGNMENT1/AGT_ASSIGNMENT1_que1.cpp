#include <iostream>
using namespace std;

void adj2inc(int **adj, int **inc, int n, int m)
{
    // Converts a given adjacency matrix to incidence matrix.
    // Uses lower-half matrix (symmetric) to calculate the adjacency matrix

    int i, j, edge_id = 1, n_edges = 0;

    // outer loop parallelizable. We can also parallelize inner loop but that will involve usage of critical sections
    // We use dynamic scheduling which means that the compiler will schedule the given process during runtime.
    // We do this because each iteration does not have equal amount of load (iterations closer to n will be more loaded)

    //#pragma omp parallel for private(j, dist) schedule(dynamic)
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (adj[i][j] != 0)
            {
                i == j ? n_edges = adj[i][j] / 2 : n_edges = adj[i][j];
                for (int k = 0; k < n_edges; k++)
                {
                    inc[i][edge_id] = 1;
                    inc[j][edge_id] = 1;
                    edge_id++;
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

    int **adjacency_matrix;
    adjacency_matrix = new int *[n + 1];
    for (i = 0; i <= n; i++)
    {
        adjacency_matrix[i] = new int[n + 1];
    }

    int **incidence_matrix;
    incidence_matrix = new int *[n + 1];
    for (i = 0; i <= n; i++)
    {
        incidence_matrix[i] = new int[m + 1];
    }

    cout << "Enter the 2 nodes connected to each other" << endl;
    cout << "Enter -1 and -1 to exit." << endl;
    while (1)
    {
        int temp1, temp2;
        cin >> temp1 >> temp2;
        if (temp1 == -1)
        {
            break;
        }
        adjacency_matrix[temp1][temp2] += 1;
        adjacency_matrix[temp2][temp1] += 1;
    }
    cout << "Adjacency Matrix:" << endl;
    printMatrix(adjacency_matrix, n, m);
    cout << endl
         << endl;

    adj2inc(adjacency_matrix, incidence_matrix, n, m);
    cout << "Incidence Matrix:" << endl;
    printMatrix(incidence_matrix, n, n);

    return 0;
}
