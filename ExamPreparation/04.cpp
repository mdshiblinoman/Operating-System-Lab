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
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void inputProcesses(vector<Process> &processes)
{
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    processes.resize(n);

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
    }

    cout << "Enter arrival times for all processes:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Arrival Time for Process " << processes[i].pid << ": ";
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter burst times for all processes:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Burst Time for Process " << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
    }
}

void sortByArrivalTime(vector<Process> &processes)
{
    for (size_t i = 0; i < processes.size(); i++)
    {
        for (size_t j = 0; j + 1 < processes.size() - i; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
}

void calculateFCFS(vector<Process> &processes, float &averageWaitingTime, float &averageTurnaroundTime)
{
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (size_t i = 0; i < processes.size(); i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    averageWaitingTime = static_cast<float>(totalWaitingTime) / processes.size();
    averageTurnaroundTime = static_cast<float>(totalTurnaroundTime) / processes.size();
}

void displayResults(const vector<Process> &processes, float averageWaitingTime, float averageTurnaroundTime)
{
    cout << "\n+-----+------+------+------+------+------+\n";
    cout << "| PID |  AT  |  BT  |  CT  | TAT  |  WT  |\n";
    cout << "+-----+------+------+------+------+------+\n";

    for (size_t i = 0; i < processes.size(); i++)
    {
        cout << "| " << setw(3) << processes[i].pid << " | "
             << setw(4) << processes[i].arrivalTime << " | "
             << setw(4) << processes[i].burstTime << " | "
             << setw(4) << processes[i].completionTime << " | "
             << setw(4) << processes[i].turnaroundTime << " | "
             << setw(4) << processes[i].waitingTime << " |\n";
    }

    cout << "+-----+------+------+------+------+------+\n";
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << averageWaitingTime << '\n';
    cout << "Average Turnaround Time: " << averageTurnaroundTime << '\n';
}

int main()
{
    vector<Process> processes;
    float averageWaitingTime = 0.0f;
    float averageTurnaroundTime = 0.0f;

    inputProcesses(processes);
    sortByArrivalTime(processes);
    calculateFCFS(processes, averageWaitingTime, averageTurnaroundTime);
    displayResults(processes, averageWaitingTime, averageTurnaroundTime);

    return 0;
}
