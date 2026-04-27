/*
Question 1-Process
Write a C program that creates a child process using fork(). Print:
    Parent PID
    Child PID
    Parent Process ID (PPID) of child
*/

#include <bits/stdc++.h>
#include <sys/wait.h>
using namespace std;

int main(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child PID: %d\n", getpid());
        printf("Parent Process ID (PPID) of child: %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("Parent PID: %d\n", getpid());
        printf("Child PID (from parent): %d\n", pid);

        // Wait so child finishes cleanly
        wait(NULL);
    }

    return 0;
}
