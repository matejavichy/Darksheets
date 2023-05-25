#ifndef EXCEL_APPLICATION_H
#define EXCEL_APPLICATION_H

#include <iostream>
#include "Table.h"
#include "Action.h"

class Application {
public:
    void run();
    void load();
private:

    void menuPrint();
    Table table;
    Action action;
};


#endif //EXCEL_APPLICATION_H
