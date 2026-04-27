/*
Question 9 — Banker’s Algorithm
Write a program to implement the Banker’s Algorithm for deadlock avoidance.
The program should:
    take Allocation, Maximum, and Available matrices as input
    determine whether the system is in a safe state
    display the safe sequence
*/

#include <bits/stdc++.h>
using namespace std;

void inputMatrix(vector<vector<int>> &mat, int r, int c, const string &name)
{
    cout << "Enter " << name << " matrix (" << r << " x " << c << "):\n";
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> mat[i][j];
        }
    }
}

bool findSafeSequence(const vector<vector<int>> &alloc, const vector<vector<int>> &mx,
                      const vector<int> &avail, vector<int> &safe_seq)
{
    int n = static_cast<int>(alloc.size());
    int m = static_cast<int>(avail.size());

    vector<vector<int>> need(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = mx[i][j] - alloc[i][j];
        }
    }

    vector<int> work = avail;
    vector<bool> done(n, false);
    safe_seq.clear();

    for (int k = 0; k < n; k++)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (done[i])
            {
                continue;
            }

            bool can_run = true;
            for (int j = 0; j < m; j++)
            {
                if (need[i][j] > work[j])
                {
                    can_run = false;
                    break;
                }
            }

            if (can_run)
            {
                for (int j = 0; j < m; j++)
                {
                    work[j] += alloc[i][j];
                }

                done[i] = true;
                safe_seq.push_back(i);
                found = true;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> mx(n, vector<int>(m));
    vector<int> avail(m);
    vector<int> safe_seq;

    inputMatrix(alloc, n, m, "Allocation");
    inputMatrix(mx, n, m, "Maximum");

    cout << "Enter Available vector (" << m << " values):\n";
    for (int i = 0; i < m; i++)
    {
        cin >> avail[i];
    }

    bool safe = findSafeSequence(alloc, mx, avail, safe_seq);

    if (safe)
    {
        cout << "\nSystem is in SAFE state.\n";
        cout << "Safe sequence: ";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << safe_seq[i];
            if (i != n - 1)
            {
                cout << " -> ";
            }
        }
        cout << "\n";
    }
    else
    {
        cout << "\nSystem is NOT in safe state (unsafe).\n";
    }

    return 0;
}
