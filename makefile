default: aencode adecode

aencode: aencode.c
	gcc -o aencode aencode.c ac_helper.c -lmpfr -lgmp
adecode: adecode.c
	gcc -o adecode adecode.c ac_helper.c -lmpfr -lgmp