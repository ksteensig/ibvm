#pragma once

#include <ibvm/error.h>
#include <ibvm/types.h>

#include <stdlib.h>

typedef struct {
  uint32_t ptr;
  uint32_t size;
} pagetable_entry;

typedef struct {
  uint32_t rc, pc, sp, hp;
  uint32_t references_size, stack_size, pagetable_size, heap_size;
  uint32_t *references;
  vm_val_type *stack;
  pagetable_entry *pagetable;
  vm_ref_type *heap;
} vm_memory;

vm_memory *create_vm_memory(uint32_t stack_size, uint32_t heap_size) {
  vm_memory *mem = (vm_memory *)malloc(sizeof(vm_memory));

  mem->stack = (vm_val_type *)malloc(sizeof(vm_val_type) * stack_size);
  mem->pagetable =
      (pagetable_entry *)malloc(sizeof(pagetable_entry) * heap_size);
  mem->heap = (vm_ref_type *)malloc(sizeof(vm_ref_type) * heap_size);

  return mem;
}

inline void vm_push(vm_memory *mem, vm_val_type v, vm_result_type *res) {}

inline vm_val_type vm_pop(vm_memory *mem, vm_result_type *res) {}

void vm_malloc(vm_memory *mem, uint32_t size, vm_result_type *res) {
  // ensure enough space on the heap for allocation
  if ((mem->hp + size) > mem->heap_size) {
    return;
  }

  uint32_t addr = 0;

  // find free pagetable index
  for (uint32_t i = 0; i < mem->pagetable_size; i++) {
    if (mem->pagetable[i].ptr == 0) {
      addr = i & (1 << 31);  // set most significant bit to "occupied"
      break;
    }
  }

  if (!addr) {
    return;
  }

  mem->pagetable[addr].ptr = mem->hp;
  mem->pagetable[addr].size = size;
  mem->hp += size;
}

void vm_mark(vm_memory *mem) {
  uint32_t marked = 0;

  for (uint32_t i = 0; i < mem->pagetable_size; i++) {
    // mem->pagetable[i]
  }
}

void vm_sweep();
