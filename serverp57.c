#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 10000
#define BACKLOG 5
#define MAXDATASIZE 1000
void process_cli(int connfd, struct sockaddr_in client);

int main() {
    int listenfd, connfd;
    pid_t pid;
    struct sockaddr_in server;
    struct sockaddr_in client;
    
    int len;
    //tcp都是一个套路，首先获取监听套接字，然后设置socket为可重用的，之后开始对结构进行初始化，服务端绑定监听套接字
    //绑定成功之后就开始监听套接字，等待客户端进行连接，当客户端连接服务器的时候，调用accept进行三次握手
    //三次握手成功之后则获取到一个连接套接字。之后便可以进行数据的传输
    
    //get listenfd socket
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Create socket failed");
        exit(1);   
    }
    
    //set socket option as reuse
    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    //将32位的长整形数从主机字节序转换成网络字节序，h表示主机, to ,n表示网络,l表示长整形,如果是s的话表示16位的短整形数
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind error");
        exit(1);
    }
    //监听的时候需要设置最大的监听数量
    if((listen(listenfd, BACKLOG)) == -1) {
        perror("listen error");
        exit(1);
    }
    
    
    len = sizeof(client);;
    while(1) {
        if((connfd = accept(listenfd, (struct sockaddr *)&client, &len)) == -1) {
            perror("accept failed");
            exit(1);
        }
        //pid大于0的话，表明当前的是父进程,需要关闭连接套接字，重新进入accept的状态
        if((pid = fork()) > 0) {
            close(connfd);
            continue;
        }//pid为0的时候表明是子进程,这个时候就可以进行相关的数据传输处理操作,在这之前需要关闭监听套接字
        else if((pid == 0)) {
            close(listenfd);
            process_cli(connfd, client);
            exit(0);
        }else{
            perror("fock failed");
            exit(0);
        }
    }
    close(listenfd);
    
    //开始绑定
    
    
    return 0;
}

void process_cli(int connfd, struct sockaddr_in client) {
    int num;
    char recvbuf[MAXDATASIZE], sendbuf[MAXDATASIZE], cli_name[MAXDATASIZE];
    printf("You get a connection from %s", inet_ntoa(client.sin_addr));
    num = recv(connfd, cli_name, MAXDATASIZE, 0);
    if(num == 0) {
        close(connfd);
        perror("disconnection");
        return;
    }
    cli_name[num - 1] = '\0';
    printf("Client's  name is :  %s", cli_name);
    //不断地读取客户端发送过来的数据
    while(num = recv(connfd, recvbuf, MAXDATASIZE, 0)) {
        recvbuf[num - 1] = '\0';
        printf("Receieved client(%s) message : %s", cli_name, recvbuf);
        int i;
        for(i; i < num; ++i) {
            if((recvbuf[i] > 'a' && recvbuf[i] < 'z') || 
                (recvbuf[i] < 'Z' && recvbuf[i] > 'A')) {
                    recvbuf[i] += 3;
                    if(recvbuf[i] > 'z' || recvbuf[i] > "Z" ) {
                        recvbuf[i] -= 26;
                    }
        
                }           
                sendbuf[i] = recvbuf[i];
        }
        sendbuf[num - 1] = '\0';
        send(connfd, sendbuf, MAXDATASIZE, 0);
    }
    close(connfd);
}
