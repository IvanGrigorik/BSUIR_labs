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
    temp_o_file.open("delete_notes.txt", std::ios::trunc);

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
    temp_i_file.open("delete_notes.txt", std::ios::in | std::ios::out);

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
    temp_i_file.close();
    target.close();

    std::cout << "The removal process was successful" << std::endl;
}

void delete_duplicated() {

    // Text remove duplicated
    std::ifstream source;
    source.open(text, std::ios::in);

    std::fstream io_file;
    io_file.open("un_duplicated.txt", std::ios::in | std::ios::out | std::ios::trunc);

    Notes note_from_source;
    Notes note_from_temp;

    bool is_in_file;

    while (true) {

        note_from_source.read_text(source);

        if (source.eof()) {
            break;
        }

        io_file.seekg(0, std::ios::beg);
        is_in_file = false;
        while (true) {
            io_file >> note_from_temp;

            if (io_file.eof()) {
                io_file.clear();
                break;
            }

            if (note_from_temp.get_note_title() == note_from_source.get_note_title() &&
                note_from_temp.get_note_text() == note_from_source.get_note_text() &&
                note_from_temp.get_is_complete() == note_from_source.get_is_complete()) {
                is_in_file = true;
                break;
            }
        }

        io_file.clear();
        if (!is_in_file) {
            io_file.seekp(0, std::ios::end);
            io_file << note_from_source;
        }
    }

    source.close();

    io_file.seekg(0, std::ios::beg);

    std::ofstream target;
    target.open(text);

    while (true) {

        io_file >> note_from_temp;

        if (io_file.eof()) {
            break;
        }

        target << note_from_temp;
    }

    target.close();


    // Binary remove duplicated
    io_file.close();
    io_file.open("un_duplicated.txt", std::ios::in | std::ios::out | std::ios::trunc);
    source.open(binary, std::ios::binary | std::ios::in);

    while (true) {

        note_from_source.read_bin(source);

        if (source.eof()) {
            break;
        }

        io_file.seekg(0, std::ios::beg);
        is_in_file = false;

        while (true) {
            io_file >> note_from_temp;

            if (io_file.eof()) {
                io_file.clear();
                break;
            }

            if (note_from_temp.get_note_title() == note_from_source.get_note_title() &&
                note_from_temp.get_note_text() == note_from_source.get_note_text() &&
                note_from_temp.get_is_complete() == note_from_source.get_is_complete()) {
                is_in_file = true;
                break;
            }
        }

        io_file.clear();
        if (!is_in_file) {
            io_file.seekp(0, std::ios::end);
            io_file << note_from_source;
        }
    }

    target.open(binary, std::ios::trunc | std::ios::in);

    io_file.seekg(0, std::ios::beg);
    while (true) {

        io_file >> note_from_temp;

        if (io_file.eof()) {
            break;
        }

        note_from_temp.write_bin(target);
    }

    target.close();
    io_file.close();

    std::cout << "The process of deleting duplicate notes was successful" << std::endl;
}

void copy_txt(std::ifstream &file, int first_line, int last_line, int position) {

    if (!file.is_open()) {
        file.open(text);
    }

    bool is_copied{};

    std::ofstream to_copy_lines_o;
    to_copy_lines_o.open("to_copy_lines.txt", std::ios::in | std::ios::out | std::ios::trunc);

    Notes temp;
    int counter{};

    while (true) {
        counter++;

        // Copy all notes to to_copy_lines_o file
        if (counter >= first_line && counter <= last_line) {
            temp.read_text(file);
            temp.write_text(to_copy_lines_o);
        } else {
            temp.read_text(file);
        }
        if (file.eof() || counter > last_line) {
            break;
        }
    }

    file.clear();
    file.close();
    file.open(text);

    to_copy_lines_o.close();

    std::ifstream to_copy_lines_i;
    to_copy_lines_i.open("to_copy_lines.txt", std::ios::in | std::ios::out);

    std::ofstream to_copy_file_o;
    to_copy_file_o.open("to_copy_file.txt", std::ios::trunc);

    counter = 0;
    while (true) {

        counter++;
        if (counter == position) {
            while (true) {

                temp.read_text(to_copy_lines_i);

                if (to_copy_lines_i.eof()) {
                    break;
                }

                temp.write_text(to_copy_file_o);
            }
            is_copied = true;
        }

        temp.read_text(file);

        if (file.eof()) {
            break;
        }

        temp.write_text(to_copy_file_o);
    }

    if (!is_copied) {
        std::cout << "No such position! Enter [0 n+1] positions!";\
        file.close();
        return;
    }

    to_copy_lines_o.close();

    std::ifstream to_copy_file_i;
    to_copy_file_i.open("to_copy_file.txt", std::ios::in | std::ios::out);

    std::ofstream target;
    target.open(text);

    while (true) {
        temp.read_text(to_copy_file_i);

        if (to_copy_file_i.eof()) {
            break;
        }

        temp.write_text(target);
    }
    target.close();

    std::cout << "Copying was successful" << std::endl;
    file.close();
}

void copy_bin(std::ifstream &file, int first_line, int last_line, int position) {
    if (!file.is_open()) {
        file.open(binary, std::ios::binary | std::ios::in);
    }


    bool is_copied{};

    std::ofstream to_copy_lines_o;
    to_copy_lines_o.open("to_copy_lines.txt", std::ios::in | std::ios::out | std::ios::trunc);

    Notes temp;
    int counter{};

    while (true) {
        counter++;

        // Copy all notes to to_copy_lines_o file
        if (counter >= first_line && counter <= last_line) {
            temp.read_bin(file);
            temp.write_text(to_copy_lines_o);
        } else {
            temp.read_bin(file);
        }
        if (file.eof() || counter > last_line) {
            break;
        }
    }

    file.clear();
    file.close();
    file.open(binary, std::ios::binary | std::ios::in | std::ios::out);

    to_copy_lines_o.close();

    std::ifstream to_copy_lines_i;
    to_copy_lines_i.open("to_copy_lines.txt", std::ios::in | std::ios::out);

    std::ofstream to_copy_file_o;
    to_copy_file_o.open("to_copy_file.txt", std::ios::trunc);

    counter = 0;
    while (true) {

        counter++;
        if (counter == position) {
            while (true) {

                temp.read_text(to_copy_lines_i);

                if (to_copy_lines_i.eof()) {
                    break;
                }

                temp.write_text(to_copy_file_o);
            }
            is_copied = true;
        }

        temp.read_bin(file);

        if (file.eof()) {
            break;
        }

        temp.write_text(to_copy_file_o);
    }

    if (!is_copied) {
        std::cout << "No such position! Enter [0 n+1] positions!";\
        file.close();
        return;
    }

    to_copy_lines_o.close();

    std::ifstream to_copy_file_i;
    to_copy_file_i.open("to_copy_file.txt", std::ios::in | std::ios::out);

    std::ofstream target;
    target.open(binary, std::ios::in | std::ios::out);

    while (true) {
        temp.read_text(to_copy_file_i);

        if (to_copy_file_i.eof()) {
            break;
        }

        temp.write_bin(target);
    }
    target.close();

    std::cout << "Copying was successful" << std::endl;
    file.close();

}