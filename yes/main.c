/* nasralutils/true
 * main.c
 * Ruzen42
*/
#include <stdio.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t keep_running = 1;

void
handle_sigint(int sig)
{
	/* handle ^C */ 
	keep_running = 0;
}


int
main(int argc, char *argv[])
{
	const char *text = "y";

	const char *first_arg = argv[1];
	/* parse --help and --version */
	if (argc > 1) {
		if (strcmp(first_arg, "--help") == 0) {
			printf("Use: %s [STRING] [--version|--help]\n", argv[0]);
			return 0;
		}
		else if (strcmp(first_arg, "--version") == 0) {
			puts("0.1");
			return 0;
		}
	}

	while (keep_running) {
		puts(text);
	}

	putchar('\n');
	return 0;
}
