#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ELTPRIM.H"
#include "LSTGRP.H"

int estAlphabetique(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ' ) {
            return 0; // contient un caractère non alphabétique
        }
    }
    return 1;
}

ELEMENT elementCreer()
{
    ELEMENT e=(ELEMENT)malloc(sizeof(UtilisateurStruct));
    if (e!=NULL)
    {
        e->id=-1;
        e->nom[0]='\0';
        e->age=0;
    }
    return e;
}
void elementLire(ELEMENT * e)
{
    printf("Donner l'id de l'utilisateur : ");
    scanf("%d", &((*e)->id));

    getchar();

    do{
    printf("Donner le nom de l'utilisateur : ");
    gets((*e)->nom);
    }while(!estAlphabetique((*e)->nom));

    printf("Donner l'age de l'utilisateur : ");
    scanf("%d", &((*e)->age));
}
void elementDetruire(ELEMENT e) {
    if (e != NULL) {
        free(e);
    }
}
void elementAfficher(ELEMENT e)
{
    printf("\nL'id d'utilisateur :%d\n",e->id);
    printf("\nLe nom d'utilisateur :%s\n",e->nom);
    printf("L'age d'utilisateur :%d\n",e->age);
}
void elementAffecter(ELEMENT* e1, ELEMENT e2)
{
    *e1=e2;
}
void elementCopier(ELEMENT* e1, ELEMENT e2)
{
    (*e1)->id=e2->id;
     strcpy((*e1)->nom,e2->nom);
    (*e1)->age=e2->age;
}
int elementComparer(ELEMENT e1, ELEMENT e2)
{
    return (e1->id==e2->id);
}
