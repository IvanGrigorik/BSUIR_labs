#include <iostream>
#include <vector>
using namespace std;



class beta{
public:
    int d;
};

class alpha{
public:
    int a;
    friend class beta;

    void printd() const{
        cout << "Hello?" << d;
    };
};


int main () {
}
