SRCFILES:= $(wildcard src/*.c src/*/*.c)

all:
	gcc $(SRCFILES) -o./bin/gb_emu_release.exe

debug:
	gcc -D DEBUG $(SRCFILES) -o./bin/gb_emu_debug.exe
