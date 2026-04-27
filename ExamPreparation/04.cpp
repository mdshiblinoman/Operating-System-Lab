#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int inputProcessCount()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    return n;
}

void inputProcesses(vector<Process> &p)
{
    for (size_t i = 0; i < p.size(); i++)
    {
        p[i].pid = static_cast<int>(i) + 1;
    }

    cout << "Enter arrival times for all processes:\n";
    for (size_t i = 0; i < p.size(); i++)
    {
        cout << "AT of P" << p[i].pid << ": ";
        cin >> p[i].at;
    }

    cout << "Enter burst times for all processes:\n";
    for (size_t i = 0; i < p.size(); i++)
    {
        cout << "BT of P" << p[i].pid << ": ";
        cin >> p[i].bt;
    }
}

void sortByArrivalTime(vector<Process> &p)
{
    for (size_t i = 0; i < p.size(); i++)
    {
        for (size_t j = i + 1; j < p.size(); j++)
        {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].pid > p[j].pid))
            {
                swap(p[i], p[j]);
            }
        }
    }
}

void calculateFCFS(vector<Process> &p, double &avgWT, double &avgTAT)
{
    int time = 0;
    int totalWT = 0;
    int totalTAT = 0;

    for (size_t i = 0; i < p.size(); i++)
    {
        if (time < p[i].at)
        {
            time = p[i].at;
        }

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        time = p[i].ct;
    }

    avgWT = static_cast<double>(totalWT) / p.size();
    avgTAT = static_cast<double>(totalTAT) / p.size();
}

void printResults(const vector<Process> &p, double avgWT, double avgTAT)
{
    cout << "\n+-----+------+------+------+------+------+\n";
    cout << "| PID |  AT  |  BT  |  CT  | TAT  |  WT  |\n";
    cout << "+-----+------+------+------+------+------+\n";

    for (size_t i = 0; i < p.size(); i++)
    {
        cout << "| " << setw(3) << p[i].pid << " | "
             << setw(4) << p[i].at << " | "
             << setw(4) << p[i].bt << " | "
             << setw(4) << p[i].ct << " | "
             << setw(4) << p[i].tat << " | "
             << setw(4) << p[i].wt << " |\n";
    }

    cout << "+-----+------+------+------+------+------+\n";
    cout << fixed << setprecision(2);
    cout << "Average WT = " << avgWT << "\n";
    cout << "Average TAT = " << avgTAT << "\n";
}

int main()
{
    int n = inputProcessCount();

    if (n <= 0)
    {
        cout << "Number of processes must be greater than 0.\n";
        return 0;
    }

    vector<Process> p(n);
    double avgWT = 0.0;
    double avgTAT = 0.0;

    inputProcesses(p);
    sortByArrivalTime(p);
    calculateFCFS(p, avgWT, avgTAT);
    printResults(p, avgWT, avgTAT);

    return 0;
}