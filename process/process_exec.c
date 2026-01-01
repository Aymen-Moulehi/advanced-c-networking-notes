#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    // Create a child process
    int pid = fork();

    if (pid == 0) {
        // --- Child Process ---
        // Replace the current process image with the "ps" command
        // execlp(file, arg0, arg1, ..., NULL)
        execlp("ps", "ps", NULL);
        
        // This part is only reached if execlp fails
        perror("execlp failed");
        exit(1);
    } 
    else {
        // --- Parent Process ---
        int status;
        printf("Parent: Waiting for child to finish...\n");
        
        // Wait for the child (which is now running 'ps') to complete
        wait(&status); 
        
        printf("Child has finished displaying processes.\n");
    }

    return 0;
}