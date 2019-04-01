all: dropbytes

dropbytes: dropbytes.c
	gcc -O3 -march=native dropbytes.c -o dropbytes

clean:
	rm dropbytes
