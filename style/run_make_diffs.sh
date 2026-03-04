# !/bin/bash

SRCDIR="../jansson/"
OUTDIR="$(pwd)"
REPORT="$OUTDIR/clang-format-report.txt"
DIFFDIR="$OUTDIR/format-diffs"
STYLE="${1:-Google}"


mkdir -p "$DIFFDIR"
cd $SRCDIR
> $REPORT

clang-format -style=$STYLE -dump-config > .clang-format

for file in src/*.c src/*.h; do
    echo "Checking: $file" | tee -a $REPORT
    
    replacements=$(clang-format -output-replacements-xml "$file" | grep -c "<replacement ")
    
    if [ "$replacements" -gt 0 ]; then
        echo "$replacements REPLACEMENTS NEEDED" >> $REPORT
        filename=$(basename "$file")
        echo $filename
        clang-format -style=$STYLE  "$file" > "$DIFFDIR/${filename}.formatted"
        diff -u $file  "$DIFFDIR/${filename}.formatted" > "$DIFFDIR/${filename}.diff"
    else
        echo "NO REPLACEMENTS NEEDED" >> $REPORT
    fi
done
 
