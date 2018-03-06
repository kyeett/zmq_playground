#!/usr/bin/env python
import zmq
from threading import Thread
import time


def get_subscriber(path):
    context = zmq.Context()
    subscriber = context.socket(zmq.SUB)
    subscriber.bind("ipc://" + path)
    subscriber.setsockopt_string(zmq.SUBSCRIBE, '')
    return subscriber


def user_connected():
    subscriber = get_subscriber("/tmp/test")

    while(True):
        received_msg = subscriber.recv()
        print("User connected %s" % received_msg)


if __name__ == "__main__":
    user_thread = Thread(target=user_connected)
    user_thread.daemon = True
    user_thread.start()

    while(True):
        time.sleep(1)