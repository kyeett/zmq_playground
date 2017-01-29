import zmq
import sys

service_name='zomg'

# Get IP and port from consul
import consul
c = consul.Consul('10.68.82.176')
response = c.catalog.service(service_name)
first_service = response[1][0]
addr = first_service['ServiceAddress']
port = first_service['ServicePort']

print("C: Connecting to server")
context = zmq.Context()
socket = context.socket(zmq.REQ)

#args = sys.argv

#addr = args[1]
#port = args[2]



socket.connect("tcp://%s:%s" % (addr, port))

while True:
    message = raw_input("Enter: ")

    print('C: Sending message: "%s"' % message)
    socket.send(message)
    
    answer = socket.recv()
    print('C: Got response "%s"' % answer)
    if(message == "quit"):
        break
