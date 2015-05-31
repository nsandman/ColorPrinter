#include "ColorPrinter.h"

int main() {
	cputs("This is output to stdout.", green);
	fcputs("This is output to stderr!\n", red, stderr);
	cprintf(purple, "%s works with both of these streams!\n", "Formatting");
	fcprintf(stderr, blue, "Isn't that %s! And yes, numbers work %d :P\n", "something", 2);
	cputs("It even works for single characters!", green);
	cputchar('g', red);
	fcputc('c', yellow, stdout);
	cputc('c', cyan, stdout);
	putchar('\n');
}