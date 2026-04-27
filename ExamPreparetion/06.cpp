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

int findShortestRemainingProcess(vector<Process> &p, int t)
{
    int idx = -1;
    int min_rt = INT_MAX;

    for (int i = 0; i < (p.size()); i++)
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

void calculateSRTF(vector<Process> &p, vector<GanttBlock> &gantt)
{
    int done = 0;
    int t = 0;
    int n = static_cast<int>(p.size());

    while (done < n)
    {
        int idx = findShortestRemainingProcess(p, t);

        if (idx == -1)
        {
            if (gantt.empty() || gantt.back().label != "Idle")
            {
                gantt.push_back({"Idle", t, t + 1});
            }
            else
            {
                gantt.back().end++;
            }

            t++;
            continue;
        }

        string label = "P" + to_string(p[idx].pid);

        if (gantt.empty() || gantt.back().label != label)
        {
            gantt.push_back({label, t, t + 1});
        }
        else
        {
            gantt.back().end++;
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

void printGanttChart(vector<GanttBlock> &gantt)
{
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < static_cast<int>(gantt.size()); i++)
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

void printResults(const vector<Process> &p)
{
    double totalTAT = 0;
    double totalWT = 0;

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

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "+-----+------+------+------+------+------+\n";

    if (!p.empty())
    {
        cout << fixed << setprecision(2);
        cout << "Average Turnaround Time: " << (totalTAT / p.size()) << "\n";
        cout << "Average Waiting Time: " << (totalWT / p.size()) << "\n";
    }
}

int main()
{
    vector<Process> p;
    vector<GanttBlock> gantt;

    inputProcesses(p);
    calculateSRTF(p, gantt);
    printGanttChart(gantt);
    printResults(p);

    return 0;
}
