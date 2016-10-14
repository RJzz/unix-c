	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <arpa/inet.h>
	#define PORT 40000
	#define MAXDATASIZE 1024
	int main(int argc, char *argv[]) {
		extern int errno;
		int socketfd, num;
		char buf[MAXDATASIZE];
		struct hostent *he;
		struct sockaddr_in server;
		
		if(argc != 3) {
			printf("Usage : %s <IP Address\n", argv[1]);
			exit(1); 
		}
		if((he = gethostbyname(argv[1])) == NULL) {
			printf("gethostbyname error");
			exit(1);
		}
		
		if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			printf("socket() error");
			exit(1);
		}
		
		
		bzero(&server, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr = *((struct in_addr *)he->h_addr);
		if((connect(socketfd, (struct sockaddr *)&server, sizeof(server))) == -1) {
			perror("connect error");
		 	printf("%s\n",strerror(errno));
			exit(1);
		} 
		//p指向最后一个/出现的位置
		char *p = rindex(argv[2], '/');
		FILE *input = NULL;
		//去掉/
		if(p != NULL) {
			p++;
			input = fopen(argv[2], "rb");
			//将文件名传过去
			send(socketfd, p, strlen(p), 0);
			printf("%s is sending", p);
		}else{
			input = fopen(argv[2], "rb");
			//将文件名传过去
			send(socketfd, argv[2], strlen(argv[2]), 0);
			printf("%s is sending", argv[2]);
		}
		
		if(input == NULL) {
			perror("file open failed");
			exit(1);
		}
		//实际读取到的个数
		int realRead = 0;

		while((realRead = fread(buf, sizeof(char), MAXDATASIZE, input)) > 0) {
			send(socketfd, buf, strlen(buf), 0);
			printf(".");
		}
		printf("\nsend over");
		close(socketfd);
		fclose(input);
	} 
