#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <getopt.h>

#define PAGE_SIZE 4096

enum ls_flags {
	LS_LONG = 0x1 << 0,
};

static inline size_t l_offset(void *p1, void *p2)
{
	return p2 - p1;
}

int do_ls(const char *path, unsigned flags)
{
	int r;
	struct dirent *e = 0;
	void *b = malloc(PAGE_SIZE);
	if (b) {
		struct stat *st = b;
		int round_up = 0;	/* FIXME round up to at least 16b */
		char *full = (void *) st + sizeof(*st) + round_up;
		DIR *d = opendir(path);
		if (d) {
			errno = 0;
			while ((e = readdir(d))) {
				if (flags & LS_LONG) {
					/*
					 * compose full path for a relative
					 * directory name (not a '.')
					 */
					snprintf(full, PAGE_SIZE - l_offset(b, full),
						"%s/%s", path, e->d_name);
					r = stat(full, st);
					if (-1 == r) {
						printf("uls: %s: %s\n", full,
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
		free(b);
	} else {
		printf("uls: %s: %s\n", path, strerror(errno));
	}
}

int main(int argc, char **argv, char **envp)
{
	struct option o[] = {
		{ "long", no_argument, 0, 'l' }
	};
	int c, i, nr = 0;
	unsigned flags = 0;

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
		nr++;
	}

	if (!nr) {
		do_ls(".", flags);
	}

	return 0;
}
