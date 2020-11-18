CC=gcc
CFLAGS=-g -Wall
EJS=main ejercicio_prueba1 ejercicio_prueba2 ejercicio_prueba3 ejercicio_prueba4 prueba1

LIB=lib_afnd_64.a
OBJECTSMAIN=main.o intermedia.o transforma.o $(LIB)

all: $(EJS)

clean:
	rm -f *.o $(EJS) *.dot *.png

main: $(OBJECTSMAIN)
	$(CC) $(CFLAGS) -o $@ $(OBJECTSMAIN)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

ejercicio_prueba1: ejercicio_prueba1.o transforma.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o ejercicio_prueba1 ejercicio_prueba1.o transforma.o intermedia.o $(LIB)

ejercicio_prueba2: ejercicio_prueba2.o transforma.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o ejercicio_prueba2 ejercicio_prueba2.o transforma.o intermedia.o $(LIB)

ejercicio_prueba3: ejercicio_prueba3.o transforma.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o ejercicio_prueba3 ejercicio_prueba3.o transforma.o intermedia.o $(LIB)

ejercicio_prueba4: ejercicio_prueba4.o transforma.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o ejercicio_prueba4 ejercicio_prueba4.o transforma.o intermedia.o $(LIB)

prueba1: prueba1.o minimiza.o transforma.o intermedia.o $(LIB)
	$(CC) $(CFLAGS) -o prueba1 prueba1.o minimiza.o transforma.o intermedia.o $(LIB)

intermedia.o: intermedia.c
	$(CC) $(CFLAGS) -c $<

transforma.o: transforma.c
	$(CC) $(CFLAGS) -c $<

minimiza.o: minimiza.c
	$(CC) $(CFLAGS) -c $<
