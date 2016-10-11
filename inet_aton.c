    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define INITDATA 1000
    char* changeB(unsigned int primary);
    int main() {
        unsigned int temp[4] = {0};
        unsigned int output;
        //声明一个字符串指针
        char *input;
        int len;
        input = (char *)malloc(sizeof(char) * INITDATA);
        while(1) {
            printf("Please input an IP address : ");
            scanf("%s", input);
            len = strlen(input);
            //如果分配的内存太大了则可以使用relloc重新分配
            if(INITDATA - len > 10) {
                realloc(input, sizeof(char) * (len + 1));
            }
            if(input == NULL) {
                printf("%s", "Out of memory!\n");
                exit(1);
            }
            if(sscanf(input, "%d.%d.%d.%d", &temp[0], &temp[1], &temp[2], &temp[3]) == 4) {
                //输出转化之后的二进制数
                //printf("%s\n", changeB(temp[1]));
                //printf("转换之后的二进制:\n%d%s%s%s", atoi(changeB(temp[0])), changeB(temp[0]), changeB(temp[0]),changeB(temp[0]));
                output = (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | (temp[3]);
                printf("Your IP address is : 0x%x\n", output);
                //printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
            }else {
                printf("input a error data\n");
            }
        }

        return 0;
        // prinf()
    }

    char* changeB(unsigned int primary) {
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
        return result;
    }
