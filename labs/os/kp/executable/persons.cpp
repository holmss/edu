#include "../header/persons.h"

persons::persons(){
    mkdir(path, 0755);
    ifstream ifs(path + string("passwd.db"));
    if (!ifs.is_open()){
        ofstream ofs(path + string("passwd.db"));
        ofs.close();
        ifs.open(path + string("passwd.db"));
    }
    string name, password;
    while (ifs >> name >> password){
        cout << name << "\t" << password << endl;
        person p;
        p.logged_in = false;
        p.password = password;
        ifstream ifs(path + name);
        if (ifs.is_open()){
            string str;
            while (getline(ifs, str)){
                p.notifies.push_back(str);
            }
        }
        data.insert(make_pair(name, p));
    }
    ifs.close();
    password_db.open(path + string("passwd.db"), ios_base::app);
}

persons::~persons(){
    for (auto i = data.begin(); i != data.end(); ++i){
        ofstream ofs(path + i->first);
        for (auto it: i->second.notifies)
            ofs << it << "\n";
        ofs.close();
    }
}

unordered_map<string, person>::iterator
persons::find(const string & name){
    return data.find(name);
}

bool
persons::find_person(const string & name){
    auto it = data.find(name);
    if (it != data.end()) return true;
    return false;
}

void
persons::add_ask(const string & from, const string & to){
    find(to)->second.notifies.push_back(string("ask ") + from);
}

void
persons::add_answer(const string & from, const string & to){
    find(to)->second.notifies.push_back(string("answer ") + from);
}

int
persons::login(const string & name, const string & password){
    auto it = data.find(name);
    if (it != data.end()){
        if (!it->second.logged_in &&
            it->second.password == password){
                it->second.logged_in = true;
                return LOGIN_SUCCESS;
        }
        else if (it->second.logged_in)
            return LOGIN_ERR_ALREADY_LOGGED;
    }
    return LOGIN_ERR_NO_CLIENT;
}

void
persons::logout(const string & name){
    auto it = data.find(name);
    if (it != data.end()){
        it->second.logged_in = false;
    }
}

int
persons::registrate(const string & name, const string & password){
    auto it = data.find(name);
    if (it != data.end()) return REGISTRATE_ERR_ALREADY_EXIST;
    password_db << name << " " << password << endl;
    struct person p = {password, list<string>(), true};
    data.insert(make_pair(name, p));
    return REGISTRATE_SUCCESS;
}

void
persons::add_message(const string & from, const string & to, const string & message){
    find(to)->second.notifies.push_back(string("message ") + from + " " + message);
}

string
persons::check(const string & name){
    auto it = find(name);
    if (it->second.notifies.empty()) return "0";
    else{
        string answer = it->second.notifies.front();
        it->second.notifies.pop_front();
        return answer;
    }
}