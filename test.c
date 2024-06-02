int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    int age = 0;
 
    fichier = fopen("test.txt", "w");
 
    if (fichier != NULL)
    {
        // On demande l'âge
        printf("Quel age avez-vous ? ");
        scanf("%d", &age);
 
        // On l'écrit dans le fichier
        fprintf(fichier, "Le Monsieur qui utilise le programme, il a %d ans", age);
        fclose(fichier);
    }
 
    return 0;
}