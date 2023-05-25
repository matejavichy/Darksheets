#ifndef EXCEL_FORMAT_H
#define EXCEL_FORMAT_H

#include <regex>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using std::string;
using std::ostream;

class Format {
public:
    virtual bool isMyFormat(const string &value) const = 0;
    virtual int getFormatID() const = 0;
};

#endif //EXCEL_FORMAT_H
