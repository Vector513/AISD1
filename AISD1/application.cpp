#include "application.h"
#include <limits>
#include <sstream>

// Application::Application() � ������ ������
Application::Application() : list(), array(), stack(), station() {}

Application::~Application() {}

bool Application::getValidInput(number& value) 
{
    std::cin >> value;
    if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear(); // ����� ��������� ������
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������������� �����
        std::cout << "������������ ����! ���������� �����.\n";
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������� ���������� ��������
    return true;
}

bool Application::getValidInput(size_t& value) 
{
    std::cin >> value;
    if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear(); // ����� ��������� ������
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������������� �����
        std::cout << "������������ ����! ���������� �����.\n";
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������� ���������� ��������
    return true;
}

bool Application::getValidInputWithIndex(number& n, size_t& i) 
{
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    if (!(iss >> n >> i) || !iss.eof()) {
        std::cout << "������������ ����! ���������� �����.\n";
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
        std::cout << "������������ ����! ���������� �����.\n";
        return false;
    }
    return true;
}

void Application::run()
{
    const char separator[] = "------------------------------------------------------------------------------------------------------------------------";
    const char commands[] = 
        "1) ����������� ������\n"
        "2) ������������ ������\n"
        "3) ����\n"
        "4) ������������� �������\n"
        "c) ������� ������ ������\n"
        "e) ����� �� ���������\n";

    std::string command = "c";

    do {
        if (command == "e") {
            std::cout << "��������� ���� ��������� �� ���� ������������\n";
            break;
        }
        
        else if (command == "c") {
            std::cout << commands;
        }

        // ������� ��� ����������� ����� ����� � ���������� ������ �����

        else if (command == "1") {
            const char listCommands[] =
                "1) �������� ������� � ������\n"
                "2) �������� ������� � �����\n"
                "3) �������� ������� �� �������\n"
                "4) ������� ������ �������\n"
                "5) ������� ��������� �������\n"
                "6) ������� ������� �� �������\n"
                "7) �������� �������� ������� �� ��������\n"
                "8) �������� �������� �������� ������ � ��������\n"
                "9) �������� �� �������\n"
                "d) �������� ������\n"
                "s) ������� ������\n"
                "c) ������� ������ ������\n"
                "<) �������� � ������� ����\n";

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
                        std::cout << "�������� ������: ";
                        list.print_forward(std::cout);
                    }
                    else {
                        std::cout << "������ ������\n";
                    }
                }

                else if (command == "d") {
                    list.clear();
                    std::cout << "������ ��� ������� ������\n";
                }

                else if (command == "1") {
                    std::cout << "������� �������: ";
                    number n;
                    if (getValidInput(n)) {
                        list.push_front(n);
                        std::cout << "������� " << n << " ��� �������� � ������ ������\n";
                    }
                }

                else if (command == "2") {
                    std::cout << "������� �������: ";
                    number n;
                    if (getValidInput(n)) {
                        list.push_back(n);
                        std::cout << "������� " << n << " ��� �������� � ����� ������\n";
                    }
                }

                else if (command == "3") {
                    std::cout << "������� ������� � ������ ����� ������: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            list.insert(i, n);
                            std::cout << "������� " << n << " ��� �������� �� ������� � �������� " << i << " \n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "4") {
                    try {
                        list.pop_front();
                        std::cout << "������ ������� ��� ������� �����\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "������: " << ex.what() << '\n';
                    }
                }

                else if (command == "5") {
                    try {
                        list.pop_back();
                        std::cout << "��������� ������� ��� ������� �����\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "������: " << ex.what() << '\n';
                    }
                }

                else if (command == "6") {
                    std::cout << "������� ������ ��������: ";
                    size_t i;
                    if (getValidInput(i)) {
                        try {
                            list.erase(i);
                            std::cout << "������� � �������� " << i << " ��� ����� �� ������\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }
                
                else if (command == "7") {
                    std::cout << "������� ������� ��������� ����� ������: ";
                    size_t i1, i2;
                    if (getValidInputWithIndex(i1, i2)) {
                        try {
                            std::swap(list[i1], list[i2]);
                            std::cout << "�������� � ��������� " << i1 << " � " << i2 << " ���� �������� �������\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }
                
                else if (command == "8") {
                    std::cout << "������� ����� ������� � ������ ����� ������: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            list[i] = n;
                            std::cout << "�������� �������� � �������� " << i << " ���� �������� �� " << n << '\n';
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "9") {
                    if (list.empty()) {
                        std::cout << "������ ������\n";
                    }
                    else {
                        std::cout << "������ �� ������\n";
                    }
                }

                else {
                    std::cout << "������������ �������. ���������� �����.\n";
                }

                std::cout << separator << '\n';
                std::cout << "������� �������: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "������������ ����! ���������� �����.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
        }

        else if (command == "2") {
            const char arrayCommands[] =
                "1) �������� ������� � ������\n"
                "2) �������� ������� � �����\n"
                "3) �������� ������� �� �������\n"
                "4) ������� ������ �������\n"
                "5) ������� ��������� �������\n"
                "6) ������� ������� �� �������\n"
                "7) �������� �������� ������� �� ��������\n"
                "8) �������� �������� �������� ������� � ��������\n"
                "9) �������� �� �������\n"
                "i) ������� capacity � size �������\n"
                "d) �������� ������\n"
                "s) ������� ������\n"
                "c) ������� ������ ������\n"
                "<) ��������� � ������� ����\n";

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
                        std::cout << "�������� �������: ";
                        array.print(std::cout);
                    }
                    else {
                        std::cout << "������ ������\n";
                    }
                }

                else if (command == "d") {
                    array.clear();
                    std::cout << "������ ��� ������� ������\n";
                }

                else if (command == "i") {
                    std::cout << "Capacity � Size �������: " << array.getCapacity() << " � " << array.getSize() << '\n';
                }

                else if (command == "1") {
                    std::cout << "������� �������: ";
                    number n;
                    if (getValidInput(n)) {
                        array.insert(0, n);
                        std::cout << "������� " << n << " ��� �������� � ������ �������\n";
                    }
                }

                else if (command == "2") {
                    std::cout << "������� �������: ";
                    number n;
                    if (getValidInput(n)) {
                        array.push_back(n);
                        std::cout << "������� " << n << " ��� �������� � ����� �������\n";
                    }
                }

                else if (command == "3") {
                    std::cout << "������� ������� � ������ ����� ������: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            array.insert(i, n);
                            std::cout << "������� " << n << " ��� �������� �� ������� � �������� " << i << " \n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "4") {
                    try {
                        array.erase(0);
                        std::cout << "������ ������� ��� ������� �����\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "������: " << ex.what() << '\n';
                    }
                }

                else if (command == "5") {
                    try {
                        array.pop_back();
                        std::cout << "��������� ������� ��� ������� �����\n";
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "������: " << ex.what() << '\n';
                    }
                }

                else if (command == "6") {
                    std::cout << "������� ������ ��������: ";
                    size_t i;
                    if (getValidInput(i)) {
                        try {
                            array.erase(i);
                            std::cout << "������� � �������� " << i << " ��� ����� �� �������\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "7") {
                    std::cout << "������� ������� ��������� ����� ������: ";
                    size_t i1, i2;
                    if (getValidInputWithIndex(i1, i2)) {
                        try {
                            std::swap(array[i1], array[i2]);
                            std::cout << "�������� � ��������� " << i1 << " � " << i2 << " ���� �������� �������\n";
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "8") {
                    std::cout << "������� ����� ������� � ������ ����� ������: ";
                    number n;
                    size_t i;
                    if (getValidInputWithIndex(n, i)) {
                        try {
                            array[i] = n;
                            std::cout << "�������� �������� � �������� " << i << " ���� �������� �� " << n << '\n';
                        }
                        catch (std::out_of_range& ex) {
                            std::cout << "������: " << ex.what() << '\n';
                        }
                    }
                }

                else if (command == "9") {
                    if (array.empty()) {
                        std::cout << "������ ������\n";
                    }
                    else {
                        std::cout << "������ �� ������\n";
                    }
                }

                else {
                    std::cout << "������������ �������. ���������� �����.\n";
                }

                std::cout << separator << '\n';
                std::cout << "������� �������: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear(); // ���������� ��������� ������
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "������������ ����! ���������� �����.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
            }

        else if (command == "3") {
            const char stackCommands[] =
                "1) �������� ������� � ����\n"
                "2) ������� ������� ������� �����\n"
                "3) ������� ������� ������� �����\n"
                "4) ������� ������ �����\n"
                "5) �������� �� ������� �����\n"
                "d) �������� ����\n"
                "s) ������� ����\n"
                "c) ������� ������ ������\n"
                "<) ��������� � ������� ����\n";

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
                        std::cout << "�������� ����� �� ��������: ";
                        stack.print(std::cout);
                    }
                    else {
                        std::cout << "���� ������\n";
                    }
                }

                else if (command == "d") {
                    stack.clear();
                    std::cout << "���� ��� ������� ������\n";
                }

                else if (command == "1") {
                    std::cout << "������� �������: ";
                    number n;
                    if (getValidInput(n)) {
                        stack.push(n);
                        std::cout << "������� " << n << " ��� �������� �� �������� �����\n";
                    }
                }

                else if (command == "2") {
                    if (!stack.empty()) {
                        stack.pop();
                        std::cout << "������� ������� ����� ��� �����\n";
                    }
                    else {
                        std::cout << "���� ������\n";
                    }
                }

                else if (command == "3") {
                    try {
                        std::cout << "������� ������� �����: " << stack.top() << '\n';
                    }
                    catch (std::out_of_range& ex) {
                        std::cout << "������: " << ex.what() << '\n';
                    }
                }

                else if (command == "4") {
                    std::cout << "������ �����: " << stack.getSize() << '\n';
                }

                else if (command == "5") {
                    if (stack.empty()) {
                        std::cout << "���� ������\n";
                    }
                    else {
                        std::cout << "���� �� ������\n";
                    }
                }

                else {
                    std::cout << "������������ �������. ���������� �����.\n";
                }

                std::cout << separator << '\n';
                std::cout << "������� �������: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear(); // ���������� ��������� ������
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "������������ ����! ���������� �����.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
        }

        else if (command == "4") {
            // 83 + 4 * (91 - (16 / 2 + 13 * 5)) - (88 / 11) * (52 - 7 * 3)
            const char stationCommands[] = 
                "1) ���� ��������� � ��������� �����\n"
                "2) ���� ��������� � ����������� �����\n"
                "3) ������������� �� ��������� � �����������\n"
                "4) ������������� �� ����������� � ���������\n"
                "5) ����� ��������� � ��������� �����\n"
                "6) ����� ��������� � ����������� �����\n"
                "7) ��������� �������� ��������� � ����������� �����\n"
                "d) �������� ���������\n"
                "c) ������� ������ ������\n"
                "<) �������� � ������� ����\n";

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
                    std::cout << "������� ��������� � ��� �����: ";
                    std::string input;
                    std::getline(std::cin, input);
                    if (station.tokenize(input)) {
                        std::cout << "��������� ���� ������� ����������\n";
                    }
                }
                else if (command == "2") {
                    std::cout << "������� ��������� � ���� �����: ";
                    std::string input;
                    std::getline(std::cin, input);
                    if (station.tokenize(input, false)) {
                        std::cout << "��������� ���� ������� ����������\n";
                    }
                }

                else if (command == "3") {
                    try {
                        station.infToPost();
                        std::cout << "��������� ���� ������� ������������� � ����������� ������\n";
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "������ ����������: " << e.what() << std::endl;
                    }
                }

                else if (command == "4") {
                    try {
                        station.postToInf();
                        std::cout << "��������� ���� ������� ������������� � ��������� ������\n";
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "������ ����������: " << e.what() << std::endl;
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
                        std::cout << "��������� ��������� ��� ������� ���������\n���������: " << station.evaluatePost() << '\n';
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "������ ����������: " << e.what() << std::endl;
                    }
                }

                else {
                    std::cout << "������������ �������. ���������� �����.\n";
                }

                std::cout << separator << '\n';
                std::cout << "������� �������: ";
                std::getline(std::cin, command);

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "������������ ����! ���������� �����.\n";
                    command = "c";
                }

                std::cout << '\n';

            } while (true);
        }

        else {
            std::cout << "������������ �������. ���������� �����.\n";
        }

        std::cout << separator << '\n';
        std::cout << "������� �������: ";
        std::getline(std::cin, command);

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������������ ����! ���������� �����.\n";
            command = "c";
        }

        std::cout << '\n';

    } while (true);
}