volatile unsigned int * const UART0DR = (unsigned int *) 0x09000000;
 
void print_uart0(const char *s) {
	while(*s != '\0') {
		*UART0DR = (unsigned int)(*s);
		s++;
	}
}

extern "C" {
void init() {
	print_uart0("Hello world!\n");
}
}
