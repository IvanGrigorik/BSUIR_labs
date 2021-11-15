//
// Created by Ivan on 15.11.2021.
//

#ifndef LAB9_FILE_NOTES_NOTES_H
#define LAB9_FILE_NOTES_NOTES_H

#include <iostream>


class Notes {
private:
    std::string note_name{};
    std::string note_text{};
    bool is_complete{};

public:
    // Constructor and destructor
    Notes() = default;

    Notes(const std::string& new_note_name, const std::string& new_note_text, bool new_is_complete);

    ~Notes() = default;


    // Getters and setters
    const std::string &get_note_name() const;

    void set_note_name(const std::string &new_note_name);

    const std::string &get_note_text() const;

    void set_note_text(const std::string &new_note_text);

    bool get_is_complete() const;

    void set_is_complete(bool new_is_complete);


};


#endif //LAB9_FILE_NOTES_NOTES_H
