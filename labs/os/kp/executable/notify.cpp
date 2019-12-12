#include "../header/notify.h"

#define max2(a, b) (a > b ? a : b)

notify::notify(){}
notify::~notify(){}

void
print_string(const string & s, size_t max_size, struct timespec * t){
    size_t i;
    for (i = 0; i < s.size(); ++i){
        cout << s[i];
        cout.flush();
        nanosleep(t, NULL);
    }
    while (i < max_size){
        cout << " ";
        ++i;
    }
    cout << "|\n";
}

void
notify::show(){
    if (messages.size() == 0 &&
        friend_answers.size() == 0 &&
        friend_ask.size() == 0) 
            return;

    size_t max_size = 10;
    for (auto i : messages)
        max_size = max2(max_size, i.first.size() + to_string(i.second).size() + 10);
    for (auto i : friend_answers)
        max_size = max2(max_size, i.size() + 6);
    for (auto i : friend_ask)
        max_size = max2(max_size, i.size() + 6);
    
    struct timespec t = {0, 6000000};

    cout << "\n ";
    for (size_t i = 0; i < max_size - 1; ++i){
        cout << "-";
        cout.flush();
        nanosleep(&t, NULL);
    }
    cout << "\n";
    nanosleep(&t, NULL);

    if (! messages.empty()){
        print_string("| messages: ", max_size, &t);
        for (auto it : messages)
            print_string(string("| -> ") + it.first + " (" + to_string(it.second) + ") ", max_size, &t);
        print_string("|", max_size, &t);
    }

    if (! friend_answers.empty()){
        print_string("| answers: ", max_size, &t);
        for (auto it : friend_answers)
            print_string(string("| -> ") + it + " ", max_size, &t);
        print_string("|", max_size, &t);
        friend_answers.clear();
    }

    if (! friend_ask.empty())
        print_string("| asks: ", max_size, &t);
    for (auto it : friend_ask)
        print_string(string("| -> ") + it + " ", max_size, &t);

    cout << " ";
    for (size_t i = 0; i < max_size - 1; ++i){
        cout << "-";
        cout.flush();
        nanosleep(&t, NULL);
    }
    cout << "\n";
}

size_t
notify::messages_count(const string& name){
    auto it = messages.find(name);
    if (it != messages.end()) return it->second;
    else return 0;
}

bool
notify::any_news(){ return messages.size() 
                    || friend_answers.size() 
                    || friend_ask.size();
                    }

void
notify::add_message(const string & name){
    auto it = messages.find(name);
    if (it == messages.end()){
        messages.insert(make_pair(name, 1));
    }else ++it->second;
}

void
notify::add_friend_answer(const string & name){
    friend_answers.insert(name);
}

void 
notify::add_friend_ask(const string & name){
    friend_ask.insert(name);
}

void
notify::message_seen(const string & name){
    messages.erase(name);
}

bool
notify::asked(const string & name){
    return friend_ask.erase(name);
}

size_t
notify::asks(){
    return friend_ask.size();
}

void
notify::print_asks(){
    for (auto i : friend_ask){
        cout << " -> " << i << "\n";
    }
}

bool
notify::read_notifies(const string & directory_path){
    fstream asks, messages;
    bool changed = false;

    if (directory_path[directory_path.size() - 1] == '/'){
        asks.open(directory_path + "notifies/asks");
        messages.open(directory_path + "messages");
    }else{
        asks.open(directory_path + "/notifies/asks");
        messages.open(directory_path + "/notifies/messages");
    }

    if (!asks.is_open() || !messages.is_open()) return false;

    string name;
    size_t count;
    
    while (asks >> name){
        friend_ask.insert(name);
        changed = true;
    }
    while (messages >> name >> count){
        this->messages.insert(make_pair(name, count));
        changed = true;
    }

    asks.close();
    messages.close();
    return changed;
}

void 
notify::save_notifies(const string & directory_path){
    ofstream asks, messages;
    string path = directory_path;

    if (directory_path[directory_path.size()] - 1 == '/'){
        path += "notifies/";
    }else{
        path += "/notifies/";
    }

    mkdir(path.data(), 0755);
    asks.open(path + "asks");
    messages.open(path + "messages");

    asks.clear();
    messages.clear();

    for (auto i : friend_ask)
        asks << i << "\n";

    for (auto i : this->messages)
        messages << i.first << "\t" << i.second << "\n";
        
    asks.close();
    messages.close();
}