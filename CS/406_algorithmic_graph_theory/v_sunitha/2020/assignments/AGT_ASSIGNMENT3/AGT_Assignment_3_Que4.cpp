#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int N;
map< int, map<int, int> > Adj;
map< int, bool > Visited;

void addNode(int x)
{
    if (Adj.find(x) != Adj.end())
    {
        cout << "Node already exists.\n";
        return;
    }
    Adj[x];
}

void removeNode(int a)
{
    Adj.erase(a);
    for (auto itr = Adj.begin(); itr != Adj.end(); itr++)
    {
        if (itr->second.find(a) != itr->second.end())
        {
            itr->second[a]--;
            if (itr->second[a] <= 0)
                itr->second.erase(a);
        }
    }
}

void addEdge(int a, int b)
{
    Adj[a][b]++;
    Adj[b][a]++;
}

void removeEdge(int a, int b)
{
    Adj[a][b]--;
    Adj[b][a]--;
    if (Adj[a][b] == 0)
    {
        Adj[a].erase(b);
        Adj[b].erase(a);
    }
}


int DFS(int a)
{
    Visited[a] = 1;
    stack<int> s;
    s.push(a);
    cout << "The DFS traversal is: " << endl;
    int cnt = 0;
    while (!s.empty())
    {
        cnt++;
        int x = s.top();
        s.pop();
        cout << x << " ";
        for (auto itr = Adj[x].begin(); itr != Adj[x].end(); itr++)
        {
            if (!Visited[itr->first])
            {
                Visited[itr->first] = true;
                s.push(itr->first);
            }
        }
    }
    cout<<endl;
    return cnt;
}

int BFS(int a)
{
    Visited[a] = 1;
    queue<int> q;
    q.push(a);
    cout << "The BFS traversal is: " << endl;
    int cnt = 0;
    while (!q.empty())
    {
        cnt++;
        int x = q.front();
        q.pop();
        cout << x << " ";
        for (auto itr = Adj[x].begin(); itr != Adj[x].end(); itr++)
        {
            if (!Visited[itr->first])
            {
                Visited[itr->first] = true;
                q.push(itr->first);
            }
        }
    }
    cout << endl;
    return cnt;
}

void _clearVisited()
{
    Visited.clear();
}

void connectedComponentsCount()
{
    Visited.clear();
    int c = 0;
    for (auto itr = Adj.begin(); itr != Adj.end(); itr++)
    {
        if (!Visited[itr->first])
        {
            int cnt = 1;
            c++;
            cnt = DFS(itr->first);
            cout << "The number of connected nodes from node " << itr->first << " are: ";
            cout << cnt << endl;
        }
    }
    cout << "The number of components are: " << c << endl;
}

int main()
{
    int m;
    cout << "Enter number of nodes and edges: " << endl;
    cin >> N >> m;
    cout << "Enter the nodes connected to each other: " << endl;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        Adj[x][y]++;
        Adj[y][x]++;
    }

    cout << "Enter a number from the following choices: " << endl;
    cout << "1. Add Node" << endl;
    cout << "2. Remove Node" << endl;
    cout << "3. Add Edge" << endl;
    cout << "4. Remove Edge" << endl;
    cout << "5. DFS Traversal from node X" << endl;
    cout << "6. BFS Traversal from node X" << endl;
    cout << "7. No of connected components" << endl;
    cout << "9. Quit" << endl;
    cout << "0. Repeat Options" << endl;

    bool loop = true;

    while (loop)
    {
        int q, a, b;
        cin >> q;
        switch (q)
        {
        case 1:
            cin >> a;
            addNode(a);
            cout << "Node added successfully." << endl;
            break;

        case 2:
            cin >> a;
            removeNode(a);
            cout << "Node removed successfully." << endl;
            break;

        case 3:
            cin >> a >> b;
            addEdge(a, b);
            cout << "Edge added successfully." << endl;
            break;

        case 4:
            cin >> a >> b;
            removeEdge(a, b);
            cout << "Edge removed successfully." << endl;
            break;

        case 5:
            _clearVisited();
            cin >> a;
            DFS(a);
            break;

        case 6:
            _clearVisited();
            cin >> a;
            BFS(a);
            break;

        case 7:
            connectedComponentsCount();
            break;

        case 9:
            loop = false;
            break;

        case 0:
            cout << "Enter a number from the following choices: " << endl;
            cout << "1. Add Node" << endl;
            cout << "2. Remove Node" << endl;
            cout << "3. Add Edge" << endl;
            cout << "4. Remove Edge" << endl;
            cout << "5. DFS Traversal from node X" << endl;
            cout << "6. BFS Traversal from node X" << endl;
            cout << "7. No of connected components" << endl;
            cout << "9. Quit" << endl;
            cout << "0. Repeat Options" << endl;
            break;

        default:
            cout << "Enter your choice again." << endl;
            break;
        }
    }
    return 0;
}
