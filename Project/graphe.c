#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "LSTGRP.H"


Node noeudCreer(ELEMENT e){

    Node n;

    n =(Node)malloc(sizeof(structNode));
    if(!n)
        printf ("\nPlus d'espace");
    else
    {
        elementAffecter(&(n->user), e);
        n->next = NULL;
    }
    return n;
}

void noeudDetruire(Node n){
    void noeudDetruire(Node n) {
    if (n != NULL) {
        elementDetruire(n->user);
        free(n);
    }
}
}

int estVide(graphePondere G) {
    return (G->V==0 || G==NULL);
}

int estSaturee(graphePondere G) {
    Node temp;
    int saturee = 1;
    temp = (Node) malloc ( sizeof ( structNode) );
    if(temp != NULL) {
        saturee = 0;
        free(temp);
        }
    return saturee;
}

int GrapheTaille(graphePondere G) {
    return G->V;
}

graphePondere creerGraphe(int V) {

    graphePondere G = (graphePondere)malloc(sizeof(GRPH));
    if (G == NULL) {
        printf("Erreur d'allocation memoire pour le graphe\n");
        return NULL;
    }

    G->V = V;

    G->utilisateurs = (ELEMENT*)malloc(V * sizeof(ELEMENT));
    if (G->utilisateurs == NULL) {
        printf("Erreur d'allocation memoire pour les utilisateurs\n");
        free(G);
        return NULL;
    }
    for (int i = 0; i < V; i++) {
        G->utilisateurs[i] = NULL;
    }
    G->adjList = (Node*)malloc(V * sizeof(Node));
    if (G->adjList == NULL) {
        printf("Erreur d'allocation memoire pour la liste d'adjacence\n");
        free(G->utilisateurs);
        free(G);
        return NULL;
    }
    for (int i = 0; i < V; i++) {
        G->adjList[i] = NULL;
    }

    return G;
}
graphePondere chargerGraphe(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return NULL;
    }

    graphePondere G;
    char ligne[200];
    int numUs = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        if (ligne[0] == 'U') {
            numUs++;
        }
    }

    G = creerGraphe(numUs);

    if (G == NULL) {
        fclose(file);
        return NULL;
    }

    rewind(file);

    while (fgets(ligne, sizeof(ligne), file)) {
        if (ligne[0] == 'U') {
            int id, age;
            char name[50];
            if (sscanf(ligne, "U %d %s %d", &id, name, &age) == 3) {
                    ELEMENT user = (ELEMENT)malloc(sizeof(UtilisateurStruct));
                    user->id = id;
                    strcpy(user->nom, name);
                    user->age = age;
                    G->utilisateurs[id] = user;

            } else {
                printf("Erreur : format invalide dans le fichier\n");
            }
        } else if (ligne[0] == 'R') {
            int src, dest, weight;
            if (sscanf(ligne, "R %d %d %d", &src, &dest, &weight) == 3) {

                ajouterRelation(G, src, dest, weight);
            } else {
                printf("Erreur : format invalide dans le fichier\n");
            }
        }
    }

    fclose(file);
    return G;
}

