#ifndef EXCEL_APPLICATION_H
#define EXCEL_APPLICATION_H

#include <iostream>
#include "Table.h"
#include "Action.h"

class Application {
public:
    void run();
    void load();
    void appUndo();
    void appRedo();
    int addValue();
    int changeFormat();
    int clearCell();
private:

    void menuPrint();
    Table table;
    Action action;
};


#endif //EXCEL_APPLICATION_H
