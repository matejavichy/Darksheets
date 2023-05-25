//
// Created by Mateja on 12-May-23.
//

#include "NumberFormat.h"

bool NumberFormat::isMyFormat(const string &value) const {
    std::regex numberPattern(R"(-?[0-9]+(\.[0-9]+)?)");
    return std::regex_match(value, numberPattern);
}


