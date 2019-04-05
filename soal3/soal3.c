#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tr1,tr2;
int wakeup_status,spirit_status;
int c_a,c_i,status=0,scan;

void* agmal(void* arg){
 while(scan==1){
    while(status!=1);
    if(c_i==3){
      printf("Fitur Agmal Ayo Bangun Disabled 10s\n");
      sleep(10);
      c_i=0;
    }
    else if(status==1){
      wakeup_status=wakeup_status+15;
      if(wakeup_status>=100){
        printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
        scan=0;
        break;
      }
      c_a++;
      if(c_a==3) status=2;
    }
  }
}

void* iraj(void* arg){
  while(scan==1){
    while(status!=2);
    if(c_a==3){
      printf("Fitur Iraj Ayo Tidur Disabled 10s\n");
      sleep(10);
      c_a=0;
    }
    else if(status==2){
      spirit_status=spirit_status-20;
      if(spirit_status<=0){
         printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal \n");
         scan=0;
         break;
      }
      c_i++;
      if(c_i==3) status=1;
    }
  }
}

int main(){
  int id;
  wakeup_status=0;
  spirit_status=100;
  c_a=0;
  c_i=0;
  scan=1;
  pthread_create(&(tr1),NULL,agmal,NULL);
  pthread_create(&(tr2),NULL,iraj,NULL);
  //pthread_create(&(tr3),NULL,all_status,NULL);
  //pthread_create(&(tr4),NULL,scan,NULL);
  printf("Fitur yang ada yaitu: \n");
  printf("\t 1. Agmal Ayo Bangun\n");
  printf("\t 2. Iraj Ayo Tidur\n");
  printf("\t 3. All Status\n");
  while(scan==1){
    printf("Masukkan fitur yang diinginkan dalam angka > \n");
    scanf("%d",&id);
    status=id;
    if(status==3){
      printf("Agmal WakeUp_Status = %d\n",wakeup_status);
      printf("Iraj Spirit_Status = %d\n",spirit_status);
    }
  }
  pthread_join(tr1,NULL);
  pthread_join(tr2,NULL);
}
