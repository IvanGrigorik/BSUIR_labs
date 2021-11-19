#include "Ring.h"

int main() {
    Ring<int, false> i_ring;

    auto it = i_ring.begin();
    i_ring.push(it, 1);
    i_ring.push(it, 2);
    i_ring.push(it, 3);
    i_ring.push(it, 4);

}
