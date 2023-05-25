#ifndef EXCEL_DATEFORMAT_H
#define EXCEL_DATEFORMAT_H

#include "Format.h"

class DateFormat : public Format{
public:
    bool isMyFormat(const string &value) const override;
    int getFormatID() const override {return 3;}
};


#endif //EXCEL_DATEFORMAT_H
