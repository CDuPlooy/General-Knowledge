# count_to_ten

This program counts to ten.

![count_to_ten](http://i.imgur.com/oYqOuVAg.png)

Looping is done via jump instructions and labels; A label
can be any position in a program. Looping is typically done by
 * Setting the initial number.
 * Doing a check.
 * Exiting the loop or executing the loop body.

 We start out by setting the loop variable.

 ````nasm
movl $0x1, -0x8(%rbp)
 ````

 Now we do the check.

 ````nasm
cmpl $0xa, -0x8(%rbp)
 ````
Should the statement evaluate to true a flag in the process is set to true. Any other operand of the jump familty which works on conditions will first check if this flag is set.

The jg opcode comes after a comparison and jumps if the destination operand is greater than the source.
 ````nasm
 jg 0x400535
 ````

The first time this check is done it will evaluate to true and 'fall through'

(Please note whenever I use <x> it's just to denote that a particular known function is called)

````nasm
movabs $0x4005c4, %rdi
mov -0x8(%rbp),%esi
mov $0x0,%al
callq <printf>
mov %eax,-0xc(%rbp)
mov -0x8(%rbp),%eax
add $0x1,%eax
mov %eax,-0x8(%rbp)
jmpq 0x400506 		' This is the start of the loop
````

Everything above the printf statement has already been discussed. Below it something interesting is happening.
* The address of our counter variable is dereferenced and the value is moved into eax.
* eax is incremented by one.
* The incremented value is restored into our counter variable.


<br>

Once the cmpl instruction evaluates to true the loop body is exited and the process exits
