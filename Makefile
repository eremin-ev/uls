all: uls

uls: uls.c
	$(CC) -O0 $< -o $@

.PHONY:
clean:
	rm -vf uls
