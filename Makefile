.PHONY: all format clean debug release run

all: format debug

format:
	indent -linux *.c *.h

clean:
	rm -rf build/

build:
	mkdir -p build

build/canvas.o: build canvas.c
	gcc -o build/canvas.o canvas.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/main.o: build main.c
	gcc -o build/main.o main.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/rawr: build build/canvas.o build/main.o
	gcc -o build/rawr build/canvas.o build/main.o -lraylib -lGL -lm -ldl -lrt -lX11 $(FLAGS)

debug: FLAGS=-g
debug: build/rawr

release: FLAGS=-O3 -DLOG_LEVEL=LOG_WARNING
release: build/rawr
