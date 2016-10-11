#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define INIT_DATA 1000
int main() {
	char *a = (char *)malloc(sizeof(char) * INIT_DATA);
    struct sockaddr_in client;
    while(1) {
        printf("Please input an IP address : ");
        scanf("%s", a);
        int len = strlen(a);
        if(INIT_DATA - len > 10) {
            realloc(a, sizeof(char) * (len + 1));
        }

	    if((inet_aton(a, (struct in_addr *)&client.sin_addr)) == 1) {
		    printf("Your IP address is : 0x%x\n",ntohl(client.sin_addr.s_addr));
	    }else{
            printf("Error\n");
        }
    }
	return 0;
}
