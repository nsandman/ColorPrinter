#include "ColorPrinter.h"

int main() {
	colorPrint(green, "This is output to stdout.");
	fcolorPrint(stderr, red, "This is output to stderr!");
	colorPrint(purple, "%s works with both of these streams!", "Formatting");
	fcolorPrint(stderr, blue, "Isn't that %s! And yes, numbers work %d :P", "something", 2);
}