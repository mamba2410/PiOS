#ifndef VMEM_H
#define VMEM_H

#include <stdint.h>
#include <proc/tasks.h>

void		map_table_entry(uint64_t *pte, uint64_t va, uint64_t pa);
uint64_t	map_table(uint64_t *table, uint64_t shift, uint64_t va, int8_t *new_table);
void		map_page(task_t *task, uint64_t va, uint64_t page);
int32_t		copy_virt_memory(task_t *dst);
int32_t		_mem_abort(uint64_t addr, uint64_t esr);

extern void		set_pgd(uint64_t);
extern uint64_t	get_pgd();

#endif /* VMEM_H */
