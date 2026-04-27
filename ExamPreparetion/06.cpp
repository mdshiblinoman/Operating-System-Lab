/*
Question 6 — SJF Preemptive (SRTF)
Write a program for Shortest Remaining Time First (SRTF) scheduling.
Calculate:
    Completion Time
    Waiting Time
    Turnaround Time
*/

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, at, bt, rt, ct, tat, wt;
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

int findShortestRemainingProcess(const vector<Process> &p, int t)
{
    int idx = -1;
    int min_rt = INT_MAX;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (p[i].at <= t && p[i].rt > 0)
        {
            if (p[i].rt < min_rt)
            {
                min_rt = p[i].rt;
                idx = i;
            }
            else if (p[i].rt == min_rt && idx != -1 && p[i].at < p[idx].at)
            {
                idx = i;
            }
        }
    }

    return idx;
}

void calculateSRTF(vector<Process> &p)
{
    int done = 0;
    int t = 0;
    int n = static_cast<int>(p.size());

    while (done < n)
    {
        int idx = findShortestRemainingProcess(p, t);

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
    }

    cout << "+-----+------+------+------+------+------+\n";
}

int main()
{
    vector<Process> p;

    inputProcesses(p);
    calculateSRTF(p);
    printResults(p);

    return 0;
}
