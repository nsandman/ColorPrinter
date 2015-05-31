#include "ColorPrinter.h"

int main() {
	cputs("This is output to stdout.", green);
	cfputs("This is output to stderr!\n", red, stderr);
	cprintf(purple, "%s works with both of these streams!\n", "Formatting");
	cfprintf(stderr, blue, "Isn't that %s! And yes, numbers work %d :P\n", "something", 2);
	cputs("It even works for single characters:", green);
	cputchar('g', red);
	cfputc('c', yellow, stdout);
	cputc('c', cyan, stdout);
	putchar('\n');
	cnputs("Use cnputs() to prevent buffer overflow!", red, 40);
	cnfputs("And, of course, cnfputs() for other streams.\n", blue, 45, stderr);
	cnprintf(44, cyan, "And use cnprintf() with %s strings!\n", "formatted");
}