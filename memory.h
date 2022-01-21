#ifndef INCLUDE_MEMORY_H
#define INCLUDE_MEMORY_H

struct gdt {
    unsigned int address;
    unsigned short size;
} __attribute__((packed));

/** load_gdt:
 *  Loads the struct into GDT. Defined in gdt.s
 *  @param *s pointer to the struct
 */
void load_gdt(struct gdt *g);


#endif /* INCLUDE_MEMORY_H */
