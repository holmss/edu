CXX=g++
WARN_FLAGS=-Wall -Wextra
CXX_FLAGS=-Werror $(WARN_FLAGS) -std=c++17 -march='native' -O2 -pedantic
OBJ_CXX_FLAGS=$(CXX_FLAGS) -c
EXE=executable/
HEAD=header/
SERVER_HEADERS=$(HEAD)connection.h $(HEAD)persons.h $(HEAD)command.h 
CLIENT_HEADERS=$(HEAD)connection.h $(HEAD)person.h $(HEAD)client_console.h $(HEAD)notify.h
SERVER_OBJECTS=connection.o persons.o command.o server.o 
CLIENT_OBJECTS=connection.o person.o client_console.o notify.o client.o 

all: server client

server: $(SERVER_OBJECTS) $(SERVER_HEADERS)
	$(CXX) $(CXX_FLAGS) -lzmq $(SERVER_OBJECTS) -o server

client: $(CLIENT_OBJECTS) $(CLIENT_HEADERS)
	$(CXX) $(CXX_FLAGS) -lzmq -pthread $(CLIENT_OBJECTS) -o client

server.o: $(EXE)server.cpp $(SERVER_HEADERS)
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)server.cpp -o server.o

client.o: $(EXE)client.cpp $(CLIENT_HEADERS)
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)client.cpp -o client.o

connection.o: $(EXE)connection.cpp $(HEAD)connection.h
	$(CXX) $(OBJ_CXX_FLAGS) -lzmq $(EXE)connection.cpp -o connection.o

persons.o: $(EXE)persons.cpp $(HEAD)persons.h
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)persons.cpp -o persons.o

command.o: $(EXE)command.cpp $(HEAD)command.h
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)command.cpp -o command.o

person.o: $(EXE)person.cpp $(HEAD)person.h $(HEAD)connection.h
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)person.cpp -o person.o

client_console.o: $(EXE)client_console.cpp $(HEAD)client_console.h $(HEAD)connection.h $(HEAD)person.h
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)client_console.cpp -pthread -o client_console.o

notify.o: $(EXE)notify.cpp $(HEAD)notify.h 
	$(CXX) $(OBJ_CXX_FLAGS) $(EXE)notify.cpp -o notify.o

clear:
	rm *.o server client
