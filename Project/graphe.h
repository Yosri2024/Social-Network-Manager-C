#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "ELTPRIM.h"

typedef struct structNode {
    ELEMENT user; // Données de l’utilisateur
    int weight; // Poids de la relation
    struct structNode* next; // Pointeur vers le prochain voisin
} structNode, *Node;


typedef struct {
    int V; // Nombre d’utilisateurs
    ELEMENT* utilisateurs; // Tableau des utilisateurs
    Node* adjList; // Listes d’adjacence
} GRPH,*graphePondere;



#endif // GRAPHE_H_INCLUDED
