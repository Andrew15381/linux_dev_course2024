# хотел запускать в cmake, но на момент cmake у нас же еще нет бинарника
# не стал городить

my_out="$(echo "SHA1 rhasher.c" | ./rhasher | tail -n 1)"
correct_out="$(sha1sum rhasher.c)"
correct_out=${correct_out% *}
if [ $my_out != $correct_out ]; then
    exit 1
fi

my_out="$(echo "MD5 rhasher.c" | ./rhasher | tail -n 1)"
correct_out="$(md5sum rhasher.c)"
correct_out=${correct_out% *}
if [ $my_out != $correct_out ]; then
    exit 1
fi

exit 0
