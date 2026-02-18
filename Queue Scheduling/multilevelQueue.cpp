/*
 * Multilevel Queue Scheduling Algorithm
 *
 * Three queues:
 *   Queue 1 (System/High priority)   -> Round Robin (quantum = 4)
 *   Queue 2 (Interactive/Medium)     -> Round Robin (quantum = 8)
 *   Queue 3 (Batch/Low priority)     -> FCFS
 *
 * Fixed-priority preemptive scheduling between queues:
 *   Queue 1 > Queue 2 > Queue 3
 *   A lower-priority queue only runs when all higher-priority queues are empty.
 */

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int queueLevel; // 1 = System, 2 = Interactive, 3 = Batch
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    bool started;
};

// Run Round Robin on a set of ready processes for one scheduling window.
// Returns the current time after processing.
int roundRobin(vector<Process *> &readyQueue, int currentTime, int quantum,
               vector<pair<int, int>> &gantt)
{
    queue<Process *> rq;
    for (auto *p : readyQueue)
        rq.push(p);
    readyQueue.clear();

    while (!rq.empty())
    {
        Process *p = rq.front();
        rq.pop();

        if (!p->started)
        {
            p->responseTime = currentTime - p->arrivalTime;
            p->started = true;
        }

        int execTime = min(quantum, p->remainingTime);
        gantt.push_back({p->id, execTime});
        currentTime += execTime;
        p->remainingTime -= execTime;

        if (p->remainingTime == 0)
        {
            p->completionTime = currentTime;
            p->turnaroundTime = p->completionTime - p->arrivalTime;
            p->waitingTime = p->turnaroundTime - p->burstTime;
        }
        else
        {
            rq.push(p);
        }
    }
    return currentTime;
}

// Run FCFS on a set of ready processes (already sorted by arrival).
int fcfs(vector<Process *> &readyQueue, int currentTime,
         vector<pair<int, int>> &gantt)
{
    for (auto *p : readyQueue)
    {
        if (!p->started)
        {
            p->responseTime = currentTime - p->arrivalTime;
            p->started = true;
        }
        gantt.push_back({p->id, p->remainingTime});
        currentTime += p->remainingTime;
        p->remainingTime = 0;
        p->completionTime = currentTime;
        p->turnaroundTime = p->completionTime - p->arrivalTime;
        p->waitingTime = p->turnaroundTime - p->burstTime;
    }
    readyQueue.clear();
    return currentTime;
}

void printGanttChart(const vector<pair<int, int>> &gantt)
{
    cout << "\n--- Gantt Chart ---\n|";
    for (auto &[pid, dur] : gantt)
        cout << " P" << pid << " |";
    cout << "\n0";
    int t = 0;
    for (auto &[pid, dur] : gantt)
    {
        t += dur;
        cout << setw(5) << t;
    }
    cout << "\n";
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "  Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "  Burst Time  : ";
        cin >> processes[i].burstTime;
        cout << "  Queue Level (1=System/RR q=4, 2=Interactive/RR q=8, 3=Batch/FCFS): ";
        cin >> processes[i].queueLevel;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].started = false;
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
        processes[i].responseTime = 0;
    }

    // Sort all processes by arrival time (stable keeps input order for ties)
    stable_sort(processes.begin(), processes.end(),
                [](const Process &a, const Process &b)
                {
                    return a.arrivalTime < b.arrivalTime;
                });

    int currentTime = 0;
    int completed = 0;
    vector<pair<int, int>> gantt; // {processId, duration}

    while (completed < n)
    {
        // Collect arrived & unfinished processes into their respective queues
        vector<Process *> q1, q2, q3;
        for (auto &p : processes)
        {
            if (p.arrivalTime <= currentTime && p.remainingTime > 0)
            {
                if (p.queueLevel == 1)
                    q1.push_back(&p);
                else if (p.queueLevel == 2)
                    q2.push_back(&p);
                else
                    q3.push_back(&p);
            }
        }

        if (!q1.empty())
        {
            int before = 0;
            for (auto *p : q1)
                before += (p->remainingTime > 0);
            currentTime = roundRobin(q1, currentTime, 4, gantt);
            for (auto &p : processes)
                if (p.remainingTime == 0 && p.completionTime != 0)
                    completed = 0; // recount below
        }
        else if (!q2.empty())
        {
            currentTime = roundRobin(q2, currentTime, 8, gantt);
        }
        else if (!q3.empty())
        {
            currentTime = fcfs(q3, currentTime, gantt);
        }
        else
        {
            // No process ready — advance time to next arrival
            int nextArrival = INT_MAX;
            for (auto &p : processes)
                if (p.remainingTime > 0)
                    nextArrival = min(nextArrival, p.arrivalTime);
            if (nextArrival == INT_MAX)
                break;
            currentTime = nextArrival;
            continue;
        }

        // Recount completed processes
        completed = 0;
        for (auto &p : processes)
            if (p.remainingTime == 0)
                completed++;
    }

    // ---- Output ----
    printGanttChart(gantt);

    cout << "\n"
         << left
         << setw(6) << "PID"
         << setw(10) << "Arrival"
         << setw(8) << "Burst"
         << setw(8) << "Queue"
         << setw(14) << "Completion"
         << setw(14) << "Turnaround"
         << setw(10) << "Waiting"
         << setw(10) << "Response"
         << "\n";
    cout << string(80, '-') << "\n";

    double totalTAT = 0, totalWT = 0, totalRT = 0;
    for (auto &p : processes)
    {
        cout << left
             << setw(6) << p.id
             << setw(10) << p.arrivalTime
             << setw(8) << p.burstTime
             << setw(8) << p.queueLevel
             << setw(14) << p.completionTime
             << setw(14) << p.turnaroundTime
             << setw(10) << p.waitingTime
             << setw(10) << p.responseTime
             << "\n";
        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nAverage Turnaround Time : " << fixed << setprecision(2) << totalTAT / n;
    cout << "\nAverage Waiting Time    : " << totalWT / n;
    cout << "\nAverage Response Time   : " << totalRT / n << "\n";

    return 0;
}
