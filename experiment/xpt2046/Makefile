all: xpt

xpt: xpt.o
	cc -g -o xpt xpt.o -lwiringPi

xpt.o: xpt.c
	cc -g -o xpt.o -c xpt.c

debug: xpt 
	sudo kdbg ./xpt

run: xpt
	sudo ./xpt 0 0 3

clean:
	rm -f *.o xpt