void detruireGraphe(graphePondere G) {
    if (G == NULL) {
        printf("Erreur : graphe non initialisé\n");
        return;
    }
    for (int i = 0; i < G->V; i++) {
        Node c = G->adjList[i];
        while (c != NULL) {
            Node temp = c;
            c = c->next;
            noeudDetruire(temp);
        }
        if (G->utilisateurs[i] != NULL) {
            elementDetruire(G->utilisateurs[i]);
        }
    }
    free(G->adjList);
    free(G->utilisateurs);
    free(G);
    printf("\n---------------------------------------------------------\n\n");
    printf("Le graphe a ete correctement detruit.\n");
    printf("\n---------------------------------------------------------\n\n");
}
int ajouterUtilisateur(graphePondere g, ELEMENT user) {
    int succee=1;
    if (g == NULL || g->utilisateurs == NULL || g->adjList == NULL) {
        printf("Erreur : graphe non initialise\n");
        return 0;
    }

    ELEMENT* nv_ut = (ELEMENT*)malloc((g->V + 1) * sizeof(ELEMENT));
    if (nv_ut == NULL) {
        printf("Erreur : echec de l'allocation memoire pour les utilisateurs.\n");
        succee=0;
    }

    for (int i = 0; i < g->V; i++) {
        nv_ut[i] = g->utilisateurs[i];
    }

    free(g->utilisateurs);
    g->utilisateurs = nv_ut;

    Node* nv_adjList = (Node*)malloc((g->V + 1) * sizeof(Node));
    if (nv_adjList == NULL) {
        printf("Erreur : echec de l'allocation memoire pour les listes d'adjacence.\n");
        free(g->utilisateurs);
        succee=0;
    }
    for (int i = 0; i < g->V; i++) {
        nv_adjList[i] = g->adjList[i];
    }

    free(g->adjList);
    g->adjList = nv_adjList;
    g->utilisateurs[g->V] = user;
    g->adjList[g->V] = NULL;
    g->V++;

    return succee;
}
int supprimerUtilisateur(graphePondere g, int idUser) {
    int succee = 0;

    if (g == NULL || g->utilisateurs == NULL || g->adjList == NULL) {
        printf("Erreur : graphe non initialise\n");
        return 0;
    }

    Node current = g->adjList[idUser];
    while (current != NULL) {
        Node temp = current;
        current = current->next;
        free(temp);
    }

    g->adjList[idUser] = NULL;
    succee = 1;

    for (int i = 0; i < g->V; i++) {
        if (i != idUser) {
            Node c = g->adjList[i];
            Node prec = NULL;

            while (c != NULL) {
                if (c->user->id == idUser) {
                    if (prec == NULL) {
                        g->adjList[i] = c->next;
                    } else {
                        prec->next = c->next;
                    }

                    free(c);
                    succee = 1;
                    c = NULL;

                } else {
                    prec = c;
                    c = c->next;
                }
            }
        }
    }

    g->utilisateurs[idUser]->id = -1;
    strcpy(g->utilisateurs[idUser]->nom, "");
    g->utilisateurs[idUser]->age = 0;

    return succee;
}
int ajouterRelation(graphePondere g, int src, int dest, int poids) {
    int succee=1;
    if (g == NULL || g->adjList == NULL || src < 0 || dest < 0 || src >= g->V || dest >= g->V) {
        printf("Erreur : parametres invalides\n");
        succee=0;
    }


    Node p = (Node)malloc(sizeof(structNode));
    if (p == NULL) {
        printf("Erreur : echec de l'allocation memoire\n");
        succee=0;
    }
    p->user = g->utilisateurs[dest];
    p->weight = poids;
    p->next = g->adjList[src];
    g->adjList[src] = p;

    return succee;
}
int supprimerRelation(graphePondere g, int src, int dest) {
    int succee = 0;

    if (g == NULL || g->adjList == NULL || src < 0 || dest < 0 || src > g->V || dest > g->V) {
        printf("Erreur : parametres invalides\n");
        succee = 0;
    } else {
        Node c = g->adjList[src];
        Node prec = NULL;


        while (c != NULL) {
            if (c->user == g->utilisateurs[dest]) {

                if (prec == NULL) {
                    g->adjList[src] = c->next;
                } else {
                    prec->next = c->next;
                }
                free(c);
                succee = 1;
            }
            prec = c;
            c = c->next;
        }


        if (succee == 0) {
            printf("\n");
        }
    }

    return succee;
}


void sauvegarderGraphe(graphePondere g, const char* filesauv) {
    FILE* file = fopen(filesauv, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");
        return;
    }

    // Sauvegarder les utilisateurs
    for (int i = 0; i < g->V; i++) {
        if (g->utilisateurs[i] != NULL) {
            fprintf(file, "U %d %s %d\n", g->utilisateurs[i]->id, g->utilisateurs[i]->nom, g->utilisateurs[i]->age);
        }
    }

    for (int i = 0; i < g->V; i++) {

        Node c = g->adjList[i];
        while (c != NULL) {

            int id_dest = -1;
            for (int j = 0; j < g->V; j++) {
                if (g->utilisateurs[j] == c->user) {
                    id_dest = j;
                }
            }
            if (id_dest != -1) {
                fprintf(file, "R %d %d %d # %s %s\n",
                        g->utilisateurs[i]->id, g->utilisateurs[id_dest]->id, c->weight,
                        g->utilisateurs[i]->nom, g->utilisateurs[id_dest]->nom);
            }

            c = c->next;
        }
    }

    fclose(file);
    printf("Graphe sauvegarde dans le fichier : %s\n", filesauv);
}

void afficherGraphe(graphePondere g) {
    if (g == NULL || g->adjList == NULL) {
        printf("Erreur : Le graphe est vide ou invalide\n");
        return;
    }

    printf("Representation graphique des relations dans le graphe :\n\n");

    for (int i = 0; i < g->V; i++) {
        Node c = g->adjList[i];
        while (c != NULL) {

            char*Relation;
            if (c->weight == 1) {
                Relation = "Relation faible";
            } else if (c->weight == 5) {
                Relation = "Relation forte";
            } else {
                Relation = "Relation normale";
            }

            printf("%s (%d) --%d--> %s (%d) (%s) \n",g->utilisateurs[i]->nom, i,c->weight,c->user->nom, c->user->id,Relation);

            c = c->next;
        }

        if (g->adjList[i] != NULL) {
            printf(" |\n +\n");
        }
    }
}


