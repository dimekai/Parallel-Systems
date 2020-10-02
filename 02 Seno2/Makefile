# Archivo Makefile usando cadenas

PROYECTO=muestreo
DESTDIR=/usr/local/bin	# Direccion destino
CFLAGS=-Wall	# Banderas del compilador
LFLAGS=-lm	# Banderas del enlazador.
CC=gcc		# Instruccion del compilador


all: $(PROYECTO)

muestreo.o: muestreo.c
	$(CC) -c muestreo.c $(CFLAGS)

procesamiento.o: procesamiento.c
	$(CC) -c procesamiento.c $(CFLAGS)

archivos.o: archivos.c
	$(CC) -c archivos.c $(CFLAGS)

$(PROYECTO): muestreo.o procesamiento.o archivos.o
	$(CC) muestreo.o procesamiento.o archivos.o -o $(PROYECTO) $(LFLAGS)

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm -f *.o $(PROYECTO)
