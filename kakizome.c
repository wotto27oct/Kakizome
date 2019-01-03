//error: unnown type name '__off64_t'
//solution by https://stackoverflow.com/questions/22663897/unknown-type-name-off64-t
#define __USE_LARGEFILE64
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

static char *p;

static int eval(){
	p++;
	return 0;
}

int main(int argc, char **argv){
	p = argv[1];
	while(*p)
		printf("%d\n", eval());
	return 0;
}
