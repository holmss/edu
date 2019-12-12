#include "../header/client_console.h"

void ok(){cout << "ok" << endl;}

struct ListenerArgs{
    pthread_t   _listener_thread;
    connection  *_connect;
    person      *_client;
    bool        _run;
}ListenerArgs;

struct ListenerFlags{
    bool        _pause,
                _background;
}ListenerFlags;

struct MessagingListenerArgs : ListenerArgs{
    string      _friend_name;
}MessagingListenerArgs;

struct ScreenCheckerArgs : ListenerArgs{
    string          _friend_name;
}ScreenCheckerArgs;


notify notification;
struct ListenerFlags listenerFlags;

bool ask(const string & text){
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

void ListenerFlagsInit(struct ListenerFlags *listenerFlags){
    listenerFlags->_background  = false;
    listenerFlags->_pause       = false;
}

void ListenerArgsInit(struct ListenerArgs *listenerArgs, connection *connect, person *client){
    listenerArgs->_client   = client;
    listenerArgs->_connect  = connect;
    listenerArgs->_run      = true;
}

void RunListener(void* (*listener)(void *), struct ListenerArgs* args){
    pthread_create(&(args->_listener_thread)
        , NULL
        , listener
        , args);
}

void PrintClosingListener(){
    cout << "closing...\n";
}

void StopListener(struct ListenerArgs* listenerArgs, bool print){
    listenerArgs->_run = false;
    if (print) PrintClosingListener();
    pthread_join(listenerArgs->_listener_thread, NULL);
}

client_console::client_console(){
    connect.connect(connection::client);
    p.enter(connect);
    if (!p.is_logged()){
        SendMessage("You not logged in");
    }else{
        SendMessage("You've been logged in");
        mkdir(p.get_name().data(), 0755);
        p.read_friends();
    }
}

client_console::~client_console(){
    if (p.is_logged()) p.logout(connect);
}

void
MainHelp(){
    cout   << "\n\nYou can:\n\t" 
           << "[clear] screen\n\t"
           << "[answer] for asking\n\t"
           << "[list] your friends\n\t"
           << "[messaging] <friend>\n\t"
           << "[find] person\n\t" 
           << "[logout]\n"
           << "[help] and show this list\n";
}

pthread_mutex_t mutex;

void* 
Listener(void* args){
    struct ListenerArgs *listenerArgs = (struct ListenerArgs*)args;
    connection * connect = listenerArgs->_connect;
    person * client = listenerArgs->_client;
    bool checked = false;

    while(listenerArgs->_run){
        if (listenerFlags._pause) sleep(1);
//        pthread_mutex_lock(&mutex);
        connect->send(string("check ") + client->get_name());
        string get = connect->receive();
        stringstream ss(get);

        string value;
        ss >> value;

        while(value != "0"){
            checked = true;

            if (value == "message"){
                string from, message;
                ss >> from;
                getline(ss, message);
                client->add_message(from, from, message);
                notification.add_message(from);

            }else if (value == "ask"){
                string name;
                ss >> name;
                notification.add_friend_ask(name);

            }else if (value == "answer"){
                string name;
                ss >> name;
                notification.add_friend_answer(name);
                client->add_friend(name);
            }

            connect->send(string("check ") + client->get_name());
            stringstream new_ss(connect->receive());
            swap(ss, new_ss);
            ss >> value;
        }

        if (checked && !listenerFlags._background && notification.any_news()){
            notification.show();
            cout << "Write command: ";
            cout.flush();
            checked = false;
        }
        sleep(1);
    }
    return NULL;
}

void
client_console::MainMenu(){
    if (!p.is_logged()) return;

    if (notification.read_notifies(p.get_name()))
        notification.show();

    MainHelp();

//    pthread_mutex_init(&mutex, NULL);
    struct ListenerArgs listenerArgs;
    ListenerFlagsInit(&listenerFlags);
    ListenerArgsInit(&listenerArgs, &connect, &p);
    void* (*listener)(void*);
    listener = Listener;
    RunListener(listener, &listenerArgs);

    for(;;){
        if (cin.eof()) break;
        cout << "Write command: ";
        if (!ParceMainCommand()) break;
    }

    StopListener(&listenerArgs, true);

    notification.save_notifies(p.get_name());
//    pthread_mutex_destroy(&mutex);
}

void
AnswerHelp(){
    cout    << "\n>>> To add write: [add] <name>\t\t<<<\n"
            << ">>> To delete write [delete] <name>\t<<<\n"
            << ">>> [help] to print this message\t\t<<<\n"
            << ">>> [quit] To end enter\t\t\t<<<\n";    
}

bool
client_console::ParceAnswer(){
    string s;
    AnswerHelp();
    if (!notification.asks()){
        SendError("You don't have asks");
        return true;
    }else{
        listenerFlags._pause = true;
        notification.print_asks();
        while (notification.asks() && cin >> s){
            if (s == "add"){
                if (! (cin >> s)) return false;
                if ((notification.asked(s))){
                    p.add_friend(s);
                    SendMessage("success added");
                    connect.send(string("answer " ) + p.get_name() + " " + s);
                    notification.asked(s);
                }else SendError("wrong name");
            }else if (s == "delete"){
                if (! (cin >> s)) return false;
                if (notification.asked(s)) SendMessage("seccess deleted");
                else SendError("wrong name");
            }else if (s == "quit") break;
            else if (s == "help") AnswerHelp();
            else SendError("Wrong command");
        }
        listenerFlags._pause = false;
    }
    return true;
}

bool
client_console::ParceMainCommand(){
    string s;
    if (!(cin >> s)) return false;
    if (s == "clear"){
        system("clear");
        return true;
    }else if (s == "list"){
        p.list_friends();
        return true;
    }else if (s == "answer"){
        if (!ParceAnswer()) return false;
    }else if (s == "messaging"){
        string name;
        cin >> name;
        if (p.is_friend(name))
            return OpenMessaging(name);
        else
            SendError("No such friend");
    }else if (s == "find"){
        string name;
        if (!(cin >> name)) return false;
        if (FindPerson(name)){
            SendMessage("person has been found");
            if (ask("Add him yo your friends?")){
                connect.send("ask " + p.get_name() + " " + name);
                connect.receive();
            }
        }else SendMessage("Not found");
    }else if (s == "logout"){
        return false;
    }else if (s == "help"){
        MainHelp();
    }
    else{
        SendError("Wrong command");
    }
    return true;
}

bool
client_console::FindPerson(const string & name){
    connect.send("find " + name);
    stringstream ss(connect.receive());
    bool is_found;
    ss >> is_found;
    return is_found;
}

void
client_console::SendMessage(const string & message){
    cout << "-----------------------------------------------------\n"
         << message << "\n" 
         << "-----------------------------------------------------\n";
}

void
client_console::SendError(const string & error){
    cout<< "\n*********************************************\n"
        << error
        << "\n*********************************************\n";
}

void HelpMessaging(){
    cout    << "You can:\n\t"
            << "[send] <message>\n\t"
            << "[help] to show this message\n\t"
            << "[quit] to close this window\n";
}

void* MessagingListener(void* args){
    struct MessagingListenerArgs * listenerArgs = (struct MessagingListenerArgs*)args;
    struct timespec t = {0, 100000000};                                     // 0.1 c

    while (listenerArgs->_run){
        if (notification.messages_count(listenerArgs->_friend_name) != 0){
            Redraw(listenerArgs->_client, listenerArgs->_friend_name);
            notification.message_seen(listenerArgs->_friend_name);
        }
        nanosleep(&t, NULL);
    }
    return NULL;
}


//checks for changing screen size
void*
ScreenCheker(void* args){
    struct ScreenCheckerArgs* arg = (struct ScreenCheckerArgs*)args;
    struct winsize wsize1, wsize2;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize1);
    wsize2 = wsize1;
    while (arg->_run){
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize1);
        if (wsize1.ws_col != wsize2.ws_col
            || wsize1.ws_row != wsize2.ws_row){
                Redraw(arg->_client, arg->_friend_name);
                wsize2 = wsize1;
            }
        sleep(1);
    }
    return NULL;
}


