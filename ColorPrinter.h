/* 
 * ColorPrinter.h - Noah Sandman
 * This file is licensed under the NSPL
 * (Noah Sandman Public Source License).
 * A copy of the NSPL should have been 
 * provided with this file.
 */

#ifndef _COLORPRINTER_H
#define _COLORPRINTER_H

#include <stdarg.h>
#include <stdio.h>

#define red    31
#define green  32
#define yellow 33
#define blue   34
#define purple 35
#define cyan   36
#define white  37

int strlen(const char*);
int cprintf(unsigned char, const char*, ...);
int cfprintf(void*, unsigned char, const char*, ...);
void cnprintf(unsigned int, unsigned char, const char*, ...);
void cnfputs(const char*, unsigned char, unsigned int, void*);

// Everything with a fixed number of args is a macro, cuz space = saved. Yay!
// a = message, b = color
#define cputs(a, b)     printf("\033[0;%dm%s\033[0m\n", b, a)
#define cputchar(a, b)  printf("\033[0;%dm%c\033[0m", b, a)

// c = the stream to write to, the rest of the variables are as above
#define cfputs(a, b, c) fprintf(c, "\033[0;%dm%s\033[0m", b, a)
#define cfputc(a, b, c) fprintf(c, "\033[0;%dm%c\033[0m", b, a)
#define cputc(a, b, c)  cfputc(a, b, c) // Same as fcputc() 

#define cnputs(a, b, c) cnfputs(a, b, c, stdout); \
						putchar('\n')

// To avoid including ALL of string.h for one function
int strlen(const char *str) {
	int i = 0;
	while(str[++i]);
	return i;
}

int cprintf(unsigned char color, const char *fmt, ...) {
	printf("\033[0;%dm", color);
	va_list args;
	va_start(args, fmt);
	int charsWritten = vfprintf(stdout, fmt, args);
	va_end(args);
	printf("\033[0m");
	return charsWritten;
}

int cfprintf(void *stream, unsigned char color, const char *fmt, ...) {
	fprintf(stream, "\033[0;%dm", color);
	va_list args;
	va_start(args, fmt);
	int charsWritten = vfprintf(stream, fmt, args);
	va_end(args);
	fputs("\033[0m", stream);
	return charsWritten;
}

void cnprintf(unsigned int len, unsigned char color, const char *fmt, ...) {
	printf("\033[0;%dm", color);
	char buf[len];
	va_list args;
  	va_start(args, fmt);
  	vsnprintf(buf, len, fmt, args);
  	fputs(buf, stdout);
  	va_end(args);
  	fputs("\033[0m", stdout);
}

void cnfputs(const char *amsg, unsigned char color, unsigned int len, void *stream) {
	int y = strlen(amsg);
	fprintf(stream, "\033[0;%dm", color);
	for (; len > 0 || len > y; *amsg++, --len)
		putc(*amsg, stream);
	fputs("\033[0m", stream);
}

#endif