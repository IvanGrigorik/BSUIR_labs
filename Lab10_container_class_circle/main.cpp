#include "src/menu_functions.h"


int main() {

    Ring<std::string> s_ring;

    std::vector<Ring<std::string> > s_ring_vec;


    while (true) {
        try {
            switch (get_menu_choice()) {

                case 1: {
                    add_element(s_ring_vec);
                    break;
                }

                case 2: {
                    rings_show(s_ring_vec);
                    system("pause > 0");
                    break;
                }

                case 3: {
                    rings_search(s_ring_vec);
                    system("pause > 0");
                    break;
                }

                case 4: {
                    rings_delete(s_ring_vec);
                    system("pause > 0");
                    break;
                }

                case 5: {
                    rings_compare(s_ring_vec);
                    system("pause > 0");
                    break;
                }

                case 6:{
                    delete_duplicated(s_ring_vec);
                    system("pause > 0");
                    break;
                }
                case 0:
                    exit(EXIT_SUCCESS);
            }
        } catch (std::exception &ex) {
            std::cout << std::endl << "Error: " << ex.what() << std::endl;
            system("pause > 0");
        }

        system("cls");
    }
}

/*
 * Ввод с клавиатуры.
 * Может быть несколько колец (вводится с клавиатуры).
 *
 * Сравниваю кольца (вывод большего или меньшего).
 *
 * Найти наибольшее кольцо, найти наименьшее кольцо.
 * Удаление дубликатов (Если два полностью совпадающих кольца - то удаляю).
 */