// parce "hello world" to
// [hello] [world]
pair<string, list<string>> ParseMessage(const string & message){        
    string sender_name, tmp;                                            
    list<string> _message;
    stringstream ss(message);
    ss >> sender_name;
    while (ss >> tmp) _message.push_back(tmp);
    return make_pair(sender_name, _message);
}

// make [hello] [world] to
// "hello"
// "world"
vector<string> MakeStringBox(const list<string>& message, size_t column){
    vector<string> result;
    string current_string;
    for (auto m : message){
        if (current_string.size() + m.size() < column){
            current_string += m + " ";
        }else if (current_string.size() != 0){
            result.push_back(current_string);
            current_string.clear();
        }
        if (current_string.size() != 0) continue;
        else if (m.size() < column) current_string += m;
        else{
            for (size_t i = 0; i < m.size();){
                for (;i < column && i < m.size(); ++i){
                    current_string += m[i];
                }
                if (i == column) result.push_back(current_string);
            }
        }
    }
    if (!current_string.empty()) result.push_back(current_string);
    return result;
}

string FillString(char value, size_t count){
    string res;
    while(count--) res += value;
    return res;
}

/*
make
"hello"
"world"
into
---------
hello   |
world   |
---------
 */
vector<string> MakeBox(string message, size_t ws_col, string my_name){
    auto sender_message = ParseMessage(message);
    auto message_box = MakeStringBox(sender_message.second, ws_col / 2 - 2);
    vector<string> result;
    bool is_me = (sender_message.first == my_name);
    if (is_me){
        result.push_back(sender_message.first);
        result.push_back(FillString('-', ws_col / 2));
        string tmp_string;
        for (auto s : message_box){
            tmp_string += s;
            tmp_string += FillString(' ', ws_col / 2 - tmp_string.size() - 1) + '|';
            result.push_back(tmp_string);
        }
        result.push_back(FillString('-', ws_col / 2));
    }else{
        result.push_back(FillString(' ', ws_col - sender_message.first.size()) + sender_message.first);
        result.push_back(FillString(' ', ws_col / 2) + FillString('-', ws_col / 2));

        string tmp_string = FillString(' ', ws_col / 2) + "|";
        for (auto s : message_box){
            tmp_string += s;
            result.push_back(tmp_string);
            string tmp_string = FillString(' ', ws_col / 2) + "|";
        }
        result.push_back(FillString(' ', ws_col / 2) + FillString('-', ws_col / 2));
    }
    return result;
}

