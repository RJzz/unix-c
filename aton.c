#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#define MAXDATA 20
#define SUBMAXDATA 4
unsigned int changeB(unsigned int primary);
//程序读入一个点分十进制的ip地址，将其转化为二进制数，并在屏幕上用16进制表示出来
int main() {
	unsigned int temp[4] = { 0 };
	unsigned int output = 0;
	//定义一个char *，接受输入的参数
	char input[MAXDATA];

	char *temp1;
	char *temp2;
	char *temp3;
	char *temp4;

	scanf("%s", input);
	int len = strlen(input);
    //打印字符串的长度
    printf("lens = %d\n", len);
	//记录已经处理了多少个
	int count = 0;
	int index = 0;
	int i = 0;
    char* position = input;
	for (i; i < len; ++i) {
		if (input[i] != '.') {
			index++;
            if (i == (len - 1)) {
                temp4 = malloc(index);                
			    strncpy(temp4, position, index);
                temp[3] = atoi(temp4);
                temp[3] = changeB(temp[3]);
                printf("第四个temp : %s\n", temp4);
		    }
		}
		else {
			switch (count) {
			    case 0:
                    temp1 = malloc(index);
				    strncpy(temp1, position, index);
					// temp1[SUBMAXDATA - 1] = '\0';
                    printf("第一个temp : %s\n", temp1);
                    temp[0] = atoi(temp1);
                    temp[0] = changeB(temp[0]);
                    printf("第一个temp整型 : %d\n", temp[0]);
				    break;
			    case 1:
                    temp2 = malloc(index);
                    printf("测试当count为2的时候%c\n", *(input + i));
				    strncpy(temp2, position, index);
                    temp[1] = atoi(temp2);
                    temp[1] = changeB(temp[1]);
                    printf("第二个temp : %s\n", temp2);
				    break;
			    case 2:
                    temp3 = malloc(index);
				    strncpy(temp3, position, index);
                    temp[2] = atoi(temp3);
                    temp[2] = changeB(temp[2]);
                    printf("第三个temp : %s\n", temp3);
				    break;
			    default:
				    break;
			}
            position += (index + 1);
			index = 0;
			count++;
		}

	}
	printf("%s\n", input);
	//int t = strlen(temp1);
	//printf("%d", t);
    // char* hehe = "hehe";
    // printf("%c", hehe[1]);
    // hehe[1] = 'w';
    // printf("%c", hehe[1]);
    int j = 0;
    for(j; j < 4; ++j) {
        printf("%d\n", temp[j]);
    }
    output = (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | (temp[3]);
    ntohl(output);
    printf("%x", output);
    changeB(100);
	return 0;
}

unsigned int changeB(unsigned int primary) {
    int remainder = 0;
    char result[] = "00000000";
    remainder = primary % 2;
    int index = 7;
    //当primary还能够够2除的时候
    while(primary) {
        if((primary % 2) == 1) {
            result[index] = '1';
        }
        primary /= 2;
        index--;
        //printf("%s\n", result);
    }
    int out = atoi(result);
    //printf("%d", out);
    return out;
}

