#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "mylib.h"

//username length <= 8
//password length <=12
int main(int argc, char *argv[]){
 if(argc<5){
   printf(2, "adduser : Error\n");
   exit();
 }
 int fd =0;
 //int newID = 0
 char *userName = argv[1];
 //char *password = argv[2];
 if((fd = open("/.userdata",O_RDONLY))<0){
  printf(1,"No File\n");
  exit();
 }
 int id = 0;
 if((id = CheckDup(fd,userName)) < 0){
  printf(1, "adduser : Duplicate user\n");
  close(fd);
  exit();
 }
 close(fd);
 if((fd = open("/.userdata", O_RDWR)) < 0){
  printf(1,"adduser: can't open userdata\n");
  exit();
 }

 char writeBuf[64],words[512],tmpID[10];
 if(read(fd,words,sizeof(words))==0){
  printf(1,"adduser: Error to add\n");
  exit();
 }
 itos(id,tmpID,0);	//id to string
 strcpy(writeBuf,tmpID);
 strcpy(writeBuf+strlen(writeBuf),";");
 strcpy(writeBuf+strlen(writeBuf),argv[1]);
 strcpy(writeBuf+strlen(writeBuf),";");
 strcpy(writeBuf+strlen(writeBuf),argv[2]);
 strcpy(writeBuf+strlen(writeBuf),";");
 //printf(1,"%s\n",words);
 //printf(1,"%s\n",writeBuf);

 if(write(fd,writeBuf,strlen(writeBuf)) < 0){
  printf(1,"adduser: can't open userdata\n");
  close(fd);
  exit();
 }

 printf(1, "Adduser Complete\n");
 close(fd);
 exit();
}
