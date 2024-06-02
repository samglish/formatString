# formatString
Particular vulnerability to study

``` Variable functions and arguments must be secure```
```c
<type> function (<type>, ARG1);
```
Macros var_start, var_arg, var_end
</br>
<b>Example</b>
```c
printf()
printf(ARG1, ARG2...ARGN);
```

#### so what happens if we don't give the right number of arguments to printf()?

<img src="formString.png" width="30%">

## The fault
using user input in a format string.
### Example
```c
printf(argv[1]);

printf("%s", argv[1]);
```
### useful formats for exploitation
* %x : hexadecimal display of a provided value
* %hn : writing the number of bytes processed by printf provided

## Solution
<hr>

* Direct parameter access > Specify the address to write to.
* Minimum size > writing a specific value.
* by forcing the formatting we prevent the hacker from wandering around and rewriting our stack.
## Exploit
<hr>

* shellcode injection
<p>looking for a function pointer after calling printf.</p>
<p>overwriting the pointer with the shellcode address.</p>
<p>once the function is overwritten, the program jumps to the shellcode address.</p>

<img src="fString.png" width="70%">

## GOT - Global Offset Table
<hr>

<img src="GOT.png" width="70%">

<hr>

## The program
<hr>

```c
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
    fic = fopen( "texte.txt", "rb") ;
    if ( fic==NULL )
    {
        printf("Unable to open file !");
        exit(0);
    }
    /* Reading from file : */
    printf("\n List of values ​​read: \n");
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
```
## Test
<hr>

* show file `texte.txt`
```terminal
$cat texte.txt
``` 
output
```
%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x

```
* Compile formatstring.c
```terminal
$gcc -g -0 FS formatstring.c
```
* execute
```terminal
$./FS
```
output
```
Liste des valeurs lues : 
307573075730757307573075730757307573075730757307573075730757307573075730757
```
* let's find out where the fault lies.
```terminal
gdb ./FS
```
```
GNU gdb (Debian 10.1-1.7) 10.1.90.20210103-git
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./FS...
(gdb) 
```
* let's locate the fault.
```terminal
(gdb)isass main
```
