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
| XDR Representation | xdr\-representation/client_xdr.c, server_xdr.c | Using XDR_ENCODE and XDR_DECODE to ensure data portability across different CPU architectures. |
| Process Synchronization | process_wait.c | Understanding wait() to block parent execution until the child terminates, and using WEXITSTATUS to retrieve the child's specific exit code. |
| Process Execution	| process_exec.c |	Using execlp to replace the child process image with a system command (ps). Learned that exec family functions do not return on success as they overwrite the current stack/heap. |
| Signal Handling	| signal_alarm.c | Using signal() to catch SIGALRM and alarm() to schedule kernel-level notifications. Learned that pause() efficiently suspends a process until a signal interrupt occurs.|
| Anonymous Pipes | ipc/pipe_basic.c | Using pipe() to create a communication channel. Learned that fd[0] is for reading and fd[1] for writing, and the importance of closing unused ends to avoid deadlocks.|
| Named Pipes (FIFO)	| ipc/fifo_reader.c	| Using mkfifo() to create a persistent pipe in the filesystem. Learned that open() on a FIFO blocks until both a reader and a writer are present, allowing communication between unrelated processes.|
| Named Pipes (FIFO) Writer	| ipc/fifo_writer.c	| Implementing the writer side of a FIFO. Understanding that O_WRONLY blocks until a reader is ready, and how FIFOs enable communication between unrelated processes via the filesystem.|
| Private Shared Memory	| ipc/shm_private.c	| Using IPC_PRIVATE to create anonymous shared memory. Learned this is safer for parent/child IPC as it avoids ftok file dependencies and potential key collisions.|
| Semaphores & Mutex | ipc/sem_shm.c	| Using semget and semop (P/V operations) to create a Critical Section. Learned how to prevent race conditions when multiple processes access the same Shared Memory segment.|