#include "assignedLinkedList.h"


AssignedLinkedList::AssignedLinkedList() {
    // std::cout << "Constructor called" << std::endl;
    std::cout << "Constructor called" << std::endl;
}

void* AssignedLinkedList::alloc(std::size_t size){
    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size >= size) {
            allocation* chunk = *i;
            freeList.erase(i);
            allocatedList.push_back(chunk);
            return chunk->space;
        }
    }

    // If no suitable chunk is found in the free list, use sbrk() to allocate more memory.
    void* new_space = sbrk(size);
    if (new_space == (void*) -1) {
        throw std::bad_alloc();
    }

    allocation* new_chunk = new allocation{size, new_space};
    allocatedList.push_back(new_chunk);
    return new_space;
    
}



void dealloc(void* chunk_space) {
    for (auto it = allocatedList.begin(); it != allocatedList.end(); ++it) {
        if ((*it)->space == chunk_space) {
            Chunk* chunk = *it;
            allocatedList.erase(it);
            freeList.push_back(chunk);
            return;
        }
    }

    // If the chunk is not found in the allocated list, this is a fatal error.
    throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
}