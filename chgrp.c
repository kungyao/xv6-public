#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
	if(argc<6){
		printf(1,"chgrp : Specify your permission Ex : chgrp filename userID\n");
		exit();
	}
	int fd = open(argv[1],O_RDONLY);
	struct stat st;
	if(fstat(fd,&st)<0){
		printf(1,"chgrp : Can't stat %s\n", argv[1]);
		exit();
	}
	if(atoi(argv[argc-3])!=0 && atoi(argv[argc-3])!=st.ownerid){
	        printf(2, "chgrp: No permission\n");
        	close(fd);
        	exit();
	}
	for (int i=0;argv[2][i]!='\0'; i++)
		if (argv[2][i]>57||argv[2][i]<48)
		{
		    printf (1,"chgrp : Entered input is not a number\n");
		    exit();
		}
	chgrp(argv[1],atoi(argv[2]));
	printf(1,"chgrp successfully\n");
	exit();
}
