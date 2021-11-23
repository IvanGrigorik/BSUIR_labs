#include "src/menu_functions.h"


int main() {

    std::ofstream target;
    std::ifstream source;
    new_files(target);


    while (true) {
        try {
            switch (get_menu_choice()) {

                case 1: {
                    target.open(text, std::ios::app);
                    add_file(target, "text");
                    target.close();
                    break;
                }

                case 2: {
                    target.open(binary, std::ios::binary | std::ios::app | std::ios::in);
                    add_file(target, "binary");
                    target.close();
                    break;
                }

                case 3: {
                    std::cout << std::endl << "File content: " << std::endl;
                    print_text(source);
                    system("pause > 0");
                    source.close();
                    break;
                }

                case 4: {
                    std::cout << std::endl << "File content: " << std::endl;
                    print_binary(source);
                    system("pause > 0");
                    source.close();
                    break;
                }

                case 5: {
                    std::cout << std::endl << "File content: " << std::endl;
                    reverse_print_text(source);
                    system("pause > 0");
                    source.close();
                    break;
                }

                case 6: {
                    std::cout << std::endl << "File content: " << std::endl;
                    reverse_print_binary(source);
                    system("pause > 0");
                    source.close();
                    break;
                }
                case 7: {
                    search_file(source, "text");
                    system("pause > 0");
                    break;
                }

                case 8: {
                    search_file(source, "binary");
                    system("pause > 0");
                    break;
                }

                case 9: {
                    delete_file_func(source, "text");
                    system("pause > 0");
                    break;
                }

                case 10: {
                    delete_file_func(source, "binary");
                    system("pause > 0");
                    break;
                }

                case 11: {
                    delete_duplicated();
                    system("pause > 0");
                    break;
                }

                case 12: {
                    copy_strings_txt(source);
                    system("pause > 0");
                    break;
                }

                case 13:{
                    copy_strings_bin(source);
                    system("pause > 0");
                    break;
                }

                case 0:
                    exit(EXIT_SUCCESS);
            }
        } catch (std::exception &ex) {
            std::cout << "Ex: " << ex.what();
            system("pause > 0");
        }
    }
}

/*
 * Ввод с клавиатуры.
 *
 * Без использования доп. памяти в любых вариантах (без массивов)).
 *
 * Удаление дубликатов по обоим файлам.
 *
 * Копирование множества (5 строк, выбирается 2, 3 строка для копирования в положение 1 и будет 2, 3, 1, 2, 3, 4, 5) (можно поставить как в начало, так и в конец (и вообще в любую точку))
 */