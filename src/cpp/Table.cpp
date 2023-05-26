#include "Table.h"

void Table::loadTableCSV(const string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) throw FileNotExistsError(fileName);
    int numberID = 0;
    char charID;
    string line;
    while (std::getline(file, line)) { //iterates through rows
        numberID++;
        charID = 65;
        auto* row = new vector<Cell>();
        std::istringstream iss(line);
        string word;
        while (std::getline(iss, word, ',')) { //iterates through columns
            std::stringstream myID;
            myID << charID << numberID;
            Cell cell(myID.str(),word);
            row->push_back(cell);
            charID++;
        }
        tableData.push_back(*row);
    }
    file.close();
    updateCellSizesMap();
    updateMaxCellSizesMap();
}

void Table::loadTableJSON(const string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) throw FileNotExistsError(fileName);
    string line;
    int position = -1;
    while (std::getline(file, line)){
        if (line.find("row") != string::npos) {
            std::getline(file, line);
            auto* newArray = new vector<Cell>();
            tableData.push_back(*newArray);
            position++;
        }
        std::istringstream iss(line);
        string word;
        std::getline(iss,word,',');
        if (word == "") {
            std::getline(iss,word,',');
            word = word.substr(1, word.length());
        }
        else if (word == "]}")break;
        string cellID = word.substr(12, word.length() - 13);
        Cell newCell(cellID);
        tableData[position].push_back(newCell);

        std::getline(iss,word,',');
        string cellValue = word.substr(11, word.length() - 12);
        tableData[position].back().setValue(cellValue);

        std::getline(iss,word,',');
        string cellFormat = word.substr(12, word.length() - 14);
        tableData[position].back().setFormatJSON(cellFormat);
    }
     updateCellSizesMap();
    updateMaxCellSizesMap();
}

void Table::printTable() {
    if (tableData.empty())
        return;

    int numCols = findLastColumn();
    const int numRows = static_cast<int>(tableData.size());

    // Print the column headers
    std::cout << std::setw(4) << "     | ";
    for (int col = 0; col < numCols; col++) {
        char letter = static_cast<char>('A' + col);
        int width = getMaxWidthFromLetter(letter);
        std::cout << std::setw(width) << std::left << letter << " | ";
    }
    std::cout << std::endl;
    std::cout << std::setw(4) << "-----|-";
    for (int col = 0; col < numCols; col++) {
        char letter = static_cast<char>('A' + col);
        int width = getMaxWidthFromLetter(letter);
        std::cout << std::setw(width) << std::left <<  std::setfill('-') << std::setw(width) << "" << "-|-";
    }
    std::cout << std::endl << std::setfill(' ');


    for (int row = 0; row < numRows; row++) {
        std::cout << std::setw(4) << row + 1 << " | ";  // Print row number
        for (int col = 0; col < numCols; col++) {
            char letter = static_cast<char>('A' + col);
            int width = getMaxWidthFromLetter(letter);
            string printThisValue = getPrintValue(letter, row);
            if (printThisValue == "ERROR"){
                std::cout << ERROR_COLOR << std::setw(width) << std::left << printThisValue << RESET_COLOR << " | ";
            }
            else std::cout << std::setw(width) << std::left << printThisValue << " | ";
        }
        std::cout << std::endl;
    }
}

void Table::updateMaxCellSizesMap() {
    for (const auto& entry : maxCellSizesMap) {
        char letter = entry.first;
        maxCellSizesMap[letter] = 0;
    }
    for (const auto& entry : cellSizesMap) {
        char letter = entry.first[0];
        size_t sizeOfCell = entry.second;

        // Update the maximum size for the letter if necessary
        if (sizeOfCell > maxCellSizesMap[letter]) {
            maxCellSizesMap[letter] = sizeOfCell;
        }
    }
}

int Table::findLastColumn() const {
    for (int i = 25; i >= 0; i--) {
        char letter = static_cast<char>('A' + i);
        if (maxCellSizesMap.find(letter) == maxCellSizesMap.end()) continue;
        if (maxCellSizesMap.find(letter)->second == 0) continue;
        else return i;
    }
    return 0;
}

