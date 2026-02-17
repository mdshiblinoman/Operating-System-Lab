#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n]; // arrival, burst, remaining time
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " -> AT: ";
        cin >> at[i];
        cout << "       BT: ";
        cin >> bt[i];
        rt[i] = bt[i]; // remaining time = burst time initially
    }

    int completed = 0, time = 0, maxRT, longest = -1;
    int ct[n], tat[n], wt[n];
    bool done[n] = {false};
    float totalTAT = 0, totalWT = 0;

    while (completed < n)
    {
        // Find process with longest remaining time at current time
        maxRT = -1;
        longest = -1;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && !done[i] && rt[i] > maxRT)
            {
                maxRT = rt[i];
                longest = i;
            }
        }

        if (longest == -1)
        {
            time++; // no process arrived yet, move time forward
            continue;
        }

        rt[longest]--; // execute for 1 unit
        time++;

        if (rt[longest] == 0)
        { // process finished
            done[longest] = true;
            completed++;
            ct[longest] = time;
            tat[longest] = ct[longest] - at[longest];
            wt[longest] = tat[longest] - bt[longest];
            totalTAT += tat[longest];
            totalWT += wt[longest];
        }
    }

    // Display results
    cout << "\n+-----+------+------+------+------+------+\n";
    cout << "| P   |  AT  |  BT  |  CT  |  TAT |  WT  |\n";
    cout << "+-----+------+------+------+------+------+\n";
    for (int i = 0; i < n; i++)
    {
        cout << "| P" << i + 1
             << "  |  " << at[i]
             << "   |  " << bt[i]
             << "   |  " << ct[i]
             << "   |  " << tat[i]
             << "   |  " << wt[i] << "   |\n";
    }
    cout << "+-----+------+------+------+------+------+\n";
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time:    " << totalWT / n << endl;

    return 0;
}
