EXE1 = testimage
OBJS1 = png.o rgbapixel.o image.o testimage.o

EXE2 = testscene
OBJS2 = png.o rgbapixel.o image.o scene.o testscene.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all: testimage testscene
$(EXE1): $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o $(EXE1)
$(EXE2): $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXE2)
png.o: png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp
rgbapixel.o: png.h rgbapixel.h rgbapixel.cpp
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
image.o: image.h png.h image.cpp
	$(CXX) $(CXXFLAGS) image.cpp
scene.o: scene.h scene.cpp image.h png.h
	$(CXX) $(CXXFLAGS) scene.cpp
testimage.o: testimage.cpp image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) testimage.cpp
testscene.o: testscene.cpp image.h scene.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) testscene.cpp
clean: 
	rm -f *.o $(EXE1) $(EXE2);
