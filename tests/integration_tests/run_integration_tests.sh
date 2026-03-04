#!/bin/bash

SCRIPT_DIR="$(pwd)"
JANSSON_DIR="../../jansson"
RESULTS_DIR="$SCRIPT_DIR/results"
COVERAGE_DIR="$SCRIPT_DIR/coverage"

mkdir -p "$RESULTS_DIR"
mkdir -p "$COVERAGE_DIR"

cd "$JANSSON_DIR"
find src -name "*.gcda" -delete
find src -name "*.gcno" -delete
make clean
./configure CFLAGS="-g -O0 --coverage" --enable-static --disable-shared
make

cd "$SCRIPT_DIR"
gcc -g -fprofile-arcs -ftest-coverage \
    -I"$JANSSON_DIR/src" \
    "$SCRIPT_DIR/suites/test_utf_integration.c" \
    "$JANSSON_DIR/src/.libs/libjansson.a" \
    -lcunit -lgcov \
    -o "$RESULTS_DIR/test_utf_integration"

cd "$RESULTS_DIR"
./test_utf_integration

cd "../$JANSSON_DIR"
lcov --capture --directory "$RESULTS_DIR" \
     --base-directory src \
     -o "$COVERAGE_DIR/coverage.info"

lcov --remove "$COVERAGE_DIR/coverage.info" \
     '/usr/include/*' '/usr/lib/*' \
     -o "$COVERAGE_DIR/coverage_filtered.info"

genhtml --branch-coverage -o "$COVERAGE_DIR/coverage_report" \
        "$COVERAGE_DIR/coverage_filtered.info"