	#include <stdio.h>
	#include <strings.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#define PORT 40000
	#define MAXDATASIZE 100
	#define BACKLOG 1
	int main() {
		int sockfd;
		struct sockaddr_in server;
		struct sockaddr_in client;
		socklen_t addrlen;
		if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			perror("socket error");
			exit(1);
		}
		int num;
		char buf[MAXDATASIZE];
		/*set socket opt*/
	
		bzero(&server, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		if((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) == -1) { 
			perror("bind error");
			exit(1);
		}
		addrlen = sizeof(client);
		while(1) {
			num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (struct sockaddr *)&client, &addrlen);
			if(num < 0) {
				perror("num error");
				exit(1);
			}
			buf[num] = '\0';
		
			printf("fuck");
			sendto(sockfd, "welcome", 8, 0, (struct sockaddr *)&client, addrlen);
			if(!strcmp(buf, "bye")) {
				break;
			}	
		}

		close(sockfd);
	
	}
