CXXFLAGS=-std=c++11 -g
LFLAGS=
LIBS=-lSDL2 -lGLEW -lGL
SRC=$(shell find . -name "*.cpp")
OBJ=$(SRC:%.cpp=%.o)

.PHONY: build buildparallel run clean

buildparallel:
	make -j 8 build

build: $(OBJ)
	g++ $(LFLAGS) $^ $(LIBS) -obuild

clean:
	rm *.o

run: buildparallel
	./build 2>&1 | tee output