#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	char *test = argv[1];
	char *p ;
	p = rindex(test, '/');
	if(p == NULL) {

		printf("%s", argv[1]);
	}else {
		p++;
		printf("%s", p);
	}
	char *x = (char *)malloc(sizeof(char) * 100);
	//sscanf(p, "\\%s", &x);
	//p++;
	//printf("%s",  p);
	return 0;


}
