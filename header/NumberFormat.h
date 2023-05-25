#ifndef EXCEL_NUMBERFORMAT_H
#define EXCEL_NUMBERFORMAT_H

#include "Format.h"

class NumberFormat : public Format {
public:
    bool isMyFormat(const string &value) const override;
    void changeDecimalPlaces(int newDecimalPlace) {decimalPlaces = newDecimalPlace;}
    int getDecimalPlaces() const {return decimalPlaces;}
    int getFormatID() const override {return 2;}
private:
    int decimalPlaces = 2;
};


#endif //EXCEL_NUMBERFORMAT_H
