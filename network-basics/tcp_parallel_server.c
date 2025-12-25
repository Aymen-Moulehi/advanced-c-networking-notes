#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9090

int main() {
    int listen_fd, conn_fd;
    struct sockaddr_in servaddr;
    char buffer[100];

    // EXERCISE 1 & 4.2: TCP Skeleton & Parallelism
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listen_fd, 5);

    printf("Parallel TCP Server waiting on port %d...\n", PORT);

    while(1) {
        conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
        
        // Parallel Handling: Create a child process
        if (fork() == 0) { 
            close(listen_fd); // Child process closes listener
            
            int n = read(conn_fd, buffer, 100);
            buffer[n] = '\0';
            
            // Logic: Just a sample response for the directory
            write(conn_fd, "Connected to Directory...", 25);
            
            close(conn_fd);
            exit(0); // Child terminates after task
        }
        close(conn_fd); // Parent closes the connection and continues listening
    }
    return 0;
}