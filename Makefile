CFLAGS = -O0

all: uls tags

uls: uls.c
	$(CC) $(CFLAGS) -Wall $< -o $@

tags: uls.c
	ctags -R .

.PHONY:
clean:
	rm -vf uls tags
