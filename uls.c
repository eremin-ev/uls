#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv, char **envp)
{
	int r;
	struct dirent *e = 0;
	struct stat *st = malloc(sizeof(*st));
	if (st) {
		DIR *d = opendir(".");
		if (d) {
			errno = 0;
			while ((e = readdir(d))) {
				r = stat(e->d_name, st);
				if (-1 == r) {
					printf("uls: %s\n", strerror(errno));
					errno = 0;
					break;
				}
				printf("%zu\t%s\n", st->st_size, e->d_name);
			}

			if (errno) {
				printf("uls: %s\n", strerror(errno));
			}

			closedir(d);
		} else {
			printf("uls: %s\n", strerror(errno));
		}
		free(st);
	} else {
		printf("uls: %s\n", strerror(errno));
	}

	return 0;
}
