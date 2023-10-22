#include "assignedLinkedList.h"


AssignedLinkedList::AssignedLinkedList() {
   
}



void* AssignedLinkedList::alloc(std::size_t size){

    std::size_t allocateMem = 600;

    //finds a chunk from the free list that is big enough to fit the size

    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size >= size) {
            if ((*i)->size < allocateMem){
                allocateMem = (*i)->size;
            }
        }
    }

    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size == allocateMem) {
            allocation* chunk = *i;
            freeList.erase(i);
            chunk->used = size;
            allocatedList.push_back(chunk);
            return chunk->space;
        }
    }

    // If no suitable chunk is found in the free list, use sbrk() to allocate more memory.

    if (size <= 32){
        allocateMem = 32;
    }

    else if (size <= 64){
        allocateMem = 64;
    }

    else if (size<= 128){
        allocateMem = 128;
    }

    else if (size <= 256){
        allocateMem = 256;
    }

    else if (size <= 512){
        allocateMem = 512;
    }

    void* new_space = sbrk(allocateMem);
    if (new_space == (void*) -1) {
        throw std::bad_alloc();
    }

    allocation* new_chunk = new allocation{allocateMem,size, new_space};
    allocatedList.push_back(new_chunk);
    return new_space;
    
}

void AssignedLinkedList::dealloc(void* chunk_space) {

    if (allocatedList.size() == 0) {
        throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
    }

    for (auto it = allocatedList.begin(); it != allocatedList.end(); ++it) {
        if ((*it)->space == chunk_space) {
            allocation* chunk = *it;
            chunk->used = 0;
            allocatedList.erase(it);
            freeList.push_back(chunk);
            return;
        }
    }

    throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
}

void AssignedLinkedList::dealloc(){
    //remove last chuck from allocated and add to free list

    if (allocatedList.size() == 0) {
        throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
    }

    allocation* chunk = allocatedList.back();
    chunk->used = 0;
    allocatedList.pop_back();
    freeList.push_back(chunk);

}

AssignedLinkedList::~AssignedLinkedList() {

    std::cout << "Allocated List" << std::endl;
    for (auto i = allocatedList.begin(); i != allocatedList.end(); ++i) {

        std::cout << (*i)->space << " Used Memory: " << (*i)->used << " Total Memory: " << (*i)->size <<std::endl;
        int ret = brk((*i)->space);
        if (ret == -1) {
            std::cout << "brk encountered error" << std::endl;
        }
        
        delete *i;
    }

    std::cout << "Free List" << std::endl;

    for (auto i = freeList.begin(); i != freeList.end(); ++i) {

        std::cout << (*i)->space << " Used Memory: " << (*i)->used << " Total Memory: " << (*i)->size <<std::endl;
        int ret2 = brk((*i)->space);
        if (ret2 == -1) {
            std::cout << "brk encountered error" << std::endl;
        }
        delete *i;
    }

    
}