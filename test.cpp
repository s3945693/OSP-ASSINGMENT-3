#include <list>
#include <cstddef>
#include <new>

struct Chunk {
    std::size_t size;
    void *space;
};

std::list<Chunk*> freeList;
std::list<Chunk*> allocatedList;

void* alloc(std::size_t chunk_size) {
    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        if ((*it)->size >= chunk_size) {
            Chunk* chunk = *it;
            freeList.erase(it);
            allocatedList.push_back(chunk);
            return chunk->space;
        }
    }

    // If no suitable chunk is found in the free list, use sbrk() to allocate more memory.
    void* new_space = sbrk(chunk_size);
    if (new_space == (void*) -1) {
        throw std::bad_alloc();
    }

    Chunk* new_chunk = new Chunk{chunk_size, new_space};
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
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    // Save the initial program break.
    void* initial_break = sbrk(0);
    if (initial_break == (void*) -1) {
        perror("sbrk failed");
        return 1;
    }

    // Allocate some memory...
    void* new_space = sbrk(1024);
    if (new_space == (void*) -1) {
        perror("sbrk failed");
        return 1;
    }

    // Use the memory...

    // At the end of the program, reset the program break to its initial position.
    if (brk(initial_break) != 0) {
        perror("brk failed");
        return 1;
    }

    return 0;
}
