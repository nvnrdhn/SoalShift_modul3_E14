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

struct monster
{
	char nama[100];
	int hunger, hygiene, health;
} player, enemy;

pthread_t tid[10];
int status = 5, *stok, food = 5, bathcd = 0;

void* menu(void *arg)
{
	while (status) {
		system("clear");
		switch (status) {

			case 3 :
			printf("Battle Mode\n");
			printf("%s's Health : %d\n", player.nama, player.health);
			printf("%s's Health : %d\n", enemy.nama, enemy.health);
			printf("Choices :\n");
			printf("1. Attack\n");
			printf("2. Run\n");
			break;

			case 4 :
			printf("Shop Mode\n");
			printf("Shop food stock : %d\n", *stok);
			printf("Your food stock : %d\n", food);
			printf("Choices :\n");
			printf("1. Buy\n");
			printf("2. Back\n");
			break;

			case 5 :
			printf("Standby Mode\n");
			printf("Health : %d\n", player.health);
			printf("Hunger : %d\n", player.hunger);
			printf("Hygiene : %d\n", player.hygiene);
			printf("Food left : %d\n", food);
			if (bathcd)
				printf("Bath will be ready in %ds\n", bathcd);
			else
				printf("Bath is ready\n");
			printf("Choices :\n");
			printf("1. Eat\n");
			printf("2. Bath\n");
			printf("3. Battle\n");
			printf("4. Shop\n");
			printf("0. Exit\n");
			break;

			default :
			printf("Wrong input!\n");
			status = 5;
			break;
		}
		sleep(1);
	}
	system("clear");
	printf("Game over!\n");

	return 0;
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

		if (c != '\n')
			status = c - '0';

		if (status == 1) {
			if (food > 0) {
				player.hunger += (player.hunger < 200 ? (player.hunger + 15 > 200 ? 200 - player.hunger : 15) : 0);
				food--;
			}
			else
				printf("No food available!\n");

			status = 5;
			continue;
		}

		if (status == 2) {
			if (bathcd)
				printf("Bath is on cooldown!\n");
			else {
				player.hygiene += (player.hygiene < 100 ? (player.hygiene + 30 > 100 ? 100 - player.hygiene : 30) : 0);
				bathcd = 20;
			}
			status = 5;
			continue;
		}

		if (status == 3)
			enemy.health = 100;

		while (status == 3) {
			char d = getchar();
			if (d == '1') {
				enemy.health -= 20;

				if (enemy.health <= 0) {
					status = 5;
					continue;
				}

				player.health -= 20;

				if (player.health <= 0) {
					status = 0;
					continue;
				}

			}
			if (d == '2')
				status = 5;
		}

		while (status == 4) {
			char d = getchar();
			if (d == '1') {
				if (*stok > 0) {
					food++;
					*stok -= 1;
				}
				else
					printf("Stok habis!\n");
				continue;
			}
			if (d == '2') {
				status = 5;
				continue;
			}

		}
	}

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

    return 0;
}

void* stat(void *arg)
{
	int i = 0;
	while (status) {
		while (status == 5 || status == 4) {
			i++;
			if (i % 10 == 0) {
				if (player.hunger > 0)
					player.hunger -= 10;
				if (player.health < 300)
					player.health += 5;
			}
			if (i % 30 == 0 && player.hygiene > 0)
				player.hygiene -= 10;
			if (player.hunger <= 0 || player.hygiene <= 0)
				status = 0;
			sleep(1);
			bathcd -= (bathcd ? 1 : 0);
		}
	}

	return 0;
}

int main()
{

	key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 5;
    
	player.health = 300;
	player.hygiene = 100;
	player.hunger = 200;
	printf("Enter your monster's name: ");
	scanf("%s", player.nama);
	strcpy(enemy.nama, "Enemy");
	enemy.health = 100;
	pthread_create(&tid[0], NULL, &menu, NULL);
	pthread_create(&tid[1], NULL, &input, NULL);
	pthread_create(&tid[2], NULL, &stat, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

	shmdt(stok);
    shmctl(shmid, IPC_RMID, NULL);

}