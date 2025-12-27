// To Write a C program for implementation of Priority Scheduling Algorithm.

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid;      // Process ID
    int bt;       // Burst Time
    int priority; // Priority
    int arival;   // Arrival Time
};

bool comparePriority(Process a, Process b)
{
    return a.priority > b.priority; // Higher priority first
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cout << "Enter burst time, priority and arrival time for process " << processes[i].pid << ": ";
        cin >> processes[i].bt >> processes[i].priority >> processes[i].arival;
    }

    // Sort processes based on priority
    sort(processes.begin(), processes.end(), comparePriority);

    vector<int> wt(n), tat(n);
    int total_wt = 0, total_tat = 0;

    // Calculate waiting time and turnaround time
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            wt[i] = 0;
        }
        else
        {
            wt[i] = wt[i - 1] + processes[i - 1].bt;
        }
        tat[i] = wt[i] + processes[i].bt;

        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Create arrays to store results by original process ID
    vector<int> wt_result(n), tat_result(n), bt_result(n), priority_result(n), arrival_result(n);
    for (int i = 0; i < n; i++)
    {
        int pid = processes[i].pid - 1; // Convert to 0-indexed
        wt_result[pid] = wt[i];
        tat_result[pid] = tat[i];
        bt_result[pid] = processes[i].bt;
        priority_result[pid] = processes[i].priority;
        arrival_result[pid] = processes[i].arival;
    }

    cout << "\nProcess\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << "  " << i + 1 << "\t" << bt_result[i] << "\t\t" << priority_result[i] << "\t\t"
             << arrival_result[i] << "\t\t" << wt_result[i] << "\t\t" << tat_result[i] << "\n";
    }

    cout << "\nAverage Waiting Time: " << (float)total_wt / n;
    cout << "\nAverage Turnaround Time: " << (float)total_tat / n << "\n";

    return 0;
}