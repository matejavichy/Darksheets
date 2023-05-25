#include "Cell.h"

void Cell::setFormat(Format *newFormat) {
    if (!newFormat->isMyFormat(value) && !value.empty()){
        throw CellDoesNotSupportFormatError();
    }
    else this->format = newFormat;
}

void Cell::setValue(const string &newValue) {
    if (format->isMyFormat(newValue)){
        value = newValue;
    }
    else throw FormatNotSupportedError();
}

bool Cell::isNumberFormat() const{
    try{
        NumberFormat numberFormat;
        Format* testingFormat = &numberFormat;
        if (!testingFormat->isMyFormat(value)){
            throw CellDoesNotSupportFormatError();
        }
        return true;
    }
    catch(std::exception &e){
        return false;
    }
}

bool Cell::isDateFormat() const{
    try{
        DateFormat dateFormat;
        Format* testingFormat = &dateFormat;
        if (!testingFormat->isMyFormat(value)){
            throw CellDoesNotSupportFormatError();
        }
        return true;
    }
    catch(std::exception &e){
        return false;
    }
}

void Cell::changeDecimalPlaces(int newDecimalPlace) {
    if (isNumberFormat()){
        NumberFormat * myFormat = (NumberFormat*)format;
        myFormat->changeDecimalPlaces(newDecimalPlace);
    }
    else throw FormatNotCorrectError();
}

string Cell::getValueWithDecimalPlace() const {
    NumberFormat * myFormat = (NumberFormat*)format;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(myFormat->getDecimalPlaces()) << getValue();
    string result = stream.str();
    return result;
}

string Cell::getFormat() const {
    if (format->getFormatID() == 1) return "Text";
    else if (format->getFormatID() == 2) return "Number";
    else return "Date";
}

void Cell::setFormatJSON(const string &formatName) {
    if (formatName == "Number"){
        NumberFormat *numberformat = new NumberFormat();
        this->format = numberformat;
    }
    else if (formatName == "Date"){
        DateFormat *dateformat = new DateFormat();
        this->format = dateformat;
    }
    else return;
}

