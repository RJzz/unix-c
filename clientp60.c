#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT 10000
#define MAXDATASIZE 100

void process(FILE *fp, int sockfd);
char* getMessage(char* sendline, int len, FILE* fp);

int main(int argc, char *argv[]) {
    int sockfd;

    struct sockaddr_in server;
    struct hostent *he;

    if(argc != 2) {
        perror("argv!=2");
        exit(1);
    }
    if((he = gethostbyname(argv[1])) == NULL) {
        perror("gethostbyname failed");
        exit(1);
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(1);
    }

    //开始做初始化操作
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    //初始化操作结束时候可以开始连接服务器
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect failed");
        exit(1);
    }
    process(stdin, sockfd);
    close(sockfd);
    
    
    
    return 0;
}

void process(FILE *fp, int sockfd) {
    char sendline[MAXDATASIZE], recvline[MAXDATASIZE];
    int num;
    printf("connected to server \n");
    printf("input client's name : ");
    if(fgets(sendline, MAXDATASIZE, fp) == NULL) {
        perror("fgets failed");
        return;
    }
    send(sockfd, sendline, strlen(sendline), 0);
    while(getMessage(sendline, MAXDATASIZE, fp) != NULL) {
        //send函数第一个为套接字，第二个为字符串，第三个为长度，第四个为选项，一般默认为0
        send(sockfd, sendline, strlen(sendline), 0);
        if((num = recv(sockfd, recvline, MAXDATASIZE, 0)) == NULL) {
            perror("server terminated.\n");
            return;
        }
        recvline[num] = '\0';
        printf("server's message is : %s", recvline);

    }
    printf("Exit");
}

char* getMessage(char* sendline, int len, FILE *fp) {
    printf("input to server :");
    return (fgets(sendline, MAXDATASIZE, fp));
}
