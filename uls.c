#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <getopt.h>

enum ls_flags {
	LS_LONG = 0x1 << 0,
};

int do_ls(const char *path, unsigned flags)
{
	int r;
	struct dirent *e = 0;
	struct stat *st = malloc(sizeof(*st));
	if (st) {
		DIR *d = opendir(path);
		if (d) {
			errno = 0;
			while ((e = readdir(d))) {
				if (flags & LS_LONG) {
					r = stat(e->d_name, st);
					if (-1 == r) {
						printf("uls: %s: %s\n",
							e->d_name,
							strerror(errno));
						errno = 0;
						break;
					}
					printf("%zu\t", st->st_size);
				}
				printf("%s\n", e->d_name);
			}

			if (errno) {
				printf("uls: %s: %s\n", path, strerror(errno));
			}

			closedir(d);
		} else {
			printf("uls: %s: %s\n", path, strerror(errno));
		}
		free(st);
	} else {
		printf("uls: %s: %s\n", path, strerror(errno));
	}
}

int main(int argc, char **argv, char **envp)
{
	struct option o[] = {
		{ "long", no_argument, 0, 'l' }
	};
	int c, i, flags = 0;

	while (-1 != (c = getopt_long(argc, argv, "l", o, &i))) {
		switch (c) {
		case 'l':
			flags |= LS_LONG;
			break;
		default:
			printf("unknown option %c (%x)\n", c, c);
			break;
		}
	}

	while (optind < argc) {
		do_ls(*(argv + optind), flags);
		optind++;
	}

	do_ls(".", flags);

	return 0;
}
