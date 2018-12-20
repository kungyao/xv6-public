#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
	//chmod -r u filename uid group
	if(argc < 5){
		printf(1,"Specify your permission Ex : chomd -r u filename\n");
		exit();
	}
	
	int fd;
	char* path = argv[3];
	
	fd = open(path , O_RDWR);
	if(fd < 0){
		printf(2,"Open failed!\n");
		exit();
	}
	struct stat st;
	
	if(fstat(fd, &st) < 0) {
        	printf(2, "chmod: cannot stat %s\n", path);
        	close(fd);
        	exit();
        }
	
	if(atoi(argv[argc-3])!=0 && atoi(argv[argc-3])!=st.ownerid){
	        printf(2, "chmod: No permission\n");
        	close(fd);
        	exit();
	}
	//取得檔案權限
	uint permission = st.permission;
	
	// rwx r-x r--
	//	u   g   o
	
	if(strcmp(argv[2] , "u") == 0){//檔案持有者權限	
		//處理持有者執行
		if(strcmp(argv[1],"-x") == 0 && (0x40&permission)){
			chmod(path,0x40 ^ permission);
		}
		else if(strcmp(argv[1],"+x") == 0 && !(0x40&permission)){
			chmod(path,0x40 ^ permission);
		}
		//處理持有者寫入
		else if(strcmp(argv[1],"-w") == 0 && (0x80&permission)){
			chmod(path,0x80 ^ permission);
		}
		else if(strcmp(argv[1],"+w") == 0 && !(0x80&permission)){
			chmod(path,0x80 ^ permission);
		}
		//處理持有者讀取
		else if(strcmp(argv[1],"-r") == 0 && (0x100&permission)){
			chmod(path,0x100 ^ permission);
		}
		else if(strcmp(argv[1],"+r") == 0 && !(0x100&permission)){
			chmod(path,0x100 ^ permission);
		}
	}
	else if(strcmp(argv[2] , "g") == 0){//群組權限
		//處理群組執行
		if(strcmp(argv[1],"-x") == 0 && (0x8&permission)){
			chmod(path,0x8 ^ permission);
		}
		else if(strcmp(argv[1],"+x") == 0 && !(0x8&permission)){
			chmod(path,0x8 ^ permission);
		}
		//處理群組寫入
		else if(strcmp(argv[1],"-w") == 0 && (0x10&permission)){
			chmod(path,0x10 ^ permission);
		}
		else if(strcmp(argv[1],"+w") == 0 && !(0x10&permission)){
			chmod(path,0x10 ^ permission);
		}
		//處理群組讀取
		else if(strcmp(argv[1],"-r") == 0 && (0x20&permission)){
			chmod(path,0x20 ^ permission);
		}
		else if(strcmp(argv[1],"+r") == 0 && !(0x20&permission)){
			chmod(path,0x20 ^ permission);
		}
	}
	else if(strcmp(argv[2] , "o") == 0){//其他人權限
		//處理其他人執行
		if(strcmp(argv[1],"-x") == 0 && (0x1&permission)){
			chmod(path,0x1 ^ permission);
		}
		else if(strcmp(argv[1],"+x") == 0 && !(0x1&permission)){
			chmod(path,0x1 ^ permission);
		}
		//處理其他人寫入
		else if(strcmp(argv[1],"-w") == 0 && (0x2&permission)){
			chmod(path,0x2 ^ permission);
		}
		else if(strcmp(argv[1],"+w") == 0 && !(0x2&permission)){
			chmod(path,0x2 ^ permission);
		}
		//處理其他人讀取
		else if(strcmp(argv[1],"-r") == 0 && (0x4&permission)){
			chmod(path,0x4 ^ permission);
		}
		else if(strcmp(argv[1],"+r") == 0 && !(0x4&permission)){
			chmod(path,0x4 ^ permission);
		}
	}	
	
	printf(1,"chmod successfully\n");
	close(fd);
	exit();
}
