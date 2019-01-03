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
static int func[26][100];

static int eval(int*);

__attribute__((noreturn)) static void error(char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

static void read_until(char c, char *buf) {
	for (; *p != c; p++, buf++)
		*buf = *p;
	p++;
	*buf = '\0';
}

static void skip(){
	while (isspace(*p))
		p++;
}

static void expect(char c) {
	if (*p != c)
		error("%c expected: %s", c, p);
	p++;
}


static int eval_string(char *code, int *args) {
	char *orig = p;
	p = code;
	int val = eval(args);
	p = orig;
	return val;
}

static int eval(int *args){
	skip();

	// Function parameter
	if ('a' <= *p && *p <= 'z')
		return args[*p++ - 'a'];

	// Function definition
	if ('A' <= *p && *p <= 'Z' && p[1] == '[') {
		char name = *p;
		p += 2;
		read_until(']', func[name - 'A']);
		return eval(args);
	}

	// Function application
	if ('A' <= *p && *p <= 'Z' && p[1] == '(') {
		int newargs[26];
		char name = *p;
		p += 2;

		int i = 0;
		skip();
		for (skip(); *p != ')'; skip())
			newargs[i++] = eval(args);

		expect(')');
		return eval_string(func[name - 'A'], newargs);
	}
	// Literal numbers
	if (isdigit(*p)){
		int val = *p++ - '0';
		while (isdigit(*p))
			val = val * 10 + (*p++ - '0');
		return val;
	}

	// Arithmetic operators
	if (strchr("+-*/", *p)){
		int op = *p++;
		int x = eval(args);
		int y = eval(args);
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
		printf("%d\n", eval(0));
	return 0;
}
