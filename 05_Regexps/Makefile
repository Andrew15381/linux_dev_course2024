all: esub

esub:
	gcc -o esub -O0 -g esub.c

clean:
	rm -f esub test-*.txt

test-1: esub
	./esub > test-1-stdout.txt 2> test-1-stderr.txt
	diff -s test-1-stdout.txt correct-test-1-stdout.txt
	diff -s test-1-stderr.txt correct-test-1-stderr.txt

test-2: esub
	./esub "a(b" ab ab > test-2-stdout.txt 2> test-2-stderr.txt
	diff -s test-2-stdout.txt correct-test-2-stdout.txt
	diff -s test-2-stderr.txt correct-test-2-stderr.txt

test-3: esub
	./esub ab "a\1b" ab > test-3-stdout.txt 2> test-3-stderr.txt
	diff -s test-3-stdout.txt correct-test-3-stdout.txt
	diff -s test-3-stderr.txt correct-test-3-stderr.txt

test-4: esub
	./esub ab BA eabc > test-4-stdout.txt 2> test-4-stderr.txt
	diff -s test-4-stdout.txt correct-test-4-stdout.txt
	diff -s test-4-stderr.txt correct-test-4-stderr.txt

test-5: esub
	./esub "a(b)c" "\1_\1" DabcE > test-5-stdout.txt 2> test-5-stderr.txt
	diff -s test-5-stdout.txt correct-test-5-stdout.txt
	diff -s test-5-stderr.txt correct-test-5-stderr.txt

test-6: esub
	./esub "(a)b(c)d(e)" "<\3\2\1>" _abcdef_ > test-6-stdout.txt 2> test-6-stderr.txt
	diff -s test-6-stdout.txt correct-test-6-stdout.txt
	diff -s test-6-stderr.txt correct-test-6-stderr.txt

test-7: esub
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thursday" > test-7-stdout.txt 2> test-7-stderr.txt
	diff -s test-7-stdout.txt correct-test-7-stdout.txt
	diff -s test-7-stderr.txt correct-test-7-stderr.txt

test: test-1 test-2 test-3 test-4 test-5 test-6 test-7
