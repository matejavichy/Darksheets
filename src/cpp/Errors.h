#ifndef EXCEL_ERRORS_H
#define EXCEL_ERRORS_H

#include "iostream"

class FileNotExistsError : public std::exception{
public:
    explicit FileNotExistsError(const std::string &file) : message_("The file: " + file + " could not be found. Try again."){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};

class FormatNotSupportedError : public std::exception{
public:
    FormatNotSupportedError() : message_("The value could not be changed due to the cells format.\nPlease change the format first!"){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};

class CellDoesNotSupportFormatError : public std::exception{
public:
    CellDoesNotSupportFormatError() : message_("The format could not be changed due to the cells value.\n"
                                               "Please set the format to Text then change the value into the desired format!"){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};

class FormulaExecutionError : public std::exception{
public:
    FormulaExecutionError() : message_("ERROR"){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};

class CellDoesNotExistError : public std::exception{
public:
    CellDoesNotExistError() : message_("The target cell does not exist."){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};

class ActionStackEmptyError : public std::exception{
public:
    ActionStackEmptyError() : message_("Nothing to undo/redo."){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};

class FormatNotCorrectError : public std::exception{
public:
    FormatNotCorrectError() : message_("The format is not correct."){}

    const char* what() const noexcept override{return message_.c_str();}

private:
    std::string message_;
};



#endif //EXCEL_ERRORS_H
