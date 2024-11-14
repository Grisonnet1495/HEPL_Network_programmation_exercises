#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include "LibSer.h"
#include "Requete.h"
#include "data.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void HandleTCPClient(int clntSocket)
{
    int recvMsgSize; /* Size of received message */
    struct Requete ARequest;
    struct VehiculeVH VehiculeData;

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, &ARequest, sizeof(struct Requete), 0)) < 0)
        DieWithError("(Error) recv() failed\n");

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0) /* zero indicates end of transmission */
    {
      printf("(Success) Packet of %d Bytes received\n", recvMsgSize);

      VehiculeData.Reference = ARequest.Reference;
      printf("Searching for reference %d...\n", VehiculeData.Reference);
      if (RechercheHV("VehiculesHV", ARequest.Reference, &VehiculeData) == -1)
      {
        printf("(Error) Search failed or didn't find anything\n");
        ARequest.Type = TypeRequete.Fail;
      }
      else
      {
        printf("(Success) Reference %d found by research :\n", ARequest.Reference);
        AfficherRequete(stderr, ARequest);

        printf("Converting the result in a packet...");
        ARequest = ConvertVehiculeVHToRequest(VehiculeData);
      }

      /* Send the response message back to the client */
      if (send(clntSocket, &ARequest, sizeof(struct Requete), 0) != sizeof(struct Requete))
          DieWithError("(Error) send() failed\n");

      /* See if there is more data to receive */
      if ((recvMsgSize = recv(clntSocket, &ARequest, sizeof(struct Requete), 0)) < 0)
          DieWithError("(Error) recv() failed\n");
    }

    close(clntSocket);    /* Close client socket */
}

struct Requete ConvertVehiculeVHToRequest(struct VehiculeVH Vehicule)
{
  struct Requete ARequest;
  ARequest.Type = TypeRequete.OK;
  ARequest.Numero = 0;
  ARequest.NumeroFacture = 0;
  ARequest.Reference = Vehicule.Reference;
  ARequest.Quantite = Vehicule.Quantite;
  ARequest.Prix = 0;
  ARequest.Constructeur = Vehicule.Constructeur;
  ARequest.Modele = Vehicule.Modele;
  ARequest.Client = "Non defini";

  return ARequest;
}
