CC=gcc
CFLAGS=-g -Wall
EJS=main

LIB=lib_afnd_64.a
OBJECTSMAIN=main.o intermedia.o transforma.o $(LIB)

all: $(EJS)

clean:
	rm -f *.o $(EJS) *.dot *.png

main: $(OBJECTSMAIN)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSMAIN)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

intermedia.o: intermedia.c
	$(CC) $(CFLAGS) -c $<

transforma.o: transforma.c
	$(CC) $(CFLAGS) -c $<

dot:
	dot -Tpng determinista.dot -o determinista.png