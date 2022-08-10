assembler:	preprocessor.o main.o tables.o	convert.o	symboltable.o	datatable.o	firstcheck.o
	gcc	-g	-Wall	-ansi	-pedantic	preprocessor.o	main.o	tables.o	convert.o	datatable.o	symboltable.o	firstcheck.o	-o	assembler
preprocessor.o: preprocessor.c preprocessor.h tables.h
	gcc	-c	-Wall	-ansi	-pedantic	preprocessor.c	-o	preprocessor.o
main.o: main.c preprocessor.h
	gcc	-c	-Wall	-ansi	-pedantic	main.c	-o	main.o
tables.o: tables.c tables.h DataTable.h
	gcc	-c	-Wall	-ansi	-pedantic	tables.c	-o	tables.o
convert.o:	convert.c	convert.h	tables.h
	gcc	-c	-Wall	-ansi	-pedantic	convert.c	-o	convert.o
symboltable.o:	SymbolTable.c	SymbolTable.h 
	gcc	-c	-Wall	-ansi	-pedantic	SymbolTable.c	-o	symboltable.o
datatable.o:	DataTable.c	DataTable.h
	gcc	-c	-Wall	-ansi	-pedantic	DataTable.c	-o	datatable.o
firstcheck.o:	firstcheck.c	firstcheck.h	SymbolTable.h	DataTable.h
	gcc	-c	-Wall	-ansi	-pedantic	firstcheck.c	-o	firstcheck.o