#ifndef EXCEL_TEXTFORMAT_H
#define EXCEL_TEXTFORMAT_H

#include "Format.h"


class TextFormat : public Format{
    bool isMyFormat(const string &value) const override;
    int getFormatID() const override {return 1;}
};


#endif //EXCEL_TEXTFORMAT_H
