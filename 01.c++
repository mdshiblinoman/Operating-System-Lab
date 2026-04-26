#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
