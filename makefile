default: aencode adecode

aencode: aencode.c
	gcc -o aencode aencode.c -lmpfr -lgmp
adecode: adecode.c
	gcc -o adecode adecode.c -lmpfr -lgmp