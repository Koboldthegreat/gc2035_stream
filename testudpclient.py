import socket
import sys

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('192.168.3.100', 8888)
message = b'This is the message.  It will be repeated.'

fd = open("output.yuv", "wb")

try:
    count=0
    frame=0
    sent = sock.sendto(b'n', server_address)
    while 1:
        sent = sock.sendto(b'n', server_address)
        # Receive response
        data, server = sock.recvfrom(256)
        count += 1
        #fd.write(data)
        sys.stdout.buffer.write(data)
        if count == 1800:
            sent = sock.sendto(b'f', server_address)
            sent = sock.sendto(b'f', server_address)
            count = 0

finally:
    fd.close()
    print ('closing socket')
    sock.close()

