#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define TAILLE_BUF 4 
void main (void)
{
    FILE* fic ;
    short int buffer[TAILLE_BUF]; /* this table stores the values ​​read in the file.*/
    short int i, nb_val_lues = TAILLE_BUF ;
    /* Opening the file (binary reading). : */
    fic = fopen( "exemple.dat", "rb") ;
    if ( fic==NULL )
    {
        printf("Ouverture du fichier impossible !");
        exit(0);
    }
    /* Reading from file : */
    printf("\n Liste des valeurs lues : \n");
    /*Filling the buffer and processing, as many times as necessary until the end of the file. : */
    while ( nb_val_lues == TAILLE_BUF ) /* vrai tant que fin du fichier non atteinte */
    {
        nb_val_lues = fread( buffer, sizeof(short int), TAILLE_BUF, fic);
        /* Processing the values ​​stored in the buffer (here, a simple display) : */
        for (i=0; i<nb_val_lues; i++) printf( "%hd", buffer[i] );
    }
    /* Closing the file : */
    fclose( fic ) ;
}