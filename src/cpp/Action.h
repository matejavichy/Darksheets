#ifndef EXCEL_ACTION_H
#define EXCEL_ACTION_H

#include "Table.h"
#include <stack>

using std::stack;

class Action {
public:
    Table redo();
    Table undo(Table table);
    void doIt(Table table);
    void undoIt();
private:
    stack<Table> goBack;
    stack<Table> goForward;
};


#endif //EXCEL_ACTION_H
