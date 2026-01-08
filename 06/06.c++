// To Write a C++ program for implementation Banker's Algorithm for Deadlock Avoidance.

#include <iostream>
using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

int n, m; // n = number of processes, m = number of resource types
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to calculate the Need matrix
void calculateNeed()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Safety Algorithm to check if the system is in a safe state
bool isSafeState(int safeSequence[])
{
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    // Initialize work = available
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                // Check if Need[i] <= Work
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    // Simulate allocation: Work = Work + Allocation[i]
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        // If no process found in this iteration, system is not in safe state
        if (!found)
        {
            return false;
        }
    }

    return true;
}

// Resource Request Algorithm
bool requestResources(int processId, int request[])
{
    // Step 1: Check if Request <= Need
    for (int j = 0; j < m; j++)
    {
        if (request[j] > need[processId][j])
        {
            cout << "Error: Process has exceeded its maximum claim!" << endl;
            return false;
        }
    }

    // Step 2: Check if Request <= Available
    for (int j = 0; j < m; j++)
    {
        if (request[j] > available[j])
        {
            cout << "Resources not available. Process must wait." << endl;
            return false;
        }
    }

    // Step 3: Pretend to allocate resources
    for (int j = 0; j < m; j++)
    {
        available[j] -= request[j];
        allocation[processId][j] += request[j];
        need[processId][j] -= request[j];
    }

    // Step 4: Check if the new state is safe
    int safeSequence[MAX_PROCESSES];
    if (isSafeState(safeSequence))
    {
        cout << "Request granted. System remains in safe state." << endl;
        return true;
    }
    else
    {
        // Rollback the allocation
        for (int j = 0; j < m; j++)
        {
            available[j] += request[j];
            allocation[processId][j] -= request[j];
            need[processId][j] += request[j];
        }
        cout << "Request denied. Granting it would lead to unsafe state." << endl;
        return false;
    }
}

// Function to display current state
void displayState()
{
    cout << "\n========== Current System State ==========" << endl;

    cout << "\nAvailable Resources: ";
    for (int j = 0; j < m; j++)
    {
        cout << available[j] << " ";
    }
    cout << endl;

    cout << "\nProcess\t  Maximum\t  Allocation\t  Need" << endl;
    cout << "-------\t  -------\t  ----------\t  ----" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t  ";

        for (int j = 0; j < m; j++)
        {
            cout << maximum[i][j] << " ";
        }
        cout << "\t  ";

        for (int j = 0; j < m; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << "\t  ";

        for (int j = 0; j < m; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    cout << "==========================================\n"
         << endl;
}

int main()
{
    cout << "===== Banker's Algorithm for Deadlock Avoidance =====" << endl;

    // Input number of processes and resources
    cout << "\nEnter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    // Input available resources
    cout << "\nEnter available instances of each resource type:" << endl;
    for (int j = 0; j < m; j++)
    {
        cout << "Resource " << j << ": ";
        cin >> available[j];
    }

    // Input maximum demand matrix
    cout << "\nEnter Maximum demand matrix:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < m; j++)
        {
            cin >> maximum[i][j];
        }
    }

    // Input allocation matrix
    cout << "\nEnter Allocation matrix:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    // Calculate Need matrix
    calculateNeed();

    // Display current state
    displayState();

    // Check if initial state is safe
    int safeSequence[MAX_PROCESSES];
    cout << "Checking if system is in safe state..." << endl;

    if (isSafeState(safeSequence))
    {
        cout << "\nSystem is in SAFE state!" << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << safeSequence[i];
            if (i < n - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "\nSystem is in UNSAFE state! Deadlock may occur." << endl;
    }

    // Resource Request handling
    char choice;
    cout << "\nDo you want to make a resource request? (y/n): ";
    cin >> choice;

    while (choice == 'y' || choice == 'Y')
    {
        int processId;
        int request[MAX_RESOURCES];

        cout << "\nEnter process ID (0 to " << n - 1 << "): ";
        cin >> processId;

        if (processId < 0 || processId >= n)
        {
            cout << "Invalid process ID!" << endl;
        }
        else
        {
            cout << "Enter resource request for P" << processId << ": ";
            for (int j = 0; j < m; j++)
            {
                cin >> request[j];
            }

            requestResources(processId, request);

            // Display updated state
            displayState();

            // Check and display safe sequence after request
            if (isSafeState(safeSequence))
            {
                cout << "Current Safe Sequence: ";
                for (int i = 0; i < n; i++)
                {
                    cout << "P" << safeSequence[i];
                    if (i < n - 1)
                        cout << " -> ";
                }
                cout << endl;
            }
        }

        cout << "\nDo you want to make another request? (y/n): ";
        cin >> choice;
    }

    cout << "\n===== Program Terminated =====" << endl;

    return 0;
}
