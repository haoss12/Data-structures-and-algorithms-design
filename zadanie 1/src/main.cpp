#include <iostream>
#include "PriorityQueue.hh"

int main() {
    PriorityQueue <int> a;

    a.enqueue(8, 1);
    a.enqueue(4, 2);
    a.enqueue(4, 5);

    std::cout << a.min() << std::endl;
    std::cout << a.size() << std::endl;
    return 0;
}