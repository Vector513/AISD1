#include "application.h"
#include <limits>
#include <sstream>

// Application::Application() и другие методы
Application::Application() : list(), array(), stack(), station() {}

Application::~Application() {}

bool Application::getValidInput(number& value) 
{
    std::cin >> value;
    if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear(); // Сброс состояния потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропуск неправильного ввода
        std::cout << "Некорректный ввод! Попробуйте снова.\n";
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Удаление оставшихся символов
    return true;
}

bool Application::getValidInput(size_t& value) 
{
    std::cin >> value;
    if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear(); // Сброс состояния потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропуск неправильного ввода
        std::cout << "Некорректный ввод! Попробуйте снова.\n";
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Удаление оставшихся символов
    return true;
}

bool Application::getValidInputWithIndex(number& n, size_t& i) 
{
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    if (!(iss >> n >> i) || !iss.eof()) {
        std::cout << "Некорректный ввод! Попробуйте снова.\n";
        return false;
    }
    return true;
}

bool Application::getValidInputWithIndex(size_t& i1, size_t& i2)
{
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    if (!(iss >> i1 >> i2) || !iss.eof()) {
        std::cout << "Некорректный ввод! Попробуйте снова.\n";
        return false;
    }
    return true;
}

void Application::run()
{
    const char separator[] = "------------------------------------------------------------------------------------------------------------------------";
    const char commands[] = 
        "1) Двухсвязный список\n"
        "2) Динамический массив\n"
        "3) Стек\n"
        "4) Сортировочная станция\n"
        "c) Вывести список команд\n"
        "e) Выход из программы\n";

    std::string command = "c";

    do {
        if (command == "e") {
            std::cout << "Программа была завершена по воле пользователя\n";
            break;
        }
        
        else if (command == "c") {
            std::cout << commands;
        }

        // Функция для безопасного ввода чисел с обработкой ошибок ввода

        else if (command == "1") {
            const char listCommands[] =
                "1) Вставить элемент в начало\n"
                "2) Вставить элемент в конец\n"
                "3) Вставить элемент по индексу\n"
                "4) Удалить первый элемент\n"
                "5) Удалить последний элемент\n"
                "6) Удалить элемент по индексу\n"
                "7) Поменять элементы местами по индексам\n"
                "8) Поменять значение элемента списка с индексом\n"
                "9) Проверка на пустоту\n"
                "d) Очистить список\n"
                "s) Вывести список\n"
                "c) Вывести список команд\n"
                "<) Вернутся в главное меню\n";

            command = "c";

            do {
                if (command == "c") {
                    std::cout << listCommands;
                }

                else if (command == "<") {
                    std::cout << "\n";
                    break;
                }

                else if (command == "s") {
                    if (!list.empty()) {
                        std::cout << "Элементы списка: ";
                        list.print_forward(std::cout);
                    }
                    else {
                        std::cout << "Список пустой\n";
                    }
                }

                else if (command == "d") {
                    list.clear();
                    std::cout << "Список был успешно очищен\n";
                }

                else if (command == "1") {
                    std::cout << "Введите элемент: ";
                    number n;
                    if (getValidInput(n)) {
                        list.push_front(n);
                        std::cout << "Элемент " << n << " был добавлен в начало списка\n";
                    }
                }

                else if (command == "2") {
                    std::cout << "Введите элемент: ";
                    number n;
                    if (getValidInput(n)) {
                        list.push_back(n);
                        std::cout << "Элемент " << n << " был добавлен в конец списка\n";
                    }
                }

                else if (command == "3") {
                    std::cout << "Введите элемент и индекс через пробел: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            list.insert(i, n);
                            std::cout << "Элемент " << n << " был добавлен на позицию с индексом " << i << " \n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "4") {
                    try {
                        list.pop_front();
                        std::cout << "Первый элемент был успешно удалён\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "Ошибка: " << ex.what() << '\n';
                    }
                }

                else if (command == "5") {
                    try {
                        list.pop_back();
                        std::cout << "Последний элемент был успешно удалён\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "Ошибка: " << ex.what() << '\n';
                    }
                }

                else if (command == "6") {
                    std::cout << "Введите индекс элемента: ";
                    size_t i;
                    if (getValidInput(i)) {
                        try {
                            list.erase(i);
                            std::cout << "Элемент с индексом " << i << " был удалён из списка\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }
                
                else if (command == "7") {
                    std::cout << "Введите индексы элементов через пробел: ";
                    size_t i1, i2;
                    if (getValidInputWithIndex(i1, i2)) {
                        try {
                            std::swap(list[i1], list[i2]);
                            std::cout << "Элементы с индексами " << i1 << " и " << i2 << " были поменяны местами\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }
                
                else if (command == "8") {
                    std::cout << "Введите новый элемент и индекс через пробел: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            list[i] = n;
                            std::cout << "Значение элемента с индексом " << i << " было изменено на " << n << '\n';
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "9") {
                    if (list.empty()) {
                        std::cout << "Список пустой\n";
                    }
                    else {
                        std::cout << "Список не пустой\n";
                    }
                }

                else {
                    std::cout << "Некорректная команда. Попробуйте снова.\n";
                }

                std::cout << separator << '\n';
                std::cout << "Введите команду: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод! Попробуйте снова.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
        }

        else if (command == "2") {
            const char arrayCommands[] =
                "1) Вставить элемент в начало\n"
                "2) Вставить элемент в конец\n"
                "3) Вставить элемент по индексу\n"
                "4) Удалить первый элемент\n"
                "5) Удалить последний элемент\n"
                "6) Удалить элемент по индексу\n"
                "7) Поменять элементы местами по индексам\n"
                "8) Поменять значение элемента массива с индексом\n"
                "9) Проверка на пустоту\n"
                "i) Вывести capacity и size массива\n"
                "d) Очистить массив\n"
                "s) Вывести массив\n"
                "c) Вывести список команд\n"
                "<) Вернуться в главное меню\n";

            command = "c";

            do {
                if (command == "c") {
                    std::cout << arrayCommands;
                }

                else if (command == "<") {
                    std::cout << "\n";
                    break;
                }

                else if (command == "s") {
                    if (!array.empty()) {
                        std::cout << "Элементы массива: ";
                        array.print(std::cout);
                    }
                    else {
                        std::cout << "Массив пустой\n";
                    }
                }

                else if (command == "d") {
                    array.clear();
                    std::cout << "Массив был успешно очищен\n";
                }

                else if (command == "i") {
                    std::cout << "Capacity и Size массива: " << array.getCapacity() << " и " << array.getSize() << '\n';
                }

                else if (command == "1") {
                    std::cout << "Введите элемент: ";
                    number n;
                    if (getValidInput(n)) {
                        array.insert(0, n);
                        std::cout << "Элемент " << n << " был добавлен в начало массива\n";
                    }
                }

                else if (command == "2") {
                    std::cout << "Введите элемент: ";
                    number n;
                    if (getValidInput(n)) {
                        array.push_back(n);
                        std::cout << "Элемент " << n << " был добавлен в конец массива\n";
                    }
                }

                else if (command == "3") {
                    std::cout << "Введите элемент и индекс через пробел: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            array.insert(i, n);
                            std::cout << "Элемент " << n << " был добавлен на позицию с индексом " << i << " \n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "4") {
                    try {
                        array.erase(0);
                        std::cout << "Первый элемент был успешно удалён\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "Ошибка: " << ex.what() << '\n';
                    }
                }

                else if (command == "5") {
                    try {
                        array.pop_back();
                        std::cout << "Последний элемент был успешно удалён\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "Ошибка: " << ex.what() << '\n';
                    }
                }

                else if (command == "6") {
                    std::cout << "Введите индекс элемента: ";
                    size_t i;
                    if (getValidInput(i)) {
                        try {
                            array.erase(i);
                            std::cout << "Элемент с индексом " << i << " был удалён из массива\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "7") {
                    std::cout << "Введите индексы элементов через пробел: ";
                    size_t i1, i2;
                    if (getValidInputWithIndex(i1, i2)) {
                        try {
                            std::swap(array[i1], array[i2]);
                            std::cout << "Элементы с индексами " << i1 << " и " << i2 << " были поменяны местами\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "8") {
                    std::cout << "Введите новый элемент и индекс через пробел: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            array[i] = n;
                            std::cout << "Значение элемента с индексом " << i << " было изменено на " << n << '\n';
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "Ошибка: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "9") {
                    if (array.empty()) {
                        std::cout << "Массив пустой\n";
                    }
                    else {
                        std::cout << "Массив не пустой\n";
                    }
                }

                else {
                    std::cout << "Некорректная команда. Попробуйте снова.\n";
                }

                std::cout << separator << '\n';
                std::cout << "Введите команду: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear(); // Сбрасываем состояние потока
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод! Попробуйте снова.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
            }

        else if (command == "3") {
            const char stackCommands[] =
                "1) Положить элемент в стек\n"
                "2) Удалить верхний элемент стека\n"
                "3) Вывести верхний элемент стека\n"
                "4) Вывести размер стека\n"
                "5) Проверка на пустоту стека\n"
                "d) Очистить стек\n"
                "s) Вывести стек\n"
                "c) Вывести список команд\n"
                "<) Вернуться в главное меню\n";

            command = "c";

            do {
                if (command == "c") {
                    std::cout << stackCommands;
                }

                else if (command == "<") {
                    std::cout << "\n";
                    break;
                }

                else if (command == "s") {
                    if (!stack.empty()) {
                        std::cout << "Элементы стека от верхушки: ";
                        stack.print(std::cout);
                    }
                    else {
                        std::cout << "Стек пустой\n";
                    }
                }

                else if (command == "d") {
                    stack.clear();
                    std::cout << "Стек был успешно очищен\n";
                }

                else if (command == "1") {
                    std::cout << "Введите элемент: ";
                    number n;
                    if (getValidInput(n)) {
                        stack.push(n);
                        std::cout << "Элемент " << n << " был добавлен на верхушку стека\n";
                    }
                }

                else if (command == "2") {
                    if (!stack.empty()) {
                        stack.pop();
                        std::cout << "Верхний элемент стека был удалён\n";
                    }
                    else {
                        std::cout << "Стек пустой\n";
                    }
                }

                else if (command == "3") {
                    try {
                        std::cout << "Верхний элемент стека: " << stack.top() << '\n';
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "Ошибка: " << ex.what() << '\n';
                    }
                }

                else if (command == "4") {
                    std::cout << "Размер стека: " << stack.getSize() << '\n';
                }

                else if (command == "5") {
                    if (stack.empty()) {
                        std::cout << "Стек пустой\n";
                    }
                    else {
                        std::cout << "Стек не пустой\n";
                    }
                }

                else {
                    std::cout << "Некорректная команда. Попробуйте снова.\n";
                }

                std::cout << separator << '\n';
                std::cout << "Введите команду: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear(); // Сбрасываем состояние потока
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод! Попробуйте снова.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
        }

        else if (command == "4") {
            // 83 + 4 * (91 - (16 / 2 + 13 * 5)) - (88 / 11) * (52 - 7 * 3)
            const char stationCommands[] = 
                "1) Ввод выражения в инфиксной форме\n"
                "2) Ввод выражения в постфиксной форме\n"
                "3) Преобразовать из инфиксной в постфиксную\n"
                "4) Преобразовать из постфиксной в инфиксную\n"
                "5) Вывод выражения в инфиксной форме\n"
                "6) Вывод выражения в постфиксной форме\n"
                "7) Вычислить значение выражения в постфиксной форме\n"
                "d) Очистить выражения\n"
                "c) Вывести список команд\n"
                "<) Вернутся в главное меню\n";

            command = "c";
            
            do {
                if (command == "c") {
                    std::cout << stationCommands;
                }

                else if (command == "d") {
                    station.clear();
                }

                else if (command == "<") {
                    std::cout << "\n";
                    break;
                }

                else if (command == "1") {
                    std::cout << "Введите выражение в инф форме: ";
                    std::string input;
                    std::getline(std::cin, input);
                    if (station.tokenize(input)) {
                        std::cout << "Выражение было успешно обработано\n";
                    }
                }
                else if (command == "2") {
                    std::cout << "Введите выражение в пост форме: ";
                    std::string input;
                    std::getline(std::cin, input);
                    if (station.tokenize(input, false)) {
                        std::cout << "Выражение было успешно обработано\n";
                    }
                }

                else if (command == "3") {
                    try {
                        station.infToPost();
                        std::cout << "Выражение было успешно преобразовано в постфиксную запись\n";
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "Ошибка вычисления: " << e.what() << std::endl;
                    }
                }

                else if (command == "4") {
                    try {
                        station.postToInf();
                        std::cout << "Выражение было успешно преобразовано в инфиксную запись\n";
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "Ошибка вычисления: " << e.what() << std::endl;
                    }
                }

                else if (command == "5") {
                    station.showInf(std::cout);
                }
                else if (command == "6") {
                    station.showPost(std::cout);
                }

                else if (command == "7") {
                    try {
                        std::cout << "Результат выражения был успешно подсчитан\nРезультат: " << station.evaluatePost() << '\n';
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "Ошибка вычисления: " << e.what() << std::endl;
                    }
                }

                else {
                    std::cout << "Некорректная команда. Попробуйте снова.\n";
                }

                std::cout << separator << '\n';
                std::cout << "Введите команду: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод! Попробуйте снова.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
        }

        else {
            std::cout << "Некорректная команда. Попробуйте снова.\n";
        }

        std::cout << separator << '\n';
        std::cout << "Введите команду: ";
        std::getline(std::cin, command);

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова.\n";
            command = "c";
        }

        std::cout << '\n';

    } while (true);
}