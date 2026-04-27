/*
Question 7 — Round Robin Scheduling
Implement Round Robin Scheduling using a user-defined time quantum.
Display:
    Gantt Chart
    Waiting Time
    Turnaround Time
*/

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, at, bt, rt, ct, tat, wt;
};

struct GanttBlock
{
    string label;
    int start, end;
};

void inputProcesses(vector<Process> &p)
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    p.resize(n);

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }

    cout << "Enter all arrival times (AT) in order P1 to P" << n << ":\n";
    for (int i = 0; i < n; i++)
    {
        cout << "AT of P" << p[i].pid << ": ";
        cin >> p[i].at;
    }

    cout << "Enter all burst times (BT) in order P1 to P" << n << ":\n";
    for (int i = 0; i < n; i++)
    {
        cout << "BT of P" << p[i].pid << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
    }
}

void runRoundRobin(vector<Process> &p, int tq, vector<GanttBlock> &g)
{
    int n = p.size();
    int done = 0;
    int t = 0;
    queue<int> q;
    vector<bool> in_q(n, false);

    while (done < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (!in_q[i] && p[i].rt > 0 && p[i].at <= t)
            {
                q.push(i);
                in_q[i] = true;
            }
        }

        if (q.empty())
        {
            int next_at = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (p[i].rt > 0)
                {
                    next_at = min(next_at, p[i].at);
                }
            }

            if (next_at == INT_MAX)
            {
                break;
            }

            if (t < next_at)
            {
                g.push_back({"Idle", t, next_at});
                t = next_at;
            }
            continue;
        }

        int idx = q.front();
        q.pop();
        in_q[idx] = false;

        int start = t;
        int run = min(tq, p[idx].rt);
        t += run;
        p[idx].rt -= run;
        g.push_back({"P" + to_string(p[idx].pid), start, t});

        for (int i = 0; i < n; i++)
        {
            if (i != idx && !in_q[i] && p[i].rt > 0 && p[i].at <= t)
            {
                q.push(i);
                in_q[i] = true;
            }
        }

        if (p[idx].rt > 0)
        {
            q.push(idx);
            in_q[idx] = true;
        }
        else
        {
            done++;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
}

void printGanttChart(const vector<GanttBlock> &g)
{
    cout << "\nGantt Chart:\n";

    for (size_t i = 0; i < g.size(); i++)
    {
        cout << "| " << g[i].label << " ";
    }
    cout << "|\n";

    if (!g.empty())
    {
        cout << g[0].start;
        for (size_t i = 0; i < g.size(); i++)
        {
            cout << setw(6) << g[i].end;
        }
        cout << "\n";
    }
}

void printResults(const vector<Process> &p)
{
    double total_wt = 0;
    double total_tat = 0;

    cout << "\n+-----+------+------+------+------+------+\n";
    cout << "| PID |  AT  |  BT  |  CT  | TAT  |  WT  |\n";
    cout << "+-----+------+------+------+------+------+\n";

    for (size_t i = 0; i < p.size(); i++)
    {
        cout << "| " << setw(3) << p[i].pid << " | "
             << setw(4) << p[i].at << " | "
             << setw(4) << p[i].bt << " | "
             << setw(4) << p[i].ct << " | "
             << setw(4) << p[i].tat << " | "
             << setw(4) << p[i].wt << " |\n";

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "+-----+------+------+------+------+------+\n";
    cout << fixed << setprecision(2);
    cout << "Average WT = " << total_wt / p.size() << "\n";
    cout << "Average TAT = " << total_tat / p.size() << "\n";
}

int main()
{
    vector<Process> p;
    vector<GanttBlock> g;
    int tq;

    inputProcesses(p);

    cout << "Enter time quantum: ";
    cin >> tq;

    runRoundRobin(p, tq, g);
    printGanttChart(g);
    printResults(p);

    return 0;
}
