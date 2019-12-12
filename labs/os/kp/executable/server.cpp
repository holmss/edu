#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>

#include "../header/connection.h"
#include "../header/persons.h"
#include "../header/command.h"

using namespace std;

command action;
connection connect;
persons database;

void ok(){cout << "ok\n";}

void login(){
	string name = action.get_next_arg();
	string password = action.get_next_arg();
	connect.send(
		to_string(
		database.login(name, password)));
}

void registrate(){
	string name = action.get_next_arg();
	string password = action.get_next_arg();
	connect.send(to_string(database.registrate(name, password)));
//	database.login(name, password);
}

void parce_action(){
	string com = action.get_action();
	if (com == "login"){
		login();
	}else if (com == "registrate"){
		registrate();
	}else if (com == "logout"){
		database.logout(action.get_next_arg());
		connect.send("");
	}else if (com == "ask"){
		string from = action.get_next_arg();
		string to = action.get_next_arg();
		database.add_ask(from, to);
		connect.send("");
	}else if (com == "answer"){
		string from = action.get_next_arg();
		string to = action.get_next_arg();
		database.add_answer(from, to);
		connect.send("");
	}else if (com == "send"){
		string from = action.get_next_arg();
		string to = action.get_next_arg();
		string message = action.get_all();
		database.add_message(from, to, message);
		connect.send("");
	}else if (com == "check"){
		string name = action.get_next_arg();
		connect.send(database.check(name));
	}else if (com == "find"){
		string name = action.get_next_arg();
		if (database.find_person(name))
			connect.send("1");
		else connect.send("0");
	}
}

int main(){
	connect.connect(connection::server);
	cout << "server started...\n";
	while (true){
		action.parce_string(connect.receive());
		parce_action();
	}
	return 0;
}
