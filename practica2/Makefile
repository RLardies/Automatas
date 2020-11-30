CC=gcc
CFLAGS=-g -Wall
EJS=main prueba1 prueba2 prueba3

LIB=lib_afnd_64.a
OBJECTSMAIN=main.o intermedia.o minimiza.o $(LIB)

all: $(EJS)

clean:
	rm -f *.o $(EJS) *.dot *.png

main: $(OBJECTSMAIN)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSMAIN)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

prueba1: prueba1.o minimiza.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o prueba1 prueba1.o minimiza.o intermedia.o $(LIB)

prueba3: prueba3.o minimiza.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o prueba3 prueba3.o minimiza.o intermedia.o $(LIB)

prueba2: prueba2.o minimiza.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o prueba2 prueba2.o minimiza.o intermedia.o $(LIB)

intermedia.o: intermedia.c
	$(CC) $(CFLAGS) -c $<

minimiza.o: minimiza.c
	$(CC) $(CFLAGS) -c $<
