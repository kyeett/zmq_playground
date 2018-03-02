#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <queue>          // std::queue

using namespace std;

struct message_t {
    int     i;
    string  s;
};

struct dog_t {
    int     age;
    string  name;
};

void printdog (dog_t dog) {
    cout << "The dog '" << dog.name << "' is " << dog.age << " years old\n";
    cout << "The dog '" << random() % 2 << "\n";
}

void print_message(message_t msg) {

    cout << "This message: s=" << msg.s << ", i=" << msg.i << "\n";
}

// The function we want to execute on the new thread.
// void task1(string msg, int period)
void task1(int age, string name, queue<dog_t> &thisqueue)
{
    cout << "Task given to dog"  << name << "\n";
    dog_t new_dog;
    new_dog.age = age;
    new_dog.name = name;

    for (int i = 0; i < 3; ++i) {
        new_dog.age = age + i;
        thisqueue.push(new_dog);
    }
}


void message_generator(string message, queue<message_t> &message_queue)
{
    for (int j = 0; j < 3; ++j) {

        if (random() % 2) {
            //Add message with integer
            int rnd = random() % 10;
            message_queue.push(message_t{ .i=rnd });
        } else {
            // Add message with string
            message_queue.push(message_t{ .s=message });
        }
    }
}


int main()
{
    dog_t dog_holder;
    queue<dog_t> myqueue;
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
}