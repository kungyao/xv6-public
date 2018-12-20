#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
	if(argc<6){
		printf(1,"chown : Specify your permission Ex : chown filename userID\n");
		exit();
	}
	int fd = open(argv[1],O_RDONLY);
	struct stat st;
	if(fstat(fd,&st)<0){
		printf(1,"chown : Can't stat %s\n", argv[1]);
		exit();
	}
	if(atoi(argv[argc-3])!=0 && atoi(argv[argc-3])!=st.ownerid){
	        printf(2, "chown: No permission\n");
        	close(fd);
        	exit();
	}
	for (int i=0;argv[2][i]!='\0'; i++)
		if (argv[2][i]>57||argv[2][i]<48)
        {
            printf (1,"Entered input is not a number\n");
            exit();
        }
	chown(argv[1],atoi(argv[2]));
	printf(1,"chown successfully\n");
	exit();
}
