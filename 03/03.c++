// To Write a C program for implementation of Round Robin Scheduling Algorithm.

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void roundRobin(vector<Process> &p, int quantum)
{
    int n = p.size();
    queue<int> ready;
    vector<bool> inQueue(n, false);
    int currentTime = 0, completed = 0;

    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process &a, Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    // Initialize remaining time
    for (int i = 0; i < n; i++)
        p[i].remainingTime = p[i].burstTime;

    // Add processes arriving at time 0
    for (int i = 0; i < n; i++)
    {
        if (p[i].arrivalTime <= currentTime)
        {
            ready.push(i);
            inQueue[i] = true;
        }
    }

    cout << "\n--- Gantt Chart ---\n";

    while (completed < n)
    {
        if (ready.empty())
        {
            for (int i = 0; i < n; i++)
            {
                if (!inQueue[i] && p[i].remainingTime > 0)
                {
                    currentTime = p[i].arrivalTime;
                    ready.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
            continue;
        }

        int idx = ready.front();
        ready.pop();

        int execTime = min(quantum, p[idx].remainingTime);
        cout << "| P" << p[idx].id << " [" << currentTime << "-" << currentTime + execTime << "] ";

        currentTime += execTime;
        p[idx].remainingTime -= execTime;

        // Add newly arrived processes
        for (int i = 0; i < n; i++)
        {
            if (!inQueue[i] && p[i].arrivalTime <= currentTime && p[i].remainingTime > 0)
            {
                ready.push(i);
                inQueue[i] = true;
            }
        }

        if (p[idx].remainingTime > 0)
        {
            ready.push(idx);
        }
        else
        {
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            completed++;
        }
    }
    cout << "|\n";
}

void printResults(vector<Process> &p)
{
    sort(p.begin(), p.end(), [](Process &a, Process &b)
         { return a.id < b.id; });

    cout << "\n--- Results ---\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    float avgTAT = 0, avgWT = 0;
    for (auto &proc : p)
    {
        cout << "P" << proc.id << "\t" << proc.arrivalTime << "\t" << proc.burstTime << "\t"
             << proc.completionTime << "\t" << proc.turnaroundTime << "\t" << proc.waitingTime << "\n";
        avgTAT += proc.turnaroundTime;
        avgWT += proc.waitingTime;
    }

    cout << "\nAvg Turnaround Time: " << fixed << setprecision(2) << avgTAT / p.size();
    cout << "\nAvg Waiting Time: " << fixed << setprecision(2) << avgWT / p.size() << "\n";
}

int main()
{
    int n, quantum;

    cout << "=== Round Robin Scheduling ===\n";
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "P" << i + 1 << " Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "P" << i + 1 << " Burst Time: ";
        cin >> processes[i].burstTime;
    }

    roundRobin(processes, quantum);
    printResults(processes);

    return 0;
}
