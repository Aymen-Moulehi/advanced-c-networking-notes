#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Structure for semop operations
// P (Proberen/Test): Decrements semaphore (Wait/Lock)
struct sembuf op_P = {0, -1, 0}; 
// V (Verhogen/Increment): Increments semaphore (Signal/Unlock)
struct sembuf op_V = {0, 1, 0};  

int main() {
    // 1. Create resources using IPC_PRIVATE
    int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int shmid = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);

    // 2. Initialize semaphore to 1 (Unlocked)
    semctl(semid, 0, SETVAL, 1);

    // Attach memory in parent initially to set value
    int *shared_val = (int*) shmat(shmid, NULL, 0);
    *shared_val = 0;

    if (fork() == 0) {
        // --- Child Process ---
        printf("Child: Attempting to enter critical section (P)...\n");
        
        semop(semid, &op_P, 1); // Lock
        
        printf("Child: Inside critical section. Incrementing shared value...\n");
        *shared_val += 50;
        sleep(2); // Simulate heavy work
        
        printf("Child: Leaving critical section (V)...\n");
        semop(semid, &op_V, 1); // Unlock
        
        shmdt(shared_val);
        exit(0);
    } 
    else {
        // --- Parent Process ---
        printf("Parent: Attempting to enter critical section (P)...\n");
        
        semop(semid, &op_P, 1); // Lock
        
        printf("Parent: Inside critical section. Current value: %d\n", *shared_val);
        *shared_val += 100;
        
        semop(semid, &op_V, 1); // Unlock
        
        wait(NULL); 
        printf("Parent: Final value of x = %d\n", *shared_val);

        // 3. Cleanup
        shmdt(shared_val);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID); 
    }

    return 0;
}