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

int nextArrivalTime(const vector<Process> &p, int currentTime)
{
    int nextArrival = INT_MAX;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (p[i].rt > 0 && p[i].at > currentTime)
        {
            nextArrival = min(nextArrival, p[i].at);
        }
    }

    return nextArrival == INT_MAX ? -1 : nextArrival;
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

void addGanttBlock(vector<GanttBlock> &gantt, const string &label, int start, int end)
{
    if (start < end)
    {
        gantt.push_back({label, start, end});
    }
}

void calculateSRTF(vector<Process> &p, vector<GanttBlock> &gantt)
{
    int done = 0;
    int t = 0;
    int n = static_cast<int>(p.size());
    string currentLabel = "";
    int segmentStart = 0;

    while (done < n)
    {
        int idx = findShortestRemainingProcess(p, t);

        if (idx == -1)
        {
            int nextArrival = nextArrivalTime(p, t);

            if (nextArrival == -1)
            {
                break;
            }

            if (currentLabel != "Idle")
            {
                addGanttBlock(gantt, currentLabel, segmentStart, t);
                currentLabel = "Idle";
                segmentStart = t;
            }

            t = nextArrival;

            if (currentLabel != "Idle")
            {
                currentLabel = "Idle";
                segmentStart = t;
            }

            continue;
        }

        string label = "P" + to_string(p[idx].pid);

        if (currentLabel != label)
        {
            addGanttBlock(gantt, currentLabel, segmentStart, t);
            currentLabel = label;
            segmentStart = t;
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

    addGanttBlock(gantt, currentLabel, segmentStart, t);
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
    vector<GanttBlock> gantt;

    inputProcesses(p);
    calculateSRTF(p, gantt);
    printGanttChart(gantt);
    printResults(p);

    return 0;
}
