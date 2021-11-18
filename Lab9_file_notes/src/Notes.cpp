//
// Created by Ivan on 15.11.2021.
//

#include "Notes.h"

// Setters and getters
Notes::Notes(const std::string &new_note_name, const std::string &new_note_text, bool new_is_complete) {
    set_note_title(new_note_name);
    set_note_text(new_note_text);
    set_is_complete(new_is_complete);
}

void Notes::set_note_title(const std::string &new_note_title) {
    this->note_title = new_note_title;
}

void Notes::set_note_text(const std::string &new_note_text) {
    this->note_text = new_note_text;
}

void Notes::set_is_complete(bool new_is_complete) {
    Notes::is_complete = new_is_complete;
}

std::ostream &operator<<(std::ostream &os, const Notes &notes) {
    os << notes.note_title << ' ' << notes.note_text << ' ' << notes.is_complete << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Notes &notes) {
    is >> notes.note_title >> notes.note_text >> notes.is_complete;
    return is;
}

void Notes::write_text(std::ofstream &file) const {

    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }

    file << *this;
}

void Notes::read_text(std::ifstream &file) {

    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }

    file >> *this;
}

void Notes::write_bin(std::ofstream &file) {
    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }


    try {// Write string sizes, to read string after
        std::size_t note_title_size = note_title.size();
        file.write(reinterpret_cast<char *>(&note_title_size), sizeof(note_title_size));
        file.write(note_title.c_str(), static_cast<std::streamsize>(note_title_size));

        std::size_t note_text_size = note_text.size();
        file.write(reinterpret_cast<char * >(&note_text_size), sizeof(note_title_size));
        file.write(note_text.c_str(), static_cast<std::streamsize>(note_text_size));

        file.write(reinterpret_cast<char *>(&is_complete), sizeof(is_complete));
    } catch (std::ofstream::failure &ex) {
        throw std::runtime_error("Invalid write data type");
    }
}

void Notes::read_bin(std::ifstream &file) {
    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }

    try {
        // Read is_complete status
        std::size_t note_title_size;
        file.read(reinterpret_cast<char * >(&note_title_size), sizeof(note_title_size));

        // Create a new string char* to then assign the value "note_title" its value.
        char *temp = new char[note_title_size + 1];
        file.read(temp, static_cast<std::streamsize>(note_title_size));
        temp[note_title_size] = '\0';
        note_title = temp;

        delete[] temp;


        // Read note_text
        std::size_t note_text_size;
        file.read(reinterpret_cast<char * >(&note_text_size), sizeof(note_text_size));

        // Same situation
        temp = new char[note_text_size + 1];
        file.read(temp, static_cast<std::streamsize>(note_text_size));
        temp[note_text_size] = '\0';
        note_text = temp;

        delete[] temp;

        // Read is_complete status
        file.read(reinterpret_cast<char *>(&is_complete), sizeof(is_complete));
    } catch (std::ifstream::failure &ex) {
        throw std::runtime_error("Invalid read data type");
    }
}

const std::string &Notes::get_note_title() const {
    return note_title;
}

const std::string &Notes::get_note_text() const {
    return note_text;
}

bool Notes::get_is_complete() const {
    return is_complete;
}
