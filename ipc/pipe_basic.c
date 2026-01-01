#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[2]; // fd[0] is read end, fd[1] is write end
    int data;

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    if (fork() == 0) {
        // --- Child Process (Receiver) ---
        close(fd[1]); // Close unused write end

        if (read(fd[0], &data, sizeof(int)) > 0) {
            printf("Child: Received %d from parent. Double is %d\n", data, data * 2);
        }

        close(fd[0]);
        exit(0);
    } 
    else {
        // --- Parent Process (Sender) ---
        close(fd[0]); // Close unused read end

        int val_to_send = 20;
        printf("Parent: Sending %d to child...\n", val_to_send);
        
        write(fd[1], &val_to_send, sizeof(int));
        
        close(fd[1]);
        wait(NULL); // Wait for child to finish printing
    }

    return 0;
}