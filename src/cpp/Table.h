#ifndef EXCEL_TABLE_H
#define EXCEL_TABLE_H

#define ERROR_COLOR "\033[31m"
#define RESET_COLOR "\033[0m"


#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include <unordered_map>
#include <string>

#include "Formula.h"
#include "Errors.h"
#include "Cell.h"

// for readability but without fear of name clashes
using std::vector;
using std::string;
using std::unordered_map;

class Table {
private:
    vector<vector<Cell>> tableData;
    unordered_map<string, size_t> cellSizesMap;
    unordered_map<char, size_t> maxCellSizesMap;
public:
    void loadTableCSV(const string &fileName);
    void loadTableJSON(const string &fileName);
    void printTable();
    int addValue(const string &newID, const string &newValue);
    void clearValue(const string &ID);
    string getValue(Cell &myCell);
    void saveTableDataToJson(const string& filename);
    void saveTableDataToCSV(const string &filename);
    void setFormat(const string &ID, Format *format);
private:
    void updateMaxCellSizesMap();
    void updateCellSizesMap();
    int findLastColumn() const;
    int getMaxWidthFromLetter(char letter) const;
    string getPrintValue(char letter,int row);
};


#endif //EXCEL_TABLE_H
