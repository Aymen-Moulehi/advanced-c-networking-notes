#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *message = "Hello from the Writer!";
    
    // Open the existing FIFO for writing only
    // This will block until a reader opens the FIFO
    printf("Writer: Waiting for a reader to join...\n");
    int fd = open("challenge_fifo", O_WRONLY);
    
    if (fd == -1) {
        perror("Error opening FIFO (make sure reader or mkfifo ran first)");
        return 1;
    }

    // Write the string to the FIFO
    printf("Writer: Sending message...\n");
    write(fd, message, strlen(message) + 1);

    close(fd);
    printf("Writer: Data sent and connection closed.\n");

    return 0;
}