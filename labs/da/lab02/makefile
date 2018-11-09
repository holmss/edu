.PHONY :  all, clean
TARGET := lab02
SRC    := $(wildcard *.cpp)
HDR    := $(wildcard *.hpp)
CXX    := g++
CFLAGS := -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3 -lm

all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^

lab02.o: lab02.cpp $(HDR) 
	$(CXX) $(CFLAGS) -c lab02.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<