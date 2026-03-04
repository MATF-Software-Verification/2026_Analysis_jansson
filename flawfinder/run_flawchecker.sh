# !/bin/bash

JANSSONDIR="../jansson/src"
OUTDIR="$(pwd)"

# python3 -m venv ~/venv_flawfinder
source ~/venv_flawfinder/bin/activate
# pip3 install flawfinder

flawfinder --minlevel=1 --html --context "$JANSSONDIR" > "$OUTDIR/flawfinder_report.html"

deactivate