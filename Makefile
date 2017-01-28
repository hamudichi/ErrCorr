# Makefile 
# Exec : make or make debug
# Auth : Mohamad Yassine
# Date : 01/27/2017
DEPS = bit_manipulation.h

all: transmit.c receive.c bit_manipulation.c 
	gcc -o tran transmit.c bit_manipulation.c
	gcc -o recv receive.c bit_manipulation.c

debug: transmit.c receive.c bit_manipulation.c 
	gcc -g -o tran transmit.c bit_manipulation.c
	gcc -g -o recv receive.c bit_manipulation.c