#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080
int run = 1;
int *stok;
pthread_t t[2];
void* server(void *arg) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (run) {
        char buffer[1024] = "";
        read( new_socket , buffer, 1024);
        if (!strcmp(buffer, "exit"))
            run = 0;
        if (!strcmp(buffer, "tambah"))
            *stok += 1;
    }
    return 0;
}

void* cetak(void *arg) {
    while (run) {
        sleep(5);
        printf("stok: %d\n", *stok);
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 0;

    pthread_create(&t[0], NULL, server, NULL);
    pthread_create(&t[1], NULL, cetak, NULL);
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    
    shmdt(stok);
    shmctl(shmid, IPC_RMID, NULL);
}