#include <stdio.h>
#define MAXDATA 1024
int main() {
    FILE *input = fopen("freedos-img.tar.gz", "rb");
    if(input == NULL) {
        perror("text.txt");
        exit(1);
    }
    FILE *output = fopen("output.tar.gz", "wb+");
    if(output == NULL) {
        perror("output.txt");
        exit(1);
    }

    char buffer[MAXDATA];
   // while(fgets(buffer, MAXDATA, input) != NULL) {
     //   fputs(buffer, output);
    //}
    int realRead = 0;
    while((realRead = fread(buffer, sizeof(char), MAXDATA, input)) > 0) {
	fwrite(buffer, sizeof(char), realRead, output);	    
    }
	fclose(input);
	fclose(output);
    return 0;
}
