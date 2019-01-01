#ifndef OVERFLOW_ERROR_H
#define OVERFLOW_ERROR_H
#include<exception>
#include<iostream>
class overflow_error: public std::exception {
public:
    overflow_error();
    virtual const char* what() const throw();
};

#endif // OVERFLOW_ERROR_H
