//
// Created by Ivan on 15.11.2021.
//

#include "notes.h"



// Setters and getters
const std::string &Notes::get_note_name() const {
    return note_name;
}

void Notes::set_note_name(const std::string &new_note_name) {
    this->note_name = new_note_name;
}

const std::string &Notes::get_note_text() const {
    return note_text;
}

void Notes::set_note_text(const std::string &new_note_text) {
    this->note_text = new_note_text;
}

bool Notes::get_is_complete() const {
    return is_complete;
}

void Notes::set_is_complete(bool new_is_complete) {
    Notes::is_complete = new_is_complete;
}

Notes::Notes(const std::string &new_note_name, const std::string &new_note_text, bool new_is_complete) {
    set_note_name(new_note_name);
    set_note_text(new_note_text);
    set_is_complete(new_is_complete);
}
