#include <thread>
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

/*

Main process, spawns two child processes.
1. sends Hello in a thread every second
2. sends World in another thread every second
#include <.h>
*/

int n_iterations = 3;

void send_string_multiple(int uuid, string s, int n_iterations, string port, string ipc_namespace) {

    zmq::context_t context (uuid);
    zmq::socket_t socket (context, ZMQ_PAIR);
    socket.connect ("tcp://localhost:" + port);

    if (ipc_namespace != "") {
        zmq::context_t ipc_context (66);
        zmq::socket_t ipc_socket (ipc_context, ZMQ_PAIR);
        ipc_socket.connect ("ipc:///tmp/" + ipc_namespace);

        // Wait for message on socket
        printf("Waiting for message on %s\n", ("ipc:///tmp/" + ipc_namespace).c_str());
        zmq::message_t reply;
        ipc_socket.recv (&reply);
    }

    for (int i = 0; i < n_iterations; ++i)
    {
        zmq::message_t request (5);
        memcpy (request.data (), s.c_str(), 5);
        std::cout << "\nSending " << s  << "…" << std::endl;
        socket.send (request);
    }
}

void send_hello() {
    int uuid = 1;
    string port = "5556";
    string ipc_namespace = "test_trigger_1";
    send_string_multiple(uuid, "Hello", n_iterations, port, ipc_namespace);
}

void send_world() {
    int uuid = 2;
    string port = "5557";
    string ipc_namespace = "";
    send_string_multiple(uuid, "World", n_iterations, port, ipc_namespace);
}

int main ()
{
    thread t1(send_hello);
    thread t2(send_world);

    t1.join();
    t2.join();



    printf("\n%s\n", "Shutting down program...");
    // //  Prepare our context and socket
    // zmq::context_t context (1);
    // zmq::socket_t socket (context, ZMQ_PAIR);

    // std::cout << "Connecting to hello world server…" << std::endl;
    // socket.connect ("tcp://localhost:5555");

    // //  Do 10 requests, waiting each time for a response
    // for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
    //     zmq::message_t request (5);
    //     memcpy (request.data (), "Hello", 5);
    //     std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
    //     socket.send (request);

    //     //  Get the reply.
    //     zmq::message_t reply;
    //     socket.recv (&reply);

    //     // Turn into string
    //     string received_string = std::string(static_cast<char*>(reply.data()), reply.size());
    //     if (is_integer(received_string)) {
    //         char *end;
    //         printf ("Received Number %ld\n", strtol( received_string.c_str(), &end, 10 ));
    //     }
    //     else {
    //         printf ("Received Word \"%s\"\n", received_string.c_str());
    // //        printf("String! \n");

    //     }
    //     // std::cout << "Received World " << request_nbr << std::endl;
    // }
    return 0;
}