/*
Question 3-Process
Create two child processes from one parent process and display the process tree.
*/

#include <bits/stdc++.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    pid_t child1 = fork();

    if (child1 < 0)
    {
        cerr << "Fork failed for child 1\n";
        return 1;
    }

    if (child1 == 0)
    {
        // First child
        cout << "Child 1 PID: " << getpid()
             << " | Parent PID: " << getppid() << "\n";
        return 0;
    }

    pid_t child2 = fork();

    if (child2 < 0)
    {
        cerr << "Fork failed for child 2\n";
        return 1;
    }

    if (child2 == 0)
    {
        // Second child
        cout << "Child 2 PID: " << getpid()
             << " | Parent PID: " << getppid() << "\n";
        return 0;
    }

    // Parent process
    cout << "Parent PID: " << getpid() << "\n";
    cout << "Process Tree:\n";
    cout << "Parent (" << getpid() << ")\n";
    cout << "|- Child 1 (" << child1 << ")\n";
    cout << "|- Child 2 (" << child2 << ")\n";

    wait(NULL);
    wait(NULL);

    return 0;
}
