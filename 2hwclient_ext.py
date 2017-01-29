import zmq
import sys

args = sys.argv

addr = args[1]
port = args[2]

print('C: Connecting to server at "%s:%s"' % (addr, port))
context = zmq.Context()
socket = context.socket(zmq.REQ)





socket.connect("tcp://%s:%s" % (addr, port))

while True:
    message = raw_input("Enter: ")

    print('C: Sending message: "%s"' % message)
    socket.send(message)
    
    answer = socket.recv()
    print('C: Got response "%s"' % answer)
    if(message == "quit"):
        break
