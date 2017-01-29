import zmq
import time
import sys

# Example taken from http://stackoverflow.com/questions/166506/finding-local-ip-addresses-using-pythons-stdlib
import socket
def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 0))
        IP = s.getsockname()[0]
    except:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP



args = sys.argv
addr = get_ip()
port = args[1]

#https://python-consul.readthedocs.io/en/latest/#consul
import consul
c = consul.Consul('10.68.82.176')

#Register the zomg service in consul
c.agent.service.register('zomg',address=addr, port=int(port))

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://%s:%s" % (addr, port))

while True:
    message = socket.recv()

    print('S: Received request: "%s"' % message)

    socket.send("accepted")
    if(message == "quit"):
        print("S: Shutting down")
        break
    time.sleep(1)