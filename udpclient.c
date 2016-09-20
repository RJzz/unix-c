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
	#define PORT 40000
	#define MAXDATASIZE 100
	int main(int argc, char *argv[]) {
		extern int errno;
		int socketfd, num;
		char buf[MAXDATASIZE];
		struct hostent *he;
		struct sockaddr_in server,peer;
		
		if(argc != 3) {
			printf("Usage : %s <IP Address\n", argv[1]);
			exit(1); 
		}
		if((he = gethostbyname(argv[1])) == NULL) {
			printf("gethostbyname error");
			exit(1);
		}
		
		if((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			printf("socket() error");
			exit(1);
		}
		
		
		bzero(&server, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr = *((struct in_addr *)he->h_addr);
		sendto(socketfd, argv[2], strlen(argv[2]), 0, 
			(struct sockaddr *)&server, sizeof(server));
		socklen_t len;
		len = sizeof(server);
		while(1) {
			if((num = recvfrom(socketfd, buf, MAXDATASIZE, 0, 
				(struct sockaddr *)&peer, &len)) == -1) {
				perror("num error");
				exit(1);			
			}
			if(len != sizeof(server) || memcmp((const void *)&server, 
				(const void *)&peer, len) != 0) {
				perror("len error");
				continue;
			}
			buf[num] = '\0';
			printf("server message: %s\n", buf);
			if(!strcmp(buf, "bye")) {
				break;
			}
		} 



		close(socketfd);
	} 
