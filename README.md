# ColorPrinter
ColorPrinter is an easy, cross-platform library to print in color.

Printing in color may not seem like a big deal, but this can be a pain to implement perfectly. ColorPrinter is small, has little dependence on the standard library (only stdarg.h and stdio.h are used), and has a familiar syntax. Also, ColorPrinter is fully header-based, so no new ".c" files need to be compiled.

###Colors Included
Many colors are included, but if you'd like, you can `#define` your own! However, the ones that come by default are:

1. red
1. green
1. cyan
1. yellow
1. light gray
1. blue
1. purple
1. pink
1. bright red
1. bright green
1. light blue
1. bright yellow
1. white

###Options
On OSX in the default Terminal palette, the colors do not *exactly* map to what is expected. Blue looks more like a purple, and purple is more like pink.
So, ColorPrinter remaps these colors so that they appear like themselves.

However, another fix to this "problem" of unconventional colors is changing it in the Terminal settings menu. If that was done by the user, the remapped colors will look off. 
So, all one needs to do to fix this is to define `MAC_OVERRIDE`. This will use the standard bash colors instead of the remapped OSX ones.

Also, if you prefer the British "grey" spelling (as opposed to the American "gray" spelling), just define `UK`. This will
`#undef` light_gray and `#define` light_grey.

###How to Use
Using is simple. In your C file, just do:
```c
#include "ColorPrinter.h"
```

This will give you access to these functions:

* `cprintf()`
* `cfprintf()`
* `cnprintf`
* `cputs()`
* `cnputs()`
* `cfputs()`
* `cfnputs()`
* `cputc()`
* `cfputc()`
* `cputchar()`

Now we will go through each of them individually.

####`cprintf()`
```c
int cprintf(unsigned char color, const char *fmt, ...)
```
This function prints formatted string *fmt* with color *color* to stdout. It will then return the number of characters written.
It is based off the C function `printf()`.

####`cfprintf()`
```c
int cfprintf(void *stream, unsigned char color, const char *fmt, ...)
```
This function prints formatted string *fmt* with color *color* to stream *stream*. It will then return the number of characters written.
It is based off the C function `fprintf()`.

####`cnprintf()`
```c
void cnprintf(unsigned int len, unsigned char color, const char *fmt, ...)
```
This function will print formatted string *fmt* with color *color* to stdout. It will print until it reaches a null `\0` character or until *len* characters have been printed, whichever comes first.
It is based off two C functions: `vsnprintf()` and `printf()`.

####`cputs()`
```c
#define cputs(a, b)       printf("\033[0;%dm%s\033[0m\n", b, a)
```
This function prints string *a* to stdout with color *b*. It also automatically appends a newline.
It is based off the C function `puts()`.

####`cnputs()`
```c
#define cnputs(a, b, c)   cfnputs(a, b, c, stdout); \
                          putchar('\n')
```
This function writes string *a* to stdout with color *b*. It will print until it reaches a null `\0` character or until *c* characters have been printed, whichever comes first.
It is based off the C function `fputs()`.

####`cfputs()`
```c
#define cfputs(a, b, c)   fprintf(c, "\033[0;%dm%s\033[0m", b, a)
```
This function writes string *a* to stream *c* with color *b*.
It is based off the C function `fputs()`.

####`cfnputs()`
```c
void cfnputs(const char *amsg, unsigned char color, unsigned int len, void *stream)
```
This function writes string *amsg* with color *color* to stream *stream*. It will print until it reaches a null `\0` character or until *len* characters have been printed, whichever comes first.
It is based off two functions: `vsnprintf()` and `fputs()`.

####`cputc()` and `cfputc()`
```c
#define cfputc(a, b, c)   fprintf(c, "\033[0;%dm%c\033[0m", b, a)
#define cputc(a, b, c)    cfputc(a, b, c)
```
Both these functions print char *a* with color *b* to stream *c*.
They are based off `putc()`.

####`cputchar()`
```c
#define cputchar(a, b)    cputc(a, b, stdout)
```
This prints char *a* with color *b* to stdout. It is based off `putchar()`.
