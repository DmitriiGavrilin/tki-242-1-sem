#include "Lecturer.h"
#include "Engineer.h"
#include "Department.h"
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace miit::domain;

template<typename T>
T readNumber(const char* prompt) {
    for (;;) {
        std::cout << prompt;
        T value{};
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        if (std::cin.eof()) throw std::runtime_error("Input ended");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid value. Try again.\n";
    }
}

std::string readText(const char* prompt) {
    std::cout << prompt;
    std::string value;
    if (!std::getline(std::cin, value)) throw std::runtime_error("Input ended");
    return value;
}

void printRecord(const std::shared_ptr<DepartmentWorker>& item) {
    if (item) std::cout << item->info() << '\n'; else std::cout << "Not found\n";
}

void printRecords(const std::vector<std::shared_ptr<DepartmentWorker>>& items) {
    if (items.empty()) std::cout << "No records\n";
    for (const auto& item : items) printRecord(item);
}

void printStrings(const std::vector<std::string>& values) {
    if (values.empty()) std::cout << "No values\n";
    for (const auto& value : values) std::cout << value << '\n';
}

void printMap(const std::map<std::string, double>& values) {
    if (values.empty()) std::cout << "No values\n";
    for (const auto& entry : values) std::cout << entry.first << ": " << entry.second << '\n';
}

int main() {
    try {
        std::vector<std::shared_ptr<DepartmentWorker>> collection{std::make_shared<Lecturer>(1, "Prof Smirnov", "lecturer", "Software Dept", "reference-a", "location A", std::vector<std::string>{"common", "research"}, 100.0, 10, 10, true, "primary record"), std::make_shared<Engineer>(2, "Alex Morozov", "engineer", "Lab", "reference-b", "location B", std::vector<std::string>{"common", "secondary"}, 60.0, 5, 20, false, "secondary record"), std::make_shared<Lecturer>(3, "Prof Smirnov", "lecturer", "Software Dept", "reference-a", "location A", std::vector<std::string>{"common", "research", "repeat"}, 100.0, 3, 15, true, "repeated match")};
        Department manager;
        std::cout << "Кафедра\nInitial polymorphic collection:\n";
        for (const auto& item : collection) { manager.add(item); std::cout << item->info() << '\n'; }
        for (;;) {
            std::cout << "\n0 - exit\n1 - all records\n2 - find by name\n3 - find by tag\n";
            std::cout << "4 - allWorkers: Выдавать сведения о работниках кафедры.\n";
            std::cout << "5 - researchProjects: Выдавать информацию о НИР.\n";
            std::cout << "6 - lecturerForClass: Находить преподавателя по дисциплине и виду занятий.\n";
            std::cout << "7 - classTypesBySubject: Выдавать виды занятий выбранной дисциплины.\n";
            const int action = readNumber<int>("Action: ");
            if (action == 0) break;
            try {
                switch (action) {
                case 1: printRecords(manager.items()); break;
                case 2: printRecords(manager.findByName(readText("Name: "))); break;
                case 3: printRecords(manager.findByTag(readText("Tag: "))); break;
                case 4: printRecords(manager.allWorkers()); break;
            case 5: printRecords(manager.researchProjects(readText("Search value: "))); break;
            case 6: { const std::string category = readText("Category: "); const std::string tag = readText("Tag: "); printRecords(manager.lecturerForClass(category, tag)); } break;
            case 7: printStrings(manager.classTypesBySubject(readText("Name: "))); break;
                default: std::cout << "Unknown action\n"; break;
                }
            } catch (const std::exception& error) {
                std::cout << "Operation error: " << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
