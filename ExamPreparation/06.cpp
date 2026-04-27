#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void inputProcesses(vector<Process> &processes)
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    processes.resize(n);

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;

        cout << "Arrival time of P" << processes[i].pid << ": ";
        cin >> processes[i].arrivalTime;

        cout << "Burst time of P" << processes[i].pid << ": ";
        cin >> processes[i].burstTime;

        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }
}

int findShortestRemainingProcess(const vector<Process> &processes, int currentTime)
{
    int index = -1;
    int bestRemainingTime = numeric_limits<int>::max();

    for (size_t i = 0; i < processes.size(); i++)
    {
        if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
        {
            if (processes[i].remainingTime < bestRemainingTime)
            {
                bestRemainingTime = processes[i].remainingTime;
                index = static_cast<int>(i);
            }
            else if (processes[i].remainingTime == bestRemainingTime && index != -1 &&
                     processes[i].arrivalTime < processes[index].arrivalTime)
            {
                index = static_cast<int>(i);
            }
        }
    }

    return index;
}

void calculateSRTF(vector<Process> &processes)
{
    int completed = 0;
    int currentTime = 0;
    int n = static_cast<int>(processes.size());

    while (completed < n)
    {
        int index = findShortestRemainingProcess(processes, currentTime);

        if (index == -1)
        {
            currentTime++;
            continue;
        }

        processes[index].remainingTime--;
        currentTime++;

        if (processes[index].remainingTime == 0)
        {
            completed++;
            processes[index].completionTime = currentTime;
            processes[index].turnaroundTime =
                processes[index].completionTime - processes[index].arrivalTime;
            processes[index].waitingTime =
                processes[index].turnaroundTime - processes[index].burstTime;
        }
    }
}

void printResults(const vector<Process> &processes)
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
}

int main()
{
    vector<Process> processes;

    inputProcesses(processes);
    calculateSRTF(processes);
    printResults(processes);

    return 0;
}