int Table::getMaxWidthFromLetter(const char letter) const {
    int width = 0;
    auto it = maxCellSizesMap.find(letter);
    if (it != maxCellSizesMap.end()) {
        width = static_cast<int>(it->second);
    }
    return width;
}

string Table::getPrintValue(const char letter,const int row) {
    std::stringstream myID;
    myID << letter << row + 1;
    for (auto& cell : tableData[row]) {
        if (myID.str() == cell.getID()) {
            return getValue(cell);
        }
    }
    return "";
}

void Table::updateCellSizesMap() {
    const int numRows = static_cast<int>(tableData.size());
    for (int i = 0; i < numRows; i++){
        for (auto& cell : tableData[i]) {
            cellSizesMap[cell.getID()] = getValue(cell).size();
        }
    }
}

string Table::getValue(Cell &myCell)  {
    if (myCell.isFormula()){
        Formula f;
        return f.calculateFormulaExpression(myCell.getValue(),tableData);
    }
    else if (myCell.isNumberFormat()){
        return myCell.getValueWithDecimalPlace();
    }
    else return myCell.getValue();
}

int Table::addValue(const string &newID, const string &newValue) {
    string number = newID.substr(1);
    int num = stoi(number);
    while (num > tableData.size()){
        auto* newArray = new vector<Cell>;
        tableData.push_back(*newArray);
    }
    for(auto &cell : tableData[num-1]){
        if (cell.getID() == newID) {
            try{
                cell.setValue(newValue);
                cellSizesMap[newID] = getValue(cell).size();
                updateMaxCellSizesMap();
            }
            catch (std::exception &e){
                std::cout << e.what() << std::endl;
                return 1;
            }
            return 0;
        }
    }
    Cell *newCell = new Cell(newID,newValue);
    tableData[num-1].push_back(*newCell);
    return 1;
}

void Table::clearValue(const string &ID) {
    string number = ID.substr(1);
    int num = stoi(number);
    int index = 0;
    bool found = false;
    for(auto &cell : tableData[num-1]){
        if (cell.getID() == ID) {
            tableData[num-1].erase(tableData[num-1].begin() + index);
            cellSizesMap[ID] = 0;
            updateMaxCellSizesMap();
            found = true;
            break;
        }
        index++;
    }
    if (!found) throw CellDoesNotExistError();
}

void Table::setFormat(const string &ID, Format *format) {
    string number = ID.substr(1);
    int num = stoi(number);
    int index = 0;
    bool found = false;
    for(auto &cell : tableData[num-1]){
        if (cell.getID() == ID) {
            try{
                cell.setFormat(format);
            }
            catch (std::exception &e){
                throw CellDoesNotSupportFormatError();
            }
            found = true;
            break;
        }
        index++;
    }
    if (!found) throw CellDoesNotExistError();
}

void Table::saveTableDataToJson(const string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    outputFile << "{";
    const int numRows = tableData.size();
    for (int row = 0; row < numRows; ++row) {
        outputFile << "\"row" << row << "\": ";
        outputFile << "[\n";

        int col = -1;
        for (auto& cell : tableData[row]) {
            col++;
            outputFile << "{";

            outputFile << "\"cellID\": \"" << cell.getID() << "\", ";
            outputFile << "\"value\": \"" << cell.getValue() << "\", ";
            outputFile << "\"format\": \"" << cell.getFormat() << "\"";
            outputFile << "}\n";
            if (col != tableData[row].size() - 1) {
                outputFile << ", ";
            }
        }
        outputFile << "]";
        if (row != tableData.size() - 1) {
            outputFile << ", ";
        }
    }

    outputFile << "}";

    outputFile.close();
}

void Table::saveTableDataToCSV(const string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    const int numRows = tableData.size();
    // Write rows
    for (int row = 0; row < numRows; ++row) {

        int col = -1;
        char currentColumn = 65;
        // Write cells
        for (auto& cell : tableData[row]) {
            while (cell.getID()[0] != currentColumn && currentColumn < cell.getID()[0]){
                outputFile << ",";
                currentColumn++;
            }
            currentColumn++;
            col++;

            // Write cell properties
            outputFile << cell.getValue();
            // Add comma if not the last cell
            if (col != tableData[row].size() - 1) {
                outputFile << ",";
            }
        }
        // End row array
        outputFile << "\n";
    }
    outputFile.close();
}
