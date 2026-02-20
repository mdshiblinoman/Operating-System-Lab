/*
    Banker's Algorithm - Deadlock Avoidance
    ----------------------------------------
    - Each process declares max resources it may need.
    - The system only grants a request if the resulting
      state is SAFE (i.e. there exists a safe sequence).
    - Uses Available, Max, Allocation, and Need matrices.
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int P, R;
    cout << "Enter number of Processes  : ";
    cin >> P;
    cout << "Enter number of Resources  : ";
    cin >> R;

    // ── Input matrices ──────────────────────────────────────
    vector<vector<int>> allocation(P, vector<int>(R));
    vector<vector<int>> max_need(P, vector<int>(R));
    vector<int> available(R);

    cout << "\nEnter Allocation Matrix (" << P << "x" << R << "):\n";
    for (int i = 0; i < P; i++)
    {
        cout << "  P" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];
    }

    cout << "\nEnter Max Matrix (" << P << "x" << R << "):\n";
    for (int i = 0; i < P; i++)
    {
        cout << "  P" << i << ": ";
        for (int j = 0; j < R; j++)
            cin >> max_need[i][j];
    }

    cout << "\nEnter Available Resources (" << R << " values): ";
    for (int j = 0; j < R; j++)
        cin >> available[j];

    // ── Calculate Need matrix: Need = Max - Allocation ──────
    vector<vector<int>> need(P, vector<int>(R));
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max_need[i][j] - allocation[i][j];

    // Print Need matrix
    cout << "\n--- Need Matrix (Max - Allocation) ---\n";
    for (int i = 0; i < P; i++)
    {
        cout << "  P" << i << ": ";
        for (int j = 0; j < R; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    // ── Safety Algorithm ────────────────────────────────────
    vector<bool> finished(P, false);
    vector<int> safeSequence;
    vector<int> work(available); // work = copy of available

    int count = 0;
    while (count < P)
    {
        bool found = false;

        for (int i = 0; i < P; i++)
        {
            if (finished[i])
                continue;

            // Check if Need[i] <= Work
            bool canRun = true;
            for (int j = 0; j < R; j++)
            {
                if (need[i][j] > work[j])
                {
                    canRun = false;
                    break;
                }
            }

            if (canRun)
            {
                // Process i can finish → release its resources
                for (int j = 0; j < R; j++)
                    work[j] += allocation[i][j];

                safeSequence.push_back(i);
                finished[i] = true;
                found = true;
                count++;
            }
        }

        if (!found)
            break; // no process could run → unsafe
    }

    // ── Result ──────────────────────────────────────────────
    cout << "\n--- Banker's Algorithm Result ---\n";
    if (count == P)
    {
        cout << "  System is in a SAFE state.\n";
        cout << "  Safe Sequence: ";
        for (int i = 0; i < P; i++)
        {
            cout << "P" << safeSequence[i];
            if (i < P - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "  System is in an UNSAFE state (deadlock possible)!\n";
    }

    return 0;
}
