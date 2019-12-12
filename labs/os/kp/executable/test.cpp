#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

using namespace std;
bool stop;
pthread_mutex_t mutex_winsize;

void* screen_checker(void* w){
    while (!stop){
        pthread_mutex_lock(&mutex_winsize);
            ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
        pthread_mutex_unlock(&mutex_winsize);

        sleep(1);
    }
    return NULL;
}

int main(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
    
    string s = "hello, world";
    int count = 1;

    stop = false;
    pthread_t checker_thread;
    pthread_mutex_init(&mutex_winsize, NULL);
    pthread_create(&checker_thread
        , NULL
        , screen_checker
        , &w);

    while (count < 10){
        system("clear");
        for (int j = 0; j < count; ++j){
            pthread_mutex_lock(&mutex_winsize);
                int ws_col = w.ws_col;
            pthread_mutex_unlock(&mutex_winsize);
            for (int i = 0; i < ws_col - s.size(); ++i) cout << " ";
            cout << s << endl;
        }
        ++count;
        sleep(1);
    }

    stop = true;
    pthread_join(checker_thread, NULL);

    return 0;
}