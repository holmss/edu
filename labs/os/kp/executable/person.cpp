#include "../header/person.h"


bool ask_yes_no(const string & text){
	string answer;
	while (true){
		cout << text << " [Y/n] ";
		cin >> answer;
		switch (answer[0])
		{
			case 'y':
			case 'Y':
				return true;
			case 'N':
			case 'n':
				return false;
		}
	}
}

person::person(){}

person::~person(){
	ofstream file;
	for (auto fr : friends){
		file.open(name + "/" + fr.first);
		for (auto message : fr.second)
			file << message << "\n";
		file.close();	
	}
}

bool
person::is_logged(){ return is_logged_in; }

string&
person::get_name() { return name; }

string&
person::get_passwd(){return passwd; }

void
person::set_name(const string & name){
    this->name = name;
}
bool
person::is_friend(const string & friend_name){
	return friends.find(friend_name) != friends.end();
}

vector<string>*
person::get_messages(const string & name){
	return &friends.find(name)->second;
}

void
person::set_passwd(const string & passwd){
    this->passwd = passwd;
}

/*
fstream*
person::get_friend(const string & name){
    return friends.find(name)->second;
}
*/

void
person::add_friend(const string & friend_name){
	FILE * file = fopen((name + "/" + friend_name).data(), "w+");
	fclose(file);
    friends.insert(make_pair(friend_name, vector<string>()));
}

void
person::add_message(const string & _friend, const string & sender, const string & message){
	friends.find(_friend)->second.push_back(sender + " " + message);
}

bool
person::enter(connection & connect){
	string name, password;
	if (login(name, password, connect)){
		return true;
	}else {
		if (ask_yes_no("Do you want registrate?")){
			if (ask_yes_no("Use last name and password?")){
				registrate(name, password, connect);
                this->name = name;
                this->passwd = password;
				return true;
			}else{
				if (registrate(connect)) return true;
			}
		}
	}
	return false;
}

bool
TryLoginAgain(){
	cout << "Error. No such login or password\n";
	if (!ask_yes_no("Try log in again?")){
		return false;
	}
	return true;
}

void AlreadyLogged(){
	cout	<< "\n!!!Your client program have been closed with errors!!!"
			<< "\n!!!But, of course, it's not problem. Good day!!!\n";
}

bool 
person::login(string & name, string & password, connection & connect){
	bool running = true;
	while (running){
		cout << "enter name: ";
		cin >> name;
		cout << "enter password: ";
		cin >> password;
		string message = "login " + name + " " + password;
		connect.send(message);
		istringstream iss(connect.receive());
		int login_error;
		iss >> login_error;
		switch (login_error)
		{
		case LOGIN_ERR_NO_CLIENT:
			if (!TryLoginAgain()) return false;
			break;
		case LOGIN_ERR_ALREADY_LOGGED:
			AlreadyLogged();
			[[fallthrough]];
		case LOGIN_SUCCESS:
            this->name = name;
            this->passwd = password;
			running = false;
			break;
		}
	}
	return true;
}

bool 
person::registrate(const string & name, const string & password, connection & connect){
	string message = "registrate " + name + " " + password;
	connect.send(message);
	int success;
	stringstream ss(connect.receive());
	ss >> success;
	return success == REGISTRATE_SUCCESS;
}

bool 
person::registrate(connection & connect){
	string name, password;
	bool success = true;
	while (success){
		cout << "enter name: ";
		cin >> name;
		cout << "enter password: ";
		cin >> password;
		if (!registrate(name, password, connect)){
			cout << "Such user is already exist\n";
			if (!ask_yes_no("Try registrate again?"))
				return false;
		}else break;
	}
    this->name = name;
    this->passwd = password;
	return true;
}

void
person::logout(connection & connnect){
    connnect.send("logout " + name);
}

void 
person::list_friends(){
	for (auto i : friends) cout << i.first << "\n";
}

void
person::read_messages(const string & friend_name){
	fstream fr(name + "/" + friend_name);
	string message;
	vector<string> friend_messages;
	while (getline(fr, message)){
		friend_messages.push_back(message);
	}
	friends.insert(make_pair(friend_name, friend_messages));
	fr.close();
}

void
person::read_friends(){
	DIR * directory = opendir(name.data());
	struct dirent * entry;
	while ((entry = readdir(directory))){
		if (entry->d_type == DT_REG) read_messages(entry->d_name);
	}
	closedir(directory);
}

void
person::show_last_messages(const string & friend_name, size_t count){
	auto _messages = friends.find(friend_name)->second;
	auto size = _messages.size();
	auto index = max(size_t(0), size - count > size ? 0 : size - count);
	for (; index < _messages.size(); ++index){
		cout << _messages[index] << "\n";
	}
}
