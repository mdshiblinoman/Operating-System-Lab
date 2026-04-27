#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, at, bt, rt, ct, tat, wt, pr;
    bool done;
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
        p[i].done = false;
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

    cout << "Enter all priorities (smaller number = higher priority) for P1 to P" << n << ":\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Priority of P" << p[i].pid << ": ";
        cin >> p[i].pr;
    }
}

int pickNextProcess(const vector<Process> &p, int t)
{
    int idx = -1;

    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].at <= t && p[i].rt > 0)
        {
            if (idx == -1 || (p[i].pr < p[idx].pr) || (p[i].pr == p[idx].pr && p[i].at < p[idx].at) ||
                (p[i].pr == p[idx].pr && p[i].at == p[idx].at && p[i].pid < p[idx].pid))
            {
                idx = i;
            }
        }
    }

    return idx;
}

int nextArrivalTime(const vector<Process> &p)
{
    int next_at = -1;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (p[i].done)
        {
            continue;
        }

        if (next_at == -1 || p[i].at < next_at)
        {
            next_at = p[i].at;
        }
    }

    return next_at;
}

void runNonPreemptivePriority(vector<Process> &p, vector<GanttBlock> &gantt)
{
    int n = static_cast<int>(p.size());
    int done_count = 0;
    int t = 0;

    while (done_count < n)
    {
        int idx = pickNextProcess(p, t);

        if (idx == -1)
        {
            int next_at = nextArrivalTime(p);
            if (next_at > t)
            {
                gantt.push_back({"Idle", t, next_at});
                t = next_at;
            }
            continue;
        }

        int start = t;
        t += p[idx].bt;
        p[idx].ct = t;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;
        done_count++;

        gantt.push_back({"P" + to_string(p[idx].pid), start, t});
    }
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
    vector<GanttBlock> gantt;

    inputProcesses(p);
    runNonPreemptivePriority(p, gantt);
    printGanttChart(gantt);
    printResults(p);

    return 0;
}
