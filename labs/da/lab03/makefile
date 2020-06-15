.PHONY :  all, clean
TARGET := lab02
SRC    := $(wildcard *.cpp)
HDR    := $(wildcard *.hpp)
CXX    := g++
CFLAGS := -pg -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -O3 -Wno-long-long -g3 -lm
#-fprofile-arcs -ftest-coverage

all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^
#``       	rm -rf *.o

lab02.o: lab02.cpp $(HDR) 
	$(CXX) $(CFLAGS) -c lab02.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clear:
	rm -f $(TARGET) *.o
