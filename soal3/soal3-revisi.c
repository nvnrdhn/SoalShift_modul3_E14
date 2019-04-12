#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tr1,tr2;
int wakeup_status,spirit_status;
int c_a=0,c_i=0,status,scan=1;
int flag_a,flag_i;
 
void* agmal(void* arg){
 while(scan==1){
    while(status!=1 && flag_a!=1);
    if(c_i==3){
      c_i=0;
      printf("Fitur Agmal Ayo Bangun Disabled 10s\n");
      flag_a=0;
      sleep(10);
      printf("Fitur Agmal Ayo Bangun Dapat diakses kembali\n");
      flag_a=1;
	status = 0;
    }
    else if(status==1 && flag_a==1){
      wakeup_status=wakeup_status+15;
      if(wakeup_status>=100){
        printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
        scan=0;
      }
      c_a++;
      if(c_a==3) status=2;
      else status=0;
    }
  }
}

void* iraj(void* arg){
  while(scan==1){
    while(status!=2 && flag_i!=1);
    if(c_a==3){
      c_a=0;
      printf("Fitur Iraj Ayo Tidur Disabled 10s\n");
      flag_i=0;
      sleep(10);
      printf("Fitur Iraj Ayo Tidur dapat diakses kembali \n");
      flag_i=1;
	status = 0;
    }
    else if(status==2){
      spirit_status=spirit_status-20;
      if(spirit_status<=0){
         printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal \n");
         scan=0;
      }
      c_i++;
      if(c_i==3) status=1;
	else status=0;
    }
  }
}

int main(){
  int id;
  wakeup_status=0;
  spirit_status=100;
  flag_a=1;
  flag_i=1;
  pthread_create(&(tr1),NULL,agmal,NULL);
  pthread_create(&(tr2),NULL,iraj,NULL);
  //pthread_create(&(tr3),NULL,all_status,NULL);
  //pthread_create(&(tr4),NULL,scan,NULL);
  printf("Fitur yang ada yaitu: \n");
  printf("\t 1. Agmal Ayo Bangun\n");
  printf("\t 2. Iraj Ayo Tidur\n");
  printf("\t 3. All Status\n");
  while(scan==1){
    //printf("Masukkan fitur yang diinginkan dalam angka > \n");
    scanf("%d",&id);
    if(id==1 && flag_a==0){
       printf("Fitur Agmal Ayo Bangun belum bisa digunakan\n");
       continue;
    }
    else if(id==2 && flag_i==0){
       printf("Fitur Iraj Ayo Tidur belum bisa digunakan\n");
       continue;
    }

    else if(id==3){
      printf("Agmal WakeUp_Status = %d\n",wakeup_status);
      printf("Iraj Spirit_Status = %d\n",spirit_status);
    }
    else if(id==0) scan=0;
    else status=id;
  }
 pthread_join(tr1,NULL);
 pthread_join(tr2,NULL);
}
