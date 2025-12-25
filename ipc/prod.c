#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/* Shared data structure used by both processes */
struct donnees {
    int nb;    // Number of entries
    int total; // Cumulative sum
};

int main(void) {
    key_t cle;
    int id;
    struct donnees *commun;
    int reponse;

    // 1. Generate a unique key using the HOME directory
    cle = ftok(getenv("HOME"), 'A');
    if (cle == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 2. Create the shared memory segment (fail if it already exists)
    id = shmget(cle, sizeof(struct donnees), IPC_CREAT | IPC_EXCL | 0666);
    if (id == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "Error: Segment already exists.\n");
        } else {
            perror("shmget");
        }
        exit(EXIT_FAILURE);
    }

    // 3. Attach the segment to our process address space
    commun = (struct donnees *)shmat(id, NULL, 0);
    if (commun == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize values
    commun->nb = 0;
    commun->total = 0;

    printf("Producer started. Enter numbers to add to shared memory (Ctrl+D to stop):\n");
    while (1) {
        printf("+ ");
        if (scanf("%d", &reponse) != 1) break;

        commun->nb++;
        commun->total += reponse; // Fixed logic error: added +=
        
        printf("Running total (%d items): %d\n", commun->nb, commun->total);
        printf(" --- \n");
    }

    // 4. Detach from the segment
    if (shmdt(commun) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // 5. Delete the segment from the system
    if (shmctl(id, IPC_RMID, NULL) == -1) {
        perror("shmctl (RMID)");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}