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

    


3.10.5 Supporting Variable-Size Stack Frames

We have examined the machine-level code for a variety of functions so far, but they all have the property that the compiler can 








