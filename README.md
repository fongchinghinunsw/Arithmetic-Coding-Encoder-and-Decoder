# Arithmetic-Coding-Encoder-and-Decoder
Encoder and decoder (called aencode and adecode, respectively) will take input from the standard input, and produce output to the standard output.

The input to the encoder is the source content to be encoded. It can be input via the terminal and terminated by a Ctrl-D ("^D"). The output of the encoder will contain: the frequency of each symbol (sorted lexicographically in ascending order and one line each); the low and the high (separated by a space) of the final result at the last line.

The input to the decoder is the same as the output from the encoder, except that the last line contains a decimal number (the AC encoded value of the source content), plus optionally a space and then some comment text.

## Usage
```
> cat a.txt
BILL GATES>
> aencode < a.txt
  1
A 1
B 1
E 1
G 1
I 1
L 2
S 1
T 1
0.2572167752 0.2572167756  
>
> cat a.txt | aencode | adecode > b.txt
> diff a.txt b.txt
>
```