/*
parce messages and redraw them into
---------
        |
---------
*/
void
Redraw(person * client, string friend_name){
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    auto messages = client->get_messages(friend_name);
    list<string> screen;
    for(auto m = messages->size() - 1; m < messages->size(); --m){
        auto box = MakeBox((*messages)[m], wsize.ws_col, client->get_name());
        for(auto it = box.rbegin(); it != box.rend(); ++it){
            screen.push_front(*it);
        }
        if (screen.size() >= wsize.ws_row) break;
    }
    while(screen.size() < wsize.ws_row) screen.push_front("");

    for (auto str : screen) cout << str << "\n";
    cout.flush();
}

bool
client_console::OpenMessaging(const string & friend_name){
    system("clear");
//    p.show_last_messages(friend_name, count_of_first_messages);
    Redraw(&p, friend_name);
    HelpMessaging();
    listenerFlags._background = true;
    string command;

    void* (*listener)(void*);
    void* (*checker)(void*);
    listener = MessagingListener;
    checker = ScreenCheker;
    struct ScreenCheckerArgs scargs;
    struct MessagingListenerArgs messagingListenerArgs;
    ListenerArgsInit(&scargs, &connect, &p);
    ListenerArgsInit(&messagingListenerArgs, &connect, &p);
    scargs._friend_name = messagingListenerArgs._friend_name = friend_name;
    RunListener(listener, &messagingListenerArgs);
    RunListener(checker, &scargs);

    bool correct_end = false;

    while (cin >> command){
        if (command == "quit") {
            correct_end = true;
            break;

        }else if (command == "send"){
            string message;
            cin.get();
            getline(cin, message);
            connect.send(string("send ") + p.get_name() + " " + friend_name + " " + message);
            p.add_message(friend_name, p.get_name(), message);
            Redraw(&p, friend_name);

        }else if (command == " send"){
            size_t value;
            cin >> value;
            p.show_last_messages(friend_name, value);

        }else if (command == "help")
            HelpMessaging();

        else{
            SendError("Wrong command");
        }
    }

    StopListener(&messagingListenerArgs, correct_end);
    StopListener(&scargs, false);

    listenerFlags._background = false;
    return correct_end;
}