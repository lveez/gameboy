ALLFILES:= $(wildcard src/*.c src/*/*.c)
SRCFILES:= $(filter-out src/tests.c, $(ALLFILES))
TESTFILES:= $(filter-out src/main.c, $(ALLFILES))


all:
	gcc $(SRCFILES) -o./bin/gb_emu_release.exe

debug:
	gcc -D GBDBG $(SRCFILES) -o./bin/gb_emu_debug.exe

test:
	gcc -D GBDBG $(TESTFILES) -o./bin/gb_emu_tests.exe
