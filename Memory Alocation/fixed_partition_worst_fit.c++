#include <bits/stdc++.h>
using namespace std;

void inputPartitions(vector<int> &partitions)
{
    int n;
    cout << "Enter number of partitions: ";
    cin >> n;
    partitions.resize(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter size of partition " << i + 1 << ": ";
        cin >> partitions[i];
    }
}

void inputProcesses(vector<int> &processes)
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    processes.resize(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter size of process " << i + 1 << ": ";
        cin >> processes[i];
    }
}

vector<int> worstFitAllocation(const vector<int> &partitions, const vector<int> &processes)
{
    vector<int> allocation(processes.size(), -1);
    vector<bool> used(partitions.size(), false);

    for (int i = 0; i < (int)processes.size(); i++)
    {
        int worstIndex = -1;
        for (int j = 0; j < (int)partitions.size(); j++)
        {
            if (!used[j] && partitions[j] >= processes[i])
            {
                if (worstIndex == -1 || partitions[j] > partitions[worstIndex])
                {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1)
        {
            allocation[i] = worstIndex;
            used[worstIndex] = true;
        }
    }

    return allocation;
}

void displayResult(const vector<int> &processes, const vector<int> &allocation)
{
    cout << "\nAllocation Table:\n";
    cout << left << setw(12) << "Process" << setw(15) << "Process Size" << "Partition\n";
    for (int i = 0; i < (int)processes.size(); i++)
    {
        cout << left << setw(12) << ("P" + to_string(i + 1)) << setw(15) << processes[i];
        if (allocation[i] == -1)
            cout << "Not Allocated";
        else
            cout << "Part " << allocation[i] + 1;
        cout << "\n";
    }
}

int main()
{
    vector<int> partitions, processes;

    inputPartitions(partitions);
    inputProcesses(processes);

    vector<int> allocation = worstFitAllocation(partitions, processes);

    displayResult(processes, allocation);

    return 0;
}
