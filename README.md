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
(gdb)disassemble main

```
output

```terminal
Dump of assembler code for function main:
   0x0000555555555185 <+0>:	push   %rbp
   0x0000555555555186 <+1>:	mov    %rsp,%rbp
   0x0000555555555189 <+4>:	sub    $0x810,%rsp
   0x0000555555555190 <+11>:	movw   $0x400,-0x4(%rbp)
   0x0000555555555196 <+17>:	lea    0xe6b(%rip),%rsi        # 0x555555556008
   0x000055555555519d <+24>:	lea    0xe67(%rip),%rdi        # 0x55555555600b
   0x00005555555551a4 <+31>:	call   0x555555555070 <fopen@plt>
   0x00005555555551a9 <+36>:	mov    %rax,-0x10(%rbp)
   0x00005555555551ad <+40>:	cmpq   $0x0,-0x10(%rbp)
   0x00005555555551b2 <+45>:	jne    0x5555555551cf <main+74>
   0x00005555555551b4 <+47>:	lea    0xe5d(%rip),%rdi        # 0x555555556018
   0x00005555555551bb <+54>:	mov    $0x0,%eax
   0x00005555555551c0 <+59>:	call   0x555555555060 <printf@plt>
   0x00005555555551c5 <+64>:	mov    $0x0,%edi
   0x00005555555551ca <+69>:	call   0x555555555080 <exit@plt>
   0x00005555555551cf <+74>:	lea    0xe64(%rip),%rdi        # 0x55555555603a
   0x00005555555551d6 <+81>:	call   0x555555555030 <puts@plt>
   0x00005555555551db <+86>:	jmp    0x555555555240 <main+187>
 --Type <RET> for more, q to quit, c to continue without paging--
   0x00005555555551dd <+88>:	mov    -0x10(%rbp),%rdx
   0x00005555555551e1 <+92>:	lea    -0x810(%rbp),%rax
   0x00005555555551e8 <+99>:	mov    %rdx,%rcx
   0x00005555555551eb <+102>:	mov    $0x400,%edx
   0x00005555555551f0 <+107>:	mov    $0x2,%esi
   0x00005555555551f5 <+112>:	mov    %rax,%rdi
   0x00005555555551f8 <+115>:	call   0x555555555040 <fread@plt>
   0x00005555555551fd <+120>:	mov    %ax,-0x4(%rbp)
   0x0000555555555201 <+124>:	movw   $0x0,-0x2(%rbp)
   0x0000555555555207 <+130>:	jmp    0x555555555236 <main+177>
   0x0000555555555209 <+132>:	movswl -0x2(%rbp),%eax
   0x000055555555520d <+136>:	cltq   
   0x000055555555520f <+138>:	movzwl -0x810(%rbp,%rax,2),%eax
   0x0000555555555217 <+146>:	cwtl   
   0x0000555555555218 <+147>:	mov    %eax,%esi
   0x000055555555521a <+149>:	lea    0xe35(%rip),%rdi        # 0x555555556056
   0x0000555555555221 <+156>:	mov    $0x0,%eax
   0x0000555555555226 <+161>:	call   0x555555555060 <printf@plt>
   0x000055555555522b <+166>:	movzwl -0x2(%rbp),%eax
   0x000055555555522f <+170>:	add    $0x1,%eax
   0x0000555555555232 <+173>:	mov    %ax,-0x2(%rbp)
   0x0000555555555236 <+177>:	movzwl -0x2(%rbp),%eax
  --Type <RET> for more, q to quit, c to continue without paging--
   0x000055555555523a <+181>:	cmp    -0x4(%rbp),%ax
   0x000055555555523e <+185>:	jl     0x555555555209 <main+132>
   0x0000555555555240 <+187>:	cmpw   $0x400,-0x4(%rbp)
   0x0000555555555246 <+193>:	je     0x5555555551dd <main+88>
   0x0000555555555248 <+195>:	mov    -0x10(%rbp),%rax
   0x000055555555524c <+199>:	mov    %rax,%rdi
   0x000055555555524f <+202>:	call   0x555555555050 <fclose@plt>
   0x0000555555555254 <+207>:	nop
   0x0000555555555255 <+208>:	leave  
   0x0000555555555256 <+209>:	ret    
```
## Two detected
<hr>

```
0x00005555555551c0 <+59>:	call   0x555555555060 <printf@plt>
0x0000555555555226 <+161>:	call   0x555555555060 <printf@plt>
```
