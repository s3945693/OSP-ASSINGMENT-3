#include "assignedLinkedList.h"
#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    std::vector<int> size;
    std::vector<std::string> function;
    //read in file

    std::ifstream file("input.txt");

    std::string line;


    while (std::getline(file, line)) {
        int a;
        std::string b;
        //split the string by colon
        std::string delimiter = ":";

        size_t pos = 0;
        if (line.find(delimiter) == std::string::npos) {

            b = "dealloc";
            size.push_back(0);
            function.push_back(b);
        }
        else{

            pos = line.find(delimiter);

            //std::cout <<"here" << std::endl;
            //std::cout << line.substr(pos+2) << std::endl;

            a = std::stoi(line.substr(pos+2));
            b = line.substr(0, pos);

            size.push_back(a);
            function.push_back(b);
        }
    }

    AssignedLinkedList* list = new AssignedLinkedList();

    for (std::vector<int>::size_type i = 0; i < size.size(); i++) {
        if (function[i] == "alloc") {
            std::cout << "allocating " << size[i] << " bytes" << std::endl;
            list->alloc(size[i]);
        }
        else if (function[i] == "dealloc") {
            std::cout << "deallocating " << size[i] << " bytes" << std::endl;
            list->dealloc();
        }
        else {
            std::cout << "Error: invalid function" << std::endl;
        }
    }
    delete list;
    return 0;

}
