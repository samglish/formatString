#include <stdio.h>
#include <stdlib.h>

int main(void){
    int fd, i;
    char buffer[1024];
    fd=open("texte.txt", O_RDONLY);
    if(fd<0) exit(0);
    read(fd, buffer, 1024);
    printf(buffer);
    close(fd);
    return 0;
}