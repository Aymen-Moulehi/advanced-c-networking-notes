#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define DELAI 2

struct donnees {
    int nb;
    int total;
};

// Global flag for clean exit
volatile sig_atomic_t encore = 1;

void arret(int sig) {
    encore = 0;
}

int main(void) {
    key_t cle;
    int id;
    struct donnees *commun;
    struct sigaction a;

    // 1. Get the same key used by the producer
    cle = ftok(getenv("HOME"), 'A');
    if (cle == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 2. Locate the existing segment (size 0, no CREATE flag)
    id = shmget(cle, 0, 0);
    if (id == -1) {
        if (errno == ENOENT) {
            printf("Error: No shared memory segment found. Run producer first.\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("shmget");
            exit(EXIT_FAILURE);
        }
    }

    // 3. Attach as Read-Only (SHM_RDONLY)
    commun = (struct donnees *)shmat(id, NULL, SHM_RDONLY);
    if (commun == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Setup signal handler for Ctrl+C
    a.sa_handler = arret;
    sigemptyset(&a.sa_mask);
    a.sa_flags = 0;
    sigaction(SIGINT, &a, NULL);

    printf("Consumer started. Reading shared memory every %ds...\n", DELAI);
    while (encore) {
        sleep(DELAI);
        printf("Latest sub-total: %d (from %d inputs)\n", commun->total, commun->nb);
        printf(" --- \n");
    }

    // 4. Detach before exiting
    shmdt(commun);
    printf("\nExiting cleanly.\n");
    return EXIT_SUCCESS;
}