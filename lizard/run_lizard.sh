# !/bin/bash

JANSSONDIR="../jansson"
OUTDIR="$(pwd)"

source ~/venv_lizard/bin/activate

lizard -V $JANSSONDIR/src/*.c 2>&1 | tee $OUTDIR/report.txt
lizard -V --html -o $OUTDIR/output.html $JANSSONDIR/src/*.c 

deactivate