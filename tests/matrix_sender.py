import socket

# create a new socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
dest_ip = '127.0.0.1'
dest_port = 12346
# connect to the server
s.connect((dest_ip, dest_port))
msg = raw_input("Line: ") + '\r\n'
while not msg == 'end\r\n':
    # send the message
    s.send(msg)
    #data = s.recv(4096)
    #print "Server sent: ", data
    msg = raw_input("Line: ") + '\r\n'

# close the socket
s.send(msg)
print("Message sent: " + msg)

# Get sol
data = s.recv(4096)
print "Server Solution: ", data

s.close()
