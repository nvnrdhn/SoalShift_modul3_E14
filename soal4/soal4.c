#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>

pthread_t tr[3];
int status;
char dirname[100] = "/home/camiliamay6/Dokumen/";

void* zip(void* arg){
  int i;
  while(status!=1);
  for(i=0;i<2;i++){
    char temp[100],temp2[100];
    char nama_zip[50];
    char nama_folder[50];
    char command[50] = "zip -j -m ";
    sprintf(nama_folder,"FolderProses%d/",i+1);
    strcpy(temp,dirname);
    strcat(temp,nama_folder);
    strcpy(temp2,temp);
    sprintf(nama_zip,"KompresProses%d.zip ",i+1);
    strcat(command,strcat(temp,nama_zip));
    strcat(temp2,"*");
    system(strcat(command,temp2));
  }
  printf("Menunggu 15 detik untuk mengekstrak kembali\n");
  sleep(15);
  status=0;
}


void* teks(void* arg){
   int i;
   status=2;
   for(i=0;i<2;i++){
     char name[50];
     char dir[100];
     char p[]= "ps -aux | head -11 >";
     strcpy(dir,dirname);
     sprintf(name,"FolderProses%d/",i+1);
     strcat(dir,name);
     mkdir(dir,0777);
     sprintf(name,"SimpanProses%d.txt",i+1);
     strcat(dir,name);
     system(strcat(p,dir));
   }
   status=1;
}

void* extract(void* arg){
  while(status!=0);
  //sleep(15);
  int i;
  for(i=0;i<2;i++){
     char nama[50];
     char folder[50];
     char dir[50];
     char temp[50];
     char command[150] = "unzip ";
     sprintf(folder,"FolderProses%d",i+1);
     strcpy(dir,dirname);
     strcat(dir,folder);
     strcpy(temp,dir);
     sprintf(nama,"/KompresProses%d.zip -d ",i+1);
     strcat(command,strcat(temp,nama));
     system(strcat(command,dir));
  }
}
int main(){
  status=2;
  pthread_create(&(tr[0]),NULL,zip,NULL);
  pthread_create(&(tr[1]),NULL,teks,NULL);
  pthread_create(&(tr[2]),NULL,extract,NULL);
  pthread_join(tr[0],NULL);
  pthread_join(tr[1],NULL);
  pthread_join(tr[2],NULL);
}
