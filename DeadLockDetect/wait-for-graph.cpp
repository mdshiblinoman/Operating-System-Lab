/*
    Wait-for Graph (WFG) - Deadlock Detection
    ------------------------------------------
    - Derived from the Resource Allocation Graph (RAG).
    - Only processes are nodes; an edge Pi → Pj means
      "Pi is waiting for a resource currently held by Pj".
    - If a cycle exists in this graph → Deadlock.
*/

#include <bits/stdc++.h>
using namespace std;

class WaitForGraph
{
    int processes;
    vector<vector<int>> adj; // adjacency list (process → process)

    // DFS-based cycle detection using a recursion stack
    bool dfs(int node, vector<bool> &visited, vector<bool> &inStack)
    {
        visited[node] = true;
        inStack[node] = true;

        for (int neighbour : adj[node])
        {
            if (!visited[neighbour])
            {
                if (dfs(neighbour, visited, inStack))
                    return true; // cycle found
            }
            else if (inStack[neighbour])
            {
                return true; // back-edge → cycle
            }
        }
        inStack[node] = false;
        return false;
    }

public:
    WaitForGraph(int p) : processes(p), adj(p) {}

    // Add edge: Pi is waiting for Pj
    void addEdge(int pi, int pj)
    {
        adj[pi].push_back(pj);
        cout << "  Added edge : P" << pi << " -> P" << pj << endl;
    }

    // Check for deadlock (cycle in the graph)
    bool detectDeadlock()
    {
        vector<bool> visited(processes, false);
        vector<bool> inStack(processes, false);

        for (int i = 0; i < processes; i++)
        {
            if (!visited[i])
            {
                if (dfs(i, visited, inStack))
                    return true;
            }
        }
        return false;
    }

    // Print the adjacency list
    void printGraph()
    {
        cout << "\n--- Wait-for Graph ---\n";
        for (int i = 0; i < processes; i++)
        {
            if (adj[i].empty())
                continue;
            cout << "  P" << i << " -> ";
            for (int nb : adj[i])
                cout << "P" << nb << "  ";
            cout << endl;
        }
    }
};

// ── Main ────────────────────────────────────────────────────────
int main()
{
    int P;
    cout << "Enter number of Processes : ";
    cin >> P;

    WaitForGraph graph(P);

    int edges;
    cout << "Enter number of edges     : ";
    cin >> edges;

    cout << "\nFor each edge enter two process ids (Pi Pj)\n"
         << "meaning Pi is waiting for Pj:\n\n";

    for (int i = 0; i < edges; i++)
    {
        int pi, pj;
        cout << "Edge " << i + 1 << " (Pi Pj): ";
        cin >> pi >> pj;
        graph.addEdge(pi, pj);
    }

    graph.printGraph();

    cout << "\n--- Deadlock Detection ---\n";
    if (graph.detectDeadlock())
        cout << "  ** DEADLOCK DETECTED (cycle exists) **\n";
    else
        cout << "  No deadlock (no cycle found).\n";

    return 0;
}
