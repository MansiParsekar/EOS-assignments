// int stat(const char *pathname, struct stat *statbuf)
//		arg1 - path of file or directory
//		arg2 - pointer to the variable of struct stat
//		returns - 0 on success or -1 on failure


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>


int main(int argc, char *argv[])
{

	char *filepath;
	struct stat st;

	if(argc != 2)
	{
		printf("File path is not mentioned .. \n");
		printf("Run as : %s <file path>\n", argv[0]);
		exit(1);
	}

	filepath = argv[1];
	int ret = stat(filepath,&st);
	if (ret==-1)
	{
		printf("stat() is failed \n");
		exit(ret);
	}

	printf("filename = %s\n", filepath);
	printf("inode = %lu\n",st.st_ino);
	printf("mode = %u\n",st.st_mode);
	printf("nlink = %lu\n",st.st_nlink);
	printf("size = %lu\n", st.st_size);

	return 0;
}






