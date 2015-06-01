# ColorPrinter
ColorPrinter is an easy, cross-platform library to print in color.

Printing in color may not seem like a big deal, but this can be a pain to implement perfectly. ColorPrinter is small, has little dependence on the standard library (only stdarg.h and stdio.h are used), and has a familiar syntax. Also, ColorPrinter is fully header-based, so no new ".c" files need to be compiled.

##"ColourPrinter"
I'm not going to provide a direct link to this repository (so they don't get more traffic), but the first person on the blacklist has copied my README and a lot of my code. So while this repo may look like a shameless ripoff, it's not. Here are two links; each is the commit where the README is made (or changed to look like mine, in his case)

* **nsandman09/ColorPrinter**: [Commit *b7aa57d*](https://github.com/nsandman09/ColorPrinter/commit/b7aa57d3cdbc1e55ed4aed16e12c3436dcfac135) **Date**: Sun May 31 03:50:56 2015 -0700
* **vidurgupta01/ColourPrinter**: [Commit *6325945*](https://github.com/vidurgupta01/ColourPrinter/commit/632594506acd40a1b2e3b1792f652a885e46f23a) **Date**: Sun May 31 10:54:36 2015 -0700

So... yeah. Also here's where he made it a header-only library (mine was from the start):

* **vidurgupta01/ColourPrinter**: [Commit *270e5ca*](https://github.com/vidurgupta01/ColourPrinter/commit/270e5ca2dcb973d7ea762859c0af54c9f9961e83) **Date**: Sun May 31 10:22:02 2015 -0700

Here's where he redefined his functions as macros (six of mine were macros from the start; the link to my repo has the first macro):

* **nsandman09/ColorPrinter**: [Commit *05cd33f*](https://github.com/nsandman09/ColorPrinter/commit/05cd33f0c098cb75928b135f3658f3560c5ad539) **Date**: Sun May 31 00:23:38 2015 -0700
* **vidurgupta01/ColourPrinter**: [Commit *3cdceb6*](https://github.com/vidurgupta01/ColourPrinter/commit/3cdceb688406d5510340e3ec36dd8edbff24cc15) **Date**: Sun May 31 10:23:15 2015 -0700

So... I think we know which repo is the shameless rip-off.

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
#define cprintf(c, f, ...) 		cfprintf(stdout, c, f, __VA_ARGS__)
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
#define cputs(m, c) 			cfputs(m, c, stdout); \
                          putchar('\n')
```
This function prints string *m* to stdout with color *c*. It also automatically appends a newline. It is based off the C function `puts()`.

####`cnputs()`
```c
#define cnputs(a, b, c)   cfnputs(a, b, c, stdout); \
                          putchar('\n')
```
This function writes string *a* to stdout with color *b*. It will print until it reaches a null `\0` character or until *c* characters have been printed, whichever comes first.
It is based off the C function `fputs()`.

####`cfputs()`
```c
int cfputs(const char *msg, color_t c, FILE *s)
```
This function writes string *msg* to stream *s* with color *c*.
It is based off the C function `fputs()`.

####`cfnputs()`
```c
int cfnputs(const char *m, color_t c, size_t n, FILE *s)
```
This function writes string *m* with color *c* to stream *s*. It will print until it reaches a null `\0` character or until *len* characters have been printed, whichever comes first.
It is based off two functions: `vsnprintf()` and `fputs()`.

####`cputc()` and `cfputc()`
```c
#define cputc(m, c, s)			startprint(c, s); putc(m, s); endprint(s)
#define cfputc(a, b, c)			cputc(a, b, c)
```
Both these functions print char *a* with color *b* to stream *c*.
They are based off `putc()`.

####`cputchar()`
```c
#define cputchar(m, c)			cputc(m, c, stdout)
```
This prints char *a* with color *b* to stdout. It is based off `putchar()`.
