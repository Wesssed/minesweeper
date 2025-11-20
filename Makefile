CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=#-lm
OUTPUT=minesweeper

# targets
all: $(OUTPUT)

$(OUTPUT): field.o main.o utill.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) field.o main.o utill.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

field.o: field.c field.h
	$(CC) $(CFLAGS) -c field.c $(LDLIBS) -o field.o

utill.o: utill.c utill.h
	$(CC) $(CFLAGS) -c utill.c $(LDLIBS) -o utill.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o

debug: field.c field.h utill.c utill.h
	$(CC) $(CFLAGS) -DDEBUG field.c utill.c -o debug
	./debug
