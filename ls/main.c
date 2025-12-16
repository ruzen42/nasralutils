/* nasralutils/ls
 * main.c
 * Ruzen42
*/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>

bool 
check_dir(const char *path)
{
	/* check if a directory exists */
	return access(path, F_OK) == 0;
}

int
main(int argc, char *argv[])
{
	/* var for storing the path to the desired diretory */
	const char *pos = ".";

	const char *first_arg = argv[1];
	/* parsing --help and --version */
	if (argc > 1) {
		if (strcmp(first_arg, "--help") == 0) {
			printf("Use: %s [PATH] [--version|--help]\n", argv[0]);
			return 0;
		}
		else if (strcmp(first_arg, "--version") == 0) {
			puts("0.1");
			return 0;
		}
		pos = first_arg;
	}

	if (!check_dir(pos)) {
		/* throw error in stderr if not exists */
		fprintf(stderr, "directory %s is not exists\n", pos); 
		return 1;
	}
	DIR *dir = opendir(pos);

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {
		/* output elements in dir line by line */
		if (entry->d_name[0] != '.') {
			printf("%s\n", entry->d_name);
		}
	}
	
	closedir(dir);
	return 0;
}
