#include "Action.h"

void Action::doIt(Table table) {
    goBack.push(table);
}

Table Action::undo(Table table) {
    if (goBack.empty()) throw ActionStackEmptyError();
    Table oldTable = goBack.top();
    goForward.push(table);
    goBack.pop();
    return oldTable;
}
Table Action::redo() {
    if (goForward.empty()) throw ActionStackEmptyError();
    Table oldTable = goForward.top();
    goForward.pop();
    return oldTable;
}

void Action::undoIt() {
    goBack.pop();
}
