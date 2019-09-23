#!/bin/sh
# tst.sh

gcc $* -Werror -Wall -I../err -g -o sb_test sb.c ../err/err.c sb_test.c

echo "./sb_test"
./sb_test 0 2>tmp.0
perl <tmp.0 -e \
' $_=<>; /^OK$/                                                  || die"ERR:$_";
  $_=<>; ! defined($_) || die $_; # check EOF
  print "OK\n";
'
echo ""
