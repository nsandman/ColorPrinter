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

typedef unsigned char color_t;

// How many ANSI colors offset the xterm-256 ones?
#define ANSI_OFFSET 	15
color_t colors[] = {
	// ANSI colors
	31, 32, 33, 36, 37, 91, 92, 93, 96, 97,
	// blue
	94, 34,
	//purple
	34, 25,
	// pink
	35, 95,
	// 256-color
	208, 237, 64, 89
};

// define the colors as macros
#define red    					0
#define green  					1
#define yellow 					2
#define cyan   					3
#define light_gray				4

#define bright_red 				5
#define bright_green			6 
#define bright_yellow			7
#define light_blue				8
#define white					9

#ifndef NO256
#	define orange 				ANSI_OFFSET + 1
#	define dark_gray			ANSI_OFFSET + 2
#	define olive				ANSI_OFFSET + 3
#	define magenta				ANSI_OFFSET + 4
#endif /* NO256 */

/*
 * On Macs, the colors are weird and screwed up.
 * Blue looks like purple.
 * Purple looks like pink.
 * So just add pink while we're at it.
 * However, it's also possible to manually fix the colors
 * using Terminal preferences, so if the user has, they can
 * define MAC_OVERRIDE at compile time with gcc (or probably clang)
 */
#if defined(__APPLE__) && !defined(MAC_OVERRIDE)
#	define blue 				10
#	define purple				12
#	define pink 				14
#else
#	define blue 				11
#	define purple 				13
#	define pink 				15
#endif /* __APPLE__ && !MAC_OVERRIDE */

// If you're a Brit and you keep forgetting about "gray" vs "grey", here
#ifdef UK
#	define light_grey			light_gray
#	define dark_grey			dark_gray
#	undef  light_gray
#	undef  dark_gray
#endif /* UK */

void startprint(color_t, FILE*);
int  cfputs(const char*, color_t, FILE*);
int  cfnputs(const char*, color_t, size_t, FILE*);
int  cfprintf(FILE*, color_t, const char*, ...);
int  cfnprintf(FILE*, color_t, size_t, const char*, ...);

#define endprint(s) fputs("\033[0m", s)		// Reset to default color
void startprint(color_t c, FILE *s) {
	if (c <= ANSI_OFFSET)
		fprintf(s, "\033[0;%dm", colors[c]);
	else
		fprintf(s, "\033[38;5;%dm", colors[c]);	
}

int cfputs(const char *msg, color_t c, FILE *s) {
	startprint(c, s);
	fputs(msg, s);
	endprint(s);
	return 0;
}

int cfnputs(const char *m, color_t c, size_t n, FILE *s) {
	startprint(c, s);
	for(; n > 0 && *m != '\0'; m++, --n)
		putc(*m, s);
	endprint(s);
	return 0;
}

int cfprintf(FILE *s, color_t c, const char *fmt, ...) {
	startprint(c, s);
	va_list arg;
	va_start(arg, fmt);
	int w = vfprintf(s, fmt, arg);
	va_end(arg);
	endprint(s);
	return w;
}

int cnfprintf(FILE *s, color_t c, size_t n, const char *fmt, ...) {
	char buf[n];
	va_list arg;
	va_start(arg, fmt);
	int w = vsnprintf(buf, n, fmt, arg);
	va_end(arg);
	cfputs(buf, c, s);
	return w;
}

// m = msg, c = color, s = stream
#define cputc(m, c, s)			startprint(c, s); putc(m, s); endprint(s)
#define cfputc(a, b, c)			cputc(a, b, c)
#define cputchar(m, c)			cputc(m, c, stdout)

#define cputs(m, c) 			cfputs(m, c, stdout); \
								putchar('\n');

#define cnputs(m, c, n) 		cfnputs(m, c, n, stdout); \
								putchar('\n');

#define cprintf(c, f, ...) 		cfprintf(stdout, c, f, __VA_ARGS__)
#define cnprintf(c, n, f, ...)	cnfprintf(stdout, c, n, f, __VA_ARGS__)

#endif /* _COLORPRINTER_H */