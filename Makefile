all: uls tags

uls: uls.c
	$(CC) -O0 -Wall $< -o $@

tags: uls.c
	ctags -R .

.PHONY:
clean:
	rm -vf uls
