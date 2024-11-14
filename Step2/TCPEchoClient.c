#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include "Requete.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echoStringLen;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() 
                                        and total bytes read */
    char bufferString[80];
    struct Requete ARequest;

    if (argc != 3) /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage: %s <Server IP> <Echo Port>\n",
                argv[0]);
        exit(1);
    }

    /* Set variables */
    servIP = argv[1];             /* First arg: server IP address (dotted quad) */
    echoServPort = atoi(argv[2]); /* Second arg: server Port */

    printf("Entrez un le numero de reference : ");
    fgets(bufferString, sizeof(bufferString), stdin);
    ARequest.Reference = atoi(bufferString);

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed\n");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("(Error) connect() failed\n");

    /* Send the structure to the server */
    if (send(sock, &ARequest, sizeof(struct Requete), 0) != sizeof(struct Requete))
        DieWithError("(Error) send() sent a different number of bytes than expected\n");

    /* Receive the same structure back from the server */
    totalBytesRcvd = 0;
    printf("The following packet has been received : "); /* Setup to print the echoed string */
    while (totalBytesRcvd < sizeof(struct Requete))
    {
        if ((bytesRcvd = recv(sock, &ARequest, sizeof(struct Requete), 0)) <= 0)
            DieWithError("(Error) recv() failed or connection closed prematurely\n");
        totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
        AfficherRequete(stderr, ARequest);
    }

    printf("\n"); /* Print a final linefeed */

    close(sock);
    exit(0);
}
