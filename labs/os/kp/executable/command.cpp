#include "../header/command.h"

command::command(){}
command::~command(){}

void
command::parce_string(const string & s){
    stringstream new_ss(s);
    swap(ss, new_ss);
    ss >> action;
}

string&
command::get_action(){ return action; }

string
command::get_next_arg(){
    string arg;
    ss >> arg;
    return arg;
}

string
command::get_all(){ 
    string all;
    getline(ss, all);
    return all;
}