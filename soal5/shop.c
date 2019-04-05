#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <termios.h>
#include <sys/ipc.h>
#include <sys/shm.h>
pthread_t tid[2];
int *stok, status = 1;

void* menu(void *arg)
{
	while (status) {
		system("clear");
		printf("Shop\n");
		printf("Food stock : %d\n", *stok);
		printf("Choices :\n");
		printf("1. Restock\n");
		printf("0. Exit\n");
		sleep(1);
	}
}

void* input(void *arg)
{
	struct termios old_tio, new_tio;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    while (status) {
 		char c = getchar();
 		if (c == '1')
 			*stok += 1;
 		if (c == '0')
 			status = 0;
    }

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

}

int main()
{
	key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

	pthread_create(&tid[0], NULL, &menu, NULL);
	pthread_create(&tid[1], NULL, &input, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	shmdt(stok);
    shmctl(shmid, IPC_RMID, NULL);

}