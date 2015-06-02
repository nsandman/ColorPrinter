#include "ColorPrinter.h"

int main() {
	cfputs("This is printed to stderr!\n", green, stderr);
	cputs("And this is stdout!", blue);
	cputchar('w', magenta);
	cputchar('t', cyan);
	cputchar('f', yellow);
	putchar('\n');
	cfprintf(stderr, orange, "It works with " "formatted" " strings %d!\n", 2);
	cnprintf(yellow, 57, "Use %s or %s to avoid buffer overflows!\n", "cn(f)printf", "cn(f)puts");
	return 0;
}