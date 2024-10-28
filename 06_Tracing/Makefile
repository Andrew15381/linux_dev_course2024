all: move protect.so

move:
	gcc -o move -O2 -g move.c

protect.so:
	gcc -o protect.so -O2 -g -fPIC -shared -ldl protect.c

test-PROTECTED1.txt:
	echo "test" > test-PROTECTED1.txt

test-PROTECTED2.txt:
	echo "test" > test-PROTECTED2.txt

test-1: move
	strace -e stat -P /dev/null -e inject=stat:error=ENOENT:when=1 ./move test-PROTECTED.txt test-output.txt; \
	[ $$? = 2 ]

test-2: move test-PROTECTED1.txt
	./move test-PROTECTED1.txt test-output1.txt
	[ ! -f test-PROTECTED1.txt ]
	[ -f test-output1.txt ]

test-3: move protect.so test-PROTECTED2.txt
	LD_PRELOAD=$$PWD/protect.so ./move test-PROTECTED2.txt test-output2.txt
	[ -f test-PROTECTED2.txt ]
	[ -f test-output2.txt ]

test: test-1 test-2 test-3

clean:
	rm -f move protect.so test-*

