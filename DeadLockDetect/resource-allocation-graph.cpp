/*
    Resource Allocation Graph (RAG) - Deadlock Detection
    ----------------------------------------------------
    - Processes request and hold resources.
    - We build a wait-for / allocation graph and check for cycles.
    - If a cycle exists → Deadlock detected.
*/

#include <bits/stdc++.h>
using namespace std;

// ── Graph with cycle detection (DFS) ────────────────────────────
class RAG
{
    int processes, resources;

    // adjacency list  (node → list of nodes it points to)
    // Nodes 0..P-1  = processes,  P..P+R-1 = resources
    map<int, vector<int>> adj;

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
    RAG(int p, int r) : processes(p), resources(r) {}

    // Process Pi requests Resource Rj   (Pi  → Rj)
    void requestEdge(int pi, int rj)
    {
        int from = pi;           // process node
        int to = processes + rj; // resource node
        adj[from].push_back(to);
        cout << "  Added request edge : P" << pi << " -> R" << rj << endl;
    }

    // Resource Rj is assigned to Process Pi   (Rj → Pi)
    void assignEdge(int rj, int pi)
    {
        int from = processes + rj; // resource node
        int to = pi;               // process node
        adj[from].push_back(to);
        cout << "  Added assign  edge : R" << rj << " -> P" << pi << endl;
    }

    // Check for deadlock (cycle in the graph)
    bool detectDeadlock()
    {
        int totalNodes = processes + resources;
        vector<bool> visited(totalNodes, false);
        vector<bool> inStack(totalNodes, false);

        for (int i = 0; i < totalNodes; i++)
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
        cout << "\n--- Resource Allocation Graph ---\n";
        for (auto &[node, neighbours] : adj)
        {
            string label = (node < processes)
                               ? "P" + to_string(node)
                               : "R" + to_string(node - processes);
            cout << "  " << label << " -> ";
            for (int nb : neighbours)
            {
                string nbLabel = (nb < processes)
                                     ? "P" + to_string(nb)
                                     : "R" + to_string(nb - processes);
                cout << nbLabel << "  ";
            }
            cout << endl;
        }
    }
};

// ── Main ────────────────────────────────────────────────────────
int main()
{
    int P, R;
    cout << "Enter number of Processes  : ";
    cin >> P;
    cout << "Enter number of Resources  : ";
    cin >> R;

    RAG graph(P, R);

    int edges;
    cout << "\nEnter number of edges      : ";
    cin >> edges;

    cout << "\nFor each edge enter:\n"
         << "  type (1 = request,  2 = assignment)\n"
         << "  process-id   resource-id\n\n";

    for (int i = 0; i < edges; i++)
    {
        int type, pi, rj;
        cout << "Edge " << i + 1 << " (type process resource): ";
        cin >> type >> pi >> rj;

        if (type == 1)
            graph.requestEdge(pi, rj); // Pi → Rj
        else
            graph.assignEdge(rj, pi); // Rj → Pi
    }

    graph.printGraph();

    cout << "\n--- Deadlock Detection ---\n";
    if (graph.detectDeadlock())
        cout << "  ** DEADLOCK DETECTED (cycle exists) **\n";
    else
        cout << "  No deadlock (no cycle found).\n";

    return 0;
}
