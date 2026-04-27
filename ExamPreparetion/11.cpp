/*
Question 10 — Deadlock Detection
Write a program to detect deadlock in a system using:
    Allocation matrix
    Request matrix
    Available resources
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

void inputVector(vector<int> &v, const string &name)
{
    cout << "Enter " << name << " vector (" << v.size() << " values):\n";
    for (int i = 0; i < v.size(); i++)
    {
        cin >> v[i];
    }
}

void detectDeadlock(const vector<vector<int>> &alloc, const vector<vector<int>> &req,
                    const vector<int> &avail)
{
    int n = alloc.size();
    int m = avail.size();

    vector<int> work = avail;
    vector<bool> finish(n, false);

    for (int i = 0; i < n; i++)
    {
        bool no_alloc = true;
        for (int j = 0; j < m; j++)
        {
            if (alloc[i][j] != 0)
            {
                no_alloc = false;
                break;
            }
        }
        if (no_alloc)
        {
            finish[i] = true;
        }
    }

    while (true)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (finish[i])
            {
                continue;
            }

            bool can_run = true;
            for (int j = 0; j < m; j++)
            {
                if (req[i][j] > work[j])
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
                finish[i] = true;
                found = true;
            }
        }

        if (!found)
        {
            break;
        }
    }

    vector<int> deadlocked;
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            deadlocked.push_back(i);
        }
    }

    if (deadlocked.empty())
    {
        cout << "\nNo deadlock detected.\n";
    }
    else
    {
        cout << "\nDeadlock detected in processes: ";
        for (size_t i = 0; i < deadlocked.size(); i++)
        {
            cout << "P" << deadlocked[i];
            if (i != deadlocked.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "\n";
    }
}

int main()
{
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> req(n, vector<int>(m));
    vector<int> avail(m);

    inputMatrix(alloc, n, m, "Allocation");
    inputMatrix(req, n, m, "Request");
    inputVector(avail, "Available");

    detectDeadlock(alloc, req, avail);

    return 0;
}
