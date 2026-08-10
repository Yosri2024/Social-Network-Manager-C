#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LSTGRP.H"

void intrf_1()
{       system("color 0A");
        system("cls");
        printf("\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||------BIENVENUE AU MENU PRINCIPAL DE NOTRE AGENCE-----||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||---- -Veuillez choisir l'objectif de votre operation--||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||         1. AJOUTER UN UTILISATEUR                    ||\n");
        printf("                   ||         2. SUPPRIMER UN UTILISATEUR                  ||\n");
        printf("                   ||         3. AJOUTER UNE RELATION                      ||\n");
        printf("                   ||         4. SUPPRIMER UNE RELATION                    ||\n");
        printf("                   ||         5. AFFICHER LE GRAPHE                        ||\n");
        printf("                   ||         6. TROUVER TOUS LES AMIS ACCESSIBLES         ||\n");
        printf("                   ||                       (DFS)                          ||\n");
        printf("                   ||         7. TROUVER TOUS LES AMIS A UNE DISTANCE      ||\n");
        printf("                   ||                       (BFS)                          ||\n");
        printf("                   ||         8. OPTIMISER LES INTERACTIONS ENTRE          ||\n");
        printf("                   ||               LES UTILISATEURS (DJIKSTRA)            ||\n");
        printf("                   ||         9. TROUVER COMMUNAUTES                       ||\n");
        printf("                   ||        10. QUITTER L'APPLICATION                     ||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("                   ||------------------------------------------------------||\n");
        printf("\n\n\n\n");
}



void intrf_1();
ELEMENT elementCreer();
void elementLire(ELEMENT* e);
graphePondere chargerGraphe(const char* filename);
void afficherGraphe(graphePondere g);
void dfs(graphePondere g, int id, int* visite);
void bfs(graphePondere g, int id_U);
void dijkstra(graphePondere g, int start, int end);
void trouver_communautes(graphePondere g);
void sauvegarderGraphe(graphePondere g, const char* filename);
void detruireGraphe(graphePondere g);
int supprimerUtilisateur(graphePondere g, int idUser);
int ajouterRelation(graphePondere g, int src, int dest, int poids);
int supprimerRelation(graphePondere g, int src, int dest);
void supprimerId(const char* nomFichier, int idASupprimer);
void supprimerRelF(const char* nomFichier, int src, int dest);

int main() {

    int choix;
    int src, dest;
    int id1,id2,poids;
    int idUser3;
    int id_U;
    int s_src, d_dest;
    const char* filename = "chargerReseau.txt";
    const char* filename2 = "FichierSauvgarde.txt";
    graphePondere g = chargerGraphe(filename);
    ELEMENT e;
    do {
        intrf_1();
        printf("Votre choix : ");
        scanf("%d", &choix);
        printf("\n");
        switch (choix) {
            case 1:
                e = elementCreer();
                elementLire(&e);
                if (ajouterUtilisateur(g, e)) {
                    FILE* fichier = fopen(filename2, "a");
                    FILE* fichier2 = fopen(filename, "a");
                    if (fichier == NULL) {
                        printf("Erreur : impossible d'ouvrir le fichier pour sauvegarde\n");
                    } else {
                        fprintf(fichier, "U %d %s %d\n", e->id, e->nom, e->age);
                        fprintf(fichier2, "U %d %s %d\n", e->id, e->nom, e->age);
                        fclose(fichier);
                        fclose(fichier2);
                        printf("Ajoute ! U %d %s %d\n", e->id, e->nom, e->age);
                    }
                }
                break;

            case 2:{
                int idUser;
                do{
                printf("Entrez l'ID de l'utilisateur a supprimer : ");
                scanf("%d", &idUser);
                }while(idUser<0 || idUser>g->V);

                int resultat = supprimerUtilisateur(g, idUser);
                if (resultat == 1) {
                    printf("L'ID %d a ete supprime avec succes\n", idUser);
                     supprimerId(filename2,idUser);
                    supprimerId(filename,idUser);
                } else {
                    printf("Échec de la suppression : utilisateur introuvable.\n");
                }

                break;}



            case 3:{

                do{
                    printf("ID du premier utilisateur : ");
                    scanf("%d", &id1);
                }while(id1>=g->V || id1<0);
                do{
                    printf("ID du deuxieme utilisateur : ");
                    scanf("%d", &id2);
                }while(id2>=g->V || id2<0);
                do{
                    printf("Force de la relation (poids) : ");
                    scanf("%d", &poids);
                }while(poids<1);
                if (ajouterRelation(g, id1, id2, poids)) {
                    FILE* fichier = fopen(filename2, "a");
                    FILE* fichier2 = fopen(filename, "a");
                    if (poids==1){
                        fprintf(fichier, "R %d %d %d # %s %s (Relation faible)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                        fprintf(fichier2, "R %d %d %d # %s %s (Relation faible)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                    }
                    else if(poids>=5)
                    {
                        printf(fichier, "R %d %d %d # %s %s (Relation forte)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                        fprintf(fichier2, "R %d %d %d # %s %s (Relation forte)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                    }
                    else
                    {
                        printf(fichier, "R %d %d %d # %s %s \n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                        fprintf(fichier2, "R %d %d %d # %s %s \n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                    }



                    fclose(fichier);
                    fclose(fichier2);
                    if (poids==1)
                        printf("Relation entre ajoutee : R %d %d %d # %s %s (Relation faible)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                    else if(poids>=5)
                        printf("Relation entre ajoutee : R %d %d %d # %s %s (Relation forte)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                    else
                        printf("Relation entre ajoutee : R %d %d %d # %s %s (Relation normale)\n", id1, id2, poids, g->utilisateurs[id1]->nom, g->utilisateurs[id2]->nom);
                }
                break;}


            case 4: {

            do{
               printf("Entrez l'ID de l'utilisateur source : ");
              scanf("%d", &src);
            }while(src>=g->V || src<0);
            do{
              printf("Entrez l'ID de l'utilisateur destination : ");
               scanf("%d", &dest);
            }while(dest>=g->V || dest<0);
                int resultat = supprimerRelation(g, src, dest);
                if (resultat == 1) {
                    printf("La relation (%d -> %d) a ete supprimee avec succes\n", src, dest);
                    supprimerRelF(filename,src,dest);
                    supprimerRelF(filename2,src,dest);
                } else {
                    printf("La relation (%d -> %d) n'a pas ete trouvee dans le fichier\n", src, dest);
                }
                break;
            }

            case 5:
                afficherGraphe(g);
                break;

            case 6: {

                 do{
                     printf("Veuillez entrer l'ID de l'utilisateur : ");
                     scanf("%d", &idUser3);
                 }while(idUser3<0 || idUser3>=g->V);
                 printf("\n");
                 printf("Exploration des amis accessibles (directs et indirects) depuis %s :\n\n", g->utilisateurs[idUser3]->nom);
                int* visite = (int*)malloc(g->V * sizeof(int));
                if (!visite) {
                    printf("Erreur d'allocation memoire.\n");
                } else {
                    for (int i = 0; i < g->V; i++) visite[i] = 0;
                    printf("[");
                    dfs(g,idUser3, visite);
                    printf("]");
                    free(visite);
                }
                break;
            }

            case 7:

                 do{
                     printf("Veuillez entrer l'ID de l'utilisateur : ");
                     scanf("%d", &id_U);
                 }while(id_U<0 || id_U>=g->V);
                printf("\n");
                printf("Debut de l'exploration des amis a differentes distances depuis %s :\n\n", g->utilisateurs[id_U]->nom);
                bfs(g, id_U);
               // bfs(g, 0);
                break;

            case 8:

                do{
                    printf("Entrez l'ID de l'utilisateur source : ");
                    scanf("%d", &s_src);
                }while(s_src>=g->V || s_src<0);
                do{
                    printf("Entrez l'ID de l'utilisateur destination : ");
                    scanf("%d", &d_dest);
                }while(d_dest>=g->V || d_dest<0);

                dijkstra(g, s_src, d_dest);
                //dijkstra(g, 0, 4);
                break;

            case 9:
                printf("Les communautes dans le reseau social :\n\n");
                trouver_communautes(g);
                break;

            case 10:
                sauvegarderGraphe(g, filename2);
                detruireGraphe(g);
                printf("Merci d'avoir utilise l'application !\n");
                break;

            default:
                printf("Choix invalide, veuillez reessayer.\n");
        }


        if (choix != 10) {
            printf("\n\nAppuyez sur une touche pour revenir au menu...\n");
            getchar(); getchar(); // pause
            system("cls");
        }

    } while (choix != 10);

    return 0;
}
void supprimerId(const char* nomFichier, int idASupprimer) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.txt", "w");
    if (fichierTemp == NULL) {
        printf("Erreur : impossible de creer le fichier temporaire\n");
        fclose(fichier);
        return;
    }

    char ligne[256];
    int idTrouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int id;
        if (sscanf(ligne, "U %d", &id) == 1) {
            if (id != idASupprimer) {
                fputs(ligne, fichierTemp);
            } else {
                idTrouve = 1;
            }
        } else {
            fputs(ligne, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    if (idTrouve) {
        if (remove(nomFichier) == 0 && rename("temp.txt", nomFichier) == 0) {
            printf("\n");
    } else {
        printf("L'ID %d n'a pas ete trouve dans le fichier\n", idASupprimer);
        remove("temp.txt");
    }
}}
void supprimerRelF(const char* nomFichier, int src, int dest) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.txt", "w");
    if (fichierTemp == NULL) {
        printf("Erreur : impossible de creer le fichier temporaire\n");
        fclose(fichier);
        return;
    }

    char ligne[256];
    int relationTrouvee = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int src2, dest2, poids;

        // Verifie si la ligne correspond a une relation
        if (sscanf(ligne, "R %d %d %d", &src2, &dest2, &poids) == 3) {
            if (src2 == src && dest2 == dest) {
                relationTrouvee = 1;
            } else {

                fputs(ligne, fichierTemp);
            }
        } else {
            fputs(ligne, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    if (relationTrouvee) {
        if (remove(nomFichier) == 0 && rename("temp.txt", nomFichier) == 0) {
            printf("\n", src, dest);
        } else {
            printf("Erreur : impossible de mettre a jour le fichier\n");
        }
    } else {
        printf("\n", src, dest);
        remove("temp.txt");
    }
}
