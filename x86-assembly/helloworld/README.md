# Notes

All examples are compiled with

````bash
$(CC) $(input) -ggdb -O0 $(output)
````

## *printf*:

![printf_debug](http://i.imgur.com/4e7lJlB.png)

When calling printf firstly 16 bytes of space is cleared on the stack.
This is done via

````nasm
mov $rsp,$rbp
sub 0x10,%rsp
````

At this point the base stack pointer (rbp)'s value is moved into the stack frame pointer (rsp). We now have 0x10 ( or 16 ) bytes of space avaidable. This the way I'm calling printf it requires two parameters ; The format specifier and the buffer ( or char * ). Both of these are passed as pointers which on a 64 bit system has a size of 8 bytes. It thus logically concludes that we need 16 bytes of stack space to call the printf function with two parameters.


After all of this happens we need to actually set up the parameters for the function call. This is done via

````nasm
movabs $0x4005b4, %rdi
movabs $0x4005b8, %rsi
````

(someone please look this up) ; If I understand correctly movabs is used to move a value ( 0x4005bx ) into an immediate 64 bit register.

At this point rdi and rsi is equals to ( pointing to really ) "%s" and "Hello world!\n" respectively.


Now the function needs to be called ( unrelated but try to remember that most functions return values are stored in rax ). al (a - low) is cleared and the function is called via

````nasm
mov $0x0, $al
callq 0x4003e0
````

callq will pushes the value of %rip onto the stack so that once the function is called the program knows where to return to.




After the function has been called we need to clean up. This is done by resetting the stack frame pointer to the base stack pointer. The offset from rsp to rbp is -10. To 'fix' this we simply do

````nasm
add $0x10,%rsp
````


As a side note you'll notice that at the start of libc initialisation push $rbp is done and then at the end of the code pop $rpb is done.
I think this is done so there are no stack overflows/underflows when the process exits.
