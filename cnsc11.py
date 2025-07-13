import socket
a=input("Enter domain name:")
addr=socket.gethostbyname(a)
print(addr)
b=input("Enter domain ip address:")
domain=socket.gethostbyaddr(addr)
print(domain)
