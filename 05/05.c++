// To Write a C++ program for implementation of SJF Scheduling Algorithm.

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid; // Process ID
    int bt;  // Burst Time
    int at;  // Arrival Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
    int ct;  // Completion Time
};

// Function to sort processes by arrival time, then by burst time
bool compare(Process a, Process b)
{
    if (a.at == b.at)
        return a.bt < b.bt;
    return a.at < b.at;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    // Input process details
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time for Process " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time for Process " << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    // Sort by arrival time
    sort(p, p + n, compare);

    int completed = 0;
    int currentTime = 0;
    bool visited[n] = {false};

    float totalWT = 0, totalTAT = 0;

    while (completed < n)
    {
        // Find process with minimum burst time among arrived processes
        int minIndex = -1;
        int minBT = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].at <= currentTime && p[i].bt < minBT)
            {
                minBT = p[i].bt;
                minIndex = i;
            }
        }

        if (minIndex == -1)
        {
            // No process has arrived yet, move time forward
            currentTime++;
        }
        else
        {
            // Execute the process
            p[minIndex].ct = currentTime + p[minIndex].bt;
            p[minIndex].tat = p[minIndex].ct - p[minIndex].at;
            p[minIndex].wt = p[minIndex].tat - p[minIndex].bt;

            totalWT += p[minIndex].wt;
            totalTAT += p[minIndex].tat;

            currentTime = p[minIndex].ct;
            visited[minIndex] = true;
            completed++;
        }
    }

    // Display results
    cout << "\n+-----+------------+------------+------------+-------------+--------------+\n";
    cout << "| PID | Arrival    | Burst      | Completion | Turnaround  | Waiting      |\n";
    cout << "|     | Time       | Time       | Time       | Time        | Time         |\n";
    cout << "+-----+------------+------------+------------+-------------+--------------+\n";

    for (int i = 0; i < n; i++)
    {
        cout << "| " << p[i].pid << "   | " << p[i].at << "          | "
             << p[i].bt << "          | " << p[i].ct << "          | "
             << p[i].tat << "           | " << p[i].wt << "            |\n";
    }

    cout << "+-----+------------+------------+------------+-------------+--------------+\n";

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;

    return 0;
}
