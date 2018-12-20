#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "mylib.h"

#define MAXLEN 20

int main(void){
 int datafd;
 //int nowfd;
 char *passwd;
 char *name;
 //char namebuf[MAXLEN] = "00000000000000000000";
 //char passwdbuf[MAXLEN] = "00000000000000000000";
 int userNow = 0;
 int isLogin = 1;
 int pid = 0;
 while(isLogin>0){
    printf(1,"Username: ");
    name = gets("0000000000",MAXLEN);
    printf(1,"Password: ");
    passwd = gets("1111111111",MAXLEN);
    dup(0);  // stdout
    dup(0);  // stderr
    if((datafd = open("/.userdata",O_RDONLY)) < 0){
     printf(1, "login: cannot open userdata\n");
     exit();
    }
    if((userNow=checkAccount(datafd,name,passwd))>=0){
      isLogin = 0;
      //nowfd = open("/.usernow",O_WRONLY);
      printf(1,"Welcome %s\n",name);
	pid = fork();
	if(pid < 0){
	  printf(1, "login: fork failed\n");
	  exit();
	}
	else if(pid==0){
          //user id
          char uid[11],groupid[11];
          itos(userNow,uid,0);
 	  itos(0,groupid,0);
	  //printf(1,"%d %s %s\n",userNow,uid,groupid);
	  char * data[] = {uid,name,groupid,0};
	  exec("sh", data);
	  printf(1, "login: exec sh failed\n");
	  exit();
	}
      //if(write(nuID,name,strlen(name))<0){
      //  printf(1, "login: error\n");
      //  exit();
      //}
      //close(nuID);
    }
    else{
     printf(1,"login fail\n");
    }
 }
 wait();
 exit();
}
