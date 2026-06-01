hexeditplus : hexeditplus.o
	gcc -m32 -g -Wall -o hexeditplus hexeditplus.o

hexeditplus.o : hexeditplus.c
	gcc -m32 -g -Wall -c -o hexeditplus.o hexeditplus.c

task4 : task4.o
	gcc -m32 -g -Wall -fno-pie -fno-stack-protector -o task4 task4.o

task4.o : task4.c
	gcc -m32 -g -Wall -fno-pie -fno-stack-protector -c -o task4.o task4.c

#clean
clean :
	rm -f *.o hexeditplus task4