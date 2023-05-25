#ifndef EXCEL_CELL_H
#define EXCEL_CELL_H

#include <iostream>

#include "Format.h"
#include "TextFormat.h"
#include "DateFormat.h"
#include "NumberFormat.h"
#include "Errors.h"

class Cell {
private:
    Format* format;
    string value;
    string cellID;
    bool genericFormat;
public:
    explicit Cell(const string &myID, const string &myValue = ""){
        this->cellID = myID;
        TextFormat* textFormat = new TextFormat();
        this->format = textFormat;
        this->value = myValue;
        genericFormat = true;
    }
    void setFormat(Format* newFormat);
    void setFormatJSON(const string& formatName);
    void setValue(const string& newValue);
    string getValue() const {return value; }
    string getID() const{ return cellID;}
    string getFormat() const;
    bool isFormula() const {return value[0] == '=';}
    bool isNumberFormat() const;
    bool isDateFormat() const;
    void changeDecimalPlaces(int newDecimalPlace);
    string getValueWithDecimalPlace() const;
};


#endif //EXCEL_CELL_H
