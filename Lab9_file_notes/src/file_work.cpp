//
// Created by Ivan on 15.11.2021.
//

#include "file_work.h"

void print_text(std::ifstream &file) {
    if (!file.is_open()) {
        file.open(text);
    }

    Notes temp;
    int counter{};

    while (true) {
        temp.read_text(file);

        if (file.eof())
            break;

        counter++;
        std::cout << counter << ") " << temp.get_note_title() << ' ' << temp.get_note_text();
        if (temp.get_is_complete()) {
            std::cout << " Complete" << std::endl;
        } else {
            std::cout << " Not complete" << std::endl;
        }
    }
    file.close();
}

void reverse_print_text(std::ifstream &file) {
    if (!file.is_open()) {
        file.open(text);
    }

    Notes temp;

    // Read how many Notes in file
    std::size_t amount = 0;


    while (true) {
        temp.read_text(file);
        if (file.eof())
            break;
        amount++;
    }

    file.clear();
    file.seekg(std::ios::beg);
    int counter{};

    while (amount != 0) {
        for (int i = 0; i < amount; ++i) {
            temp.read_text(file);
        }


        counter++;
        std::cout << counter << ") " << temp.get_note_title() << ' ' << temp.get_note_text();
        if (temp.get_is_complete()) {
            std::cout << " Complete" << ' ' << std::endl;
        } else {
            std::cout << " Not complete" << std::endl;
        }

        file.seekg(std::ios::beg);
        amount--;
    }

    file.close();
}

void print_binary(std::ifstream &file) {
    if (!file.is_open()) {
        file.open(binary, std::ios::binary | std::ios::in);
    }

    Notes temp;

    int counter{};
    while (true) {
        temp.read_bin(file);
        if (file.eof()) {
            break;
        }
        counter++;

        std::cout << counter << ") " << temp.get_note_title() << ' ' << temp.get_note_text();
        if (temp.get_is_complete()) {
            std::cout << " Complete" << std::endl;
        } else {
            std::cout << " Not complete" << std::endl;
        }
    }
    file.close();
}

void reverse_print_binary(std::ifstream &file) {
    if (!file.is_open()) {
        file.open(binary, std::ios::binary | std::ios::in);
    }

    Notes temp;
    std::size_t amount = 0;
    int counter{};
    while (true) {
        temp.read_bin(file);
        if (file.eof()) {
            break;
        }
        amount++;
    }

    file.clear();
    file.seekg(std::ios::beg);

    while (amount != 0) {
        for (int i = 0; i < amount; i++) {
            temp.read_bin(file);
        }

        counter++;

        std::cout << counter << ") " << temp.get_note_title() << ' ' << temp.get_note_text();
        if (temp.get_is_complete()) {
            std::cout << " Complete" << std::endl;
        } else {
            std::cout << " Not complete" << std::endl;
        }

        file.seekg(std::ios::beg);
        amount--;
    }
    file.close();
}

void new_files(std::ofstream &file) {
    file.open(text, std::ios::trunc);
    file.close();
    file.open(binary, std::ios::trunc);
    file.close();
}

void file_searching(const std::string &file_type, std::ifstream &file,
                    const std::string &note_info_to_find, int field_to_find) {

    if (file_type == "text") {
        if (!file.is_open()) {
            file.open(text);
        }
    } else if (file_type == "binary") {
        if (!file.is_open()) {
            file.open(binary, std::ios::binary | std::ios::in);
        }
    }

    Notes temp;

    while (true) {
        if (file_type == "text") {
            temp.read_text(file);
        } else if (file_type == "binary") {
            temp.read_bin(file);
        }
        if (file.eof())
            break;

        switch (field_to_find) {
            case 1:
                if (temp.get_note_title() == note_info_to_find) {

                    std::cout << temp.get_note_title() << ' ' << temp.get_note_text();
                    if (temp.get_is_complete()) {
                        std::cout << " Complete" << std::endl;
                    } else {
                        std::cout << " Not complete" << std::endl;
                    }
                }
                break;

            case 2:
                if (temp.get_note_text() == note_info_to_find) {
                    std::cout << temp.get_note_title() << ' ' << temp.get_note_text();
                    if (temp.get_is_complete()) {
                        std::cout << " Complete" << std::endl;
                    } else {
                        std::cout << " Not complete" << std::endl;
                    }
                }
                break;

            case 3: {
                std::string is_complete = temp.get_is_complete() ? "true" : "false";
                if (is_complete == note_info_to_find) {
                    std::cout << temp.get_note_title() << ' ' << temp.get_note_text();
                    if (temp.get_is_complete()) {
                        std::cout << " Complete" << std::endl;
                    } else {
                        std::cout << " Not complete" << std::endl;
                    }
                }
                break;
            }

            default:
                break;
        }
    }
    file.close();
}

void file_delete(const std::string &file_type, std::ifstream &file, int delete_number) {

    if (file_type == "text") {
        if (!file.is_open()) {
            file.open(text);
        }
    } else if (file_type == "binary") {
        if (!file.is_open()) {
            file.open(binary, std::ios::binary | std::ios::in);
        }
    }

    std::ofstream temp_o_file;
    temp_o_file.open("temp.txt", std::ios::trunc);

    Notes temp;
    int counter{};

    while (true) {
        if (file_type == "text") {
            temp.read_text(file);
        }
        if (file_type == "binary") {
            temp.read_bin(file);
        }

        counter++;

        if (delete_number == counter) {
            if (file_type == "text") {
                temp.read_text(file);
                if (file.eof()) {
                    break;
                }
            }
            if (file_type == "binary") {
                temp.read_bin(file);
                if (file.eof()) {
                    break;
                }
            }
        }

        if (file.eof()) {
            break;
        }

        temp.write_text(temp_o_file);
    }

    temp_o_file.close();
    temp_o_file.clear();

    file.close();

    std::ofstream target;
    if (file_type == "text") {
        target.open(text, std::ios::trunc);
    } else if (file_type == "binary") {
        target.open(binary, std::ios::binary | std::ios::in | std::ios::trunc);
    }

    std::ifstream temp_i_file;
    temp_i_file.open("delete_notes.txt");

    while (true) {


        temp.read_text(temp_i_file);

        if (temp_i_file.eof()) {
            break;
        }

        if (file_type == "text") {
            temp.write_text(target);
        } else if (file_type == "binary") {
            temp.write_bin(target);
        }
    }


    temp_o_file.close();
    target.close();
}

void delete_duplicated(){

    std::ofstream target;
    std::ifstream source;

    // Text file deleting
    source.open(text);

}