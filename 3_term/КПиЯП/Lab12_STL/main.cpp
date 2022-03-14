#include "src/menu_functions.h"

int main() {
    std::cout << "Source file: " << source_filename << std::endl;
    std::cout << "Target file: " << target_filename << std::endl << std::endl;

    // Open source file.
    std::ofstream source_o;
    source_o.open(source_filename, std::ios::trunc);
    source_o.close();
    std::ifstream source_i;

    std::ofstream target_o;
    target_o.open(target_filename, std::ios::trunc);
    target_o.close();
    std::ifstream target_i;

    bool is_first = true;

    while (true) {
        switch (get_menu_choice()) {

            case 1: {
                add_new_string(source_o, is_first);
                is_first = false;
                break;
            }

            case 2: {
                show_source(source_i);
                system("pause > 0");
                break;
            }

            case 3: {
                show_target(target_i);
                system("pause > 0");
                break;
            }

            case 4: {
                search_without(source_i);
                system("pause > 0");
                break;
            }

            case 5: {
                search_with(source_i);
                system("pause > 0");
                break;
            }

            case 6:{
                delete_duplicated(source_i);
                system("pause > 0");
                break;
            }

            case 0: {
                exit(EXIT_SUCCESS);
            }

        }
        system("cls");
    }
}

/*
 * Добавление строк в файл.
 * Удаление дубликатов (конкретных строк).
 * Поиск подстроки.
 */