#include "ColorPrinter.h"

int main() {
	cputs("This is output to stdout.", bright_green);
	cfputs("This is output to stderr!\n", red, stderr);
	cprintf(purple, "%s works with both of these streams!\n", "Formatting");
	cfprintf(stderr, blue, "Isn't that %s! And yes, numbers work %d :P\n", "something", 2);
	cputs("It even works for single characters:", green);
	cputchar('g', pink);
	cfputc('c', yellow, stdout);
	cputc('c', light_blue, stdout);
	putchar('\n');
	cnputs("Use cnputs() to prevent buffer overflow!", bright_red, 40);
	cfnputs("And, of course, cfnputs() for other streams.\n", pink, 45, stderr);
	cnprintf(44, cyan, "And use cnprintf() with %s strings!\n", "formatted");
	crputs("Use 256 colors if it's supported! (That's how this is orange!)", orange);
	crputs("It even has olive...", olive);
	crputs("And magenta!", magenta);
	return 0;
}