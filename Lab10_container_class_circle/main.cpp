#include <iostream>
#include "src/Ring.h"

int main() {

    Ring<int> i_ring;

    i_ring.add_back(6);
    i_ring.add_back(7);
    i_ring.add_front(8);

    i_ring.print();

    Ring<std::string> s_ring;
    s_ring.add_back("first");
    s_ring.add_back("second");
    s_ring.add_front("last");

    s_ring.print();
}
