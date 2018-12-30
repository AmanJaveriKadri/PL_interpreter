CC = clang
CFLAGS = -Wall -Wextra -c -O2
DEPS = file_input.h

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

PLinterpret: PL_interpreter.o file_input.o
	$(CC) -o PLinterpret PL_interpreter.o file_input.o

clean:
	rm -f *.o core* *~ PLinterpret
