
all:	admin TCPEchoClient TCPEchoServer

admin:	admin.c	data.h	LibSerHV.o
	gcc -o admin admin.c LibSerHV.o 

TCPEchoClient:	TCPEchoClient.c Requete.h
	gcc -o TCPEchoClient TCPEchoClient.c

TCPEchoServer:	TCPEchoServer.c HandleTCPClient.o LibSerHV.h
	gcc -o TCPEchoServer TCPEchoServer.c

LibSerVH.o:	LibSerHV.c LibSerHV.h data.h Requete.h
	gcc -o LibSerHV.o LibSerHV.c

HandleTCPClient.o:	HandleTCPClient.c HandleTCPClient.h data.h Requete.h
	gcc -o HandleTCPClient.o HandleTCPClient.c
