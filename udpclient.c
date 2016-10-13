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
		
		if(argc != 2) {
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
		
		//初始化
		bzero(&server, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);
		server.sin_addr = *((struct in_addr *)he->h_addr);
		while(1) {
			//输入想要发送的数据
			char *text = (char *)malloc(sizeof(char) * MAXDATASIZE);
			printf("Message send to server : ");
			scanf("%s", text);
			sendto(socketfd, text, strlen(text), 0, (struct sockaddr *)&server, sizeof(server));
			socklen_t len;
			len = sizeof(server);
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
			
			if(!strcmp(buf, "bye")) {
				printf("goodbye!");
				//收到别人发的bye之后也要发送一个bye给对方,不然对方就在那里傻等着什么都干不了
				sendto(socketfd, "bye", 3, 0, (struct sockaddr *)&server, sizeof(server));
				break;
			}else {
				printf("Receieve from server : %s\n", buf);
			}
			free(text);
		} 
		close(socketfd);
	} 