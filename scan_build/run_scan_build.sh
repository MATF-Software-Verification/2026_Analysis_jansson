#!/bin/bash

SCRIPT_DIR="$(pwd)"
JANSSON="../jansson"
RESULTS_DIR="$SCRIPT_DIR/results"
REPORT_DIR="$RESULTS_DIR/scan-build-report"

mkdir -p "$RESULTS_DIR"
mkdir -p "$REPORT_DIR"

cd "$JANSSON"
make clean

scan-build -o "$REPORT_DIR" ./configure
scan-build -o "$REPORT_DIR"  make 2>&1 | tee "$RESULTS_DIR/scan-build-output.txt"

LATEST_REPORT=$(find "$REPORT_DIR" -name "index.html" | head -1)

if [ -n "$LATEST_REPORT" ]; then
    echo "Report generated: $LATEST_REPORT"

    cp "$LATEST_REPORT" "$RESULTS_DIR/scan-build-report.html"
else
    echo "No HTML found. Check: $REPORT_DIR"
fi
