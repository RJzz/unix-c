#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define INIT_NUMBER 100
int main() {
    //ipv4
    struct sockaddr_in ipV4;
    struct sockaddr_in6 ipV6;
    while(1) {
        char *input = (char *)malloc(sizeof(char) * INIT_NUMBER);
        printf("Please input your IP address : ");
        scanf("%s", input);
        //重新分配
        int len = strlen(input);
        if(INIT_NUMBER - len > 10) {
            realloc(input, sizeof(char) * (len + 1));
        }
        //判断是否是ipv4
        // if(sscanf(input, "%u.%u.%u.%u", &outtmp[0], &outtmp[1], &outtmp[2], &outtmp[3]) == 4) {

        // 
        //ipv4
        if(inet_pton(AF_INET, input, &ipV4.sin_addr.s_addr)) {
            printf("Yout IPV4 address is : 0x%X\n", ntohl(ipV4.sin_addr.s_addr));
        }else if(inet_pton(AF_INET, &input, ipV4.sin_addr.s_addr) == -1) {
            printf("ipv4 error");
        }else { //指定的不是一个有效的IPV4格式,检测一下是否式IPV6
            if(inet_pton(AF_INET6, input, &ipV6.sin6_addr)) {
                printf("Your IPV6 address is : 0x");
                    //printf("%x", ntohl(ipV6.sin6_addr));
                //输出ipv6
                int i = 0;
                for(i; i < 8; ++i) {
                    printf("%X", ntohs(ipV6.sin6_addr.s6_addr[i]));
                }
                printf("\n");
            }else if(inet_pton(AF_INET6, input, &ipV6.sin6_addr.s6_addr) == 0) {
                printf("Error input\n");
            }else {
                printf("ipv6 error");
            }
        }
        free(input);
    }
    return 0;
}
