target=src/main.o src/log.o src/builtins.o src/execute.o src/parser.o src/pipe.o src/redirect.o src/my_ls.o src/my_ps.o

CC=gcc

my_shell: $(target)
	$(CC) $(target) -o bin/myshell -Llib -lmathlib -Wl,-rpath=$(PWD)/lib

src/main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o -Iinclude -Ilib/include

src/log.o: src/log.c
	$(CC) -c src/log.c -o src/log.o -Iinclude -Ilib/include

src/builtins.o: src/builtins.c
	$(CC) -c src/builtins.c -o src/builtins.o -Iinclude -Ilib/include

src/execute.o: src/execute.c
	$(CC) -c src/execute.c -o src/execute.o -Iinclude -Ilib/include

src/parser.o: src/parser.c
	$(CC) -c src/parser.c -o src/parser.o -Iinclude -Ilib/include

src/pipe.o: src/pipe.c
	$(CC) -c src/pipe.c -o src/pipe.o -Iinclude -Ilib/include

src/redirect.o: src/redirect.c
	$(CC) -c src/redirect.c -o src/redirect.o -Iinclude -Ilib/include

src/my_ls.o: src/my_ls.c
	$(CC) -c src/my_ls.c -o src/my_ls.o -Iinclude -Ilib/include
src/my_ps.o: src/my_ps.c
	$(CC) -c  src/my_ps.c -o src/my_ps.o -Iinclude -Ilib/include
clean:
	@echo "cleaning Object files..."
	@rm -f src/*.o bin/myshell

setup:
	@echo "Configuring environment..."
	@grep -qxF 'export PATH=$$PATH:$(PWD)/bin' ~/.bashrc || \
	echo 'export PATH=$$PATH:$(PWD)/bin' >> ~/.bashrc
	@grep -qxF 'export MANPATH=$(PWD)/lib/man:$$MANPATH' ~/.bashrc || \
	echo 'export MANPATH=$(PWD)/lib/man:$$MANPATH' >> ~/.bashrc
	@echo "Done. Run: source ~/.bashrc"
