OBJECTS = test_rrr.o rrr.o bitvector.o compactIntArray.o
CC = g++
test_rrr:$(OBJECTS)
	$(CC) -g -o test_rrr $(OBJECTS)
test_rrr.o:test_rrr.cpp rrr.h
	$(CC) -g -c test_rrr.cpp
rrr.o:rrr.cpp rrr.h
	$(CC) -g -c rrr.cpp
bitvector.o:bitvector.cpp bitvector.h
	$(CC) -g -c bitvector.cpp
compactIntArray.o:compactIntArray.cpp compactIntArray.h
	$(CC) -g -c compactIntArray.cpp
clean:
	rm test_rrr $(OBJECTS)
