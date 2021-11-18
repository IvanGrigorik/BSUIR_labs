#include <iostream>
#include "src/file_work.h"


int main() {

    std::ofstream target;
    std::ifstream source;

    new_files(target);

    Notes note1("Remind1", "remind1", false);
    Notes note2("Remind2", "remind2", true);
    Notes note3("Remind3", "remind3", true);
    Notes note4("Remind4", "remind4", false);

    target.open(text, std::ios::app);
    note1.write_text(target);
    note2.write_text(target);
    note3.write_text(target);
    note4.write_text(target);
    target.close();

    target.open(binary, std::ios::app | std::ios::in);
    note1.write_bin(target);
    note2.write_bin(target);
    note3.write_bin(target);
    note4.write_bin(target);
    target.close();

    print_text(source);
    std::cout << std::endl;
    print_binary(source);
    std::cout << std::endl;
    reverse_print_text(source);
    std::cout << std::endl;
    reverse_print_binary(source);
    std::cout << std::endl;

    file_searching("text",source, "remind1", 2);
    file_searching("binary",source, "remind3", 2);

    file_delete("text",source, "remind2", 2);
}
