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
    {
        p[i].pid = i + 1;
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
    }
}

int pickNextProcess(const vector<Process> &p, int time)
{
    int idx = -1;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (p[i].done || p[i].at > time)
        {
            continue;
        }

        if (idx == -1)
        {
            idx = static_cast<int>(i);
        }
        else if (p[i].bt < p[idx].bt)
        {
            idx = static_cast<int>(i);
        }
        else if (p[i].bt == p[idx].bt && p[i].at < p[idx].at)
        {
            idx = static_cast<int>(i);
        }
        else if (p[i].bt == p[idx].bt && p[i].at == p[idx].at && p[i].pid < p[idx].pid)
        {
            idx = static_cast<int>(i);
        }
    }

    return idx;
}

int nextArrivalTime(const vector<Process> &p)
{
    int minArrival = -1;

    for (size_t i = 0; i < p.size(); i++)
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
    int n = static_cast<int>(p.size());

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

        int start = time;
        int end = start + p[idx].bt;

        p[idx].ct = end;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;

        gantt.push_back({"P" + to_string(p[idx].pid), start, end});

        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;
        time = end;
        completed++;
    }

    avgWT = static_cast<double>(totalWT) / n;
    avgTAT = static_cast<double>(totalTAT) / n;
}

void printGanttChart(const vector<GanttBlock> &gantt)
{
    cout << "\nGantt Chart:\n";

    for (size_t i = 0; i < gantt.size(); i++)
    {
        cout << "| " << gantt[i].label << " ";
    }
    cout << "|\n";

    if (!gantt.empty())
    {
        cout << gantt[0].start;
        for (size_t i = 0; i < gantt.size(); i++)
        {
            cout << setw(6) << gantt[i].end;
        }
        cout << "\n";
    }
}

void printResults(const vector<Process> &p, double avgWT, double avgTAT)
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
    cout << fixed << setprecision(2);
    cout << "Average WT = " << avgWT << "\n";
    cout << "Average TAT = " << avgTAT << "\n";
}

void printCalculationDetails(const vector<Process> &p)
{
    cout << "\nCalculation Details:\n";
    for (size_t i = 0; i < p.size(); i++)
    {
        cout << "P" << p[i].pid
             << ": TAT = CT - AT = " << p[i].ct << " - " << p[i].at
             << " = " << p[i].tat
             << ", WT = TAT - BT = " << p[i].tat << " - " << p[i].bt
             << " = " << p[i].wt << "\n";
    }
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
    printCalculationDetails(p);
    printResults(p, avgWT, avgTAT);

    return 0;
}