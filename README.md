# uls

upd: moved to test

```Bash
uls> echo $[(1<<32)/4096]
1048576
```

```Bash
uls> dd if=/dev/zero of=a-big-file.bin bs=4096 count=$[1048576 + 1]
1048577+0 records in
1048577+0 records out
4294971392 bytes (4.3 GB, 4.0 GiB) copied, 1.1342 s, 3.8 GB/s
```

```Bash
uls> ./uls -l
180     ./.
300     ./..
4294971392      ./a-big-file.bin
6       ./README.md
17360   ./uls
838     ./tags
260     ./.git
105     ./Makefile
2235    ./uls.c
```
