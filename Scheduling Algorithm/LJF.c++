/*
    Longest Job First (LJF) - Preemptive Scheduling Algorithm
    At each time unit, the process with the LONGEST remaining burst time runs.
*/

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;
    int arrival;    // Arrival Time
    int burst;      // Burst Time (remaining)
    int burstOrig;  // Original Burst Time (for output)
    int completion; // Completion Time
    int turnaround; // Turnaround Time = CT - AT
    int waiting;    // Waiting Time = TAT - BT
};

int main()
{
    const int n = 4;
    Process p[n];

    // --- Input: set up 4 processes ---
    // Process IDs: 1, 2, 3, 4
    // Arrival Times: 1, 2, 3, 4
    // Burst Times:   2, 4, 6, 8
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        p[i].arrival = i + 1;
        p[i].burst = 2 * (i + 1);
        p[i].burstOrig = p[i].burst;
    }

    // Display process info before scheduling
    cout << "PNo\tAT\tBT\n";
    for (int i = 0; i < n; i++)
        cout << p[i].id << "\t" << p[i].arrival << "\t" << p[i].burstOrig << "\n";
    cout << endl;

    // Sort by arrival time
    sort(p, p + n, [](const Process &a, const Process &b)
         { return a.arrival < b.arrival; });

    // Calculate total time needed
    int currentTime = p[0].arrival;
    int totalBurst = 0;
    for (int i = 0; i < n; i++)
        totalBurst += p[i].burst;
    int endTime = currentTime + totalBurst;

    // --- LJF Preemptive Scheduling ---
    while (currentTime < endTime)
    {
        // Find the process with the longest remaining burst among arrived ones
        int longest = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= currentTime && p[i].burst > 0)
            {
                if (longest == -1 || p[i].burst > p[longest].burst)
                    longest = i;
            }
        }

        cout << "Time " << currentTime << ": P" << p[longest].id << " running\n";

        // Execute for 1 time unit
        p[longest].burst--;
        currentTime++;

        // If process finishes, record its completion time
        if (p[longest].burst == 0)
        {
            p[longest].completion = currentTime;
            cout << "  -> P" << p[longest].id << " completed at time " << currentTime << "\n";
        }
    }

    // --- Calculate TAT and WT ---
    int totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burstOrig;
        totalTAT += p[i].turnaround;
        totalWT += p[i].waiting;
    }

    // --- Display results ---
    cout << "\nAfter execution of all processes ...\n";
    cout << "PNo\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].id << "\t" << p[i].arrival << "\t" << p[i].burstOrig << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\n";
    }

    cout << "\nTotal TAT = " << totalTAT << endl;
    cout << "Average TAT = " << totalTAT / (double)n << endl;
    cout << "Total WT = " << totalWT << endl;
    cout << "Average WT = " << totalWT / (double)n << endl;

    return 0;
}