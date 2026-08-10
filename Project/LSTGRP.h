#ifndef LSTGRP_H_INCLUDED
#define LSTGRP_H_INCLUDED

#include "graphe.h"



graphePondere creerGraphe(int V);

graphePondere chargerGraphe(const char* filename);

void detruireGraphe(graphePondere g);

int ajouterUtilisateur(graphePondere g, ELEMENT user);

int supprimerUtilisateur(graphePondere g, int idUser);

int ajouterRelation(graphePondere g, int src, int dest, int poids);

int supprimerRelation(graphePondere g, int src, int dest);

void sauvegarderGraphe(graphePondere g, const char* filename);

void afficherGraphe(graphePondere g);



#endif // LSTGRP_H_INCLUDED
