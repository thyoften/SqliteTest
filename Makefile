CC := gcc
CFLAGS ?= -c
CPPC := g++

OUTPUT := sqlite_test.exe

.PHONY: clean

all: main.o sqlite3.o
	@echo Building executable...
	@${CPPC} main.o sqlite3.o -o ${OUTPUT}
	
main.o: main.cpp
	@echo Compiling main application...
	@${CPPC} ${CFLAGS} $< -o $@
	
sqlite3.o: amalgam\sqlite3.c
	@echo Compiling SQLite...
	@${CC} ${CFLAGS} $< -o $@
	
clean:
	@echo Deleting database and object files...
	@del *.o
	@del test.db
	@echo Done
	