//------------------------------------------------
//Partie 2




int dfs_virgule = 1;
void dfs(graphePondere g, int idUser, int* visite) {

    if (g == NULL || g->adjList == NULL || g->utilisateurs == NULL) {
        printf("Erreur : graphe non initialise\n");

    }

    visite[idUser] = 1;
    if (!dfs_virgule) printf(", ");
    else dfs_virgule = 0;
    printf("%s", g->utilisateurs[idUser]->nom);


    Node c = g->adjList[idUser];
    while (c != NULL) {
        int NId = c->user->id;
        if (!visite[NId]) {
            dfs(g, NId, visite);
        }
        c = c->next;
    }
}



void bfs(graphePondere g, int idUser) {
    if (g == NULL || g->adjList == NULL || g->utilisateurs == NULL) {
        printf("Erreur : graphe non initialise\n");

    }

    int* visite = (int*)calloc(g->V, sizeof(int));   // tableau pour marquer les noeuds visites
    int* niveau = (int*)malloc(g->V * sizeof(int));  // tableau pour stocker le niveau de chaque noeud
    int* file = (int*)malloc(g->V * sizeof(int));    // file pour simuler le parcours
    int debut = 0, fin = 0;                          // indices pour la file

    if (!visite || !niveau || !file) {
        printf("Erreur d'allocation memoire\n");

    }

    visite[idUser] = 1;
    niveau[idUser] = 0;
    file[fin] = idUser;
    fin++;

    int niveauActuel = 0;
    printf("Niveau %d: [", niveauActuel);
    int virg = 1;

    while (debut < fin) {
        int u = file[debut];
        debut++;

        if (niveau[u] > niveauActuel) {
            printf("]\nNiveau %d: [", niveau[u]);
            niveauActuel = niveau[u];
            virg = 1;
        }

        if (!virg) printf(", ");
        printf("%s", g->utilisateurs[u]->nom);
        virg = 0;

        Node voisin = g->adjList[u];
        while (voisin) {
            int idVoisin = voisin->user->id;
            if (!visite[idVoisin]) {
                visite[idVoisin] = 1;
                niveau[idVoisin] = niveau[u] + 1;
                file[fin] = idVoisin;
                fin++;
            }
            voisin = voisin->next;
        }
    }
    printf("]\n");

    free(visite);
    free(niveau);
    free(file);
}

/*
void dijkstra(graphePondere g, int src_id, int dest_id) {
    printf("\n\n");
    if (g == NULL || g->adjList == NULL || g->utilisateurs == NULL) {
        printf("Erreur : graphe non initialise\n");

    }

    int Maxim=99;


    int V = g->V;


    int* dist = (int*)malloc(V * sizeof(int));    // Tableau des distances minimales depuis la source
    int* prec = (int*)malloc(V * sizeof(int));    // Tableau des sommets precedents
    int* visite = (int*)malloc(V * sizeof(int)); // Tableau pour suivre les sommets visites


    for (int i = 0; i < V; i++) {
        dist[i] = Maxim;
        prec[i] = -1;
        visite[i] = 0;
    }
    dist[src_id] = 0;


    int ii = V;
    while (ii > 0) {

        int minDist = Maxim;
        int c = -1;

        for (int j = 0; j < V; j++) {
            if (visite[j] == 0 && dist[j] < minDist) {
                minDist = dist[j];
                c = j;
            }
        }

        if (c == -1) {
            ii = 0;
        } else {

            visite[c] = 1;
            ii--;


            Node nbv = g->adjList[c];
            while (nbv != NULL) {
                int nbvId = nbv->user->id;
                int weight = nbv->weight;


                if (visite[nbvId] == 0 && dist[c] + weight < dist[nbvId]) {
                    dist[nbvId] = dist[c] + weight;
                    prec[nbvId] = c;
                }
                nbv = nbv->next;
            }
        }
    }

    if (dist[dest_id] == Maxim) {
        printf("Aucun chemin n'existe entre %s et %s.\n",g->utilisateurs[src_id]->nom, g->utilisateurs[dest_id]->nom);

    } else {

        int chemin[V];     // Tableau pour stocker le chemin pour mettre les ids des utilisateurs de chemin
        int Taille_chemin = 0; // Taille actuelle du chemin
        int act = dest_id; // Partir de la destination


        while (act != -1) {
            chemin[Taille_chemin] = act;
            Taille_chemin++;
            act = prec[act];
        }


        printf("Chemin le plus court entre %s et %s :\n\n",g->utilisateurs[src_id]->nom, g->utilisateurs[dest_id]->nom);
        for (int i = Taille_chemin - 1; i >= 0; i--) {
            int k=chemin[i];
            printf("%s", g->utilisateurs[k]->nom);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf("\n\nPoids total : %d\n", dist[dest_id]);
    }


    free(dist);
    free(prec);
    free(visite);
}
*/



