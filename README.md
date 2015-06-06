# ColorPrinter
ColorPrinter is an easy, cross-platform library to print in color.

Printing in color may not seem like a big deal, but this can be a pain to implement perfectly. ColorPrinter is small, has little dependence on the standard library (only stdarg.h and stdio.h are used), and has a familiar syntax. Also, ColorPrinter is fully header-based, so no new ".c" files need to be compiled.

###Building the Test
The test is simple to build. To build with no weird magic, just run
```bash
make
```

However, if you want to build without the Mac fixed colors, or no 256-colors, or with UK color names, just use these Makefile targets:

1. nomacfix
2. uk
3. 8color

There is also "embedded", but it's a work in progress.

So, just choose a target (or multiple ones) and then choose the "build" target.

For example, you could run:
```bash
make nomacfix build
```
For default Linux colors on the Mac.

Or, you could even run:
```
make nomacfix uk 8color build
```
For all of them.

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
2. orange
3. dark gray
4. olive
5. magenta

###Options
On OSX in the default Terminal palette, the colors do not *exactly* map to what is expected. Blue looks more like a purple, and purple is more like pink.
So, ColorPrinter remaps these colors so that they appear like themselves.

However, another fix to this "problem" of unconventional colors is changing it in the Terminal settings menu. If that was done by the user, the remapped colors will look off. So, all one needs to do to fix this is to define `MAC_OVERRIDE`. This will use the standard bash colors instead of the remapped OSX ones.

Also, if your terminal does not support 256 colors, define `NO256`.

If you prefer the British "grey" spelling (as opposed to the American "gray" spelling), just define `UK`. This will `#undef` light_gray and dark_gray and `#define` light_grey and dark_grey.

###How to Use
Using is simple. In your C file, just do:
```c
#include "ColorPrinter.h"
```

This will give you access to these functions:

* [`cprintf()`](#cprintf)
* [`cfprintf()`](#cfprintf)
* [`cnprintf()`](#cnprintf)
* [`cputs()`](#cputs)
* [`cnputs()`](#cnputs)
* [`cfputs()`](#cfputs)
* [`cfnputs()`](#cfnputs)
* [`cputc()`](#cputc-and-cfputc)
* [`cfputc()`](#cputc-and-cfputc)
* [`cputchar()`](#cputchar)

Now we will go through each of them individually.

####`cprintf()`
```c
#define cprintf(c, f, ...)
```
This function prints formatted string *f* with color *c* to stdout. It will then return the number of characters written.
It is based off the C function `printf()`.

####`cfprintf()`
```c
int cfprintf(FILE *s, color_t c, const char *fmt, ...)
```
This function prints formatted string *fmt* with color *c* to stream *s*. It will then return the number of characters written.
It is based off the C function `fprintf()`.

####`cnprintf()`
```c
int cnfprintf(FILE *s, color_t c, size_t n, const char *fmt, ...)
```
This function will print formatted string *fmt* with color *c* to stdout. It will print until it reaches a null `\0` character or until *n* characters have been printed, whichever comes first.
It is based off two C functions: `vsnprintf()` and `printf()`.

####`cputs()`
```c
#define cputs(m, c)
```
This function prints string *m* to stdout with color *c*. It also automatically appends a newline. It is based off the C function `puts()`.

####`cnputs()`
```c
#define cnputs(a, b, c)
```
This function writes string *a* to stdout with color *b*. It will print until it reaches a null `\0` character or until *c* characters have been printed, whichever comes first.
It is based off the C function `fputs()`.

####`cfputs()`
```c
#define cfputs(a, b, c)
```
This function writes string *a* to stream *c* with color *b*.
It is based off the C function `fputs()`.

####`cfnputs()`
```c
int cfnputs(const char *m, color_t c, size_t n, FILE *s)
```
This function writes string *m* with color *c* to stream *s*. It will print until it reaches a null `\0` character or until *len* characters have been printed, whichever comes first.
It is based off two functions: `vsnprintf()` and `fputs()`.

####`cputc()` and `cfputc()`
```c
#define cputc(a, b, c)
#define cfputc(a, b, c)
```
Both these functions print char *a* with color *b* to stream *c*.
They are based off `putc()`.

####`cputchar()`
```c
#define cputchar(a, b)
```
This prints char *a* with color *b* to stdout. It is based off `putchar()`.
