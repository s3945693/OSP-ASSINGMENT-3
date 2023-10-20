#include "assignedLinkedList.h"


AssignedLinkedList::AssignedLinkedList() {
    // std::cout << "Constructor called" << std::endl;
    std::cout << "Constructor called" << std::endl;
}



void* AssignedLinkedList::alloc(std::size_t size){

    std::size_t allocateMem = 600;

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

    allocation* new_chunk = new allocation{size, new_space};
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
            allocatedList.erase(it);
            freeList.push_back(chunk);
            return;
        }
    }

    // If the chunk is not found in the allocated list, this is a fatal error.
    throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
}

void AssignedLinkedList::dealloc(){
    //remove last chuck from allocated and add to free list

    if (allocatedList.size() == 0) {
        throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
    }

    allocation* chunk = allocatedList.back();
    allocatedList.pop_back();
    freeList.push_back(chunk);

}

AssignedLinkedList::~AssignedLinkedList() {
    // std::cout << "Destructor called" << std::endl;
    std::cout << "Destructor called" << std::endl;
    for (auto i = allocatedList.begin(); i != allocatedList.end(); ++i) {
        int ret = brk((*i)->space);
        std::cout << "brk returned " << ret << std::endl;
        delete *i;
    }
    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        int ret2 = brk((*i)->space);
        std::cout << "brk2 returned " << ret2 << std::endl;
        delete *i;
    }

    
}