#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUF 1024

// EXERCISE 2.1: Function to create a local address (Server side)
struct sockaddr_in create_local_addr(int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; 
    addr.sin_port = htons(port);
    return addr;
}

// EXERCISE 4: The Directory Search Logic
int Recherche(char *Abonne, char *telephone) {
    if (strcasecmp(Abonne, "ALICE") == 0) { strcpy(telephone, "06-11-22-33"); return 1; }
    if (strcasecmp(Abonne, "BOB") == 0) { strcpy(telephone, "07-44-55-66"); return 1; }
    return 0;
}

int main() {
    int sockfd;
    char buffer[MAX_BUF], phone[MAX_BUF];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // EXERCISE 1: UDP Skeleton
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr = create_local_addr(PORT);
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("UDP Directory Server ready on port %d...\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, MAX_BUF, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';

        // EXERCISE 3: Transform to Uppercase
        for(int i = 0; buffer[i]; i++) buffer[i] = toupper(buffer[i]);

        printf("Search requested for: %s\n", buffer);

        if (Recherche(buffer, phone)) {
            sendto(sockfd, phone, strlen(phone), 0, (struct sockaddr *)&cliaddr, len);
        } else {
            char *msg = "Error: Not found";
            sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, len);
        }
    }
    return 0;
}