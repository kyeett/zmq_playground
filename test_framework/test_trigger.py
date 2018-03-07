import sys
import zmq


context = zmq.Context()
socket = context.socket(zmq.PAIR)

socket.bind("ipc:///tmp/" + sys.argv[1])
socket.send_string("trigger")
