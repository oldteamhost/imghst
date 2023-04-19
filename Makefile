all:
	gcc -c imghst.c -lcurl
	gcc -o imghst imghst.o -lcurl
	rm -rf *.o
