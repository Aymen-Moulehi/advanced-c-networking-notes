#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void alarm_handler(int sig) {
    printf("Beep! Beep! Wake up! (Signal %d received)\n", sig);
}

int main() {
    // Register the custom handler for the SIGALRM signal
    signal(SIGALRM, alarm_handler);

    // Schedule an alarm signal in 3 seconds
    alarm(3);

    printf("Waiting for the alarm...\n");

    // Suspend the process until any signal is caught
    pause();

    printf("Program resumed after signal and exiting.\n");

    return 0;
}