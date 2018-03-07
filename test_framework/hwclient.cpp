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

        // Turn into string
        string received_string = std::string(static_cast<char*>(reply.data()), reply.size());
        if (is_integer(received_string)) {
            char *end;
            printf ("Received Number %ld\n", strtol( received_string.c_str(), &end, 10 ));
        }
        else {
            printf ("Received Word \"%s\"\n", received_string.c_str());
    //        printf("String! \n");

        }
        // std::cout << "Received World " << request_nbr << std::endl;
    }
    return 0;
}