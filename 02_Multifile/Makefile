SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
GENERATES = prog prog-* README *.so *.a *.o test*
CC = gcc
CFLAGS = 

all:	test 

test:	prog prog-a prog-so
	./prog > test_1-1 2>&1
	./prog-a > test_1-2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > test_1-3 2>&1
	./prog 	 param1 > test_2-1 2>&1
	./prog-a param1 > test_2-2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so param1 > test_2-3 2>&1
	./prog 	 a b c > test_3-1 2>&1
	./prog-a a b c > test_3-2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so a b c > test_3-3 2>&1
	@echo "\nTest 1:\n"
	-cmp test_1-1 test_1-2
	-cmp test_1-2 test_1-3
	-cmp test_1-3 test_1-1
	@echo "\nTest 2:\n"
	-cmp test_2-1 test_2-2
	-cmp test_2-2 test_2-3
	-cmp test_2-3 test_2-1
	@echo "\nTest 3:\n"
	-cmp test_3-1 test_3-2
	-cmp test_3-2 test_3-3
	-cmp test_3-3 test_3-1
	

prog:	$(OBJECTS)
	$(CC) $^ -o $@

prog-a:	prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@ 

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^
	
prog-so: clean_objects
	make CFLAGS=-fPIC $(OBJECTS)
	$(CC) -shared const.o fun.o -o liboutput.so
	$(CC) -L. prog.o -loutput -o $@
	
%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

prog.o: outlib.h
fun.o: outlib.h

clean:
	rm -rf $(GENERATES) 

clean_objects:	$(OBJECTS)
	rm -f $^
