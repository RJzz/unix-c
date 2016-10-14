	#include <stdio.h>
	#include <strings.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#define PORT 40000
	#define MAXDATA 1024
	#define BACKLOG 1
	int main() {
		int listenfd, connectfd;
		struct sockaddr_in server;
		struct sockaddr_in client;
		socklen_t addrlen;
		if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket error");
			exit(1);
		}
		
		/*set socket opt*/
		int opt = SO_REUSEADDR;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
		bzero(&server, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		if((bind(listenfd, (struct sockaddr *)&server, sizeof(server))) == -1) { 
			perror("bind error");
			exit(1);
		}
	
		if((listen(listenfd, BACKLOG)) == -1) {
			perror("listen error");
			exit(1);
		}
	
		addrlen = sizeof(client);
		if((connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen)) == -1) {
			perror("accept error");
			exit(1);
		}
		//接收缓冲
		char recvbuf[MAXDATA];
		int num = 0;
		//输出文件
		FILE *output = NULL;
		if(!(num = recv(connectfd, recvbuf, MAXDATA, 0)))  {
			perror("get file name failed");
			exit(1);
		}
		output = fopen(recvbuf, "wb+");
		if(output == NULL) {
			perror("open stream to write failed");
			exit(1);
		}
		printf("starting receive %s from client\n", recvbuf);
		
		while(num = recv(connectfd, recvbuf, MAXDATA, 0) > 0) {
			fwrite(recvbuf, sizeof(char), num, output);
			printf("...");
		}
		printf("\nreceive over");
		close(connectfd);
		close(listenfd);
		fclose(output);
		return 0;
	}
