#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string> 
#include <iostream>
#include <list>
#include <cstdlib>
#include <unistd.h>

class AssignedLinkedList{

    public:
        struct allocation {
            std::size_t size;
            std::size_t used;
            void *space;
        };

        std::list<allocation*> allocatedList;
        std::list<allocation*> freeList;

        void* alloc(std::size_t chunk_size);
        void dealloc(void* chunk_space);
        void dealloc();



        AssignedLinkedList();
        ~AssignedLinkedList();

        void printAllocatedList();

};


#endif  // LINKEDLIST_H