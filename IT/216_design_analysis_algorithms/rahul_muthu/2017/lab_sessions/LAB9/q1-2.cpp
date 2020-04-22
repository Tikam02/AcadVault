/*----Part 2 - Topological Sort ----*/

/*     Name: Mohamed Shadab
       ID:201601211           */

			 #include<iostream>
			 #include<list>
			 #include<stack>

			 using namespace std;

			 class Graph {
			     int V;
			     list<int> *adj;
			     bool visited[100];
			     void DFSUtil(int v, bool visited[]);
			     void Util(int v, bool visited[], stack<int> &Stack);

			 public:
			     Graph(int V);
			     void reset();
			     void addEdge(int v, int w);
			     void DFS();
			     void topologicalSort();
			     void printSCCs();
			     Graph getTranspose();
			 };

			 void Graph::reset() {
			     for (int i = 0; i < V; i++)
			         visited[i] = false;
			 }

			 Graph::Graph(int V) {
			     this->V = V;
			     adj = new list<int>[V];
			 }

			 void Graph::addEdge(int v, int w) {
			     adj[v].push_back(w);
			 }

			 void Graph::DFSUtil(int v, bool visited[]) {
			     visited[v] = true;
			     cout << v << " ";

			      list<int>::iterator i;
			     for(i = adj[v].begin(); i != adj[v].end(); ++i)
			         if(!visited[*i])
			             DFSUtil(*i, visited);
			 }


			 void Graph::DFS() {
			     reset();

			     for (int i = 0; i < V; i++)
			         if (visited[i] == false)
			             DFSUtil(i, visited);
			 }

			 void Graph::Util(int v, bool visited[],
			                                 stack<int> &Stack) {
			     visited[v] = true;

			     list<int>::iterator i;
			     for (i = adj[v].begin(); i != adj[v].end(); ++i)
			         if (!visited[*i])
			             Util(*i, visited, Stack);

			     Stack.push(v);
			 }

			 void Graph::topologicalSort() {
			     stack<int> Stack;

			     reset();

			     for (int i = 0; i < V; i++)
			       if (visited[i] == false)
			         Util(i, visited, Stack);

			     while (Stack.empty() == false) {
			         cout << Stack.top() << " ";
			         Stack.pop();
			     }
			 }

			 Graph Graph::getTranspose()
			 {
			     Graph g(V);
			     for (int v = 0; v < V; v++) {
			         list<int>::iterator i;
			         for(i = adj[v].begin(); i != adj[v].end(); ++i) {
			             g.adj[*i].push_back(v);
			         }
			     }
			     return g;
			 }


			 void Graph::printSCCs() {
			     stack<int> Stack;

			     reset();

			     for(int i = 0; i < V; i++)
			         if(visited[i] == false)
			             Util(i, visited, Stack);

			     Graph gr = getTranspose();

			     reset();

			     while (Stack.empty() == false) {
			         int v = Stack.top();
			         Stack.pop();

			         if (visited[v] == false) {
			             gr.DFSUtil(v, visited);
			             cout << endl;
			         }
			     }
			 }

			 int main() {
			     Graph g(5);
			     g.addEdge(0, 2);
			     g.addEdge(2, 1);
			     g.addEdge(2, 4);
			     g.addEdge(3, 4);
			     g.addEdge(1, 3);
					 g.topologicalSort();
			     return 0;
			 }
