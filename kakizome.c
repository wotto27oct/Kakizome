//error: unnown type name '__off64_t'
//solution by https://stackoverflow.com/questions/22663897/unknown-type-name-off64-t
#define __USE_LARGEFILE64
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static char *p;

__attribute__((noreturn)) static void error(char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

static void skip(){
	while (isspace(*p))
		p++;
}

static int eval(){
	skip();
	if (isdigit(*p)){
		int val = *p++ - '0';
		while (isdigit(*p))
			val = val * 10 + (*p++ - '0');
		return val;
	}

	if (strchr("+-*/", *p)){
		int op = *p++;
		int x = eval();
		int y = eval();
		switch (op){
		case '+': return x + y;
		case '-': return x - y;
		case '*': return x * y;
		case '/': return x / y;
		}
	}
	error("invalid character: %c", *p);
}

int main(int argc, char **argv){
	p = argv[1];
	while(*p)
		printf("%d\n", eval());
	return 0;
}
