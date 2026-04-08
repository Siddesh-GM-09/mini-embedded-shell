target=main.o log.o 
CC=gcc
my_shell:$(target)
	$(CC) $(target) -o my_shell
main.o:main.c
	$(CC) -c main.c
log.o:log.c
	$(CC) -c log.c
clear:
	@echo "cleaning Object files..."
	@rm -vr *.o
