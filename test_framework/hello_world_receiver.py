from threading import Thread
import zmq

hello_port = "5556"
world_port = "5557"


def receiver(name, port):
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.bind("tcp://*:%s" % port)

    while(True):
        message = socket.recv()
        print("Received message from %s: %s" % (name, message))


while True:

    t1 = Thread(target=receiver, kwargs={"name": "hello", "port": hello_port})
    t1.daemon = True
    t1.start()

    t2 = Thread(target=receiver, kwargs={"name": "world", "port": world_port})
    t2.daemon = True
    t2.start()

    t1.join()
    t2.join()
