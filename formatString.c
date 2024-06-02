#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
int main(){
FILE* fd = NULL;
int i;   
    char buffer[1024];
    fd = fopen("texte.txt", O_RDONLY);
    if (fd < 0) exit ( 0 );
    fread( buffer, sizeof(short int), 1024, fd);
    printf(buffer);
    fclose(fd);
    return 0;
}