EXENAME = mp1
OBJS = main.o png.o rgbapixel.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

mp1: main.o png.o rgbapixel.o
	clang++ main.o png.o rgbapixel.o -o mp1
main.o: main.cpp png.h rgbapixel.h
	clang++ -c main.cpp
png.o: png.cpp png.h rgbapixel.h
	clang++ -c png.cpp
rgbapixel.o: png.h rgbapixel.h
	     clang++ -c rgbapixel.cpp
clean: 
	rm mp1 *.o
