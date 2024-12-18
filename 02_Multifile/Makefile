GENERATES = liboutput_static.a liboutput.so prog prog-a prog-so prog.txt prog-a.txt prog-so.txt
TRASH = *.o o.* *~

all: prog prog-a prog-so

fun.o:  fun.c 
	gcc -fPIC fun.c -c -o fun.o

prog.o: prog.c 
	gcc prog.c -c -o prog.o

const.o: const.c 
	gcc const.c -c -o const.o

liboutput_static.a: fun.o const.o
	ar r liboutput_static.a fun.o const.o
	ranlib liboutput_static.a

liboutput.so: fun.o const.o
	gcc fun.o const.o -o liboutput.so -shared

prog: prog.o fun.o const.o
	gcc prog.o fun.o const.o -o prog

prog-a: prog.o liboutput_static.a
	gcc prog.o liboutput_static.a -o prog-a

prog-so: prog.o liboutput.so
	gcc prog.o -L. -loutput -o prog-so

test-no-args: prog prog-a prog-so
	./prog > prog.txt 2>&1
	./prog-a > prog-a.txt 2>&1
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./prog-so > prog-so.txt 2>&1
	diff -s prog.txt prog-a.txt
	diff -s prog.txt prog-so.txt

test-one-arg: prog prog-a prog-so
	./prog > prog.txt 2>&1 a
	./prog-a > prog-a.txt 2>&1 a
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./prog-so > prog-so.txt 2>&1 a
	diff -s prog.txt prog-a.txt
	diff -s prog.txt prog-so.txt

test-three-args: prog prog-a prog-so
	./prog > prog.txt 2>&1 a b c
	./prog-a > prog-a.txt 2>&1 a b c
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./prog-so > prog-so.txt 2>&1 a b c
	diff -s prog.txt prog-a.txt
	diff -s prog.txt prog-so.txt

test: test-no-args test-one-arg test-three-args

clean:
	rm -f $(TRASH) $(GENERATES)
