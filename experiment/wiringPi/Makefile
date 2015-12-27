
all: gpio2

gpio2: gpio2.o
	cc -g -o gpio2 gpio2.o -lwiringPi

gpio2.o: gpio2.c
	cc -g -o gpio2.o -c gpio2.c

debug: gpio2
	sudo kdbg ./gpio2

run: gpio2
	sudo ./gpio2

clean:
	rm -f *.o gpio2
