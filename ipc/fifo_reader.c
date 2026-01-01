#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char buffer[128];
    
    // Create the Named Pipe (FIFO) with read/write permissions for all (0666)
    // If it already exists, mkfifo will return -1
    mkfifo("challenge_fifo", 0666); 

    printf("Reader: Opening the FIFO...\n");
    
    // Open the FIFO for reading. 
    // Note: This call will block until a writer opens the other end.
    int fd = open("challenge_fifo", O_RDONLY); 
    if (fd == -1) {
        perror("Failed to open FIFO");
        return 1;
    }

    // Read the data sent by a writer process
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        printf("Reader: Received message: %s\n", buffer);
    }

    close(fd);
    
    // Optional: Remove the FIFO file from the filesystem when done
    unlink("challenge_fifo");
    
    return 0;
}