#!/bin/bash

OUTDIR="$(pwd)"
TESTDIR="./suites"
JANSSON_DIR="../../jansson"


cd $TESTDIR
make clean
rm -f *.gcda *.gcno

make

./test_dtoa

cd $JANSSON_DIR
# make distclean
# rm -f *.gcda *.gcno
# rm -rf src/.libs
# ./configure CFLAGS="-g -O0 --coverage" --enable-static --disable-shared
# make

lcov --capture --directory src \
     --gcov-tool /usr/bin/gcov \
     --base-directory src \
     --output-file $OUTDIR/data/new_coverage.info


lcov --remove $OUTDIR/data/new_coverage.info \
     '/usr/include/*' '/usr/lib/*' \
     -o $OUTDIR/data/new_filtered.info

genhtml --branch-coverage -o $OUTDIR/new_report \
        $OUTDIR/data/new_filtered.info
