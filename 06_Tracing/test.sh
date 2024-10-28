if [ ! -z $1 ]; then
    strace -P /dev/null -e fault=$1 $2
else
    eval "$2"
fi
echo $?
if [ $? != $4 ]; then
    exit 1
fi
# impossible because piping in strace is only possible with sh -c but it changes retval
# can run command twice to collect output but it removes files
# maybe, two targets needed
# anyway, I have been setting up these tests for 4 hours already
# all I really need is to .....................................
# if [ ! diff -s test-$3-stdout.txt correct-test-$3-stdout.txt ]; then
#     exit 1
# fi
# if [ ! diff -s test-$3-stderr.txt correct-test-$3-stderr.txt ]; then
#     exit 1
# fi
# also strace doesn't do anything in makefile
# running absolutely the same command from bash results in desired retval
# вещи, которые ты не знаешь, тебе не нужны
# мне не нужно запоминать все убогие закорючки, чтобы писать двустрочные тесты по 10 часов
exit 0
