CC = gcc
CFLAGS = -g -Wall -I../../jansson/src -I../../jansson
LDFLAGS = -lcunit -lgcov -fprofile-arcs
JANSSON_LIB = ../../jansson/src/.libs/libjansson.a

TARGET = test_dtoa
SRC = test_dtoa.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< $(JANSSON_LIB) $(LDFLAGS) -o $@

check: $(TARGET)
	./$(TARGET)


clean:
	rm -f $(TARGET)
	rm -f *.gcda *.gcno
	rm -f new_coverage.info new_coverage_filtered.info
	rm -rf new_coverage_report/


.PHONY: clean check