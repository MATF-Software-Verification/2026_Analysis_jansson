#!/bin/bash

RED='\033[0;31m'
BLUE='\033[1;34m'
CYAN='\033[0;36m'
NC='\033[0m'

SRCDIR="../../jansson/"
OUTDIR="$(pwd)"

cd $SRCDIR

# remove files from previous builts
make clean
# set flags for compiling
./configure CFLAGS="-g -O0 --coverage"
make

# run tests
make check 

# create data directory if it doesn't exist
mkdir -p $OUTDIR/data
mkdir -p $OUTDIR/report

# collect data for coverage
lcov --capture --directory . \
     --output-file $OUTDIR/data/coverage.info

# disregard libraries and test files
lcov --remove $OUTDIR/data/coverage.info \
     '/usr/include/*' '/usr/lib/*' '*/test/*'\
      -o $OUTDIR/data/coverage_filtered.info

# generate html
genhtml --branch-coverage -o $OUTDIR/report \
        $OUTDIR/data/coverage_filtered.info
