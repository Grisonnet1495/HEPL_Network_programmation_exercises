#ifndef DATA_H
#define DATA_H

#include <time.h>
// 2022 , interdit de modifier les champs existants

struct VehiculeHV
{
	int Supprime;
	int Reference;
	char Constructeur[30];
	char Modele[30];
	int Quantite;
	float Cylindree;
};

struct FactureHV
{
	int NumeroFacturation;
	char Acheteur[40];
	time_t DateFacturation;
	int Quantite;
	int Reference;
};

#endif
