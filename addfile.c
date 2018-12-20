#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
	int fd;
	if(argc < 5){
		printf(1,"Specify filename Ex.: addfile 'filename'\n");
		exit();
	}
	
	fd = open(argv[1] , O_CREATE);
	if(fd >= 0){
		printf(1,"addfile %s successed\n" , argv[1]);
	}else{
		printf(1,"addfile %s failed\n" , argv[1]);
		exit();
	}
	close(fd);
	fd = open(argv[1] , O_RDWR);
	struct stat st;
	
	if(fstat(fd, &st) < 0) {
        	printf(2, "addfile: cannot stat %s\n", argv[1]);
        	close(fd);
        	exit();
        }
	
	//uint permission = st.permission;
	chown(argv[1],atoi(argv[argc-3]));
	chgrp(argv[1],atoi(argv[argc-2]));
	chmod(argv[1],0x1c0);
	close(fd);
	exit();
}

