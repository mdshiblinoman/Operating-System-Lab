/*
Question 5 — SJF Non-Preemptive
Implement Shortest Job First (Non-Preemptive) scheduling algorithm.
Display:
    Gantt Chart
    Waiting Time
    Turnaround Time
*/

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, at, bt, ct, tat, wt;
    bool done = false;
};

struct GanttBlock
{
    string label;
    int start;
    int end;
};

void inputProcesses(vector<Process> &p)
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    p.resize(n);

    for (int i = 0; i < n; i++)
        p[i].pid = i + 1;

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
    }
}

int pickNextProcess(vector<Process> &p, int time)
{
    int idx = -1;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].done || p[i].at > time)
            continue;

        if (idx == -1 ||
            p[i].bt < p[idx].bt ||
            (p[i].bt == p[idx].bt && p[i].at < p[idx].at) ||
            (p[i].bt == p[idx].bt && p[i].at == p[idx].at && p[i].pid < p[idx].pid))
        {
            idx = i;
        }
    }

    return idx;
}

int nextArrivalTime(vector<Process> &p)
{
    int minArrival = -1;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].done)
        {
            continue;
        }

        if (minArrival == -1 || p[i].at < minArrival)
        {
            minArrival = p[i].at;
        }
    }

    return minArrival;
}

void runSJF(vector<Process> &p, vector<GanttBlock> &gantt, double &avgWT, double &avgTAT)
{
    int time = 0;
    int completed = 0;
    int totalWT = 0;
    int totalTAT = 0;
    int n = p.size();

    while (completed < n)
    {
        int idx = pickNextProcess(p, time);

        if (idx == -1)
        {
            int next = nextArrivalTime(p);
            gantt.push_back({"Idle", time, next});
            time = next;
            continue;
        }

        p[idx].ct = time + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;

        gantt.push_back({"P" + to_string(p[idx].pid), time, p[idx].ct});

        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;
        time = p[idx].ct;
        completed++;
    }

    avgWT = (double)(totalWT) / n;
    avgTAT = (double)(totalTAT) / n;
}

void printGanttChart(vector<GanttBlock> &gantt)
{
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < gantt.size(); i++)
    {
        cout << "| " << gantt[i].label << " ";
    }
    cout << "|\n";

    if (!gantt.empty())
    {
        cout << gantt[0].start;
        for (int i = 0; i < gantt.size(); i++)
        {
            cout << setw(6) << gantt[i].end;
        }
        cout << "\n";
    }
}

void printResults(vector<Process> &p, double avgWT, double avgTAT)
{
    cout << "\n+-----+------+------+------+------+------+\n";
    cout << "| PID |  AT  |  BT  |  CT  | TAT  |  WT  |\n";
    cout << "+-----+------+------+------+------+------+\n";

    for (int i = 0; i < p.size(); i++)
    {
        cout << "| " << setw(3) << p[i].pid << " | "
             << setw(4) << p[i].at << " | "
             << setw(4) << p[i].bt << " | "
             << setw(4) << p[i].ct << " | "
             << setw(4) << p[i].tat << " | "
             << setw(4) << p[i].wt << " |\n";
    }

    cout << "+-----+------+------+------+------+------+\n";
    cout << fixed << setprecision(2);
    cout << "Average WT = " << avgWT << "\n";
    cout << "Average TAT = " << avgTAT << "\n";
}

int main()
{
    vector<Process> p;
    vector<GanttBlock> gantt;
    double avgWT = 0.0;
    double avgTAT = 0.0;

    inputProcesses(p);
    runSJF(p, gantt, avgWT, avgTAT);
    printGanttChart(gantt);
    printResults(p, avgWT, avgTAT);

    return 0;
}
