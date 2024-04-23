.PHONY: all format clean debug release run

all: format debug

format:
	indent -linux *.c *.h

clean:
	rm -rf build/

build:
	mkdir -p build

build/raygui.o: build raygui/src/raygui.h
	cp raygui/src/raygui.h build/raygui.c
	gcc -o build/raygui.o -o build/raygui.o build/raygui.c -c -fpic -DRAYGUI_IMPLEMENTATION -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/gui.o: build gui.c
	gcc -o build/gui.o gui.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/canvas.o: build canvas.c
	gcc -o build/canvas.o canvas.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/ui.o: build ui.c
	gcc -o build/ui.o ui.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/main.o: build main.c
	gcc -o build/main.o main.c -c -fpic -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(FLAGS)

build/rawr: build build/raygui.o build/gui.o build/canvas.o build/ui.o build/main.o
	gcc -o build/rawr build/raygui.o build/gui.o build/canvas.o build/ui.o build/main.o -lraylib -lGL -lm -ldl -lrt -lX11 $(FLAGS)

debug: FLAGS=-g
debug: build/rawr

release: FLAGS=-O3 -DLOG_LEVEL=LOG_WARNING
release: build/rawr
