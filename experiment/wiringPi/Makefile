all: gpio2

gpio2: gpio2.o
	cc -o gpio2 gpio2.o -lwiringPi

run: gpio2
	sudo ./gpio2

clean:
	rm -f *.o gpio2
