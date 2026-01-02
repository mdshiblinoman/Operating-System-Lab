// To Write a C++ program for implementation of FCFS Scheduling Algorithm.

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];

    // Input process details
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter Arrival Time for Process " << pid[i] << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for Process " << pid[i] << ": ";
        cin >> bt[i];
    }

    // Sort processes by arrival time (FCFS)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    // Calculate Completion Time
    ct[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++)
    {
        if (ct[i - 1] < at[i])
        {
            ct[i] = at[i] + bt[i]; // CPU was idle
        }
        else
        {
            ct[i] = ct[i - 1] + bt[i];
        }
    }

    // Calculate Turnaround Time and Waiting Time
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i]; // Turnaround Time = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i]; // Waiting Time = Turnaround Time - Burst Time
        totalTAT += tat[i];
        totalWT += wt[i];
    }

    // Display results
    cout << "\n+-----+------+------+------+------+------+\n";
    cout << "| PID |  AT  |  BT  |  CT  | TAT  |  WT  |\n";
    cout << "+-----+------+------+------+------+------+\n";

    for (int i = 0; i < n; i++)
    {
        cout << "|  " << setw(2) << pid[i] << " | "
             << setw(4) << at[i] << " | "
             << setw(4) << bt[i] << " | "
             << setw(4) << ct[i] << " | "
             << setw(4) << tat[i] << " | "
             << setw(4) << wt[i] << " |\n";
    }

    cout << "+-----+------+------+------+------+------+\n";

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    return 0;
}
