//use gcc helloglib.c -Wall -o helloglib `pkg-config --cflags --libs glib-2.0`
#include <stdio.h>
#include "/usr/local/Cellar/glib/2.34.1/include/glib-2.0/glib.h"


int main() {
	char* str = "Hello World!";
     printf("%s\n", str);
     return 0;
}