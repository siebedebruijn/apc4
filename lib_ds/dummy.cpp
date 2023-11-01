#include <iostream>
#include <string>
#include "list.h"

int main() {
    [[maybe_unused]] saxion::list<int> lst{};

    std::cout << "dummy created and doing well: ";

    for (auto i=0; i < 10; ++i){
        lst.emplace_back(i*42);
    }

    std::cout << "The list has now " << lst.size() << " elements.\nThey are:\n";


    for (auto i=0; i<10; ++i){
        std::cout << "  lst[" << i << "] = " << lst[i] << '\n';
    }

}