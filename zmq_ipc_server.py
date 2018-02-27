import zmq, json, time

def main():
    context = zmq.Context()
    publisher = context.socket(zmq.PUB)
    publisher.connect("ipc:///tmp/test")
    while True:
        publisher.send( "hello world" )
        time.sleep( 1 )

if __name__ == "__main__":
    main()
