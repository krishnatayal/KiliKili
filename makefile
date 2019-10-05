CC = gcc
ARGS = -Wall

all: tiny adder mul div shellcode

tiny: tiny.c
	$(CC) $(ARGS) -o tiny tiny.c -g

tinytar:
	tar cvf - * >tiny.tar

adder:
	gcc cgi-bin/adder.c -o cgi-bin/adder -lcurl -g
 
mul:
	gcc -O0 -m32 -fno-pie -no-pie -fno-stack-protector -mpreferred-stack-boundary=2 cgi-bin/mul.c -o cgi-bin/mul -lcurl -g

div:
	gcc -m32 -O0 -fno-pie -no-pie -fno-stack-protector -mpreferred-stack-boundary=2 -z execstack cgi-bin/div.c -o cgi-bin/div -g -lcurl
 
shellcode:
	gcc -m32  -O0 -fno-pie -no-pie -fno-stack-protector -mpreferred-stack-boundary=2 -z execstack  run_shellcode.c -o run_shellcode -g
clean:
	rm -f *.o tiny *~ cgi-bin/adder cgi-bin/mul cgi-bin/div run_shellcode


