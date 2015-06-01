#include "ColorPrinter.h"

int main() {
	cfputs("This is printed to stderr!\n", green, stderr);
	cputs("And this is stdout!", blue);
	cputchar('g', magenta);
	cputchar('c', cyan);
	cputchar('c', yellow);
	putchar('\n');
	cfprintf(stderr, orange, "It works with %s strings %d!\n", "formatted", 2);
	cnprintf(yellow, 57, "Use %s or %s to avoid buffer overflows!\n", "cn(f)printf", "cn(f)puts");
	return 0;
}