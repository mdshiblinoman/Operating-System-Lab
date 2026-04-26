#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t child1 = fork();

    if (child1 < 0)
    {
        std::cerr << "Fork failed for child 1\n";
        return 1;
    }

    if (child1 == 0)
    {
        // First child
        std::cout << "Child 1 PID: " << getpid()
                  << " | Parent PID: " << getppid() << "\n";
        return 0;
    }

    pid_t child2 = fork();

    if (child2 < 0)
    {
        std::cerr << "Fork failed for child 2\n";
        return 1;
    }

    if (child2 == 0)
    {
        // Second child
        std::cout << "Child 2 PID: " << getpid()
                  << " | Parent PID: " << getppid() << "\n";
        return 0;
    }

    // Parent process
    std::cout << "Parent PID: " << getpid() << "\n";
    std::cout << "Process Tree:\n";
    std::cout << "Parent (" << getpid() << ")\n";
    std::cout << "|- Child 1 (" << child1 << ")\n";
    std::cout << "|- Child 2 (" << child2 << ")\n";

    wait(NULL);
    wait(NULL);

    return 0;
}
