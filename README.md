# advanced-c-networking-notes
This repository serves as a technical log for my journey through Linux Network Development. It contains low-level implementations of networking concepts using the C language.

### 📂 Repository Structure
* **/basics**: Fundamental concepts (Byte ordering, Address structures).
* **/sockets**: Standard TCP/UDP Client-Server architectures.
* **/multiplexing**: Scalable I/O (select, poll, epoll).
* **/protocols**: Custom and standard protocol implementations.

### 📈 Learning Progress
| Topic | File | Key Knowledge Gained |
| :--- | :--- | :--- |
|Topic,File,Key Knowledge Gained System V Shared Memory |ipc/prod.c, ipc/cons.c|How processes share data in RAM using shmget/shmat. Learned about ftok for key generation and IPC_RMID for cleanup. |