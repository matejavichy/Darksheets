#include "Application.h"

void Application::run() {
    bool isRunning = true;
    string newID;
    string newValue;
    int test;
    while (isRunning){
        table.printTable();
        char userInput;
        menuPrint();
        std::cout << "Enter input: ";
        std::cin >> userInput;
        std::getline(std::cin,newID);
        switch (userInput) {
            case 'A':
            case 'a':
                std::cout << "Enter cell Identification (ID): ";
                std::getline(std::cin, newID);
                std::cout << "Enter new value: ";
                std::getline(std::cin, newValue);
                action.doIt(table);
                test = table.addValue(newID,newValue);
                if (!test) action.undoIt();
                break;
            case 'F':
            case 'f':
                try{
                    std::cout << "Enter cell Identification (ID): ";
                    std::getline(std::cin, newID);
                    std::cout << "Enter new format: ";
                    std::cout << "1 - Text";
                    std::cout << "2 - Number";
                    std::cout << "3 - Date";
                    std::cin >> test;
                    action.doIt(table);
                    if (test == 1){
                        auto *textformat = new TextFormat();
                        table.setFormat(newID,textformat);
                    }
                    else if (test == 2) {
                        auto *numberformat = new NumberFormat();
                        table.setFormat(newID, numberformat);
                    }
                    else {
                        auto *dateformat = new DateFormat();
                        table.setFormat(newID, dateformat);
                    }
                }
                catch (std::exception &e){
                    std::cout << e.what() << std::endl;
                }
                break;
            case 'X':
            case 'x':
                try{
                    std::cout << "Enter cell Identification (ID): ";
                    std::getline(std::cin, newID);
                    action.doIt(table);
                    table.clearValue(newID);
                }
                catch (std::exception &e){
                    std::cout << e.what() << std::endl;
                }
                break;
                break;
            case 'U':
            case 'u':
                std::cout << "Aktiviran je U" << std::endl;
                try{
                    table = action.undo(table);
                }
                catch (std::exception &e){
                    std::cout << e.what() << std::endl;
                }
                break;
            case 'R':
            case 'r':
                std::cout << "Aktiviran je R" << std::endl;
                try{
                    action.doIt(table);
                    table = action.redo();
                }
                catch (std::exception &e){
                    std::cout << e.what() << std::endl;
                }
                break;
            case 'Q':
            case 'q':
                std::cout << "Aktiviran je Q";
                table.saveTableDataToJson("src/jason.json");
                table.saveTableDataToCSV("src/tablic.csv");
                isRunning = false;
                break;
            default:
                break;
        }
    }
}

void Application::load() {
    bool isRunning = true;
    int userInput;
    while (isRunning){
        std::cout << "0 -> load from CSV. file" << std::endl;
        std::cout << "1 -> load from JSON. file" << std::endl;
        std::cout << "Enter input: ";
        std::cin >> userInput;
        try{
            string fileName;
            std::cout << "Enter input: ";
            std::cin >> fileName;
            if (userInput) table.loadTableJSON(fileName);
            else table.loadTableCSV(fileName);
            isRunning = false;
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void Application::menuPrint() {
    std::cout << "User Controls" << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << "A -> add/change a value from the worksheet" << std::endl;
    std::cout << "X -> remove value from worksheet" << std::endl;
    std::cout << "F -> change format of a Cell" << std::endl;
    std::cout << "U -> undo last control" << std::endl;
    std::cout << "R -> redo last control" << std::endl;
    std::cout << "Q -> exit application" << std::endl;
}

