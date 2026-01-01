#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    // Create a child process
    int pid = fork();

    if (pid == 0) {
        // --- Child Process ---
        pid_t id = getpid();
        printf("Child Process ID: %d\n", id);
        
        // Simulate work
        sleep(4);
        
        // Exit with a specific status code (10)
        exit(10);
    } 
    else {
        // --- Parent Process ---
        int status;
        printf("Parent: Waiting for child to finish...\n");
        
        // Block execution until the child process changes state
        wait(&status); 
        
        // Check exit status using WEXITSTATUS macro
        printf("Child [%d] finished with status %d\n", pid, WEXITSTATUS(status));
    }

    return 0;
}