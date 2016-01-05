
all: lcd

lcd: lcd.o
	cc -g -o lcd lcd.o -lwiringPi

lcd.o: lcd.c
	cc -g -o lcd.o -c lcd.c

debug: lcd
	sudo kdbg ./lcd

run: lcd
	sudo ./lcd

clean:
	rm -f *.o lcd 
