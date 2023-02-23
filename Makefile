CC = @gcc 								# compilador que queremos (@ esconde comando)
CFLAGS = -g -Wall						# flags para compilar .c

all: criptografa decriptografa

# condicoes implicitas compilam com CC e CFLAGS
criptografa:  criptografa.o 
decriptografa: decriptografa.o

clean:
	rm -f decriptografa.o criptografa.o

purge: clean
	rm -f criptografa decriptografa

run: clean purge all