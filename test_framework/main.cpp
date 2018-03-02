#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <queue>          // std::queue

using namespace std;


struct dog_t {
    int     age;
    string  name;
};

void printdog (dog_t dog) {
    cout << "The dog '" << dog.name << "'\n";
}

// The function we want to execute on the new thread.
// void task1(string msg, int period)
void task1(int age, string name, queue<dog_t> &thisqueue)
{
    cout << "Task given to dog"  << name << "\n";
    dog_t new_dog;
    new_dog.age = age;
    new_dog.name = name;

    thisqueue.push(new_dog);
}

int main()
{
    dog_t dog_holder;
    dog_t other_dog;
    other_dog.name = "John";
    other_dog.age = 10;
    queue<dog_t> myqueue;

    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, 1, "doggo", ref(myqueue));
    thread t2(task1, 5, "fido", ref(myqueue));

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    t2.join();


    while(!myqueue.empty()) {
        // dog_holder = myqueue.front();
        printdog(other_dog);
//        cout << "Dog named " >> other_dog.name << "\n";
        myqueue.pop();
    }
}