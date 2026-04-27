/*
Question 2-Process
Write a program where:
    parent prints numbers 1–5
    child prints numbers 6–10
Observe execution order.
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
        // Child prints 6 to 10
        for (int i = 6; i <= 10; i++)
        {
            printf("Child: %d\n", i);
            fflush(stdout);
            usleep(100000);
        }
    }
    else
    {
        // Parent prints 1 to 5
        for (int i = 1; i <= 5; i++)
        {
            printf("Parent: %d\n", i);
            fflush(stdout);
            usleep(100000);
        }

        wait(NULL);
    }

    return 0;
}
