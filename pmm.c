#include <stdint.h>
#include "memlayout.h"
#include "multiboot.h"
#include <stddef.h>
#include "str.h"

#define NUM_BYTES 512



//this file contains code for the physical memory manager


/* 
    initialize bookkeeping region
    starting after heap_start we allocate 512 bytes to keep track of pages
    this can keep track of 2048 pages
    pool size is 8MiB and page size is 4kb.
    With 2bits per page we can address 4 pages per byte
    therefore we have 2048 pages we can address

    new plan just use 1 byte per page, so you need one page full of page metadata
 */
#define PGSIZE 4096
#define bookkeep_end  ((uintptr_t)HEAP_START + (PGSIZE * 8))

typedef enum {BK_FREE=0, BK_TAKEN=2, BK_RESERVED=2} bk_state_t;

//please just use a byte instead of 2 bits, 2bit headache :(

void bk_get(size_t offset) {
    uint8_t *heap = (uint8_t *)HEAP_START;
    return heap[offset];
}


void initialize_heap() {
    size_t heap_size = HEAP_END - HEAP_START;
    memset((void *)HEAP_START, 0, heap_size);
    //zero heap 
}

void alloc_page(size_t num_pages) {
    char* address =  (char*) PGROUNDUP((uint)bookkeep_end );
    uint8_t *heap = (uint8_t)HEAP_START;
    size_t i = 0;
    while(address < HEAP_END && heap[i] == BK_TAKEN) { 
        address += 4096;

    }
    heap[i] = BK_TAKEN;

    return address;

    
}

