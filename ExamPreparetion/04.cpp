/*
Question 4 — FCFS Scheduling
Write a program to implement First Come First Serve (FCFS) CPU scheduling algorithm
and calculate:
    Waiting Time
    Turnaround Time
    Average Waiting Time
    Average Turnaround Time
*/

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid, at, bt, ct, tat, wt;
};

struct GanttBlock
{
    string label;
    int start, end;
};

void inputProcesses(vector<Process> &p)
{
    for (int i = 0; i < p.size(); i++)
        p[i].pid = i + 1;

    cout << "Enter arrival times for all processes:\n";
    for (int i = 0; i < p.size(); i++)
    {
        cout << "AT of P" << p[i].pid << ": ";
        cin >> p[i].at;
    }

    cout << "Enter burst times for all processes:\n";
    for (int i = 0; i < p.size(); i++)
    {
        cout << "BT of P" << p[i].pid << ": ";
        cin >> p[i].bt;
    }
}

void sortByArrivalTime(vector<Process> &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = i + 1; j < p.size(); j++)
        {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].pid > p[j].pid))
            {
                swap(p[i], p[j]);
            }
        }
    }
}

void calculateFCFS(vector<Process> &p, vector<GanttBlock> &gantt, double &avgWT, double &avgTAT)
{
    int time = 0;
    int totalWT = 0;
    int totalTAT = 0;

    for (int i = 0; i < p.size(); i++)
    {
        if (time < p[i].at)
        {
            gantt.push_back({"Idle", time, p[i].at});
            time = p[i].at;
        }

        int start = time;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        gantt.push_back({"P" + to_string(p[i].pid), start, p[i].ct});

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        time = p[i].ct;
    }

    avgWT = static_cast<double>(totalWT) / p.size();
    avgTAT = static_cast<double>(totalTAT) / p.size();
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
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    vector<GanttBlock> gantt;
    double avgWT = 0.0;
    double avgTAT = 0.0;

    inputProcesses(p);
    sortByArrivalTime(p);
    calculateFCFS(p, gantt, avgWT, avgTAT);
    printGanttChart(gantt);
    printResults(p, avgWT, avgTAT);

    return 0;
}