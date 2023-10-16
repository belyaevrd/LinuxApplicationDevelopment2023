CFLAGS = -O0 -g
all:	test

test:	range sample
	gdb --command=script1 range | grep '@@@' > test1.txt
	gdb --command=script2 range | grep '@@@' > test2.txt
	cat test1.txt
	cat test2.txt
	-cmp test1.txt sample1.txt 
	-cmp test2.txt sample2.txt 

range:	range.c
	cc $(CFLAGS) $^ -o $@

sample:
	/bin/echo -e '@@@1 12 1 5\n@@@1 12 1 10' > sample1.txt
	/bin/echo -e '@@@-100 100 3 -16\n@@@-100 100 3 -13\n@@@-100 100 3 -10\n@@@-100 100 3 -7\n@@@-100 100 3 -4\n@@@-100 100 3 -1\n@@@-100 100 3 2\n@@@-100 100 3 5' > sample2.txt

clean:
	rm -rf *.txt range
