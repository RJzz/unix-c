	#include <stdio.h>
	#include <unistd.h>
	#include <strings.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <arpa/inet.h>
	#define PORT 1234
	#define MAXDATASIZE 100
	int main(int argc, char *argv[]) {
		extern int errno;
		int socketfd, num;
		char buf[MAXDATASIZE];
		struct hostent *he;
		struct sockaddr_in server;
		
		if(argc != 2) {
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
		server.sin_port = PORT;
		server.sin_addr = *((struct in_addr *)he->h_addr);
		if((connect(socketfd, (struct sockaddr *)&server, sizeof(server))) == -1) {
			perror("connect error");
		 	printf("%s\n",strerror(errno));
			exit(1);
		} 
		if((num = recv(socketfd, buf, MAXDATASIZE, 0)) == -1) {
			printf("recv() error");
			exit(1);
		}
		buf[num - 1] = '\0';
		printf("server message: %s\n", buf);
		close(socketfd);
	} 
