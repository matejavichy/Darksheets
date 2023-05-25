//
// Created by Mateja on 12-May-23.
//

#include "DateFormat.h"

bool DateFormat::isMyFormat(const string &value) const {
    std::regex datePattern(R"(\d{2}\.\d{2}\.\d{4})");
    return std::regex_match(value, datePattern);
}
