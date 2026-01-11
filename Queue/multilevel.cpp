#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority; // 1 = System (highest), 2 = Interactive, 3 = Batch (lowest)
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

// Function to display process information
void displayProcesses(vector<Process> &processes)
{
    cout << "\n+-----+----------+-------+----------+----------+------------+------------+" << endl;
    cout << "| PID | Priority | Burst | Arrival  | Waiting  | Turnaround | Completion |" << endl;
    cout << "+-----+----------+-------+----------+----------+------------+------------+" << endl;

    for (auto &p : processes)
    {
        cout << "| P" << p.id << "  |    " << p.priority << "     |   " << p.burstTime
             << "   |    " << p.arrivalTime << "     |    " << p.waitingTime
             << "     |     " << p.turnaroundTime << "      |     " << p.completionTime << "      |" << endl;
    }
    cout << "+-----+----------+-------+----------+----------+------------+------------+" << endl;
}

// Multilevel Queue Scheduling
void multilevelQueueScheduling(vector<Process> &processes)
{
    // Three queues for different priority levels
    // Queue 1: System processes (FCFS) - Highest priority
    // Queue 2: Interactive processes (Round Robin, quantum = 2)
    // Queue 3: Batch processes (FCFS) - Lowest priority

    queue<Process *> systemQueue;      // Priority 1
    queue<Process *> interactiveQueue; // Priority 2
    queue<Process *> batchQueue;       // Priority 3

    int timeQuantum = 2; // Time quantum for interactive queue (RR)
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();

    vector<bool> inQueue(n, false);

    cout << "\n=== Multilevel Queue Scheduling ===" << endl;
    cout << "Queue 1 (System): FCFS - Highest Priority" << endl;
    cout << "Queue 2 (Interactive): Round Robin (Quantum = " << timeQuantum << ")" << endl;
    cout << "Queue 3 (Batch): FCFS - Lowest Priority" << endl;
    cout << "\n--- Execution Order ---" << endl;

    while (completed < n)
    {
        // Add arriving processes to their respective queues
        for (int i = 0; i < n; i++)
        {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                inQueue[i] = true;
                if (processes[i].priority == 1)
                {
                    systemQueue.push(&processes[i]);
                }
                else if (processes[i].priority == 2)
                {
                    interactiveQueue.push(&processes[i]);
                }
                else
                {
                    batchQueue.push(&processes[i]);
                }
            }
        }

        // Execute from highest priority queue first
        if (!systemQueue.empty())
        {
            // System Queue - FCFS (run to completion)
            Process *p = systemQueue.front();
            systemQueue.pop();

            cout << "Time " << currentTime << ": P" << p->id << " (System Queue) runs for " << p->remainingTime << " units" << endl;

            currentTime += p->remainingTime;
            p->remainingTime = 0;
            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;
            completed++;
        }
        else if (!interactiveQueue.empty())
        {
            // Interactive Queue - Round Robin
            Process *p = interactiveQueue.front();
            interactiveQueue.pop();

            int execTime = min(timeQuantum, p->remainingTime);
            cout << "Time " << currentTime << ": P" << p->id << " (Interactive Queue) runs for " << execTime << " units" << endl;

            currentTime += execTime;
            p->remainingTime -= execTime;

            // Check for new arrivals before re-adding to queue
            for (int i = 0; i < n; i++)
            {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
                {
                    inQueue[i] = true;
                    if (processes[i].priority == 1)
                    {
                        systemQueue.push(&processes[i]);
                    }
                    else if (processes[i].priority == 2)
                    {
                        interactiveQueue.push(&processes[i]);
                    }
                    else
                    {
                        batchQueue.push(&processes[i]);
                    }
                }
            }

            if (p->remainingTime > 0)
            {
                interactiveQueue.push(p);
            }
            else
            {
                p->completionTime = currentTime;
                p->turnaroundTime = p->completionTime - p->arrivalTime;
                p->waitingTime = p->turnaroundTime - p->burstTime;
                completed++;
            }
        }
        else if (!batchQueue.empty())
        {
            // Batch Queue - FCFS (run to completion)
            Process *p = batchQueue.front();
            batchQueue.pop();

            cout << "Time " << currentTime << ": P" << p->id << " (Batch Queue) runs for " << p->remainingTime << " units" << endl;

            currentTime += p->remainingTime;
            p->remainingTime = 0;
            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;
            completed++;
        }
        else
        {
            // No process ready, increment time
            currentTime++;
        }
    }

    // Calculate averages
    float avgWaiting = 0, avgTurnaround = 0;
    for (auto &p : processes)
    {
        avgWaiting += p.waitingTime;
        avgTurnaround += p.turnaroundTime;
    }
    avgWaiting /= n;
    avgTurnaround /= n;

    // Display results
    displayProcesses(processes);

    cout << "\n--- Statistics ---" << endl;
    cout << "Average Waiting Time: " << avgWaiting << endl;
    cout << "Average Turnaround Time: " << avgTurnaround << endl;
}

int main()
{
    int n;

    cout << "=== Multilevel Queue CPU Scheduling ===" << endl;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "\nPriority Levels:" << endl;
    cout << "  1 - System (Highest, FCFS)" << endl;
    cout << "  2 - Interactive (Round Robin)" << endl;
    cout << "  3 - Batch (Lowest, FCFS)" << endl;

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "\nProcess P" << i + 1 << ":" << endl;

        cout << "  Arrival Time: ";
        cin >> processes[i].arrivalTime;

        cout << "  Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;

        cout << "  Priority (1-3): ";
        cin >> processes[i].priority;

        // Validate priority
        if (processes[i].priority < 1 || processes[i].priority > 3)
        {
            cout << "  Invalid priority! Setting to 3 (Batch)" << endl;
            processes[i].priority = 3;
        }

        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].completionTime = 0;
    }

    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](Process &a, Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    multilevelQueueScheduling(processes);

    return 0;
}
