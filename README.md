# advanced-c-networking-notes
This repository serves as a technical log for my journey through Linux Network Development. It contains low-level implementations of networking concepts using the C language.

## 🛠️ How to Run
This repo includes a Python helper to quickly compile and run any exercise:
1. Ensure you are on a Linux/WSL system.
2. Run `python3 run.py`.
3. Select the program you wish to execute.

### 📈 Learning Progress
| Topic | File | Key Knowledge Gained |
| :--- | :--- | :--- |
|Knowledge Gained System V Shared Memory |ipc/prod.c, ipc/cons.c|How processes share data in RAM using shmget/shmat. Learned about ftok for key generation and IPC_RMID for cleanup. |
| UDP Datagrams | network\-basics/udp_directory.c | How to use sendto and recvfrom for connectionless communication and string manipulation.|
|TCP Parallelism | network\-basics/tcp_parallel_server.c | Using fork() to create a ""Child Process"" so the server can handle multiple clients simultaneously." |
| Socket Addresses | network\-basics/udp_directory.c | Encapsulating sockaddr_in setup into functions and using htons for Big-Endian network order. |