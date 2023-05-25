#include "Formula.h"

bool Formula::isOperator(const char o) {
    return (o == '+' || o == '-' || o == '*' || o == '/');
}

bool Formula::isID(const string &word) {
    static const std::regex IDRegex("[A-Z][0-9]+");
    return std::regex_match(word, IDRegex);
}

int Formula::priorityOperators(const char operation) {
    switch(operation){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

vector<string> Formula::createInfix(const string &expression, vector<vector<Cell>> &tableData) {
    vector<string>infix;
    std::istringstream iss(expression);
    string word;
    while (std::getline(iss, word, ' ')) { //iterates through columns
        if (isID(word)) {
            try{
                Cell myCell = cellExists(tableData, word);
                if (myCell.isNumberFormat()){
                    infix.push_back(myCell.getValue());
                }
                else throw FormulaExecutionError();
            }
            catch (std::exception &e){
                infix.clear();
                infix.emplace_back("ERROR");
                return infix;
            }
        }
        else infix.push_back(word);
    }
    return infix;
}

string Formula::calculateFormulaExpression(const string &expression, vector<vector<Cell>> &tableData, int decimalPlaces) {
    string withoutEqualsSign = expression.substr(1);
    vector<string> infix = createInfix(withoutEqualsSign,tableData);
    if (infix[0] == "ERROR") return "ERROR";
    vector<string> postfix = infixToPostfix(infix);
    std::stack<float> stack;

    for (string c : postfix) {
        if (!isOperator(c[0])){
            stack.push(stof(c));
        }
        else {
            float operand2 = stack.top();
            stack.pop();
            float operand1 = stack.top();
            stack.pop();
            float result = doOperation(operand1, operand2, c[0]);
            stack.push(result);
        }
    }

    if (!stack.empty()) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(decimalPlaces) << stack.top();
        string result = stream.str();
        return result;
    }
    return "ERROR";
}

Cell Formula::cellExists(vector<vector<Cell>> &tableData, const string &ID){
    string stringToInt;
    for (int i = 1; i < ID.length(); i++) {
        stringToInt += ID[i];
    }
    for(const auto& cell : tableData[stoi(stringToInt) - 1]){
        if (cell.getID() == ID) return cell;
    }
    throw CellDoesNotExistError();
}

vector<string> Formula::infixToPostfix(const vector<string> &infix) {
    vector<string> postfix;
    stack<string> stack;
    for (string word : infix) {
        if (!isOperator(word[0]) && word[0] != '(' && word[0] != ')')
            postfix.push_back(word);
        else if (word[0] == '(')
            stack.emplace("(");
        else if (word[0] == ')') {
            while (!stack.empty() && stack.top() != "(") {
                postfix.push_back(stack.top());
                stack.pop();
            }
            if (!stack.empty() && stack.top() == "(")
                stack.pop();
        }
        else if (isOperator(word[0])) {
            while (!stack.empty() && isOperator(stack.top()[0]) && priorityOperators(stack.top()[0]) >= priorityOperators(word[0])) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(word);
        }
    }
    while (!stack.empty()) {
        postfix.push_back(stack.top());
        stack.pop();
    }
    return postfix;
}

float Formula::doOperation(float operand1, float operand2, char operation) {
    switch(operation){
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            throw;
    }
}
