#ifndef EXCEL_FORMULA_H
#define EXCEL_FORMULA_H

#include <stack>
#include <vector>

#include "Cell.h"

using std::vector;
using std::stack;

class Formula {
public:
    string calculateFormulaExpression(const string& expression, vector<vector<Cell>> &tableData, int decimalPlaces = 2);
private:
    static bool isOperator(char o);
    int priorityOperators(char operation);
    static float doOperation(float operand1, float operand2, char operation);
    vector<string> infixToPostfix(const vector<string> &infix);
    vector<string> createInfix(const string &expression, vector<vector<Cell>> &tableData);
    static bool isID(const string& word);
    Cell cellExists( vector<vector<Cell>> &tableData, const string& word);
};


#endif //EXCEL_FORMULA_H
