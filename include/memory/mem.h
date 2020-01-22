#ifndef MEM_H
#define MEM_H


/*
 * Function definitions
 */

#include <stdint.h>
#include <memory/mem_values.h>

uint64_t	get_page();
void		free_page(uint64_t);
void		zero_memory(uint64_t src, uint64_t n);


#endif /* MEM_H */
