/*
 * Multilevel Feedback Queue (MLFQ) Scheduling Algorithm
 *
 * Processes can move between queues based on their CPU-burst behaviour:
 *   Queue 1 (Highest priority) -> Round Robin, quantum = 4
 *   Queue 2 (Medium  priority) -> Round Robin, quantum = 8
 *   Queue 3 (Lowest  priority) -> FCFS
 *
 * Rules:
 *   1. A new process enters Queue 1.
 *   2. If a process uses its full quantum without finishing, it is demoted
 *      to the next lower queue.
 *   3. If a process finishes within its quantum, it leaves the system.
 *   4. Queue 3 (FCFS) runs only when Queues 1 & 2 are empty.
 *   5. Higher queues preempt lower queues when a new process arrives.
 */

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int currentQueue; // 1, 2, or 3
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    bool started;
    bool inQueue; // already sitting in a ready queue
    bool completed;
};

void printGanttChart(const vector<pair<int, int>> &gantt)
{
    if (gantt.empty())
        return;

    // Merge consecutive entries of the same process
    vector<pair<int, int>> merged;
    for (auto &g : gantt)
    {
        if (!merged.empty() && merged.back().first == g.first)
            merged.back().second += g.second;
        else
            merged.push_back(g);
    }

    cout << "\n--- Gantt Chart ---\n|";
    for (auto &[pid, dur] : merged)
    {
        if (pid == -1)
            cout << " idle |";
        else
            cout << " P" << pid << " |";
    }

    cout << "\n0";
    int t = 0;
    for (auto &[pid, dur] : merged)
    {
        t += dur;
        cout << setw(6) << t;
    }
    cout << "\n";
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> proc(n);
    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        cout << "\nProcess " << i + 1 << ":\n";
        cout << "  Arrival Time: ";
        cin >> proc[i].arrivalTime;
        cout << "  Burst Time  : ";
        cin >> proc[i].burstTime;
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].currentQueue = 1; // all start in highest-priority queue
        proc[i].started = false;
        proc[i].inQueue = false;
        proc[i].completed = false;
        proc[i].completionTime = 0;
        proc[i].turnaroundTime = 0;
        proc[i].waitingTime = 0;
        proc[i].responseTime = 0;
    }

    // Sort by arrival time (stable for ties)
    stable_sort(proc.begin(), proc.end(),
                [](const Process &a, const Process &b)
                {
                    return a.arrivalTime < b.arrivalTime;
                });

    // Three ready queues
    queue<Process *> q1, q2, q3;

    int quantum[4] = {0, 4, 8, 0}; // quantum[queueLevel]; 0 for FCFS
    int currentTime = 0;
    int completedCount = 0;
    vector<pair<int, int>> gantt; // {processId (-1=idle), duration}

    // Lambda: enqueue all processes that arrive at or before 'time'
    auto admitNewArrivals = [&](int time)
    {
        for (auto &p : proc)
        {
            if (!p.completed && !p.inQueue && p.arrivalTime <= time)
            {
                p.inQueue = true;
                if (p.currentQueue == 1)
                    q1.push(&p);
                else if (p.currentQueue == 2)
                    q2.push(&p);
                else
                    q3.push(&p);
            }
        }
    };

    while (completedCount < n)
    {
        // Admit processes that have arrived by currentTime
        admitNewArrivals(currentTime);

        // Pick the highest-priority non-empty queue
        Process *cur = nullptr;
        int curQL = 0;
        if (!q1.empty())
        {
            cur = q1.front();
            q1.pop();
            curQL = 1;
        }
        else if (!q2.empty())
        {
            cur = q2.front();
            q2.pop();
            curQL = 2;
        }
        else if (!q3.empty())
        {
            cur = q3.front();
            q3.pop();
            curQL = 3;
        }

        if (!cur)
        {
            // CPU idle — advance to the next process arrival
            int nextArrival = INT_MAX;
            for (auto &p : proc)
                if (!p.completed && p.arrivalTime > currentTime)
                    nextArrival = min(nextArrival, p.arrivalTime);
            if (nextArrival == INT_MAX)
                break;
            gantt.push_back({-1, nextArrival - currentTime});
            currentTime = nextArrival;
            continue;
        }

        // Record response time on first execution
        if (!cur->started)
        {
            cur->responseTime = currentTime - cur->arrivalTime;
            cur->started = true;
        }

        // Determine execution slice
        int slice;
        if (curQL == 3)
        {
            // FCFS — but we still run 1 unit at a time to allow preemption
            // by higher queues when new processes arrive
            slice = 1;
        }
        else
        {
            slice = min(quantum[curQL], cur->remainingTime);
        }

        // For RR queues (1 & 2), check if a higher-priority arrival happens
        // mid-quantum. If so, run only until that arrival (preempt).
        if (curQL <= 2)
        {
            for (auto &p : proc)
            {
                if (!p.completed && !p.inQueue &&
                    p.arrivalTime > currentTime &&
                    p.arrivalTime < currentTime + slice)
                {
                    // A new arrival during this quantum — preempt at that point
                    // only if it would enter a higher queue than current
                    if (p.currentQueue < curQL)
                    {
                        slice = p.arrivalTime - currentTime;
                    }
                }
            }
        }

        // For FCFS queue, check if higher-priority arrival happens next unit
        if (curQL == 3)
        {
            // Already slice = 1, preemption handled each tick
        }

        // Execute the process for 'slice' time units
        gantt.push_back({cur->id, slice});
        currentTime += slice;
        cur->remainingTime -= slice;

        // Admit any processes that arrived during this execution
        admitNewArrivals(currentTime);

        if (cur->remainingTime == 0)
        {
            // Process finished
            cur->completed = true;
            cur->inQueue = false;
            cur->completionTime = currentTime;
            cur->turnaroundTime = cur->completionTime - cur->arrivalTime;
            cur->waitingTime = cur->turnaroundTime - cur->burstTime;
            completedCount++;
        }
        else if (curQL <= 2 && slice == quantum[curQL])
        {
            // Used full quantum in RR queue — demote
            cur->currentQueue = min(3, curQL + 1);
            if (cur->currentQueue == 2)
                q2.push(cur);
            else
                q3.push(cur);
        }
        else
        {
            // Preempted before finishing quantum (or FCFS tick) — re-enqueue
            // at the same queue level
            if (curQL == 1)
                q1.push(cur);
            else if (curQL == 2)
                q2.push(cur);
            else
                q3.push(cur);
        }
    }

    // ---- Output ----
    printGanttChart(gantt);

    cout << "\n"
         << left
         << setw(6) << "PID"
         << setw(10) << "Arrival"
         << setw(8) << "Burst"
         << setw(14) << "Completion"
         << setw(14) << "Turnaround"
         << setw(10) << "Waiting"
         << setw(10) << "Response"
         << "\n";
    cout << string(72, '-') << "\n";

    double totalTAT = 0, totalWT = 0, totalRT = 0;
    for (auto &p : proc)
    {
        cout << left
             << setw(6) << p.id
             << setw(10) << p.arrivalTime
             << setw(8) << p.burstTime
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
