#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <queue>          // std::queue
#include <mutex>
#include <time.h>

#define NUM_MESSAGES 5

using namespace std;

mutex g_pages_mutex;

struct message_t {
    int     i;
    string  s;
};


class Doggo
{
public:
    Doggo(string name, queue<message_t> q);
    ~Doggo();
    void main_dog_loop();
    string name;
    static mutex dog_mutex;
    queue<message_t> message_queue;
};

Doggo::Doggo(string name, queue<message_t> q) {
    this->name = name;
    this->message_queue = q;
}

Doggo::~Doggo() {};

void Doggo::main_dog_loop() {
    cout << "Take lock";
    lock_guard<mutex> guard(Doggo);
    cout << "Take lock";
}

void add_msg(message_t msg, queue<message_t> &message_queue) {
    lock_guard<mutex> guard(g_pages_mutex);
    message_queue.push(msg);
}

void print_message(message_t msg) {

    if(msg.s != "") {
        cout << msg.s << "\n";
    }
    else {
        cout << msg.i << "\n";
    }
}


void message_generator(string message, queue<message_t> &message_queue)
{
    for (int j = 0; j < NUM_MESSAGES; ++j) {

        if (random() % 2 == 0) {
            //Add message with integer
            int rnd = random() % 10;
            add_msg(message_t{ .i=rnd }, message_queue);
        } else {
            // Add message with string
            add_msg(message_t{ .s=message }, message_queue);
        }
    }
}


int main()
{
    srand(time(0));


    queue<message_t> message_queue;

    thread msger1(message_generator, "sync_func",      ref(message_queue));
    thread msger2(message_generator, "discover_func",  ref(message_queue));
    thread msger3(message_generator, "traffic_func",   ref(message_queue));

    msger1.join();
    msger2.join();
    msger3.join();

    while(!message_queue.empty()) {
        print_message(message_queue.front());
        message_queue.pop();
    }
    Doggo d1 = Doggo("magnus", message_queue);
    thread dog(message_generator, "traffic_func",   ref(message_queue));
}