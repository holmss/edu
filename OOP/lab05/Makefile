.PHONY   :  all, clean
TARGET   := $(shell basename $(shell pwd))
SRC      := $(wildcard *.cpp)
HDR      := $(wildcard *.h{,pp})
CXX      := g++
CFLAGS   := -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3 -Weffc++

all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm

main.o: main.cpp $(HDR) 
	$(CXX) $(CFLAGS) -c $< 

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) -c -o $@ $<