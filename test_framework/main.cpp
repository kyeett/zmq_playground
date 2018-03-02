#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <queue>          // std::queue


using namespace std;

// The function we want to execute on the new thread.
// void task1(string msg, int period)
void task1(int id, int period, queue<int> &thisqueue)
{
    cout << "Task #" << id << " stopping\n";
    thisqueue.push(period);
    sleep(period);
    thisqueue.push(period+1);
    thisqueue.push(period+2);
}

int main()
{
    queue<int> myqueue;

    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, 0, 1, ref(myqueue));
    thread t2(task1, 1, 1, ref(myqueue));

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    t2.join();


    while(!myqueue.empty()) {
        cout << myqueue.front() << "\n";
        myqueue.pop();
    }
}