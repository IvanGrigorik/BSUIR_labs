//
// Created by Ivan on 15.11.2021.
//

#pragma once

#include <iostream>
#include <fstream>
#include <ostream>

class Notes {
private:
    std::string note_title{};
    std::string note_text{};
    bool is_complete{};


public:
    // Constructor and destructor
    Notes() = default;

    Notes(const std::string &new_note_name, const std::string &new_note_text, bool new_is_complete);

    ~Notes() = default;


    // Getters and setters
    void set_note_title(const std::string &new_note_title);

    const std::string &get_note_title() const;

    void set_note_text(const std::string &new_note_text);

    const std::string &get_note_text() const;

    void set_is_complete(bool new_is_complete);

    bool get_is_complete() const;

    // Overloading ostream/istream operators
    friend std::ostream &operator<<(std::ostream &os, const Notes &notes);

    friend std::istream &operator>>(std::istream &is, Notes &notes);


    // Functions to read and write to text file
    void write_text(std::ofstream &file) const;

    void read_text(std::ifstream &file);


    // Functions to read and write to binary file
    void write_bin(std::ofstream &file);

    void read_bin(std::ifstream &file);
};
