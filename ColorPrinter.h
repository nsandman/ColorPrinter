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

// Everything with a fixed number of args is a macro, cuz space = saved. Yay!
// a = message, b = color
#define cputs(a, b)     printf("\033[0;%dm%s\033[0m\n", b, a)
#define cputchar(a, b)  printf("\033[0;%dm%c\033[0m", b, a)

// c = the stream to write to, the rest of the variables are as above
#define fcputs(a, b, c) fprintf(c, "\033[0;%dm%s\033[0m", b, a)
#define fcputc(a, b, c) fprintf(c, "\033[0;%dm%c\033[0m", b, a)
#define cputc(a, b, c)  fcputc(a, b, c) // Same as fcputc() 

int cprintf(unsigned char color, const char *fmt, ...) {
	printf("\033[0;%dm", color);
	va_list args;
	va_start(args, fmt);
	int charsWritten = vfprintf(stdout, fmt, args);
	va_end(args);
	printf("\033[0m");
	return charsWritten;
}

int fcprintf(void *stream, unsigned char color, const char *fmt, ...) {
	fprintf(stream, "\033[0;%dm", color);
	va_list args;
	va_start(args, fmt);
	int charsWritten = vfprintf(stream, fmt, args);
	va_end(args);
	fputs("\033[0m", stream);
	return charsWritten;
}

#endif