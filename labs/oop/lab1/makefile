.PHONY=all clean
KEYS=-pedantic -Wall -Wextra -Wpedantic -Werror -Wno-sign-compare -Wno-long-long -g3 -lm
TARGET=lab1
CXX=g++

all: $(TARGET)

PENTAGON.o: PENTAGON.cpp PENTAGON.h 
	$(CXX) $(KEYS) PENTAGON.cpp -c

HEXAGON.o: HEXAGON.cpp HEXAGON.h 
	$(CXX) $(KEYS) HEXAGON.cpp -c 
	
OCTAGON.o: OCTAGON.cpp OCTAGON.h 
	$(CXX) $(KEYS) OCTAGON.cpp -c 

MAIN.o: PENTAGON.h HEXAGON.h OCTAGON.h MAIN.cpp
	$(CXX) $(KEYS) MAIN.cpp -c 

$(TARGET): MAIN.o PENTAGON.o HEXAGON.o OCTAGON.o
	$(CXX) $(KEYS) -o $(TARGET) MAIN.o PENTAGON.o HEXAGON.o OCTAGON.o 

clean:
	rm -rf *.o $(TARGET)
