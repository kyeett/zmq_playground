//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

using namespace std;

bool is_integer(string s) {

    char *end;
    long i = strtol( s.c_str(), &end, 10 );
    if ( *end == '\0' )
    {
        return true;// Success
    }
    else
    {
        return false;// Failure
    }
}


int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "Hello", 5);
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        if (is_integer(std::string(static_cast<char*>(reply.data()), reply.size()))) {
            printf("Integer! \n");
        }
        else {
            printf("String! \n");

        }
        printf ("Received Word \"%s\"\n", std::string(static_cast<char*>(reply.data()), reply.size()).c_str());
        printf ("Received Word %zu bytes: \"%s\"\n", reply.size(), reply.data());
        // std::cout << "Received World " << request_nbr << std::endl;
    }
    return 0;
}