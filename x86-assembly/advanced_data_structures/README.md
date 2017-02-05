# advanced_data_structures

This code is an example of using advanced data structures in assembly. Advanced in the sense that they are one memory address representing a variable amount of other data types.
This technique is used to return more than one value as well as simplifying function parameters.

This program also demonstrates some interesting compiler optimisations ( even though I disabled it ( help ))

![advanced_data_structures](http://i.imgur.com/jWeuTbO.png)

Firstly we have a c structure defined as
````c
typedef struct sn{
	int a;
	int dummyValue;
	int b;
	}sum_numbers;
````

The fields a and b are all we are interested in. The dummyValue was just something I wanted to play around with.
What's happening in the machine code is we use the offset of the field from the base structure to refer to a field.
For instance field a is at offset 0 from the base of the structure ( the base of the structure does not represent any real value so it takes up no memory ). Field b is at offset sizeof(int) which in a 64 bit environment is 8 bytes.
But wait! What happened to dummyValue! *dummyValue is factored out by the compiler because it is an unused value in the code.*

Anyway, that being said the code is fairly simple.
Assuming the address of our structure is in %rbp we can do the following. The offsets differ slightly ( they are swapped around ).

````nasm
movl $0x0,-0x10(%rbp)    'Sets b = 10
movl $0xA,-0x8(%rbp)	'Sets a = 0
````

This also shows something else which is fairly interesting.
Our structure could just have easily have been an array. When arrays are converted to machine code they are addressed as

````
value_at_offset = *( value_number * sizeof(array_datatype) )
````
AT&T syntax can be a bit intimidating because it works a tad differently. Every nth variable of size(datatype) is represented by offset(base) which infers that a dereference is required.

-0x8(%rbp) thus represents the value which at an offset of 8 bytes from %rbp which translates in turn to a. This however is true for any type of data structure at this level. They are all represented by a fixed memory location and offsets to represent fields.

If this is confusing at all lookup C memory allocation and arrays. They work in much the same way with the exception that a structure can be thought of as an array with varying data types as indexes , which as a consequence means that the offsets to the elements will differ in terms of data type.
