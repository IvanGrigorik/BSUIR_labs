#include "src/menu_functions.h"


int main() {

    std::ofstream target;
    std::ifstream source;
    new_files(target);

    while (true) {
        switch (get_menu_choice()) {

            case 1: {
                target.open(text, std::ios::app);
                add_file(target, "text");
                target.close();
                break;
            }

            case 2: {
                target.open(binary, std::ios::app | std::ios::in);
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


            case 0:
                exit(EXIT_SUCCESS);
        }

    }

//
//    Notes note1("Remind1", "remind1", false);
//    Notes note2("Remind2", "remind2", true);
//    Notes note3("Remind3", "remind3", true);
//    Notes note4("Remind4", "remind4", false);
//
//    target.open(text, std::ios::app);
//    std::cout << "Enter info into .txt file..." << std::endl;
//    note1.write_text(target);
//    note2.write_text(target);
//    note3.write_text(target);
//    note4.write_text(target);
//    target.close();
//    system("pause > 0");
//
//    std::cout << std::endl << "Enter info into .bin file..." << std::endl;
//    target.open(binary, std::ios::app | std::ios::in);
//    note1.write_bin(target);
//    note2.write_bin(target);
//    note3.write_bin(target);
//    target.close();
//    system("pause > 0");
//
//    std::cout << std::endl << ".txt file content: " << std::endl;
//    print_text(source);
//    system("pause > 0");
//
//    std::cout << std::endl << ".bin file content: " << std::endl;
//    print_binary(source);
//    system("pause > 0");
//
//    std::cout << std::endl << "Reverse output .txt file: " << std::endl;
//    reverse_print_text(source);
//    system("pause > 0");
//
//    std::cout << std::endl << "Reverse output .bin file" << std::endl;
//    reverse_print_binary(source);
//    system("pause > 0");
//
//    std::cout << std::endl << "Search \"remind1\" in .txt file: " << std::endl;
//    file_searching("text", source, "remind1", 2);
//    system("pause > 0");
//
//    std::cout << std::endl << "Search \"remind3\" in .bin file: " << std::endl;
//    file_searching("binary", source, "remind3", 2);
//    system("pause > 0");
//
//    std::cout << std::endl << "Delete \"remind2\" from .txt file: " << std::endl;
//    file_delete("text", source, "remind2", 2);
//    system("pause > 0");
//
//    std::cout << std::endl << "Delete \"remind1\" from .bin file: " << std::endl;
//    file_delete("binary", source, "remind1", 2);
//    system("pause > 0");
//
//    std::cout << std::endl << ".txt file content: " << std::endl;
//    print_text(source);
//
//    system("pause > 0");
//
//    std::cout << std::endl << ".bin file content: " << std::endl;
//    print_binary(source);
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