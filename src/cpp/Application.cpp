#include "Application.h"

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


int Application::addValue(){
    string newID;
    string newValue;
    int test;
    std::cout << "Enter cell Identification (ID): ";
    std::getline(std::cin, newID);
    std::cout << "Enter new value: ";
    std::getline(std::cin, newValue);
    test = table.addValue(newID,newValue);
    return test;
}

int Application::changeFormat(){
    int test;
    string newID;
    std::cout << "Enter cell Identification (ID): ";
    std::getline(std::cin, newID);
    std::cout << "Enter new format: ";
    std::cout << "1 - Text";
    std::cout << "2 - Number";
    std::cout << "3 - Date";
    std::cin >> test;
    switch (test)
    {
    case 1:
        auto *textformat = new TextFormat();
        table.setFormat(newID,textformat);
        break;
    case 2:
        auto *numberformat = new NumberFormat();
        table.setFormat(newID, numberformat);
        break;
    case 3:
        auto *dateformat = new DateFormat();
        table.setFormat(newID, dateformat);
        break;
    default:
        return 1;
        break;
    }
    return 0;
}

int Application::clearCell()
{
    string newID;
    std::cout << "Enter cell Identification (ID): ";
    std::getline(std::cin, newID);
    table.clearValue(newID);
    return 0;
}

void Application::appUndo(){
    try{
        table = action.undo(table);
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void Application::appRedo()
{
    try{
        action.doIt(table);
        table = action.redo();
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void Application::run() {
    bool isRunning = true;
    char userInput;
    while (isRunning){
        table.printTable();
        menuPrint();
        std::cout << "Enter input: ";
        userInput = std::getchar();
        switch (userInput) {
            case 'A': case 'a':
                action.doIt(table);
                if (addValue()) action.undoIt();
                break;
            case 'F': case 'f':
                action.doIt(table);
                try{
                    if (changeFormat()) action.undoIt();
                }
                catch (std::exception &e){
                    action.undoIt();
                    std::cout << e.what() << std::endl;
                }
                break;
            case 'X': case 'x':
                action.doIt(table);
                try{
                    clearCell();
                }
                catch (std::exception &e){
                    action.undoIt();
                    std::cout << e.what() << std::endl;
                }
                break;
            case 'U': case 'u':
                appUndo();
                break;
            case 'R': case 'r':
                appRedo();
                break;
            case 'Q': case 'q':
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

