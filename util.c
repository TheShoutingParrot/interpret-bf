#include "interpret-bf.h"

void die(const char *fmt, ...) {
	va_list vargs;

	va_start(vargs, fmt);
	vfprintf(stderr, fmt, vargs);

	va_end(vargs);

	if(*(fmt+strlen(fmt)-1) == ':') {
		fputc(' ', stderr);
		perror(NULL);
	}

	else
		fputc('\n', stderr);

	exit(1);
}
