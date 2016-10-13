#include <stdio.h>
#define MAXDATA 1024
int main() {
    FILE *input = fopen("freedos-img.tar.gz", "r");
    if(input == NULL) {
        perror("text.txt");
        exit(1);
    }
    FILE *output = fopen("output.tar.gz", "w");
    if(output == NULL) {
        perror("output.txt");
        exit(1);
    }

    char buffer[MAXDATA];
    while(fgets(buffer, MAXDATA, input) != NULL) {
        fputs(buffer, output);
    }
    return 0;
}
