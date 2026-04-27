/*
write a c program to create a main process named tintin having two child processes
without any grandchildren processes. the names of child processes are captain_haddock
and prof_calculus
*/

#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    prctl(PR_SET_NAME, "tintin", 0, 0, 0);
    printf("Main process: tintin (PID=%d, PPID=%d)\n", getpid(), getppid());

    pid_t child1 = fork();
    if (child1 < 0)
    {
        perror("fork child1 failed");
        return 1;
    }

    if (child1 == 0)
    {
        prctl(PR_SET_NAME, "captain_haddock", 0, 0, 0);
        printf("Child process: captain_haddock (PID=%d, PPID=%d)\n", getpid(), getppid());
        _exit(0);
    }

    pid_t child2 = fork();
    if (child2 < 0)
    {
        perror("fork child2 failed");
        return 1;
    }

    if (child2 == 0)
    {
        prctl(PR_SET_NAME, "prof_calculus", 0, 0, 0);
        printf("Child process: prof_calculus (PID=%d, PPID=%d)\n", getpid(), getppid());
        _exit(0);
    }

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    printf("All child processes finished.\n");
    return 0;
}
