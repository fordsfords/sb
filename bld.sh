#!/bin/sh
# bld.sh

gcc $* -Werror -Wall -I../err -g -o sb_test sb.c ../err/err.c sb_test.c
