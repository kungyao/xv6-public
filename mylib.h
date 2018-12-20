

//check duplicate
int CheckDup(int fd,char* newUser){
  int idCount = -1;
  //int n = 0;
  char ch[1];
  int flag = 1;
  while(flag==1){
   flag = 0;
   //id
   while(read(fd,ch,sizeof(ch)) > 0){
    flag = 1;
    if(ch[0]==';')
     break;
   }
   if(flag==0)
    break;
   idCount++;
   //name
   int length = 0;
   char otherName[11];
   while(read(fd,ch,sizeof(ch)) > 0){
    //printf(1,"%c",ch[0]);
    if(ch[0]==';')
     break;
    otherName[length] = ch[0];
    length++;
   }
   otherName[length] = '\0';
   //printf(1,"%s",otherName);
   if(strlen(otherName)==strlen(newUser)){
    for(int i=0;i<length;i++){
     if(newUser[i]==0)
      break;
     if(newUser[i]!=otherName[i])
      break;
     if(i==length-1)
      return -1;
    }
   }

   //password
   while(read(fd,ch,sizeof(ch))){
    if(ch[0]==';')
     break;
   }
  }
  return idCount;
}

//check account
int checkAccount(int fd,char *name,char *password){
 int length;
 if(name[strlen(name)-1]=='\n')
  name[strlen(name)-1]='\0';
 if(password[strlen(password)-1]=='\n')
  password[strlen(password)-1]='\0';
 //printf(1,"%s %d %s %d\n",name,strlen(name),password,strlen(password));
 //printf(1,"%d %d\n",strlen(name),strlen(password));
  int idCount = -1;
  char ch[1];
  int flag = 1;
  int nameHit = -1;
  while(flag==1){
   flag = 0;
   //id
   //printf(1,"read id\n");
   while(read(fd,ch,sizeof(ch)) > 0){
    flag = 1;
    if(ch[0]==';')
     break;
   }
   if(flag==0)
    break;
   idCount++;
   //name
   //printf(1,"read name\n");
   length = 0;
   char dataName[11];
   while(read(fd,ch,sizeof(ch)) > 0){
    if(ch[0]==';')
     break;
    dataName[length] = ch[0];
    length++;
   }
   dataName[length] = '\0';
   if(strlen(dataName)==strlen(name)){
    for(int i=0;i<length;i++){
     if(name[i]==0)
      break;
     if(name[i]!=dataName[i])
      break;
     if(i==length-1)
      nameHit = 1;
    }
   }
   //password
   //printf(1,"read password\n");
   length = 0;
   char dataPassword[11];
   while(read(fd,ch,sizeof(ch)) > 0){
    if(ch[0]==';')
     break;
    if(nameHit==1){
     dataPassword[length] = ch[0];
     length++;
    }
   } 
   dataPassword[length] = '\0';
   //printf(1,"%s\n",dataPassword);
   if(nameHit==1){
    if(strlen(dataPassword)==strlen(password)){
     for(int i=0;i<length;i++){
      if(password[i]==0)
       break;
      if(password[i]!=dataPassword[i])
       break;
      if(i==length-1)
       return idCount;
     }
     //password error
     return -1;
    }
    else{
     //password error
     return -1;
    }
   }
  }
 return -1;
}


//turn int id to string
void itos(int num,char *intnum,int offset){
 int i=0;
 num += offset;
 if(num==0)
  intnum[i++] = 0+48;
 else{
  while(num>0){
   intnum[i] = num%10+48;
   num/=10;
   i++;
  }
  char tmp;
  for(int length = 0;length < i/2;length++){
   tmp = intnum[length];
   intnum[length] = intnum[i-length-1];
   intnum[i-length-1] = tmp;
  }
 }
 intnum[i] = '\0';
}
