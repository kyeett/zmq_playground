#!/usr/bin/env python
import zmq
import time

def send_message(path, message):
    context = zmq.Context()
    publisher = context.socket(zmq.PUB)
    ipc_path = "ipc://" + path
    print("connecting to " + ipc_path)
    publisher.connect(ipc_path)
    time.sleep(0.5)
    i = 0
    while True:
        print("sendy")
        i += 1
        publisher.send_string("hello world " + str(i))
        time.sleep( 0.2 )


if __name__ == "__main__":
    send_message("/tmp/test", "my_msg")