void dijkstra(graphePondere g, int src_id, int dest_id) {
    printf("\n\n");
    if (g == NULL || g->adjList == NULL || g->utilisateurs == NULL) {
        printf("Erreur : graphe non initialise\n");
        return;
    }

    // ** Étape 1 : Multiplier tous les poids par -1 **
    for (int i = 0; i < g->V; i++) {
        Node current = g->adjList[i];
        while (current != NULL) {
            current->weight *= -1; // Inverser le poids
            current = current->next;
        }
    }

    int Maxim = 99;
    int V = g->V;

    int* dist = (int*)malloc(V * sizeof(int));    // Tableau des distances minimales depuis la source
    int* prec = (int*)malloc(V * sizeof(int));    // Tableau des sommets precedents
    int* visite = (int*)malloc(V * sizeof(int));  // Tableau pour suivre les sommets visites

    for (int i = 0; i < V; i++) {
        dist[i] = Maxim;
        prec[i] = -1;
        visite[i] = 0;
    }
    dist[src_id] = 0;

    int ii = V;
    while (ii > 0) {
        int minDist = Maxim;
        int c = -1;

        for (int j = 0; j < V; j++) {
            if (visite[j] == 0 && dist[j] < minDist) {
                minDist = dist[j];
                c = j;
            }
        }

        if (c == -1) {
            ii = 0;
        } else {
            visite[c] = 1;
            ii--;

            Node nbv = g->adjList[c];
            while (nbv != NULL) {
                int nbvId = nbv->user->id;
                int weight = nbv->weight;

                if (visite[nbvId] == 0 && dist[c] + weight < dist[nbvId]) {
                    dist[nbvId] = dist[c] + weight;
                    prec[nbvId] = c;
                }
                nbv = nbv->next;
            }
        }
    }

    if (dist[dest_id] == Maxim) {
        printf("Aucun chemin n'existe entre %s et %s.\n", g->utilisateurs[src_id]->nom, g->utilisateurs[dest_id]->nom);
    } else {
        int chemin[V];      // Tableau pour stocker le chemin (IDs des utilisateurs)
        int Taille_chemin = 0; // Taille actuelle du chemin
        int act = dest_id;  // Partir de la destination

        while (act != -1) {
            chemin[Taille_chemin] = act;
            Taille_chemin++;
            act = prec[act];
        }

        printf("Chemin le plus solide entre %s et %s :\n\n", g->utilisateurs[src_id]->nom, g->utilisateurs[dest_id]->nom);
        for (int i = Taille_chemin - 1; i >= 0; i--) {
            int k = chemin[i];
            printf("%s", g->utilisateurs[k]->nom);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf("\n\nPoids total : %d\n", -(dist[dest_id])); // Revenir au poids positif
    }

    free(dist);
    free(prec);
    free(visite);

    // ** Étape 3 : Remultiplier les poids par -1 pour revenir aux valeurs originales **
    for (int i = 0; i < g->V; i++) {
        Node current = g->adjList[i];
        while (current != NULL) {
            current->weight *= -1; // Revenir au poids original
            current = current->next;
        }
    }
}

void trouver_communautes(graphePondere g) {
    if (g == NULL || g->adjList == NULL || g->utilisateurs == NULL) {
        printf("Erreur : graphe non initialise\n");
        return;
    }


    int* visite = (int*)malloc(g->V * sizeof(int));
    for (int i = 0; i < g->V; i++) {
        visite[i] = 0;
    }

    int communauteNum = 1;

    for (int i = 0; i < g->V; i++) {
        if (!visite[i]) {
            printf("Communaute %d : [", communauteNum);
            communauteNum++;
            //Partie BFS
            int* file = (int*)malloc(g->V * sizeof(int));
            int debut = 0, fin = 0;
            file[fin] = i;
            fin++;
            visite[i] = 1;

            int virg = 1;
            while (debut < fin) {
                int current = file[debut];
                debut++;

                if (!virg) {
                    printf(", ");
                }
                printf("%s", g->utilisateurs[current]->nom);
                virg = 0;

                // parcourir les voisins de noeud actuel
                Node voisin = g->adjList[current];
                while (voisin != NULL) {
                    int voisinId = voisin->user->id;
                    if (!visite[voisinId]) {
                        visite[voisinId] = 1;
                        file[fin] = voisinId;
                        fin++;
                    }
                    voisin = voisin->next;
                }
            }
            //Jusqu'ici
            printf("]\n");
            free(file);
        }
    }

    free(visite);
}
