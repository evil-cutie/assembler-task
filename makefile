assembler:	preprocessor.o main.o tables.o
	gcc	-g	-Wall	-ansi	-pedantic	preprocessor.o	main.o	tables.o	-o	assembler
preprocessor.o: preprocessor.c preprocessor.h tables.h
	gcc	-c	-Wall	-ansi	-pedantic	preprocessor.c	-o	preprocessor.o
main.o: main.c preprocessor.h
	gcc	-c	-Wall	-ansi	-pedantic	main.c	-o	main.o
tables.o: tables.c tables.h
	gcc	-c	-Wall	-ansi	-pedantic	tables.c	-o	tables.o