#include "src/Ring.h"
#include "src/menu_functions.h"

int main() {

/*
    program();
*/

    Ring<int> i_ring;

    try {
        auto it = i_ring.begin();

        i_ring.add_front(1);
        i_ring.add_front(2);
        i_ring.add_front(4);

        i_ring.print();


        std::cout << std::endl;

        it = i_ring.find(1);
        i_ring.delete_element(it);

        it = i_ring.find(2);
        i_ring.delete_element(it);

        it = i_ring.find(4);
        i_ring.delete_element(it);

        i_ring.add_back(7);
        i_ring.add_back(8);

        std::cout << std::endl;


        i_ring.print();
    } catch (std::exception &ex) {
        std::cout << std::endl << "Error: " << ex.what();
    }
}
