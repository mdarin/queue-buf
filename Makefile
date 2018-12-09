a: queue.o sllist.o main.o 
	gcc --std=gnu99 queue.o sllist.o main.o -o a
main.o: main.c
	gcc --std=gnu99 -c main.c
sllist.o: sllist.c sllist.h
	gcc --std=gnu99 -c sllist.c
queue.o: queue.c queue.h
	gcc --std=gnu99 -c queue.c
clean:
	rm -f a c main.o sllist.o queue.o
install:
	cp a /usr/local/bin/a
uninstall: 
	rm -f /usr/local/bin/a
