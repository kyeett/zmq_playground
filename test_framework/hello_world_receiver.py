import time
import zmq

hello_port = "5556"
world_port = "5557"


context = zmq.Context()
context_2 = zmq.Context()
hello_socket = context.socket(zmq.PAIR)
world_socket = context_2.socket(zmq.PAIR)

hello_socket.bind("tcp://*:%s" % hello_port)
world_socket.bind("tcp://*:%s" % world_port)



while True:

    #  Wait for next request from client
    message = hello_socket.recv()
    print("Received message from %s: %s" % ("hello", message))

    message = world_socket.recv()
    print("Received message from %s: %s" % ("world", message))