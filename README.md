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