#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    // 1. Create the segment using IPC_PRIVATE
    // This generates a unique key automatically and doesn't require ftok/external files.
    int shmid = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
    
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // 2. Attach the segment before forking
    // Both parent and child will inherit this mapping
    int *shared_val = (int*) shmat(shmid, NULL, 0);
    if (shared_val == (void*) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Initialize the value in parent
    *shared_val = 100;
    printf("Parent: Shared memory initialized to %d\n", *shared_val);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // --- Child Process ---
        printf("Child: Reading value... it is %d\n", *shared_val);
        
        // Modify the value
        *shared_val += 100;
        printf("Child: Incremented value. New value is %d\n", *shared_val);
        
        // Detach and exit
        shmdt(shared_val);
        exit(0);
    } 
    else {
        // --- Parent Process ---
        wait(NULL); // Wait for child to finish its update
        
        printf("Parent: Final value after child's work: %d\n", *shared_val);

        // 3. Cleanup: Detach and then delete the segment
        shmdt(shared_val);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Parent: Shared memory cleaned up.\n");
    }

    return 0;
}