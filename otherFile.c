#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define TAILLE_BUF 4 /* valeur quelconque (en gÃ©nÃ©ral, beaucoup plus grande) */
void main (void)
{
    FILE* fic ;
    short int buffer[TAILLE_BUF]; /* ce tableau mÃ©morisera les valeurs lues dans le fichier */
    short int i, nb_val_lues = TAILLE_BUF ;
    /* Ouverture du fichier (en lecture binaire) : */
    fic = fopen( "exemple.dat", "rb") ;
    if ( fic==NULL )
    {
        printf("Ouverture du fichier impossible !");
        exit(0);
    }
    /* Lecture dans le fichier : */
    printf("\n Liste des valeurs lues : \n");
    /*Remplissage du buffer et traitement, autant de fois que nÃ©cessaire jusqu'Ã  la fin fichier : */
    while ( nb_val_lues == TAILLE_BUF ) /* vrai tant que fin du fichier non atteinte */
    {
        nb_val_lues = fread( buffer, sizeof(short int), TAILLE_BUF, fic);
        /* Traitement des valeurs stockÃ©es dans le buffer (ici, un simple affichage) : */
        for (i=0; i<nb_val_lues; i++) printf( "%hd", buffer[i] );
    }
    /* Fermeture du fichier : */
    fclose( fic ) ;
}