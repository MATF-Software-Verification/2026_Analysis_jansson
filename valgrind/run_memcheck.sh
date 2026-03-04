OUTDIR="$(pwd)"
JANSSONDIR="../jansson"
SUITEDIR="test/suites/api"

cd $JANSSONDIR
# make distclean
# rm -rf src/.libs
# ./configure CFLAGS="-g -O0" --enable-static --disable-shared
#make 

cd $SUITEDIR

for testfile in test_*; do
    if [ -x "$testfile" ]; then
        logfile="${OUTDIR}/${testfile}_valgrind_log.txt"
        
        valgrind --leak-check=full --track-origins=yes --show-mismatched-frees=yes --log-file="$logfile" ./"$testfile"
    fi
done
