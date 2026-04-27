/*
Question 8 — Priority Scheduling
Write a program to implement:
Preemptive priority scheduling
Calculate:
    Completion Time
    Waiting Time
    Turnaround Time
*/

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, at, bt, rt, ct, tat, wt, pr;
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
        p[i].pr = 0;
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

    cout << "Enter all priorities (smaller number = higher priority) for P1 to P" << n << ":\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Priority of P" << p[i].pid << ": ";
        cin >> p[i].pr;
    }
}

int pickProcess(const vector<Process> &p, int t)
{
    int idx = -1;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (p[i].at <= t && p[i].rt > 0)
        {
            if (idx == -1)
            {
                idx = i;
            }
            else if (p[i].pr < p[idx].pr)
            {
                idx = i;
            }
            else if (p[i].pr == p[idx].pr && p[i].at < p[idx].at)
            {
                idx = i;
            }
            else if (p[i].pr == p[idx].pr && p[i].at == p[idx].at && p[i].pid < p[idx].pid)
            {
                idx = i;
            }
        }
    }

    return idx;
}

void runPreemptivePriority(vector<Process> &p)
{
    int n = static_cast<int>(p.size());
    int done = 0;
    int t = 0;

    while (done < n)
    {
        int idx = pickProcess(p, t);

        if (idx == -1)
        {
            t++;
            continue;
        }

        p[idx].rt--;
        t++;

        if (p[idx].rt == 0)
        {
            done++;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
}

void printResults(const vector<Process> &p)
{
    double total_wt = 0;
    double total_tat = 0;

    cout << "\n+-----+------+------+------+------+------+------+\n";
    cout << "| PID |  AT  |  BT  | PRI  |  CT  | TAT  |  WT  |\n";
    cout << "+-----+------+------+------+------+------+------+\n";

    for (size_t i = 0; i < p.size(); i++)
    {
        cout << "| " << setw(3) << p[i].pid << " | "
             << setw(4) << p[i].at << " | "
             << setw(4) << p[i].bt << " | "
             << setw(4) << p[i].pr << " | "
             << setw(4) << p[i].ct << " | "
             << setw(4) << p[i].tat << " | "
             << setw(4) << p[i].wt << " |\n";

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "+-----+------+------+------+------+------+------+\n";
    cout << fixed << setprecision(2);
    cout << "Average WT = " << total_wt / p.size() << "\n";
    cout << "Average TAT = " << total_tat / p.size() << "\n";
}

int main()
{
    vector<Process> p;

    inputProcesses(p);
    runPreemptivePriority(p);
    printResults(p);

    return 0;
}
