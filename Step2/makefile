CFLAGS = -Wall -g
OBJS = LibSerHV.o HandleTCPClient.o

all: admin TCPEchoClient TCPEchoServer

admin: admin.c data.h LibSerHV.o
	gcc $(CFLAGS) -o admin admin.c LibSerHV.o

TCPEchoClient: TCPEchoClient.c Requete.h data.h
	gcc $(CFLAGS) -o TCPEchoClient TCPEchoClient.c

TCPEchoServer: TCPEchoServer.c HandleTCPClient.o LibSerHV.o Requete.h data.h
	gcc $(CFLAGS) -o TCPEchoServer TCPEchoServer.c HandleTCPClient.o LibSerHV.o

LibSerHV.o: LibSerHV.c LibSerHV.h data.h Requete.h
	gcc $(CFLAGS) -c -o LibSerHV.o LibSerHV.c

HandleTCPClient.o: HandleTCPClient.c HandleTCPClient.h LibSerHV.h data.h Requete.h
	gcc $(CFLAGS) -c -o HandleTCPClient.o HandleTCPClient.c

# Nettoyage
clean:
	rm -f admin TCPEchoClient TCPEchoServer $(OBJS)
