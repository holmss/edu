.PHONY :  all, clean
TARGET := lab3
SRC    := $(wildcard *.cpp)
HDR    := $(wildcard *.hpp)
CXX    := g++
CFLAGS := -pedantic -Wall -Wextra -Wpedantic -W -Wno-sign-compare -Wno-long-long -g3#-std=c++11 # -lm -pg -DDMALLOC -DDMALLOC_FUNC_CHECK -I/usr/local/include -L/usr/local/lib


all: $(TARGET)

clean:
	rm -f $(TARGET) $(SRC:%.cpp=%.o)

main.o: main.cpp $(HDR)
	$(CXX) $(CFLAGS) -c main.cpp

%.o: %.cpp $(HDR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(SRC:%.cpp=%.o)
	$(CXX) $(CFLAGS) -o $@ $^ -lm