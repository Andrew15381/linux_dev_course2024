all: range

range:
	gcc -o range -O0 -g range.c

clean:
	rm -f range test-*.txt

test-1: range
	gdb --quiet --batch ./range --command=gdb-test-1.txt | grep @@@ > test-1.txt
	cmp test-1.txt correct-test-1.txt

test-2: range
	gdb --quiet --batch ./range --command=gdb-test-2.txt | grep @@@ > test-2.txt
	cmp test-2.txt correct-test-2.txt

test: test-1 test-2
