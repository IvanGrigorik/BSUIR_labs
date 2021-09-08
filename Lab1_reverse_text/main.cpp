#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void reverse_string();

int main() {
    reverse_string();
    return 0;
}

/*  Вопрос: Вводим цифры или буквы
 * В зависимости от выбора пользователя защита на ввод цифр/букв
 *
 * Вопрос: в каком варианте выводить
 */

// Function to get new string
bool get_string(char *string, int string_size)
{
    char c;
    int i;
    // Cycle to get new symbol in string
    for(i = 0; i < string_size; i++) {
        cin.unsetf(ios::skipws);
        cin >> c;
        // If enter symbols/numbers
        if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '\n' && c != ' '){
            cerr << "Enter only letters of english alphabet: " << endl;
            cin.ignore(100, '\n');
            return false;
        }
        if (c == '\n') {
            string[i] = '\0';
            break;
        }
        string[i] = c;
    }
    //
    if(i >= string_size && cin.peek()){
        cerr << "Enter no longer than 80 symbols: " << endl;
        cin.ignore(100, '\n');
        return false;
    }
    return true;
}
bool get_digits(char *string, int number_size){
    char c;
    int i;
    // Cycle to get new symbol in string
    for(i = 0; i < number_size; i++) {
        cin.unsetf(ios::skipws);
        cin >> c;
        // If enter symbols/numbers
        if((c < '0' || c > '9') && c != '\n' && c != ' '){
            cerr << "Enter number's: " << endl;
            cin.ignore(100, '\n');
            return false;
        }
        if (c == '\n') {
            string[i] = '\0';
            break;
        }
        string[i] = c;
    }
    if(i >= number_size && cin.peek()){
        cerr << "Enter no longer than 80 symbols: " << endl;
        cin.ignore(100, '\n');
        return false;
    }
    return true;
}
void reverse(char str[]){
    unsigned int size = strlen(str);
    char temp;
    for(int i = 0; i < size/2; i++)
    {
        temp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = temp;
    }
}
void reverse_string(){
    const int MAX_SIZE = 80;
    char *str_to_reverse;
    int choose;

    str_to_reverse = (char*)malloc((MAX_SIZE + 1) * sizeof(char));
    assert(str_to_reverse && "Memory allocation error!");

    while(true) {
        system("cls");
        cout << "Choose what you what to enter: " <<
             endl << "1) Letters" <<
             endl << "2) Numbers" <<
             endl << "0) Exit" << endl << ">>";
        cin >> choose;
        cin.ignore(1, '\n');
        system("cls");
        switch (choose) {
            case 1: {
                do {
                    cout << "Enter string to reverse, no longer than 80 symbols: ";
                } while (!get_string(str_to_reverse, MAX_SIZE));
                break;
            }
            case 2: {
                do {
                    cout << "Enter string to reverse, no longer than 80 symbols: ";
                } while (!get_digits(str_to_reverse, MAX_SIZE));
                break;
            }
            case 0: {
                system("pause > 0");
                return;
            }
            default: {
                cout << "Invalid input, try again!";
                cin >> choose;
                break;
            }
        }


        bool reverse_flag = false;

        while(true) {
            system("cls");
            cout << endl << "Enter hat format you want to output" <<
                 endl << "1) Reversed" <<
                 endl << "2) Non-reversed" <<
                 endl << "0) Exit" << endl << ">> ";
            cin >> choose;
            cin.ignore(1, '\n');

            switch (choose) {
                case 1: {
                    if(!reverse_flag)
                        reverse(str_to_reverse);
                    cout << str_to_reverse;
                    system("pause > 0");
                    reverse_flag = true;
                    break;
                }
                case 2: {
                    if (reverse_flag)
                        reverse(str_to_reverse);
                    cout << str_to_reverse;
                    system("pause > 0");
                    reverse_flag = false;
                    break;
                }
                case 0: {
                    system("pause > 0");
                    return;
                }
                default: {
                    cout << "Invalid input, try again!";
                    cin >> choose;
                    break;
                }
            }
        }
    }
}

