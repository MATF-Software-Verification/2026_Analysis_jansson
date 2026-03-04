# !/bin/bash

JANSSONDIR="../jansson"
OUTDIR="$(pwd)"

python3 -m venv ~/venv_lizard 
source ~/venv_lizard/bin/activate 
pip install lizard 
pip install jinja2

lizard -V $JANSSONDIR/src/*.c 2>&1 | tee $OUTDIR/report.txt
lizard -V --html -o $OUTDIR/output.html $JANSSONDIR/src/*.c 

deactivate