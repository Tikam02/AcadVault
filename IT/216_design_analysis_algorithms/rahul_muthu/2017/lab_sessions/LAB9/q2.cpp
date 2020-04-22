/*  Name: Mohamed Shadab
	ID: 201601211         */


#include <limits.h>
#include <iostream>
using namespace std;

#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

int printMST(int parent[], int n, int graph[V][V], int graph2[V][V], int j) {
    cout<<"Edge   Weight\n";
    for (int i = 0; i < V; i++) {
        if(i!=j) {
            cout << parent[i] <<" - " << i << "   " << graph[i][parent[i]] << "\n";
            graph2[i][parent[i]]++;
        }
    }
    cout<<"\n\n";
    return 0;
}

void primMST(int graph[V][V], int graph2[V][V]) {
    for (int j = 0; j < V; ++j) {
        int parent[V];
        int key[V];
        bool mstSet[V];

        for (int i = 0; i < V; i++) {
            key[i] = INT_MAX, mstSet[i] = false;
          }

        key[j] = 0;
        parent[j] = -1;

        for (int count = 0; count < V-1; count++) {
            int u = minKey(key, mstSet);

            mstSet[u] = true;

            for (int v = 0; v < V; v++)
                if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
                    parent[v]  = u, key[v] = graph[u][v];

      }

    printMST(parent, V, graph, graph2, j);
    }

}

int main() {
   /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
    int graph[V][V] = {{0, 2, 0, 6, 0},
                      {2, 0, 3, 3, 3},
                      {0, 3, 0, 0, 4},
                      {6, 3, 0, 0, 3},
                      {0, 3, 4, 3, 0},
                     };
    int graph2[V][V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
                graph2[i][j] = 0;

    primMST(graph,graph2);

    cout<<"\n";
    for (int i=0; i< V; i++) {
        for (int j=0; j<V; j++)
            cout<<graph2[i][j]<<"   ";
        cout << endl;
    }
  return 0;
}
