3.9.2 Unions
Unions provide a way to circumvent the tyep system of C, allowing a single object to be referenced according to multiple types. The syntax of a union declaration is identical to that for structures, but its semantics are very different. Rather than having the different fields reference blocks of memory, they all reference the same block.

struct S3 {
    char c;
    int i[2];
    double v;
}

union U3 {
    char c;
    int i[2];
    double v;
}
When compiled on x86-64 Linux machine, the offsets of the fields, as well as the total size of types S3 and U3, are as shown in the following table:

Type    c   i   v   Size
S3      0   4   16  24
U3      0   0   0   8

We will see shortly why i has offset 4 in S3 rather than 1, and why v has offset 16, rather than 9 or 12. For pointer p of type union U3 *, references p->c, p->i[0], and p->v would all reference the beginning of the data structure. Observer also that the overall size of a union equals the maximum size of any of its fields.
    Unions can be usefull in several contexts. However, they can also lead to nasty bugs, since they bypass the safety provided by the C type system. One application is when we know in advance that the use of two different fields in a data structure will be mutually exclusive. Then, declaring these two fields as part of a union rather than a structure will reduce the total space allocated.
    For example, suppose we want to implement a binary tree data structure where each leaf node has two double data values and each internal node has pointers to two double values and each internal node has pointers to two children but no data. If we declare this as

    struct node_s {
        struct node_s *left;
        struct node_s *right;
        double data[2];
    };

    then every node requires 32 bytes, with half the bytes wasted for each type of node. On the other hand, if we declare a node as

    union node_u {
        struct {
            union node_u *left;
            union node_u *right;
        } internal
        double data[2];
    };

    then every node will require just 16 bytes. If n is a pointer to a node of type union node_u *, we would reference the data of a leaf node as n->data[0] and n->data[1], and the children of an internal node as n->internal.left and n->internal.right.

    With this encoding, however, there is no way to determine whether a given node is a leaf or an internal node. A common method is to introduce an enumerated type defining the different possible choices for the union, and then create a structure containing a tag field and the union:

    3.9.3 Data Alignment
    Many computer systems place restrictions on the allowable address for the primitive data types, requiring that the address for some objects must be a multiple of some value K(typically2,4,or 8). Such alignment restrictions simplify the design of the hardware forming the interface between the processor and the memory system. For example, suppose a processor always fetches 8 bytes from memory with an address that must be a multiple of 8. If we can guarantee that any double will be aligned to have its address be a multiple of 8, then the value can be read or written with a single memory operation. Otherwise, we may need to perform two memory accesses, since the object might be split scross two 8-byte memory blocks.
    //leaq instruction support only 8 bytes

The x86-64 hardware will work correctly regardless of the alignment of data. However, Intel recommends that data be aligned to improve memory system performance. Their alignment rule is based on the principle that any primitive objects K bytes must  have an address that is a multiple of K. We can see that this rule leads to the following alignments:
        K      Types
        1       char
        2       short
        4       int,float
        8       long,double, char *

Alignment is enforced by making sure taht every data type is organized and allocated in such a way that every object within the type satisfies its alignment restrictions. The compiler places directives in the assembly code indicating the desired alignment for global data. For example,
.align 8
This ensures that the data following it(in this case the start of the jump table) will start with an address that is a multiple of 8. Since each table entry is 8 bytes long, the successive elements will obey the 8-byte alignment restriction.
    For code involving structures, the compiler may need to insert gaps in the field allocation to ensure that each structure element satisfies its alignement requirement. The structure will then have some required alignment for its starting address.
For example, consider the structure declaration

    struct S1{
        int i;
        char c;
        int j;
    }


3.10.3 Out-of-Bounds Memory References and Buffer Overflow

We have seen that C does not perform any bounds checking for array references, and that local variables are stored on the stack along with state information such as saved register values and return addresses. This combination can lead to serious program errors, where the state stored on the stack gets corrupted by a write to an out-of-bounds array element. When the program then tries to reload  the register or execute a ret instruction with this corrupted state, things can go seriously wrong.
    A particularly common source of state corruption is know as buffer overflow. Typically, some character array is allocated on the stack to hold a string, but the size of the string exceeds the space allocated for the array.
eg.
char *gets(char *s) {
    int c;
    char *dest = s;
    .....
}

Characters types                Additional corrupted state
------------------------------------------------------------------
0-7                                None
9-23                             Unused stack space
24-31                             Return address
32+                              Save state in caller


    No serious consequence occurs for strings of up to 23 characters, but beyond that, the value of the return pointer, and possibly additional saved state, will be corrupted. If the stored value of the return address is corrupted, then the ret instruction willcause the program to jump to a totally unexpected location. None of these behaviors would seem possible based on the C code. The impact of out-of-bounds writing to memory by functions such as gets can only be understood by studying the program at the machine-code level.

A more pernicious use of buffer overflow is to get a program to perform a function that it would otherwise be unwilling to do. This is one of the most common methods to attack the security of system over a computer network. Typically, the program is fed with a string that contains the byte encoding of some executable code, called the exploit code, plus some extra bytes that overwrite the return address with a pointer to the exploit code. The effect of executing the ret instruction is then to jump to the exploit code.
In one form of attack, the exploit code then uses a system call to start up a shell program, providing the attacker with a range of operating system functions. In another form , the exploit code performs some otherwise unauthorized task, repairs the damage to the stack, and then executes ret a second time, causing an normal return to the caller.

3.10.4 Thwarting Buffer Overflow Attacks

Buffer overflow attacks have become so pervasive and have caused so many problems with computer systems that modern compilers and operation systems have implemented mechanisms to make it more difficult to mount these attacks and to limit the ways by which an intruder can seize control of a system via a buffer overflow attack. In this section, we will present mechanisms that are provided by recent versions of GCC for Linux.

Stack Randomization
In order to insert exploit code into a system, the attacker needs to inject both the code as well as a pointer to this code as part of the attack string. Generating this pointer requires knowing the stack address where the string will located. Historically, the stack addresses for a program were highly predictable. For all systems running the same combination of program and operating system version, the stack locations were fairly stable across many machines. So, for example, if an attacker could determine the stack address used by a common web server, it could devise an attack that would work on many machines.
With ASLR, different parts of the program, including program code, library code, stack, global variables, and heap data, are loaded into different regions of memory each time a program is run.

3.10.5 Supporting Variable-Size Stack Frames

We have examined the machine-level code for a variety of functions so far, but they all have the property that the compiler can 








