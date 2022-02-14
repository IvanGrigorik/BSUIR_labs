/*
 * Created by Ivan on 24.11.2021.
 * BSUiR, 2021
 */

#pragma once

#include "Ring.h"

int get_menu_choice();

int get_int(int min_size, int max_size);

void add_element(std::vector<Ring<std::string> > &s_ring_vec);

void add_exist(std::vector<Ring<std::string> > &s_ring_vec);

void rings_show(std::vector<Ring<std::string> > &s_ring_vec);

void rings_search(std::vector<Ring<std::string> > &s_ring_vec);

void rings_delete(std::vector<Ring<std::string> > &s_ring_vec);

void rings_compare(std::vector<Ring<std::string> > &s_ring_vec);

void delete_ring(std::vector<Ring<std::string> > &s_ring_vec, int ring_number);

template<class T>
int compare_elements(Ring<T> ring_1_to_compare, Ring<T> ring_2_to_compare);

void delete_duplicated(std::vector<Ring<std::string> > &s_ring_vec);