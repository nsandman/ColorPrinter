/* 
 * ColorPrinter.h - Noah Sandman
 * This file is licensed under the NSPL
 * (Noah Sandman Public Source License).
 * A copy of the NSPL should have been 
 * provided with this file.
 */

#ifndef _COLORPRINTER_H
#define _COLORPRINTER_H

#include <assert.h>
#include <stdarg.h>		// va_list, va_start(), va_end()
#include <stdio.h>		// vfprintf(), vsnprintf(), putc(), fprintf(), fputs()

// define the cross-platform colors as macros
#define red    			31
#define green  			32
#define yellow 			33
#define cyan   			36
#define light_gray		37

#define bright_red 		91
#define bright_green	92 
#define bright_yellow	93
#define light_blue		96
#define white			97

#ifndef NO256
#	define orange 		208
#	define dark_gray	237
#	define olive		64
#	define magenta		89
#endif

// On Macs, the colors are weird and screwed up.
// Blue looks like purple.
// Purple looks like pink.
// So just add pink while we're at it.

// However, it's also possible to manually fix the colors
// using Terminal preferences, so if the user has, they can
// define MAC_OVERRIDE at compile time with gcc (or probably clang)
#if defined(__APPLE__) && !defined(MAC_OVERRIDE)
#	define blue 		94
#	define purple		34
#	define pink 		35
// Uncomment to give a notice that Mac colors are different.
// #warning "ColorPrinter: You're building on a Mac! Just so you know, colors (read: pink and blue) will be a bit different!"
#else
#	define blue 		34
#	define purple 		35
#	define pink 		95
#endif /* __APPLE__ && !MAC_OVERRIDE */

// If you're a Brit and you keep forgetting about "gray" vs "grey", here
#ifdef UK
#	define light_grey	37
#	define dark_grey	237
#	undef  light_gray
#	undef  dark_gray
#endif /* UK */

// Function prototypes so that calling something before it is defined works
int  		  cprintf(unsigned char, const char*, ...);
int  		  cfprintf(void*, unsigned char, const char*, ...);
unsigned char cnprintf(unsigned int, unsigned char, const char*, ...);
unsigned char cfnputs(const char*, unsigned char, unsigned int, void*);

// Everything with a fixed number of args is a macro, cuz space = saved. Yay!
// a = message, b = color
#define cputs(a, b)     		b <= 97 ? fprintf(stdout, "\033[0;%dm%s\033[0m\n", b, a) : -1
#define cputchar(a, b)  		b <= 97 ? cputc(a, b, stdout) : -1

// c = the stream to write to, the rest of the variables are as above
#define cfputs(a, b, c) 		b <= 97 ? fprintf(c, "\033[0;%dm%s\033[0m", b, a) : -1
#define cfputc(a, b, c) 		fprintf(c, "\033[0;%dm%c\033[0m", b, a)
#define cnputs(a, b, c) 		cfnputs(a, b, c, stdout); putchar('\n')		// c = the length here
#define cputc(a, b, c)  		cfputc(a, b, c) // Same as fcputc() 

#define crputs(a, b)			fprintf(stdout, "\033[38;5;%dm%s\033[0m\n", b, a);

// Standard color print for formatted string
int cprintf(unsigned char color, const char *fmt, ...) {
	if (color <= 97) {
		printf("\033[0;%dm", color);
		va_list args;
		va_start(args, fmt);
		int charsWritten = vfprintf(stdout, fmt, args);			// vfprintf returns the number of chars written
		va_end(args);
		fputs("\033[0m", stdout);
		return charsWritten;
	} else
		return -1;		// No 256-color prompts with this function!
}

// cprintf(), but you get to chose the stream
int cfprintf(void *stream, unsigned char color, const char *fmt, ...) {
	if (color <= 97) {
		fprintf(stream, "\033[0;%dm", color);
		va_list args;
		va_start(args, fmt);
		int charsWritten = vfprintf(stream, fmt, args);
		va_end(args);
		fputs("\033[0m", stream);
		return charsWritten;
	} else
		return -1;
}

// Specify how many characters to write to prevent buffer overflows (just in case)
unsigned char cnprintf(unsigned int len, unsigned char color, const char *fmt, ...) {
	if (color <= 97) {
		char buf[len];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, len, fmt, args);
		cfputs(buf, color, stdout);
	  	va_end(args);
	  	return 1;
	} else 
		return -1;
}

// colorful fputs(), but manually specify how many characters
unsigned char cfnputs(const char *amsg, unsigned char color, unsigned int len, void *stream) {
	if (color <= 97) {
		fprintf(stream, "\033[0;%dm", color);
		for (; len > 0 && *amsg != '\0'; amsg++, --len)
			putc(*amsg, stream);
		fputs("\033[0m", stream);
		return 1;
	} else 
		return -1;
}

/*
// Convert rgb(r, g, b) to 256-color terminal output
unsigned short rgb_color(unsigned char r, unsigned char g, unsigned char b) {
	return r * 36 + g * 6 + b + 16;
}
*/

#endif /* _COLORPRINTER_H */